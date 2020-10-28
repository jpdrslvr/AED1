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
    palavras = substrings(linha, &size, " ");

    for (size_t i = 0; i < size; i++){
        printf("%s\n", *(palavras + i));
        free(*(palavras + i));
    }
    free(palavras);
    return 0;
}

char **substrings(char *string, size_t *size, char *sep){
    char **substrings = NULL, *token;
    token = malloc(strlen(string) + 1); //pra não modificar a string original
    memmove(token, string, strlen(string) + 1);
    
    token = strtok(token, sep);
    for(*size = 0; token != NULL; (*size)++){
        substrings = realloc(substrings, sizeof(char *) * (*size + 1));
        *(substrings + *size) = malloc(strlen(token) + 1);

        memmove(*(substrings + *size), token, strlen(token) + 1);
        token = strtok(NULL, sep);
    }
    free(token);

    return substrings;
}