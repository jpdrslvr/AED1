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

// structs
struct contact{
    char *pContacts;
    char *pTemp; // pointer temp pra evitar erros de realloc
    char tempString[MAX];
    char *token;
    char *start, *end;
    int total;
    int first;
    int option;
    int toRemove;
    // contadores e flags
    size_t i, j, counter, spaces, found;

} typedef Agenda;


// funções
void addContact(Agenda *p); //1
void removeContact(Agenda *p); //2
void findContact(Agenda *p); //3
void listContacts(Agenda *p); //4

void readString(char *prompt, char *string, char *sep);
void clearScreen();
void menu();

void main(){
    void *pBuffer;
    pBuffer = malloc(sizeof(Agenda));
    Agenda *c;
    c = pBuffer;

    c->first = 1;
    c->total = 0;
    while(1){
        if(c->first){
            // printf("%d", c->first);
            // pBuffer = malloc(sizeof(Agenda));
            // c = pBuffer;
            clearScreen();
            c->first = 0;
        }

        scanf("%d", &c->option);
        while(getchar() != '\n');
        switch (c->option){
        case 1:
            clearScreen();
            addContact(c);
            break;
        case 2:
            clearScreen();
            // printf("removeName();\n");
            removeContact(c);
            break;
        case 3:
            clearScreen();
            findContact(c);
            break;
        case 4:
            clearScreen();
            listContacts(c);
            break;
        case 5:
            free(c->pContacts);
            free(c);
            exit(0);
            break;
        default:
            break;
        }
    }

}

void addContact(Agenda *p){
    printf("Novo contato\n");
    
    // NOME
    readString("Nome: ", p->tempString, ",\0");
    if(p->pContacts){
        while(!(p->pTemp))
            p->pTemp = realloc(p->pContacts, strlen(p->pContacts) + strlen(p->tempString) + 1);
        p->pContacts = p->pTemp;
    }
    else{
        while(!(p->pContacts))
            p->pContacts = malloc(strlen(p->tempString) + 1);
    }
    strcat(p->pContacts, p->tempString);
    p->pTemp = NULL;

    // TELEFONE
    readString("Telefone: ", p->tempString, ";\0");
    while(!(p->pTemp))
        p->pTemp = realloc(p->pContacts, strlen(p->pContacts) + strlen(p->tempString) + 1);
    p->pContacts = p->pTemp;
    strcat(p->pContacts, p->tempString);
    p->pTemp = NULL;
    p->total++;
}

void removeContact(Agenda *p){
    if(p->pContacts){
        p->found = 0;
        readString("Contato: ", p->tempString, NULL);
        
        if(atoi(p->tempString) && atoi(p->tempString) <= p->total && atoi(p->tempString) > 0){ //int
            p->toRemove = atoi(p->tempString);
            p->counter = 1;
            for(p->i = 0; p->i < strlen(p->pContacts); p->i++){
                if(*(p->pContacts + p->i) == ';'){
                p->counter++;
                }
                if(p->counter == p->toRemove){
                    p->start = p->pContacts + p->i + 1;
                    p->counter++;
                }
                else if(p->counter > p->toRemove && *(p->pContacts + p->i) == ';'){
                    p->end = p->pContacts + p->i;
                    p->found = 1;
                    break;
                }
            }
        }
        else if(strcmp(p->tempString, "0")){ // string
            while(!(p->pTemp = malloc(strlen(p->pContacts) + 1)));
            strcpy(p->pTemp, p->pContacts);
            p->token = strtok(p->pTemp, ",;");

            for(p->i = 0; p->token; p->i++){
                if(strcmp(p->token, p->tempString) == 0){
                    p->start = strstr(p->pContacts, p->token);
                    p->token = strtok(NULL, ",;");
                    p->end = strstr(p->pContacts, p->token) + strlen(p->token);
                    p->found = 1;
                    break;
                }
                p->token = strtok(NULL, ",;");
            }            
        }
        else{
            printf("Não encontrado.\n");
        }
        if(p->found){
            if(p->total == 1){
                free(p->pContacts);
                p->pContacts = NULL;
            }
            else{
                // printf("start: %s\tend: %s\n", p->start, p->end);
                memmove(p->start, p->end + 1, strlen(p->end));
                p->pTemp = NULL;
                while(!(p->pTemp = realloc(p->pContacts, strlen(p->pContacts) + 1)));
                p->pContacts = p->pTemp;
            }
            p->total--;
            printf("Contato \"%s\" removido.\n", p->tempString);
        }
        p->pTemp = p->token = p->start = p->end = NULL;
    }
    else{
        printf("Agenda vazia.\n");
    }
}

void findContact(Agenda *p){
    if(p->pContacts){
        p->found = 0;
        while(!(p->pTemp = malloc(strlen(p->pContacts) + 1)));
        strcpy(p->pTemp, p->pContacts);
        readString("Nome: ", p->tempString, "\0");
        p->token = strtok(p->pTemp, ",;");

        for(p->i = 0, p->counter = 1; p->token; p->i++){
            if(p->i % 2) p->counter++;
            if(!strcmp(p->token, p->tempString)){
                p->found = 1;
                printf("%ld: %s\t", p->counter, p->token);
                p->token = strtok(NULL, ",;");
                printf("%s\n", p->token);
                
            }
            p->token = strtok(NULL, ",;");
        }
        if(!(p->found)) printf("Não encontrado.\n");

        p->pTemp = NULL;
    }
    else{
        printf("Agenda vazia.\n");
    }
    
}

void listContacts(Agenda *p){
    if(p->pContacts){
        printf("Nome                      Telefone\n");
        printf("----------------------------------\n");
        p->spaces = 25;
        for (p->i = 0, p->counter = 1; p->i < strlen(p->pContacts) - 1; p->i++){
            if(*(p->pContacts + p->i) != ',') p->spaces--;
            else{
                p->i++;
                for (p->j = 0; p->j < p->spaces; p->j++){
                    printf(" ");
                }
            }
            if(!(p->i)) printf("1: %c", *(p->pContacts));
            else if(*(p->pContacts + p->i) == ';'){
                printf("\n%ld: ", ++(p->counter));
                if(p->counter >= 10)
                    p->spaces = 24;
                else
                    p->spaces = 25;

            }
            else printf("%c", *(p->pContacts + p->i));
        }
        printf("\n");
    }
    else{
        printf("Agenda vazia.\n");
    }
}


void menu() {
    printf("----------------------------------\n");
    printf("Selecione a opção:\n");
    printf("1 Incluir\n");
    printf("2 Apagar\n");
    printf("3 Buscar\n");
    printf("4 Listar\n");
    printf("5 Sair\n");
    printf("----------------------------------\n");
}

void clearScreen(){
    system(CLEAR);
    menu();
}

void readString(char *prompt, char *string, char *sep){
    printf("%s", prompt);
    fgets(string, MAX, stdin);
    if(sep) memmove(string + strlen(string) - 1, sep, 2);
    else memmove(string + strlen(string) - 1, "\0", 1);
}