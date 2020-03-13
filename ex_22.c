#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//JOÃO PEDRO SILVEIRA
//FALTOU 85%

void menu();
void addName(char ** string);
void removeName();
void listNames(char ** string);

void main(){
    int option;
    char *names;
    while (1){
        menu();
        scanf("%d", &option);
        switch (option){
            case 1:
                addName(&names);
                break;
            case 2:
                removeName();
                break;
            case 3:
                listNames(&names);
                break;
            case 4:
                exit(0);
            default:
                printf("Opção %d não existe.", option);
        }
    }
}


void menu(){
    printf("\n----------------------\n");
    printf("1. Adicionar nome.\n");
    printf("2. Remover nome.\n");
    printf("3. Listar.\n");
    printf("4. Sair.\n");
    printf("\n----------------------\n");
}

void addName(char ** string){
    int count = 0;
    char c;
    getchar();
    *string = (char*)malloc(sizeof(char));

    while((c = getchar()) != '\n'){
        *string[count] = c;
        count++;
        printf("%d", count);
        *string = (char*)realloc(string, sizeof(char) * (count+1));
    }

}

void removeName(){
    printf("remove\n");
}

void listNames(char ** string){
    printf("%s\n", *string);
}