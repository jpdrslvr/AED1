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
char *pNomes;
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
        while( getchar() != '\n' );
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
    char *pTemp = NULL, *tempName = NULL;

    while(!tempName){
        tempName = (char *) malloc(MAX);
    }

    printf("Nome: ");
    fgets(tempName, MAX, stdin);
    tempName[strcspn(tempName, "\n")] = 0;

    if(pNomes){
        while(!pTemp){
            pTemp = (char *) realloc(pNomes, strlen(pNomes) + strlen(tempName) + 2); // + 2 -> \0 e separador
        }
        pNomes = pTemp;
        strcat(pNomes, tempName);
    }
    else{
        while(!pNomes)
            pNomes = (char *) malloc(strlen(tempName) + 2);
        strcat(pNomes, tempName);
    }
    
    strcat(pNomes, "-"); // separador
    c.total++;

    free(tempName);
}

void removeName(){
    int toRemove, range[] = {-1, -1}, counter = 1, first = 0;
    size_t size;
    if(pNomes){
        listNames();
        printf("Remover: ");
        scanf("%d", &toRemove);

        for (size_t i = 0; i < strlen(pNomes) - 1; i++){
            if(*(pNomes + i) == '-'){
                counter++;
            }
            if(counter == toRemove){
                range[0] = i;
                counter++;
            }
            else if(counter > toRemove && *(pNomes + i) == '-'){
                range[1] = i;
                break;
            }
        }
        first = toRemove == 1 ? 1 : 0;
        size = strlen(pNomes) - range[1] + 1;
        memmove(pNomes + range[0], pNomes + range[1] + first, size);
        if(toRemove == c.total) strcat(pNomes, "-");
        c.total--;
        printf("%d removido.", toRemove);
    }
    else
        printf("Agenda vazia.\n");
}

void listNames(){
    if(pNomes){
        for (size_t i = 0, counter = 1; i < strlen(pNomes) - 1; i++){
            if(!i) printf("1: %c", *(pNomes));
            else if(*(pNomes + i) == '-') printf("\n%ld: ", ++counter);
            else printf("%c", *(pNomes + i));
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