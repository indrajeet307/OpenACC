#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdlib.h>
#include <errno.h>
int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Invalid number of argumnets");
        return 1;
    }
    char *train_data_path=argv[1];
    char *curr_path = train_data_path;
    DIR * dirptr = opendir(curr_path); 
    DIR * stack[8];
    stack[0]=dirptr;
    //init_ds();
    int stop=1;
    struct dirent* dc; //dc = directory_contents
    while(1)
    {
        dc = readdir(dirptr);
        if(dc == NULL)
        {
            if(stop<=0)
                break;
            else{
                dirptr = stack[--stop];
                if(stop == 1){
                }
                if(stop == 2){
                }
                int tlen = strlen(curr_path);
                char *ptr = &curr_path[tlen-1];
                while(*ptr != '/')
                    ptr--;
                *ptr='\0';
                continue;
            }
        }
        if(!strcmp(dc->d_name , ".") || !strcmp(dc->d_name , ".."))
            continue;
        if(dc->d_type == DT_DIR)
        {
            stack[stop++] = dirptr;
            strcat(curr_path,"/");
            strcat(curr_path,dc->d_name);
            dirptr = opendir(curr_path);
            if(dirptr == NULL)
                break;
        }
        if(dc->d_type == DT_REG)
        {
            if(!strstr(dc->d_name,"freq"))
            {
      //              printf("Useless file %s\n",dc->d_name);
            }
            else{
                char fname[1024];
                char cmd[1024];
                strcpy(cmd,"cat ");
                strcpy(fname ,curr_path);
                strcat(fname,"/");
     //               printf("Analysing file %s\n",dc->d_name);
                strcat(fname,dc->d_name);
                strcat(cmd,fname);
                strcat(cmd,"|xargs -n1|sort|uniq -c >");
                strcat(cmd,fname);
                strcat(cmd,".freq");
                printf("%s \n",cmd);
                system(cmd);
            }
        }
    }
    //printf("Number of words %d.\n",g_word_count);
    return 0;
}
