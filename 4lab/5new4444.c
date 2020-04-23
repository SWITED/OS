#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct Node{
    char *str;
    struct Node* next;
} Node;

int push(Node **node, const char *str, size_t length)
{
    Node *tmp = (Node*)malloc(sizeof(Node));
    if (NULL == tmp){
        return -1;
    }
    tmp->next = NULL;
    tmp->str = (char*)malloc(sizeof(char) * (length + 1));
    if (NULL == tmp->str){
        free(tmp);
        return -1;
    }
    strncpy(tmp->str, str, length);
    Node* last = *node;
    if (*node == NULL){
        *node = tmp;
    }
    else{
        while (last->next){
            last = last->next;
        }
        last->next = tmp;
    }
    return 0;
}


void pop(Node **node)
{
    if (NULL == node){
        return;
    }
    Node *tmp = *node;
    (*node) = (*node)->next;
    free(tmp->str);
    free(tmp);
}


void clear(Node *node)
{
    while (node){
        Node *tmp = node;
        node = node->next;
        free(tmp->str);
        free(tmp);
    }
}


void print(Node *node)
{
    if (NULL == node){
        return;
    }
    Node *tmp = node;
    for (   ; tmp; tmp = tmp->next){
        printf("%s\n", tmp->str);
    }
}


char* read_buffer() 
{
    size_t str_len = 0;
    size_t buf_size = 3;
    char *str = (char *)malloc(buf_size);
    while (1) {
        if (fgets(str + str_len, buf_size - str_len, stdin) == NULL){
            if (feof(stdin) && str_len > 0){
                break;
            } 
            else{
                return NULL;
            }
        }
        str_len += strlen(str + str_len);
        if ((str_len + 1 < buf_size) || (str[str_len - 1] == '\n')){
            break;
        }
        buf_size *= 2;
        str = (char *)realloc(str, buf_size);
    }
    if (str[str_len - 1] == '\n'){
        str[str_len - 1] = '\0';
    }
    char* return_str = (char *)realloc(str, str_len + 1);
    return return_str;
}


int main()
{
    Node* List = NULL;
    while (1){
        char* buffer = read_buffer();
        if(strcmp(buffer, ".") == 0){
            break;
        }
        if (push(&List, buffer, strlen(buffer)) == -1){
            fprintf(stderr, "Memory error!\n");
            clear(List);
            return 1;
        }
    }
    print(List);
    clear(List);
    return 0;
}

