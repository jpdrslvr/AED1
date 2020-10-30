#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Faça um programa que leia uma string (de 80 caracteres) chamada linha
e, com uma função, identifique cada palavra (substring) desta linha
copiando-a para um novo vetor. Ao final, o programa deve imprimir as
palavras separadas, uma palavra por linha
*/

char **substrings(char *string, size_t *size, char *sep);

int main(){
    char linha[80], **palavras = NULL;
    size_t size;
    fgets(linha, 80, stdin);
    // strcpy(linha, "i'm a mountain bike vampire witch from the future");
    palavras = substrings(linha, &size, " \n");

    for (size_t i = 0; i < size; i++){
        printf("%s\n", *(palavras + i));
        free(*(palavras + i));
    }
    printf("%s", linha);
    free(palavras);
    return 0;
}

char **substrings(char *string, size_t *size, char *sep){
    char **substrings = NULL, *token = NULL, *garbage, **pTemp = NULL;

    // faz uma cópia da string para não perder a original
    token = malloc(strlen(string) + 1);
    if(!token) exit(EXIT_FAILURE);
    strcpy(token, string);

    // guarda o início de token para poder liberar a memória no fim
    garbage = token;

    token = strtok(token, sep);
    for(*size = 0; token != NULL; (*size)++){
        pTemp = realloc(substrings, sizeof(char *) * (*size + 1));
        if(pTemp) substrings = pTemp;
        else exit(EXIT_FAILURE);

        *(substrings + *size) = malloc(strlen(token) + 1);
        if(!(*(substrings + *size))) exit(EXIT_FAILURE);

        memmove(*(substrings + *size), token, strlen(token) + 1);
        token = strtok(NULL, sep);
    }
    free(garbage);

    return substrings;
}