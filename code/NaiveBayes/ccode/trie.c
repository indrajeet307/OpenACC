/*
 * Trie Implementation
 * https://en.wikipedia.org/wiki/Trie
 * TODO: ADD . as the part of the word, add clean up
 *
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORDS 2048
#define MAX_ALPHA 48 // allowed characters in a word
enum {DOT=26, ORB, CRB, ONE, THREE, TWO, SIX, FOUR, COMMA,
        E8, S7, Z0, DASH}; //ORB : Open Rounded Bracket, CRB = Close Rounded Bracket
inline int get_number_from_alpha(int x)
{
    if( x == ',')
        return COMMA;
    if( x == '.')
        return DOT;
    if( x == '(')
        return ORB;
    if( x == ')')
        return CRB;
    if( x == '1')
        return ONE;
    if( x == '2')
        return TWO;
    if( x == '3')
        return THREE;
    if( x == '4')
        return FOUR;
    if( x == '6')
        return SIX;
    if( x == '7')
        return S7;
    if( x == '8')
        return E8;
    if( x == '0')
        return Z0;
    if( x == '-')
        return DASH;
    if( x >= 'A' && x <= 'Z')
        return (x - 'A');
    else if (x >= 'a' && x <= 'z')
        return (x - 'a');
    else return -1;
}

unsigned int g_numwords;

typedef struct trie_node{
    struct trie_node *next;
    unsigned int word_num;
}trie_node;

typedef struct word_node{
    char *word;
    int  Id; 
}word_node;

struct trie_node *g_trie;
struct word_node *g_word_list;

inline void init_trie_level(struct trie_node * node)
{
    int i = 0;
    for( i = 0 ; i<MAX_ALPHA; i++)
    {
        node[i].next = NULL;
        node[i].word_num = 0;
    }
}

void init_trie()
{
    int i = 0;
    
    g_trie = (trie_node*) malloc(sizeof(trie_node)*MAX_ALPHA);
    init_trie_level(g_trie);
    g_numwords = 0;
}

void init_word_list()
{
    g_word_list = (word_node*) calloc (sizeof(word_node),MAX_WORDS);
}

void init_ds()
{
    init_trie();
    init_word_list();
}

inline int get_numwords()
{
    return g_numwords;  
}

inline int inc_numwords()
{
    int x = g_numwords;
    g_numwords+=1;  
    return x;
}

trie_node* add_trie_level()
{
    trie_node *temp;
    temp = (trie_node*) malloc(sizeof(trie_node)*MAX_ALPHA);
    init_trie_level(temp);
    return temp;
}

/*
*	@DESC   : add word to a list
*	@PRAM   : index in the list, word , size of word
*	@return : 
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
    g_word_list[val].Id = val ;
}

/*
*	@DESC   : adds a word to the trie
*	@PRAM   : the to be added and its size
*	@return : index of the word else retrurn -1 on error
*	@SEE    :
*	@TODO   :
*	
*/
int add_word(char *word,int wsize)
{
    trie_node *temp = g_trie;
    int val,i,in;
    if( MAX_WORDS-1 == get_numwords())
    {
        printf("PANIC: more than MAX_WORDS update, MAX_WORDS and run again \n");
        return -1;
    }

    for(  i=0;i < wsize;i++)
    {
        in = get_number_from_alpha(word[i]);
        if( in == -1){
            printf("Cannot Add word,%s :( \n",word);
            return -1;
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

            return val;
        }
    }
}

/*
*	@DESC   : Finds a word in the trie
*	@PRAM   : the word to be addded and its size
*	@return : index fo the word if found else RETURNs -1
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
            return -1;
        }
        if(i != (wsize-1))
        {
            if(temp[in].next == NULL){
                return -1;
            }
            if (temp[in].next ){
                temp = temp[in].next;
            }
        }
        else // i== wsize-1
        {
            return temp[in].word_num ;
        }
    }
    return -1;
}

/*
*	@DESC   : Shows the words in the dicitionary
*	@PRAM   :
*	@return :
*	@SEE    :
*	@TODO   :
*	
*/
int show_words()
{
    int i=0;
    for( i=0 ; i<get_numwords(); i++)
    {
        printf("[%d] == %s. \n",g_word_list[i].Id,g_word_list[i].word);
    }
}
 
 /*
 int main()
 {
    init_ds();
    if( find_word("ABHI",4) == -1)
        printf("%d ",add_word("ABHI",4));

    if( find_word("ABHI",4) == -1)
    printf("%d ",add_word("ABHI",4));
    else
        printf("Word exists");
    if( find_word("ABHI.IK",7) == -1)
    printf("%d ",add_word("ABHI.IK",7));

    if( find_word("ABHI.IK",7) == -1)
    printf("%d ",add_word("ABHI",4));
    else
        printf("Word exists");
    return 0;
 }
 */
