/*
João Pedro de Morais da Silveira
Ciência da Computação
19102244
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls" 
#elif defined __unix__
#define CLEAR "clear" 
#endif

#define MAX 30 // tamanho máximo de cada nome

struct{
    int total;
    int first;
    int option;
} typedef Control;

// funções
void addName(); // 1
void removeName(); // 2
void listNames(); // 3
void menu();
void clearScreen();

// declaração de variáveis
char *pNames;
Control c;

void main() {    
    // inicialização
    c.first = 1;
    c.total = 0;

    while (1){
        if (c.first){
            clearScreen();
            c.first = 0;
        }

        scanf("%d", &c.option);
        while(getchar() != '\n');
        switch (c.option){
        case 1:
            clearScreen();
            addName();
            break;
        case 2:
            clearScreen();
            removeName();
            break;
        case 3:
            clearScreen();
            listNames();
            break;
        case 4:
            free(pNames);
            exit(0);
            break;
        default:
            clearScreen();
            printf("Opção não existente.\n");
            break;
        }
    }
}

void menu() {
    printf("--------------------------------\n");
    printf("Selecione a opção:\n");
    printf("1 Adicionar nome\n");
    printf("2 Remover nome\n");
    printf("3 Listar\n");
    printf("4 Sair\n");
    printf("--------------------------------\n\n");
}

void addName(){
    // char *pTemp = NULL, *tempName = NULL;
    char *pTemp = NULL, tempName[MAX];

    printf("Nome: ");
    fgets(tempName, MAX, stdin);
    tempName[strcspn(tempName, "\n")] = 0;

    // alocação
    if(pNames){
        while(!pTemp){
            pTemp = (char *) realloc(pNames, strlen(pNames) + strlen(tempName) + 2); // + 2 -> \0 e separador
        }
        pNames = pTemp;
        strcat(pNames, tempName);
    }
    else{
        while(!pNames)
            pNames = (char *) malloc(strlen(tempName) + 2);
        strcat(pNames, tempName);
    }
    
    strcat(pNames, "-"); // separador
    c.total++;

}

void removeName(){
    int toRemove, range[] = {-1, -1}, counter = 1, firstOrLast = 0;
    char *pTemp = NULL;
    size_t size, len;

    if(pNames){
        listNames();
        printf("Remover: ");
        scanf("%d", &toRemove);

        // não existe na agenda
        if(toRemove > c.total){
            printf("Não encontrado.\n");
            return;
        }

        // agenda com só uma entrada
        if(toRemove == 1 && c.total == 1){
            free(pNames);
            return;
        }

        // busca o início e fim da substring a ser removida
        for (size_t i = 0; i < strlen(pNames) - 1; i++){
            if(*(pNames + i) == '-'){
                counter++;
            }
            if(counter == toRemove){
                range[0] = i;
                counter++;
            }
            else if(counter > toRemove && *(pNames + i) == '-'){
                range[1] = i;
                break;
            }
        }

        // move os bytes do fim para o começo
        firstOrLast = toRemove == 1 || toRemove == c.total;
        if(toRemove == c.total){ // última substring
            memmove(pNames + range[0], "-\0", 2);
        }
        else{ // outras
            size = strlen(pNames) - range[1] + 1;
            memmove(pNames + range[0], pNames + range[1] + firstOrLast, size);
        }

        c.total--;

        // realoca pNames
        // usa pTemp pra não perder a referência
        len = strlen(pNames);
        while(!(pTemp = realloc(pNames, strlen(pNames) + 1)));
        pNames = pTemp;

        printf("%d removido.\n", toRemove);
    }
    else
        printf("Agenda vazia.\n");
}

void listNames(){
    if(pNames){
        for (size_t i = 0, counter = 1; i < strlen(pNames) - 1; i++){
            if(!i) printf("1: %c", *(pNames));
            else if(*(pNames + i) == '-') printf("\n%ld: ", ++counter);
            else printf("%c", *(pNames + i));
        }
        printf("\n");
    }
    else
        printf("Agenda vazia.\n");
}

void clearScreen(){
    system(CLEAR);
    menu();
}