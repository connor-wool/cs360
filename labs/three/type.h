#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define STR_LEN 256
#define MAX_TOK 64

char line[STR_LEN];
char *tokens[MAX_TOK];
char active = 1;
