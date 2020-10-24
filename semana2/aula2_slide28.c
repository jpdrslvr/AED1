/*
João Pedro de Morais da Silveira
Ciência da Computação
19102244

Faça um programa que armazene a informação de várias
pessoas.
- O programa só deve sair quando o usuário disser que não
deseja mais entrar com os dados de outra pessoa.
- Antes de sair o programa deve apresentar, de forma
organizada, os dados de todas as pessoas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls" 
#elif defined __unix__
#define CLEAR "clear" 
#endif

typedef struct{
    char nome[30];
    int idade;
    int altura;
} Pessoa;

Pessoa *addPessoa(Pessoa *p, int size);
void listPessoas(Pessoa *p, int size);
void menu();
void clearScreen();

int main(){
    Pessoa *pPessoa = NULL;
    int total = 0;
    int option = 1;
    while(option){
        clearScreen();
        pPessoa = addPessoa(pPessoa, total);
        total++;
        printf("Adicionar outra? (1 = sim, 0 = não) ");
        scanf("%d", &option);
        while(getchar() != '\n');

    }
    clearScreen();
    listPessoas(pPessoa, total);
    free(pPessoa);
    return 0;
}

Pessoa *addPessoa(Pessoa *p, int size){
    Pessoa *pTemp = NULL;
    if(p){
        while(!pTemp) pTemp = realloc(p, sizeof(Pessoa) * (size + 1));
    }
    else{
        while(!pTemp) pTemp = malloc(sizeof(Pessoa));
    }
    p = pTemp;

    printf("Nome: ");
    scanf("%[^\n]", (p + size)->nome);
    printf("Idade: ");
    scanf("%d", &((p + size)->idade));
    printf("Altura: ");
    scanf("%d", &((p + size)->altura));
    printf("Pessoa adicionada.\n");

    return p;
}

void listPessoas(Pessoa *p, int size){
    for (int i = 0; i < size; i++){
        printf("Pessoa %d:\n", i + 1);
        printf("  Nome: %s\n", (p + i)->nome);
        printf("  Idade: %d anos\n", (p + i)->idade);
        printf("  Altura: %dcm\n", (p + i)->altura);
    }
}

void clearScreen(){
    system(CLEAR);
}