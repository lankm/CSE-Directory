#include <string.h>
#include <stdlib.h>
#include "list_products.h"

#define STR_BUFF 128

void print_data(fnct_ptr function, FILE *file){
    printf("ID    NAME                               PRICE     QTY\n");
    printf("------------------------------------------------------\n");


    data product = function(file);
    while(product.Quantity!=-1) {
        printf("%-6d%-35s$%-9.2f%3d\n",product.ID,product.Name,product.Price,product.Quantity);
    
        product = function(file);
    }
}

data read_CSV_line(FILE *file){ 
    data product;

    if(feof(file)) {    //using quantity=-1 as a end statement. probably a better way to signify the last product though. can't have less than nothing .
        product.Quantity=-1;
        return product;
    }
    
    char line[STR_BUFF];
    fgets(line, STR_BUFF, file);

    product.ID=atoi(strtok(line,","));
    strcpy(product.Name, strtok(NULL,","));
    product.Price=atof(strtok(NULL,","));
    product.Quantity=atoi(strtok(NULL,","));

    
    return product;
}
data read_BIN_line(FILE *file){
    data product;

    fread(&product,152,1,file); //no idea why its 152. Probably struct padding. Should have told us that in the assignment. 4+128+8+4=144.

    if(feof(file)) {    //using quantity=-1 as a end statement. Only reaches eof if the eof bit is read. this means this if statement needs to be after fread when its reading nothing.
        product.Quantity=-1;
        return product;
    }
    
    return product;
}

int main(int argc, const char **argv) {
    if (argc!=2) {
        printf("USAGE: ./a.out FILENAME");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");  //opens file and exits if not found.
    if(file==NULL) {
        printf("\"%s\" could not be found. Exiting program.", argv[1]);
        return 1;
    }

    char *index=strchr(argv[1], '.');
    char fileType[5];
    strncpy(fileType, index, 5);  //just to check if its .csv


    fnct_ptr type;  //determines the file type and makes a pointer to a funtion to read a line of the file.
    if(!strcmp(fileType,".csv"))    //if csv
        type=*read_CSV_line;
    else {  //if its binary data
        type=*read_BIN_line;

        char str[5];
        fread(str,1,4,file);
        str[5]=0;

        if(strcmp(str,"CSEP")) {    //if the first 4 
            printf("Invalid data. \"CSEP\" not read at beginning of file.");
            fclose(file);
            return 1;
        }   
    }


    print_data(type, file);

    fclose(file);
    return 0;
}
