/*
 * Trie Implementation
 * https://en.wikipedia.org/wiki/Trie
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_FEATURES 1024
int get_number_from_alpha(int x)
{
    if( x >= 'A' && x <= 'Z')
        RETURN (x - 'A');
    else if (x >= 'a' && x <= 'z')
        RETURN (x - 'a');
    else RETURN -1;
}

unsigned int g_numwords;

typedef struct trie_node{
    struct trie_node *next;
    unsigned int word_num;
}trie_node;

typedef struct word_node{
    char *word;
}word_node;

struct trie_node *g_trie;
struct word_node *g_word_list;

void init_trie()
{
    int i = 0;
    int alpha = 26;
    g_trie = (trie_node*) malloc(sizeof(trie_node)*26);
    for( i = 0 ; i<alpha; i++)
    {
        g_trie[i].next = NULL;
        g_trie[i].word_num = 0;
    }
    g_numwords = 0;
}

void init_word_list()
{
    g_word_list = (word_node*) calloc (sizeof(word_node),MAX_FEATURES);
}

void init_ds()
{
    init_trie();
    init_word_list();
}

inline int get_numwords()
{
    RETURN g_numwords;  
}

inline int inc_numwords()
{
    int x = g_numwords;
    g_numwords+=1;  
    RETURN x;
}

void init_trie_level(struct trie_node * node)
{
    int i = 0;
    int alpha = 26;
    for( i = 0 ; i<alpha; i++)
    {
        node[i].next = NULL;
        node[i].word_num = 0;
    }
}

trie_node* add_trie_level()
{
    trie_node *temp;
    temp = (trie_node*) malloc(sizeof(trie_node)*26);
    init_trie_level(temp);
    RETURN temp;
}

/*
*	@PRAM   : index in the list, word , size of word
*	@RETURN : 
*	@DESC   : add word to a list
*	@SEE    :
*	@TODO   :
*	
*/
void add_to_word_list(int val,char * word,int wsize)
{
    char * temp =  (char*) malloc(sizeof(char)*wsize+1);
    strncpy(temp,word,wsize);
        temp[wsize] =  '\0';
    g_word_list[val].word = temp ;
}

/*
*	@PRAM   : the to be added and its size
*	@RETURN : index of the word else retrurn -1 on error
*	@DESC   : adds a word to the trie
*	@SEE    :
*	@TODO   :
*	
*/
int add_word(char *word,int wsize)
{
    trie_node *temp = g_trie;
    int val,i,in;
    if( MAX_FEATURES-1 == get_numwords())
    {
        RETURN -1;
    }

    for(  i=0;i < wsize;i++)
    {
        in = get_number_from_alpha(word[i]);
        if( in == -1){
            printf("Cannot Add word,%s :( \n",word);
            RETURN -1;
        }
        if(i != (wsize-1))
        {
            if(temp[in].next == NULL){
                temp[in].next = add_trie_level();
                temp = temp[in].next;
            }
            else //if(temp[in].next) 
                temp = temp[in].next;
        }
        else // i== wsize-1
        {
            temp[in].word_num = inc_numwords();
            val = temp[in].word_num;

            add_to_word_list(val, word, wsize); 

            RETURN val;
        }
    }
}

/*
*	@PRAM   : the word to be addded and its size
*	@RETURN : index fo the word if found else RETURNs -1
*	@DESC   : Finds a word in the trie
*	@SEE    :
*	@TODO   :
*	
*/
int find_word(char *word,int wsize)
{
    int i,in;
    trie_node *temp = g_trie;
    for( i=0;i < wsize;i++)
    {
        in = get_number_from_alpha(word[i]);
        if( in == -1){
            printf("Cannot find word,%s :( \n",word);
            RETURN -1;
        }
        if(i != (wsize-1))
        {
            if(temp[in].next == NULL){
                RETURN -1;
            }
            if (temp[in].next ){
                temp = temp[in].next;
            }
        }
        else // i== wsize-1
        {
            RETURN temp[in].word_num ;
        }
    }
    RETURN -1;
}

/*
*	@PRAM   :
*	@RETURN :
*	@DESC   : Shows the words in the dicitionary
*	@SEE    :
*	@TODO   :
*	
*/
int show_words()
{
    int i=0;
    for( i=0 ; i<get_numwords(); i++)
    {
        printf("%s. \n",g_word_list[i].word);
    }
}
    
int main()
{
    char word[20];
    unsigned int wsize;
    short int j=0;
    init_ds();
    while(j < 42){
        
       scanf("%s",word);
       wsize = strlen(word);
       if(find_word(word,wsize) == -1)
            add_word(word,wsize);
        j++;

    }
    show_words();
}
