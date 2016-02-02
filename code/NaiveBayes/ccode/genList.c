#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include<stdlib.h>
#include <errno.h>

/*
 *	@DESC   :  opens the file
 *	@PRAM   : filename
 *	@RETURN : -1 on Error
 *	@SEE    :  
 *	@TODO   : 
 *	
 */
FILE* open_file(char *fname)
{
    FILE *fp;
    errno = 0;
    fp = fopen(fname,"r+");
    if(errno != 0)
    {
        printf("Error: %s",strerror(errno));
        return NULL;
    }
    return fp;
}

/*
 *	@DESC   : Close the file pointer safely
 *	@PRAM   :   
 *	@RETURN :  
 *	@SEE    :  
 *	@TODO   : 
 *	
 */
int close_file(FILE *fp)
{
    if ( fclose(fp))
        return -1;
}

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
    init_ds();
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
                    printf("Changed Catagory%s\n",curr_path);
                }
                if(stop == 2){
                    printf("Changed Group %s\n",curr_path);
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
            if(strstr(dc->d_name,".freq"))
            {
                //printf("Processing file : %s/%s...\n", curr_path,dc->d_name);
                char filename[256];
                strcpy(filename,curr_path);
                strcat(filename,"/");
                strcat(filename,dc->d_name);
                
                FILE *fp = open_file(filename);
                int freq;
                char opcode[32];
                while(!feof(fp))
                {
                    fscanf(fp,"%d %s",&freq,opcode);
                    //printf("%d, %s\n",freq,opcode);
                    if( find_word(opcode, strlen(opcode)) < 1)
                        add_word(opcode);
                }
                close_file(fp);
            }
        }
    }
    //printf("Number of words %d.\n",g_word_count);
    printf("Number of opcodes %d", get_numwords());
    return 0;
}
