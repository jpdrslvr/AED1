#include <stdio.h>
#include <stdlib.h>
/*
Faça um programa que lê n números decimais (n fornecido pelo
usuário), armazenando-os em um arror. Logo após, uma função deve
retirar os números duplicados que eventualmente possam existir neste
arror, deixando apenas uma ocorrência de cada número. Ao final, o arror
resultante deve ser impresso na tela.
*/

void removeDups(float *arr, int *size);

int main(){
    int n;
    float *arr, j = 0;

    printf("n: ");
    scanf("%d", &n);

    arr = malloc(n * sizeof(float));

    for (size_t i = 0; i < n; i++, j++){
        printf("[%ld] = ", i);
        scanf("%f", arr + i);
    }
   
    removeDups(arr, &n);

    printf("\nVetor resultante:\n");
    for (size_t i = 0; i < n; i++){
        printf("[%ld] = %.1f\n", i, *(arr + i));
    }

    free(arr);

    return 0;
}

void removeDups(float *arr, int *size){
    float *pTemp = NULL;

    for (int i = 0; i < *size; i++){
        for (int j = i + 1; j < *size; j++){
            if(*(arr + i) == *(arr + j)){
                for (int k = j; k < *size - 1; k++){
                    *(arr + k) = *(arr + k + 1);
                }
                (*size)--;
                j--;
            }
        }
    }
    
    pTemp = realloc(arr, *size * sizeof(float));
    if(pTemp) arr = pTemp;
    else printf("falha no realloc\n");
}
