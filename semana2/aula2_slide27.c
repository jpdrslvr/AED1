/*
João Pedro de Morais da Silveira
Ciência da Computação
19102244

Faça a implementação da função realloc, você
deve utilizar a função malloc para isso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *realloc2(void *ptr, size_t oldSize, size_t newSize);

int main(){
    // TESTES
    char *test;

    test = malloc(10);
    strcpy(test, "aaaaaaaaa");
    printf("malloc: %s\n", test);
    printf("end: %p\n\n", (void *)test);

    // diminui
    test = realloc2(test, 10, 5);
    printf("diminui: %s\n", test);
    printf("end: %p\n\n", (void *)test);

    // aumenta
    test = realloc2(test, 5, 15);
    strcat(test, "bbbbbbbbb");
    printf("aumenta: %s\n", test);
    printf("end: %p\n\n", (void *)test);
    free(test);

    return 0;
    
}

void *realloc2(void *ptr, size_t oldSize, size_t newSize){
    /*
    opção 1: 
        - alocar memória com o novo tamanho;
        - liberar bloco do ponteiro original;
        - retornar novo ponteiro.
    opção 2:
        - diminuir ou expandir o bloco atual de memória;
        - retornar o ponteiro original com o novo tamanho.
    A função realloc() pode retornar o mesmo ponteiro (opção 2), mas isso 
    não é garantido.
    Não é possível reimplementar essa funcionalidade sem saber como a memória
    é gerenciada pela implementação da stdlib, então optei por sempre alocar 
    um novo bloco de memória e retornar o novo ponteiro (opção 1).
    
    Da documentação:
    The realloc function returns a pointer to the new object (which may have
    the same value as a pointer to the old object), or a null pointer if the new 
    object could not be allocated.
    */
    void *newPtr = NULL;
    
    if(newSize == 0){
        free(ptr);
        return NULL;
    }
    while(!newPtr) newPtr = malloc(newSize);
    if(ptr){
        if(newSize > oldSize) memcpy(newPtr, ptr, oldSize);
        else memcpy(newPtr, ptr, newSize);
        free(ptr);
    }
    return newPtr;
}
