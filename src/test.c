#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool charNumbcheck(char* filename);

int main(){

    char* fileName = "test2.aop";

    if (charNumbcheck(fileName)) {
        printf("\nYour file is ready to be parsed.\n");
    }
    else {
        printf("The number of characters per line shouldn't above 64 in a file.\n");
        printf("Please respect that condition.");
    }
    return 0;
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
        printf("Line %d has %d characters.\n", lineCount, count);
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
    printf("LineCount = %d\n", lineCount);
    // Closing the file
    fclose(fp);
    return conditionChecked;
}
