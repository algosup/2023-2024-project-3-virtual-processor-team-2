#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    FILE *fp;
    char ch;
    int count;
    int lineCount = 0;
    
    fp = fopen("test2.aop", "r");
    if (fp == NULL)
    {
        printf("Couldn't open file\n");
        return 1;
    }

    // Extract characters from file and store in character c
    for (char c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            lineCount = lineCount + 1;

    printf("LineCount = %d\n", lineCount);

     // Printing what is written in file
    // character by character using loop.
    do {
        ch = fgetc(fp);
        // printf("%c", ch);
        count++;
        // Checking if character is not EOF.
        // If it is EOF stop reading.
    } while (ch != EOF);
 
    // Closing the file
    fclose(fp);

    printf("Count = %d\n", count-1);

    return 0;
}