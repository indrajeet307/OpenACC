/*
 * Reads a file Line by line and adds the word to the trie
* TODO: add to trie
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#define DEBUG 1
FILE *fp;
int open_file(char *fname)
{
    errno = 0;
    fp = fopen(fname,"r+");
    if(errno != 0)
        printf("Cannot open file");
    if (fp == NULL)
        return -1;
}

int close_file()
{
    if ( fclose(fp))
        return -1;
}

void tokenize_line(char * line, ssize_t len)
{
  char *str,*saveptr,*token;
  str = line;
  token = strtok_r(str, " _|*", &saveptr);
  while(token != NULL)
  {
    if (DEBUG) 
        printf("%s\n", token);
    
    token = strtok_r(NULL, " _|*", &saveptr);
  }
}

void read_file()
{
    char line[1024];
    ssize_t len = 0;
    ssize_t read;
    char ch;
    while(1)
    {
        if(( ch = fgetc(fp)) == EOF)
            break;
        if(ch == '\n')
        {
            line[len]='\0';
            tokenize_line(line, len);
            len = 0;
        }
        else
        {
            line[len++] = ch;
        }
    }
    if(len>0){
        line[len]='\0';
        tokenize_line(line, len);
    }
}

int main()
{
    if (open_file("./temp.txt") != -1) {
        read_file();
        close_file();
    }
}
