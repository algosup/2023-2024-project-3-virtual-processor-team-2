#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

    char* fileName = "test2.aop";

    charNumbcheck(fileName);

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
        conditionChecked = false;
        
    }    
    printf("LineCount = %d\n", lineCount);
    // Closing the file
    fclose(fp);
    return conditionChecked;
}
