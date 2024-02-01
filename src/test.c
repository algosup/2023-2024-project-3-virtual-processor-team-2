#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

bool charNumbcheck(char* filename);
bool checkLineSizes(char* filename);

int main(){

    char* fileName = "test2.aop";
    if(checkLineSizes(fileName)) {
        printf("File have valid lines\n");
    }
    else{
        fprintf(stderr,"Lines shouldn't be above 64 in a file.\nPlease enter a valid file.\n");
        exit(EXIT_FAILURE); //Exit the program when the condition isn't met.
    }
    return 0;    
}

bool checkLineSizes(char* fileName){
    FILE *fp;
    fp=fopen(fileName,"r");
    bool conditionChecked;
    char string[64];// The maximum length a line should have
    while(fgets(string, 64, fp) != NULL) {    //Reading the file, line by line
        if (strchr(string, '\n') != NULL)
        {// the line contains an '\n'
            continue;
        }
        else if (fgets(string, 64, fp) == NULL)
        {// It's the last line at the end of the file
            conditionChecked = true;
        }
        else
        { // Throws an error when the characters limit isn't respected
            conditionChecked = false;
            break;
        }
    }
    return conditionChecked;
}

bool charNumbcheck(char* filename){
    FILE *fp;
    char ch;
    int lineCount = 0;
    bool conditionChecked;
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Couldn't open file\n");
        exit(0);
    }
    int count = 0;

    while (ch != EOF)
    {
        do
        {
            ch = fgetc(fp);
            count++; 
        } while (ch != '\n' && ch != EOF);
        if (count <= 64)
        {
            conditionChecked = true;
            lineCount = lineCount + 1;
            count = 0;
        }
        else
        {
            conditionChecked = false;
            break;
        }
        
    }    
    // Closing the file
    fclose(fp);
    return conditionChecked;
}
