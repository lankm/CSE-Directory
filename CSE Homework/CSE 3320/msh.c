/*

  Name: Landon Moon
  ID:   1001906270

*/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n" // Whitespace used for tokenization

#define MAX_COMMAND_SIZE 255       // The maximum command-line size
#define MAX_NUM_ARGUMENTS 10       // Mav shell supports 10 arguments
#define MAX_NUM_PID_HISTORY 20     // Max listpids display length is 20
#define MAX_NUM_COMMAND_HISTORY 15 // Max history display length is 15

/* push a given 'pid' into a circular array 'pids' */
void pushPid(int pids[], int pid, int* start)
{
  //finding correct index
  *start += 1;
  if (*start > MAX_NUM_PID_HISTORY)
    *start = 0;

  //setting value
  pids[*start] = pid;

  //finding next correct index
  int end_set = (*start) + 1;
  if (end_set > MAX_NUM_PID_HISTORY)
    end_set = 0;

  pids[end_set] = -1; // setting the next value to -1 so it knows where to stop
}
/* push a given 'cmd' into a circular array 'history' */
void pushCmd(char *history[], char *cmd, int* start)
{
  *start += 1;
  if (*start > MAX_NUM_COMMAND_HISTORY) //if looped over
    *start = 0;

  /* setting value */
  free(history[*start]);
  history[*start] = malloc(sizeof(char) * strlen(cmd));
  strcpy(history[*start], cmd);

  /* setting the ending null character to know where to stop */
  int end_set = (*start) + 1;
  if (end_set > MAX_NUM_COMMAND_HISTORY)
    end_set = 0;
  free(history[end_set]);
  history[end_set] = NULL;
  }

int main()
{
  /* circular arrays for history and listpids */
  int pid_history[] = {[0 ... MAX_NUM_PID_HISTORY] = -1};
  int pid_history_start = 0;
  char *command_history[] = {[0 ... MAX_NUM_COMMAND_HISTORY] = NULL};
  int command_history_start = 0;
  
  char *command_string = (char *)malloc(MAX_COMMAND_SIZE);
  int rerun = 0;  //if !# was input

  while (1)
  {
    /* Print out the msh prompt */
    printf("msh> ");

    
    if (rerun) // if !# was input. continues with preset command_string
    {
      printf("%s\n", command_string);
    }
    else
    {
      while (!fgets(command_string, MAX_COMMAND_SIZE, stdin));  //input from user
      command_string[strlen(command_string) - 1] = 0; // delete extra /n for input commands
    }

    /* Parse input */
    char *token[] = {[0 ... MAX_NUM_ARGUMENTS] = NULL}; //init to null
    int token_count = 0;

    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;
    char *working_string = strdup(command_string);

    // we are going to move the working_string pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *head_ptr = working_string;

    // Tokenize the input strings with whitespace used as the delimiter
    while (((argument_ptr = strsep(&working_string, WHITESPACE)) != NULL) &&
           (token_count < MAX_NUM_ARGUMENTS + 1))
    {
      token[token_count] = strndup(argument_ptr, MAX_COMMAND_SIZE);
      if (strlen(token[token_count]) == 0)
      {
        token[token_count] = NULL;
      }
      token_count++;
    }

    char *command = token[0];
    if (command == NULL); // empty command
    else if (command[0] == '!') // command selection
    {
      if (strlen(command)==1)
      {
        printf("No number given.\n\n");
        continue;
      }
      int num = atoi(command+1); //convert to useable value


      if (num >= MAX_NUM_COMMAND_HISTORY) // if out of bounds
      {
        printf("Command not in history.\n\n");
      }
      else
      {
        // find actual index
        int index = command_history_start - num;
        if (index < 0)
          index += MAX_NUM_COMMAND_HISTORY+1;

        //if within array scope but not changed yet.
        if(command_history[index]==NULL)
        {
          printf("Command not in history.\n\n");
        }
        else
        {
          // setup for next loop
          rerun = 1; 
          strcpy(command_string, command_history[index]);
          continue;
        }
      }
    }
    else if (strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0) // exit
    {
      //freeing command history list
      for (int i = command_history_start, j = 0;; i--, j++)
      {
        if (i < 0)
          i = MAX_NUM_COMMAND_HISTORY;
        if (command_history[i] == NULL) // order of operations within for loops are wonky
          break;

        free(command_history[i]);
      }
      
      free(head_ptr);

      exit(0);
    }
    else if (strcmp(command, "history") == 0) // history
    {
      /* adding command to history */
      pushCmd(command_history, command_string, &command_history_start);

      /* display history */
      for (int i = command_history_start, j = 0;; i--, j++)
      {
        if (i < 0)  // if looped over
          i = MAX_NUM_COMMAND_HISTORY;
        if (command_history[i] == NULL) // if at end of list
          break;

        printf("%d: %s\n", j, command_history[i]);
      }
      printf("\n");
    }
    else if (strcmp(command, "listpids") == 0) // listpids
    {
      // adding command to history
      pushCmd(command_history, command_string, &command_history_start);

      for (int i = pid_history_start, j = 0;; i--, j++)
      {
        if (i == -1)
          i = MAX_NUM_PID_HISTORY;
        if (pid_history[i] == -1)
          break;

        printf("%d: %d \n", j, pid_history[i]);
      }
      printf("\n");
    }
    else if (strcmp(command, "cd") == 0) // cd
    {
      if (token_count >= 2) // if a path is given
      {
        int status = chdir(token[1]);
        if(!status) { // if directory is found
          /* adding command to history */
          pushCmd(command_history, command_string, &command_history_start);
        }
        else {
          printf("No such file or directory\n");
        }
        printf("\n");

      }
      else
      {
        printf("No path given\n\n");
      }
    }
    else // everything else
    {
      int pid = fork();
      if (pid == 0)
      {
        char str_buff[MAX_COMMAND_SIZE];

        //this can all be in a execvp command. This just manually checks each.
        strcpy(str_buff,"./");
        execv(strcat(str_buff, command), token);
        strcpy(str_buff,"/usr/local/bin/");
        execv(strcat(str_buff, command), token);
        strcpy(str_buff,"/usr/bin/");
        execv(strcat(str_buff, command), token);
        strcpy(str_buff,"/bin/");
        execv(strcat(str_buff, command), token);

        printf("%s: Command not found.\n", command);
        exit(1);
      }
      if (pid > 0)
      {
        /* add pid to pid list */
        pushPid(pid_history, pid, &pid_history_start);

        int status;
        wait(&status);  //wait for child to finish
        printf("\n");

        /* if the command was valid */
        if (!status)
        {
          pushCmd(command_history, command_string, &command_history_start);
        }
      }
    }

    free(head_ptr);
    rerun = 0;  //reset rerun so the user can input
  }
  
  return 0;
}
