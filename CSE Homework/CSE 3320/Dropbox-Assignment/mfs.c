/* README:
 * This assignment gave us a lot of extra space. bitfields are not used but should be.
 *
 * I did a lot of input verification and asking whether to save on close and quit.
 * I dare you to segfault it with bad input.
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n" // Whitespace

#define MAX_COMMAND_SIZE 255 // The maximum command-line size
#define MAX_NUM_ARGUMENTS 10 // Can have 9 flags

#define NUM_BLOCKS 4226
#define BLOCK_SIZE 8192
#define MAX_NAME_S 33
#define NUM_INODES 125
#define MAX_FILE_B 1250
#define VERSION 69

typedef struct directory
{
  char init;
  char imageName[MAX_NAME_S];
  char version;
} Directory;

typedef struct inode
{
  time_t time;
  size_t size;

  uint blocks[MAX_FILE_B];

  char fileName[MAX_NAME_S];
  char readOnly;
  char hidden;

} Inode;

typedef struct block
{
  unsigned char data[BLOCK_SIZE];
} Block;

// all data
Block image[NUM_BLOCKS];

// utility pointers
Directory *dirInfo = (Directory *)&image[0];
unsigned char *freeIN = (char *)&(image[2].data);
unsigned char *freeBK = (char *)&(image[3].data);

#define NO_IMAGE "No active image.\n"
#define NO_FILE "No file name given.\n"
#define FILE_NF "File not found.\n"

// utility functions
int validName(char *str)
{

  if (strlen(str) > 32)
  {
    return -1;
  }

  int dots = 1;
  for (int i = strlen(str); i > 0; i--)
  {
    char c = str[i - 1];

    // if valid continue
    if (dots && c == '.')
    {
      dots--;
      continue;
    }
    else if (isalnum(c))
    {
      continue;
    }
    // if not return false
    return 0;
  }

  // if all chars are valid, return true
  return 1;
}
size_t fsize(FILE *fp)
{
  size_t size = 0;

  while (!feof(fp))
  {
    fgetc(fp);
    size++;
  }
  size--;
  // resetting fp
  fseek(fp, 0, SEEK_SET);

  return size;
}

// commands
void CMDput(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("put: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }
  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: put <filename> <newFilename>\n");
    return;
  }

  char *fileName = token[1];
  char *newFileName = fileName;
  // if new file name given
  if (token_count > 3)
  {
    newFileName = token[2];
  }

  int valid = validName(newFileName);
  // if invalid name
  if (valid == 0)
  {
    printf("Invalid file name.\n");
    return;
  }
  // if name too long
  if (valid == -1)
  {
    printf("File name too long.\n");
    return;
  }

  // searching for duplicate name
  Inode *in = NULL;
  for (int i = 0; i < NUM_INODES; i++)
  {
    Inode *in = (Inode *)&image[i + 5];

    // if in the image and matches name
    if (!freeIN[i] && !strcmp(newFileName, in->fileName))
    {
      printf("File name is already in the image.\n");
      return;
    }
  }

  FILE *fp = fopen(fileName, "rb");
  // if file is not opened
  if (!fp)
  {
    printf(FILE_NF);
    return;
  }

  size_t size = fsize(fp);
  // if file is too large
  if (size > MAX_FILE_B * BLOCK_SIZE)
  {
    printf("File is too large (%d).", MAX_FILE_B * BLOCK_SIZE);
    return;
  }

  // searching for open Inode
  in = NULL;
  int inIndex = 0;
  for (; inIndex < NUM_INODES; inIndex++)
  {
    // printf("%d", freeIN[i]); // prints inodes
    if (freeIN[inIndex])
    {
      // setting Inode
      in = (Inode *)&image[inIndex + 5];
      break;
    }
  }

  // if inode not found
  if (!in)
  {
    printf("No Inodes left.");
    return;
  }

  // counting available blocks
  int freeBlocks = 0;
  for (int i = 0; i < NUM_BLOCKS - NUM_INODES - 5; i++)
  {
    if (freeBK[i] == 1)
    {
      freeBlocks++;
    }
  }

  // if not enough free blocks
  if (freeBlocks * BLOCK_SIZE < size)
  {
    printf("Not enough disk space.");
    return;
  }

  // allocating the inode
  freeIN[inIndex] = 0;

  // copying data
  for (int i = 0; i * BLOCK_SIZE < size; i++)
  {
    // allocating next block
    for (int j = 0; j < NUM_BLOCKS - NUM_INODES - 5; j++)
    {
      if (freeBK[j] == 1)
      {
        // taking block
        in->blocks[i] = j + NUM_INODES + 5;
        freeBK[j] = 0;
        break;
      }
    }

    size_t readNum = size - i * BLOCK_SIZE;
    if (readNum > BLOCK_SIZE)
      readNum = BLOCK_SIZE;

    fread(&image[in->blocks[i]], 1, readNum, fp);
    // printf("something: (%d) at %p \n", readNum, &image[ in->blocks[i] ]);
  }

  // setting other fields
  in->time = time(0);                             // set date. Docker thinks we're british.
  in->size = size;                                // set size
  strncpy(in->fileName, newFileName, MAX_NAME_S); // set name
  in->hidden = 0;                                 // set attributes
  in->readOnly = 0;

  fclose(fp);
  printf("file put successful.\n");
}
void CMDget(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("get: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }
  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: get <filename> <newFilename>\n");
    return;
  }

  char *fileName = token[1];
  char *newFileName = fileName;
  // if new file name given
  if (token_count > 3)
  {
    newFileName = token[2];
  }

  FILE *fp = fopen(newFileName, "wb");
  if (!fp)
  {
    printf("File could not be created.\n");
    return;
  }

  // searching for matching inode
  for (int i = 0; i < NUM_INODES; i++)
  {
    Inode *in = (Inode *)&image[i + 5];

    // if in the image and matches name
    if (!freeIN[i] && !strcmp(fileName, in->fileName))
    {
      // reading blocks
      for (int j = 0; j <= in->size / BLOCK_SIZE; j++)
      {
        // number of bytes to be read
        size_t readNum = in->size - j * BLOCK_SIZE;
        if (readNum > BLOCK_SIZE)
          readNum = BLOCK_SIZE;

        fwrite(&image[in->blocks[j]], 1, readNum, fp);
        // printf("something: (%d) at %p \n", readNum, &image[ in->blocks[j] ]);
      }
      fclose(fp);

      printf("File retrieved.\n");
      return;
    }
  }

  // if no inode matched
  printf("File not found.");
}
void CMDdel(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("del: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }
  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: del <filename>\n");
    return;
  }

  int i = 0;
  for (; i < NUM_INODES; i++)
  {
    Inode *in = (Inode *)&image[i + 5];

    if (!in->readOnly)
    {
      // if it's in use and matches name
      if (!freeIN[i] && !strcmp(token[1], in->fileName))
      {
        // freeing blocks
        for (int j = 0; j <= in->size / BLOCK_SIZE; j++)
        {
          freeBK[in->blocks[j] - NUM_INODES - 5] = 1;
        }

        // freeing inode
        freeIN[i] = 1;

        printf("File deleted.\n");
        return;
      }
    }
    else
    {
      printf("File is read only.\n");
      return;
    }
  }

  // if file not found
  printf(FILE_NF);
}
void CMDundel(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("undel: ");
  fflush(stdout);

  // if no active image
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }

  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: undel <filename> <newFilename>\n");
    return;
  }

  char *fileName = token[1];
  char *newFileName = fileName;
  // if new file name given
  if (token_count > 3)
  {
    newFileName = token[2];
  }

  // if file name given
  int i = 0;
  for (; i < NUM_INODES; i++)
  {
    Inode *in = (Inode *)&image[i + 5];

    // if matches name and not active
    if (freeIN[i] && !strcmp(fileName, in->fileName))
    {
      // searching for duplicate name
      Inode *ind = NULL;
      for (int j = 0; j < NUM_INODES; j++)
      {
        Inode *ind = (Inode *)&image[j + 5];

        // if in the image and matches name
        if (!freeIN[j] && !strcmp(newFileName, ind->fileName))
        {
          printf("File name is already in the image.\n");
          return;
        }
      }

      // checking for corruption.
      for (int j = 0; j <= in->size / BLOCK_SIZE; j++)
      {
        // if currently used
        if (!freeBK[in->blocks[j] - NUM_INODES - 5])
        {
          printf("Corrupted block found. undel canceled.\n");
          return;
        }
      }

      // reallocating blocks
      for (int j = 0; j <= in->size / BLOCK_SIZE; j++)
      {
        freeBK[in->blocks[j] - NUM_INODES - 5] = 0;
      }

      // reallocating inode
      freeIN[i] = 0;
      strncpy(in->fileName, newFileName, MAX_NAME_S); // set name

      printf("File undeleted.\n");
      return;
    }
  }

  printf(FILE_NF);
}
void CMDlist(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // if not initialized
  if (!dirInfo->init)
  {
    printf("list: ");
    printf(NO_IMAGE);
    return;
  }

  char none = 1;
  for (int i = 0; i < NUM_INODES; i++)
  {
    // if being used
    if (!freeIN[i])
    {
      Inode *in = (Inode *)&image[i + 5];

      char *strTime = ctime(&(in->time));
      // string formatting for date
      strTime[strlen(strTime) - 9] = 0; // setting new end
      strTime += 4;                     // setting new start

      // if not hiden
      if (!in->hidden)
      {
        none = 0;
        printf("%-9llu %s %s ", in->size, strTime, in->fileName);
        printf("%s\n", in->readOnly ? "(r)" : "");
      }
    }
  }

  if (none)
  {
    printf("list: No files found.\n");
  }
}
void CMDdf(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("df: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }

  // calculating free bytes
  size_t dataBlocks = NUM_BLOCKS - NUM_INODES - 5;
  size_t total = dataBlocks * BLOCK_SIZE;
  for (int i = 0; i < NUM_INODES; i++)
  {
    // if being used
    if (!freeIN[i])
    {
      Inode *in = (Inode *)&image[i + 5];
      total -= in->size;
    }
  }
  printf("%d bytes free.\n", total);
}
void CMDopen(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("open: ");
  fflush(stdout);

  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: open <filename>\n");
    return;
  }

  FILE *fp = fopen(token[1], "rb");
  // if file not opened
  if (!fp)
  {
    printf("File not found.\n");
    return;
  }

  // reading data
  fread(image, BLOCK_SIZE, NUM_BLOCKS, fp);

  // if not a older version
  if (dirInfo->version != VERSION)
  {
    dirInfo->init = 0;
    printf("Invalid file data or old version.\n");

    return;
  }
  fclose(fp);
  printf("File opened.\n");
}
void CMDclose(char *token[MAX_NUM_ARGUMENTS], int token_count)
{

  // initial print
  printf("close: ");
  fflush(stdout);

  // if open image
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }

  // ask whether we should save
  if (dirInfo->init)
  {
    printf("Save active image? (y/n): ");

    char str[MAX_COMMAND_SIZE];
    while (1)
    {
      fgets(str, MAX_COMMAND_SIZE, stdin);
      str[strlen(str) - 1] = 0; // removing \n

      if (!strcasecmp(str, "y"))
      {
        // saving
        FILE *fp = fopen(dirInfo->imageName, "wb");
        fwrite(image, BLOCK_SIZE, NUM_BLOCKS, fp);
        fclose(fp);
        printf("close: File system saved.\n");

        break;
      }
      else if (!strcasecmp(str, "n"))
      {
        break;
      }
      else
      {
        printf("Invalid input, try again: ");
      }
    }

    printf("close: ");
  }

  // set init to false
  dirInfo->init = 0;
  printf("File system closed.\n");
}
void CMDcreatefs(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("createfs: ");
  fflush(stdout);

  // if file name not given
  if (!(token_count > 2))
  {
    printf("\rusage: createfs <filename>\n");
    return;
  }
  // if there is already an active image
  if (dirInfo->init)
  {
    printf("Active image detected.\n");

    // saving
    FILE *fp = fopen(dirInfo->imageName, "wb");
    fwrite(image, BLOCK_SIZE, NUM_BLOCKS, fp);
    fclose(fp);
    printf("createfs: File system saved.\n");

    printf("createfs: ");
  }

  int valid = validName(token[1]);
  // if invalid name
  if (valid == 0)
  {
    printf("Invalid file name.\n");
    return;
  }
  // if name too long
  if (valid == -1)
  {
    printf("File name too long.\n");
    return;
  }

  // if overide
  FILE *fp = fopen(token[1], "rb");
  if (fp)
  {
    printf("Image with same name found. Overwrite? (y/n): ");

    char str[MAX_COMMAND_SIZE];
    while (1)
    {
      fgets(str, MAX_COMMAND_SIZE, stdin);
      str[strlen(str) - 1] = 0; // removing \n

      if (!strcasecmp(str, "y"))
      {
        break;
      }
      else if (!strcasecmp(str, "n"))
      {
        return;
      }
      else
      {
        printf("Invalid input, try again: ");
      }
    }

    printf("createfs: ");
    fclose(fp);
  }

  // setting image name
  strncpy(dirInfo->imageName, token[1], MAX_NAME_S);

  // initilizing fields
  for (int i = 0; i < NUM_INODES; i++)
  {
    // initilizing free inode map
    freeIN[i] = 1;

    // set empty name
    Inode *in = (Inode *)&image[i + 5];
    strncpy(in->fileName, "", MAX_NAME_S);
  }
  for (int i = 0; i < NUM_BLOCKS - NUM_INODES - 5; i++)
  {
    // initilizing free block map
    freeBK[i] = 1;
  }

  // final setup
  dirInfo->init = 1;
  dirInfo->version = VERSION;
  // saving to file
  fp = fopen(dirInfo->imageName, "wb");
  fwrite(image, BLOCK_SIZE, NUM_BLOCKS, fp);
  fclose(fp);

  printf("File system created and saved.\n");
}
void CMDsavefs(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("savefs: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }

  // if file could not be opened
  FILE *fp = fopen(dirInfo->imageName, "wb");
  if (!fp)
  {
    printf("Image could not be saved.\n");
    return;
  }

  // writing the data
  fwrite(image, BLOCK_SIZE, NUM_BLOCKS, fp);
  fclose(fp);

  printf("File system saved.\n");
}
void CMDattrib(char *token[MAX_NUM_ARGUMENTS], int token_count)
{
  // initial print
  printf("attrib: ");
  fflush(stdout);

  // if not initialized
  if (!dirInfo->init)
  {
    printf(NO_IMAGE);
    return;
  }
  // if file name not given
  if (token_count == 3)
  {
    printf("No attributes given\n");
    return;
  }
  if (!(token_count > 3))
  {
    printf("\rusage: attrib <+hr> <-hr> <filename>\n");
    return;
  }

  // variable helper
  char *fileName = token[token_count - 2];
  if (!fileName) // the tokenizer is messed up
    fileName = "";

  // searching for matching inode
  int i = 0;
  Inode *in = NULL;
  for (; i < NUM_INODES; i++)
  {
    in = (Inode *)&image[i + 5];
    // if in the file system and name matches
    if (!freeIN[i] && !strcmp(fileName, in->fileName))
    {

      break;
    }
  }

  // no inode matched
  if (i == NUM_INODES)
  {
    printf("File not found.\n");
    return;
  }

  // attribute handling
  for (int i = 1; i < token_count - 2; i++)
  {
    char *attrib = token[i];

    char r = strstr(attrib, "r") ? 1 : 0;
    char h = strstr(attrib, "h") ? 1 : 0;

    if (strstr(attrib, "+"))
    {
      if (r)
        in->readOnly = 1;
      if (h)
        in->hidden = 1;
    }
    else if (strstr(attrib, "-"))
    {
      if (r)
        in->readOnly = 0;
      if (h)
        in->hidden = 0;
    }
    else
    {
      // do nothing?
    }
  }
  printf("Attributes changed.\n");
}

int main(int argc, char *argv[])
{
  // no image on startup
  dirInfo->init = 0;

  char *command_string = (char *)malloc(MAX_COMMAND_SIZE);
  while (1)
  {
    // Print out the msh prompt
    printf("mfs> ");

    // get input
    while (!fgets(command_string, MAX_COMMAND_SIZE, stdin))
      ;

    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];
    int token_count = 0;

    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;
    char *working_string = strdup(command_string);

    // keeping track of the original pointer
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while (((argument_ptr = strsep(&working_string, WHITESPACE)) != NULL) &&
           (token_count < MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
      if (strlen(token[token_count]) == 0)
      {
        token[token_count] = NULL;
      }
      token_count++;
    }
    //************************************************************************|

    char *command = token[0];
    if (command == NULL) {} // done
    else if (!strcmp(command, "quit")) // done
    {
      if (dirInfo->init)
      {
        printf("quit: Save active image? (y/n): ");

        char str[MAX_COMMAND_SIZE];
        while (1)
        {
          fgets(str, MAX_COMMAND_SIZE, stdin);
          str[strlen(str) - 1] = 0; // removing \n

          if (!strcasecmp(str, "y"))
          {
            // saving
            FILE *fp = fopen(dirInfo->imageName, "wb");
            fwrite(image, BLOCK_SIZE, NUM_BLOCKS, fp);
            fclose(fp);

            printf("quit: File system saved.\n");

            return 0;
          }
          else if (!strcasecmp(str, "n"))
          {
            return 0;
          }
          else
          {
            printf("Invalid input, try again: ");
          }
        }

        printf("quit: ");
      }

      return 0;
    }
    else if (!strcmp(command, "put")) // done
    {
      CMDput(token, token_count);
    }
    else if (!strcmp(command, "get")) // done
    {
      CMDget(token, token_count);
    }
    else if (!strcmp(command, "del")) // done
    {
      CMDdel(token, token_count);
    }
    else if (!strcmp(command, "undel")) // done
    {
      CMDundel(token, token_count);
    }
    else if (!strcmp(command, "list")) // done
    {
      CMDlist(token, token_count);
    }
    else if (!strcmp(command, "df")) // done
    {
      CMDdf(token, token_count);
    }
    else if (!strcmp(command, "open")) // done
    {
      CMDopen(token, token_count);
    }
    else if (!strcmp(command, "close")) // done
    {
      CMDclose(token, token_count);
    }
    else if (!strcmp(command, "createfs")) // done
    {
      CMDcreatefs(token, token_count);
    }
    else if (!strcmp(command, "savefs")) // done
    {
      CMDsavefs(token, token_count);
    }
    else if (!strcmp(command, "attrib")) // done
    {
      CMDattrib(token, token_count);
    }
    else // done
    {
      printf("Command not reconized.\n");
    }

    free(head_ptr);
  }
  return 0;
}
