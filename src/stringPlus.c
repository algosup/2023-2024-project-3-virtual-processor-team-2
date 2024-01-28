/*
    This file contains functions to manipulate strings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stringPlus.h"


int strToBin(char *arg) {
    // Convert a string to binary
    int bin = 0;
    size_t size = strlen(arg);
    for (size_t i = 2; i < size; i++) {
        bin = bin * 2 + (arg[i] - '0');
    }

    return bin;
}

int strToOct(char *arg) {
    // Convert a string to octal
    int oct = 0;
    size_t size = strlen(arg);
    for (size_t i = 2; i < size; i++) {
        oct = oct * 8 + (arg[i] - '0');
    }

    return oct;
}

int strToHex(char *arg) {
    // Convert a string to hexadecimal
    int hex = 0;
    size_t size = strlen(arg);
    for (size_t i = 2; i < size; i++) {
        if (arg[i] >= '0' && arg[i] <= '9') {
            hex = hex * 16 + (arg[i] - '0');
        } else if (arg[i] >= 'a' && arg[i] <= 'f') {
            hex = hex * 16 + (arg[i] - 'a' + 10);
        } else if (arg[i] >= 'A' && arg[i] <= 'F') {
            hex = hex * 16 + (arg[i] - 'A' + 10);
        }
    }

    return hex;
}

char strToChar(char *arg) {
    // Remove quotes from a string to get the char
    return arg[1];
}

char *strToString(char *arg) {
    // Remove quotes at beginning and at the end of a string
    size_t size = strlen(arg);
    char *str = malloc((size - 1) * sizeof(char));
    if (!str) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    strncpy(str, arg + 1, size - 2);
    str[size - 2] = '\0';  // Null-terminate the string

    return str;
}

char *cleanString(char *str) {
    // Remove spaces and newline characters at the beginning and at the end of a string
    size_t size = strlen(str);

    // Check for an empty string
    if (size == 0) {
        char *emptyString = malloc(1);
        if (!emptyString) {
            fprintf(stderr, "Memory allocation error\n");
            exit(EXIT_FAILURE);
        }
        emptyString[0] = '\0';
        return emptyString;
    }

    size_t start = 0;
    size_t end = size - 1;

    // Find the index of the first non-space, non-newline character
    while (start < size && (str[start] == ' ' || str[start] == '\n')) {
        start++;
    }

    // Find the index of the last non-space, non-newline character
    while (end > 0 && (str[end] == ' ' || str[end] == '\n')) {
        end--;
    }

    // Calculate the length of the cleaned string
    size_t cleanedSize = (start <= end) ? (end - start + 1) : 0;

    // Allocate memory for the cleaned string
    char *cleaned = malloc((cleanedSize + 1) * sizeof(char));
    if (!cleaned) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }

    // Copy the non-space, non-newline characters to the cleaned string
    strncpy(cleaned, str + start, cleanedSize);
    cleaned[cleanedSize] = '\0';  // Null-terminate the cleaned string

    return cleaned;
}