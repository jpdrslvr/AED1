/*
João Pedro de Morais da Silveira
Ciência da Computação
19102244

Implementar em C um programa que utilize uma matriz com vetor de ponteiros e que ofereça as seguintes opções para o usuário:
1) Criar e redimencionar uma matriz m x n, onde n e m são fornecidos pelo usuário;
2) Realizar a leitura dos elementos da matriz;
3) Fornecer a soma dos elementos da matriz;
4) Retornar em um vetor (utilizando ponteiros) os elementos de uma determinada coluna da matriz;
5) Imprimir a matriz
6) Sair do programa
*/

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#define CLEAR "cls" 
#elif defined __unix__
#define CLEAR "clear" 
#endif

int **criaMatriz(int m, int n); //1
void leiaMatriz(int **mat, int m, int n); //2
int somaMatriz(int **mat, int m, int n); //3
int *colunaMatriz(int ** mat, int m, int n, int ncoluna); //4
void liberaMatriz(int **mat, int ncoluna); //5
void imprimeMatriz(int **mat, int m, int n); //6
void imprimeVetor(int *vet, int n); //7

void menu();
void clearScreen();

int main(){
    int option = -1, soma, ncoluna;
    int m, n; // m linhas, n colunas
    int **matriz = NULL;
    while(1){
        if(option == -1){
            clearScreen();
        }
        scanf("%d", &option);
        while(getchar() != '\n');
        switch (option){
        case 1:
            clearScreen();
            if(matriz){
                liberaMatriz(matriz, m);
                matriz = NULL;
            }

            printf("1 Criar/redimensionar matriz\n");
            printf("m: ");
            scanf("%d", &m);
            printf("n: ");
            scanf("%d", &n);

            matriz = criaMatriz(m, n);
            printf("Matriz criada.\n");
            break;
        case 2:
            clearScreen();
            leiaMatriz(matriz, m, n);
            printf("Matriz inserida.\n");
            break;
        case 3:
            clearScreen();
            if(!matriz){
                printf("Criar/ler matriz primeiro.\n");
            }
            else{
                soma = somaMatriz(matriz, m, n);
                printf("Soma: %d\n", soma);
            }
            break;
        case 4:
            clearScreen();
            do{
                printf("Coluna: ");
                scanf("%d", &ncoluna);
            }
            while(ncoluna <= 0 || ncoluna > n);
            imprimeVetor(colunaMatriz(matriz, m, n, ncoluna - 1), m);
            break;
        case 5:
            clearScreen();
            printf("Matriz %d x %d\n", m, n);
            imprimeMatriz(matriz, m, n);
            break;
        case 6:
            if(matriz) liberaMatriz(matriz, m);
            exit(EXIT_SUCCESS);
            break;
        case 7:
            clearScreen();
            liberaMatriz(matriz, m);
            matriz = NULL;
            break;
        default:
            clearScreen();
            break;
        }
    }

    return 0;
}

int **criaMatriz(int m, int n){
    int **mat = malloc(sizeof(int*) * m);
    if(!mat){
        printf("falha no malloc\n");
        exit(EXIT_FAILURE);
    }
    for (size_t i = 0; i < m; i++){
        *(mat + i) = malloc(sizeof(int) * n);
        if(!(*(mat + i))){
            printf("falha no malloc\n");
            exit(EXIT_FAILURE);
        }
    }
    return mat;
}


void leiaMatriz(int **mat, int m, int n){ //2
    for (size_t i = 0; i < m; i++){
        for (size_t j = 0; j < n; j++){
            printf("M[%ld, %ld] = ", i + 1, j + 1);
            scanf("%d", *(mat + i) + j);
        }
    }
}

int somaMatriz(int **mat, int m, int n){ //3
    int soma = 0;
    for (size_t i = 0; i < m; i++){
        for (size_t j = 0; j < n; j++){
            soma += *(*(mat + i) + j);
        }
    }
    return soma;
}

int *colunaMatriz(int ** mat, int m, int n, int ncoluna){ //4
    int *vet = NULL;
    while(!vet) vet = malloc(sizeof(int) * m);
    for (size_t i = 0; i < m; i++){
        *(vet + i) = *(*(mat + i) + ncoluna);
    }
    return vet;
}

void liberaMatriz(int **mat, int ncoluna){ //5
    for (int i = 0; i < ncoluna; i++)
        free(*(mat + i));
    free(mat);
}

void imprimeMatriz(int **mat, int m, int n){ //6
    for (size_t i = 0; i < m; i++){
        for (size_t j = 0; j < n; j++){
                printf("%-7d", *(*(mat + i) + j));
        }
        printf("\n");
    }
}

void imprimeVetor(int *vet, int n){ //7
    for (size_t i = 0; i < n; i++){
        printf("%d\n", *(vet + i));
    }
}


void menu(){
    printf("------------------------\n");
    printf("1 Criar matriz\n");
    printf("2 Ler elementos\n");
    printf("3 Soma dos elementos\n");
    printf("4 Coluna\n");
    printf("5 Imprimir\n");
    printf("6 Sair\n");
    printf("7 Free\n");
    printf("------------------------\n");
}

void clearScreen(){
    system(CLEAR);
    menu();
}