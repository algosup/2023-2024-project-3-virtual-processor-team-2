#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define true 1
#define false 0

int charNumbcheck(char* filename);

int main(){
    // FILE *fp;
    // char ch;
    // int lineCount = 0;
    
    // fp = fopen("test2.aop", "r");
    // if (fp == NULL)
    // {
    //     printf("Couldn't open file\n");
    //     return 1;
    // }

    // int count = 0;

    // while (ch != EOF)
    // {
    //     do
    //     {
    //         ch = fgetc(fp);
    //         count++;
    //     } while (ch != '\n' && ch != EOF);
    //     printf("Line %d has %d characters.\n", lineCount, count);
    //     lineCount = lineCount + 1;
    //     count = 0;
    // }    
 
    // // Closing the file
    // fclose(fp);
    // printf("LineCount = %d\n", lineCount);

    char* fileName = "test3.aop";


    if (charNumbcheck(fileName)) {
        printf("\nYour file is ready to be parsed.\n");
    }
    else {
        printf("The number of characters per line shouldn't above 64 in a file.\n");
        printf("Please respect that condition.");
    }

    return 0;
}

int charNumbcheck(char* filename){
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
