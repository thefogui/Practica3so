/*****************************************************************************
author: Vitor carvaho
leer palabras de un fichero df y los pone el arbol binario
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "red-black-tree.h"

#define MAXLINE 100
#define MAXVALUE 10

int main(int argc, char **argv){
    int i, len, j, indicator, indicator2;
    FILE *fpout;
    char *new_str, *aux_str, *word, *second_str, line[MAXLINE];
    RBTree *tree;
    RBData *treeData;

    srand(time(NULL));
    tree = (RBTree *) malloc(sizeof(RBTree));
    initTree(tree); //inicializate the tree

    fpout = popen("pdftotext prova.pdf - >&1", "r"); //do the pipe with pdftotext

    if (!fpout){
        printf("ERROR: no puc crear canonada.\n");
        exit(EXIT_FAILURE);
    }

    while(fgets(line, MAXLINE, fpout) != NULL){
        word = strtok(line, " ,.-'"); //separate the sentence in words
        while(word != NULL){
            len = strlen(word)-1; //size of the string
            j = 0;
            new_str = malloc(sizeof(char)*len); //allocate memory fot the new string
            indicator = 0; //indicator for the first word
            indicator2 = 0; //indicator fot the second word
            for (i = 0; i <= len; i++){
                if(!ispunct(word[i]) && !isdigit(word[i]) && indicator == 0){
                    new_str[j] = tolower(word[i]); //to lower the char
                    j++;
                }else{
                    if(!ispunct(word[i]) && !isdigit(word[i]) && indicator == 1){
                        if (indicator2 == 0)
                            second_str = (char *)malloc(sizeof(char)); //allocate the memory for the second string
                        second_str[indicator2] = tolower(word[i]);
                        indicator2 = indicator2 + 1;
                    }
                    indicator = 1;
                }
            }
            //Insertion in the tree
            aux_str = malloc(sizeof(char)* j);
            strcpy(aux_str, new_str); //make a copy to put in the tree
            treeData = findNode(tree, aux_str); //put the string in the tree
            if(treeData != NULL){
                treeData->num_vegades++;
            }else{
                treeData = malloc(sizeof(RBData));
                treeData->key = aux_str;
                treeData->num_vegades = 1;
                insertNode(tree, treeData);
            }
            word = strtok(NULL, " ,.-'"); //catch the next word of the setence
        }
    }
    strcpy(aux_str, "text"); //test of the tree should print El string that apareix 2 cops a l'arbre.\n
    treeData = findNode(tree, aux_str);
    if (treeData)
        printf("El string %s apareix %d cops a l'arbre.\n", treeData->key, treeData->num_vegades);

    if (pclose(fpout) == -1){
        printf("ERROR : pclose\n");
        exit(EXIT_FAILURE);
    }
    free(new_str);
    free(aux_str);
    free(second_str);
    deleteTree(tree);
    free(tree);
    return 0;
}
