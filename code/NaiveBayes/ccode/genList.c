#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#define MAX_OPCODES 1280
/*
 *                           x - min(X)
 * Normalized value = --------------------
 *                      max(X) - min(X)
 * */
struct file_prop{
    float opcode_freq[MAX_OPCODES];
    int num_opcodes;
    int min_freq;
    int max_freq;
};
/*
 *	@DESC   : opens the file
 *	@PRAM   : filename
 *	@RETURN : -1 on Error
 *	@SEE    :  
 *	@TODO   : 
 *	
 */
FILE* open_file(char *fname, char *mode)
{
    FILE *fp;
    errno = 0;
    fp = fopen(fname,mode);
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
    errno = 0;
    if ( fclose(fp))
        if(errno !=0 )
        {
            printf("Error: %s",strerror(errno));
            return -1;
        }
    return ;
}

inline int get_numOpcodes()
{
    return get_numwords();
}

int getGroup(char *gname)
{
    if(strcmp("0-5k",gname   )==0) return 1;
    if(strcmp("5-10k",gname  )==0) return 3;

    if(strcmp("10-15k",gname )==0) return 5;
    if(strcmp("15-20k",gname )==0) return 7;

    if(strcmp("21-25k",gname )==0) return 9;
    if(strcmp("25-30k",gname )==0) return 11;

    if(strcmp("30-35k",gname )==0) return 13;
    if(strcmp("35-40k",gname )==0) return 15;

    if(strcmp("40-45k",gname )==0) return 17;
    if(strcmp("45-50k",gname )==0) return 19;

    if(strcmp("50-55k",gname )==0) return 21;
    if(strcmp("55-60k",gname )==0) return 23;

    if(strcmp("60-65k",gname )==0) return 25;
    if(strcmp("65-70k",gname )==0) return 27;

    if(strcmp("70-75k",gname )==0) return 29;
    if(strcmp("75-80k",gname )==0) return 31;

    if(strcmp("80-85k",gname )==0) return 33;
    if(strcmp("85-90k",gname )==0) return 35;

    if(strcmp("90-95k",gname )==0) return 37;
    if(strcmp("95-100k",gname)==0) return 39;
}

float opcode_freq[MAX_OPCODES][40];

void resetFileProp(struct file_prop *fprop)
{
    int i =0;
    for( i=0; i< MAX_OPCODES; i++)
        fprop->opcode_freq[i] = 0;

    fprop->min_freq = INT_MAX;
    fprop->max_freq = INT_MIN;
    fprop->num_opcodes = 0;
}

void putFreq(char *filename)
{
    FILE* fp = open_file(filename,"w+");
    int i=0;
    int j=0,numgroups=40;
    for(i=0;i<get_numOpcodes();i++)
    {
        fprintf(fp,"%d,",i);
        for(j=0;j<numgroups;j++)
        {
            fprintf(fp,"%f,",opcode_freq[i][j]);
        }
        fprintf(fp,"\n");
    }
    close(fp);
}

void putFileProp(char *filename,struct file_prop *fprop)
{
    FILE* fp = open_file(filename,"w");
    int i=0;
    int j=0,numgroups=40;
    fprintf(fp," max[%d] min[%d] total[%d] \n", fprop->max_freq, fprop->min_freq, fprop->num_opcodes);
    for(i=0;i<MAX_OPCODES;i++)
    {
        if(fprop->opcode_freq[i])
            fprintf(fp,"%d %1.4f\n", i,fprop->opcode_freq[i]);
    }
    close(fp);
}

void normalizeFileProps(struct file_prop *fprop)
{
    int i =0;
    for ( i=0;i<MAX_OPCODES; i++)
    {
        if(fprop->opcode_freq[i])
            fprop->opcode_freq[i] = (float)(fprop->opcode_freq[i] - fprop->min_freq) / (fprop->max_freq - fprop->min_freq);
    }
}

void updateFileProp(struct file_prop *fprop, int opindex, int freq)
{
    fprop->opcode_freq[opindex] = freq;
    fprop->num_opcodes += 1;
    if(fprop->max_freq < freq)
        fprop->max_freq = freq;
    if(fprop->min_freq > freq)
        fprop->min_freq = freq;

}
void updateOpcodeFreq(struct file_prop *fprop,int index )
{
    int i=0;
    for(i=0;i<MAX_OPCODES;i++)
        opcode_freq[i][index] = fprop->opcode_freq[i];
    //opcode_freq[wordin][index]+=freq;
}
void putTofile(char *opcodefile,char *masterfreqfile)
{
    putWords(opcodefile);
    putFreq(masterfreqfile);
}

void populateOpcodes(char *fname)
{
    char opcode[32];
    int loc=-1;
    FILE *fp;
    fp = open_file(fname,"r");
    while(!feof(fp))
    {
        fscanf(fp,"%s",opcode);
        loc = find_word(opcode,strlen(opcode)) ;
        if( loc < 1)
            add_word(opcode,strlen(opcode));
        else
            printf("Duplicate in master file at %d, %s :(\n",loc,opcode);
    }

    close_file(fp);
}

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printf("Invalid number of argumnets ...\n");
        printf("USAGE:\n");
        printf("./genList <master_list_of_opcodes> <directory>\n");
        printf(" NOTE: directory contains directories malware and benign \n");
        printf("which in turn contains files, grouped(insied directories) according to file sizes\n");
        printf("\n");
        return 1;
    }
    char *train_data_path=argv[2];
    char *curr_path = train_data_path;
    DIR * dirptr = opendir(curr_path); 
    DIR * stack[8];
    stack[0]=dirptr;
    //init_ds();
    int stop=1;
    struct dirent* dc; //dc = directory_contents
    init_ds();
    int total_opcodes;
    int factor = 0;
    int index=0;
    struct file_prop fprop;


    populateOpcodes(argv[1]);
    total_opcodes = get_numOpcodes();


    while(1)
    {
        dc = readdir(dirptr);
        if(dc == NULL)
        {
            if(stop<=0)
                break;
            else{
                closedir(dirptr);
                dirptr = stack[--stop];
                if(stop == 1){
                    printf("Changed Catagory %s\n",curr_path);
                    factor = 1;
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
            if(stop == 3){
                printf("A new Group %s",curr_path);
                index = getGroup(dc->d_name);
                if(factor) index -=1;
            }
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

                FILE *fp = open_file(filename,"r");
                assert(fp!=NULL);
                int freq;
                char opcode[32];
                int wordin=0;
                resetFileProp(&fprop);
                while(!feof(fp))
                {
                    int red = fscanf(fp,"%d %s",&freq,opcode);
                    if(!red)break;
                    //printf("%d, %s\n",freq,opcode);
                    wordin =find_word(opcode, strlen(opcode));
                    if( wordin < 1)
                    {
                        add_word(opcode);
                        printf("New Word added %s\n", opcode);
                    }
                    updateFileProp(&fprop, wordin, freq);
                    //ADD to the file_prop
                }
                close_file(fp);
                normalizeFileProps(&fprop);
                // EOF encountred update the opcode_freq from file_prop
                updateOpcodeFreq(&fprop, index);
                //putFileProp("/tmp/lol.log", &fprop);
            }
        }
    }
    //printf("Number of words %d.\n",g_word_count);
    printf("Number of opcodes %d", get_numwords());
    putTofile("master_opcodes_id.txt","master_freq_train.csv");
    return 0;
}
