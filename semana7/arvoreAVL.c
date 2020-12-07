#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool PRINT_ROTACAO = false;

// macro para testar o malloc
#define testMalloc(ptr) if (!(ptr)) {fprintf(stderr, "Falha no malloc.\n"); exit(EXIT_FAILURE);}

// struct nó
typedef struct Nodo {
    int chave;
    struct Nodo *pEsq, *pDir;
} Nodo;


// funções árvore
bool insere(Nodo **raiz, int chave);
int altura(Nodo *raiz);
bool freeArvore(Nodo *raiz);
bool verificaAVL(Nodo *raiz);

// balanceamento
int fb(Nodo *raiz); // fator de balanceamento
void rotEsquerda(Nodo **raiz);
void rotDireita(Nodo **raiz);
bool balanEsquerda(Nodo **raiz);
bool balanDireita(Nodo **raiz);
bool balanceamento(Nodo **raiz);

// funções auxiliares
Nodo *nodo(int chave);
void printNos(Nodo *no);
void printArvore(Nodo *raiz);


int main () {
    Nodo *raiz = NULL;
    int n;

    // PRIMEIRO CENÁRIO --------------------------------------
    printf("Número de nós: ");
    scanf("%d", &n);

    srand(time(0));
    
    while (n--) insere(&raiz, rand());
    
    printf("\n-------- PRIMEIRO CENÁRIO --------\n");
    printf("Árvore aleatória\n");
    printf("Altura: %d\n", altura(raiz));
    printf("Fator de balancemanto: %d\n", fb(raiz));
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("----------------------------------\n");

    freeArvore(raiz);
    raiz = NULL;

    // SEGUNDO CENÁRIO ---------------------------------------
    int no;
    printf("\n--------- SEGUNDO CENÁRIO --------\n");
    printf("Testando os casos da resposta marcada como aceita no link:\n");
    printf("https://stackoverflow.com/questions/3955680/how-to-check-if-my-avl-tree-implementation-is-correct\n\n");

    printf("\n-- Creating a new tree.\n");

    printf("-- Inserting the first value.\n");
    no = 20;
    insere(&raiz, no);
    printf("Nó inserido: %d\n", no);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------

    printf("\n-- Inserting a bigger value.\n");
    no = 40;
    insere(&raiz, no);
    printf("Nó inserido: %d\n", no);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------

    printf("\n-- Inserting a smaller value.\n");
    no = 15;
    insere(&raiz, no);
    printf("Nó inserido: %d\n", no);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------

    PRINT_ROTACAO = true;

    printf("\n-- Inserting a value that causes LL Rotation (rotação simples para esquerda).\n");
    
    printf("Nós inseridos: %d, %d\n", 50, 55);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    printf("Rotações: ");
    
    insere(&raiz, 50);
    insere(&raiz, 55);
    printf("\n");
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------

    printf("\n-- Rotação simples para direita (RR).\n");
    printf("Nós inseridos: %d, %d\n", 10, 6);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    printf("Rotações: ");
    
    insere(&raiz, 10);
    insere(&raiz, 6);
    printf("\n");
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------

    printf("\n-- Rotação dupla para esquerda (LR).\n");
    printf("Nós inseridos: %d, %d\n", 8, 7);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    printf("Rotações: ");
    insere(&raiz, 8);
    insere(&raiz, 7);
    printf("\n");
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    // ----------------------------------------------------------------
    
    printf("\n-- Rotação dupla para direita (RL).\n");
    printf("Nós inseridos: %d, %d\n", 30, 35);
    printf("Fator de balanceamento: %d\n", fb(raiz));
    printf("Altura: %d\n", altura(raiz));
    printf("Rotações: ");
    insere(&raiz, 30);
    insere(&raiz, 35);
    printf("\n");
    if (verificaAVL(raiz)) printf("Validação: É árvore AVL.\n");
    else printf("Validação: Não é árvore AVL.\n");
    printf("Árvore: ");
    printArvore(raiz);

    printf("\n----------------------------------\n");
    freeArvore(raiz);
    raiz = NULL;
    return EXIT_SUCCESS;
}

// funções árvore
bool insere(Nodo **raiz, int chave) {
    if (!*raiz) {
        *raiz = nodo(chave);
        return true;
    }
    else if (chave < (*raiz)->chave) { // insere na esquerda
        if (insere(&(*raiz)->pEsq, chave)) {
            if (balanceamento(raiz)) return false;
            else return true;
        }
    }
    else if (chave > (*raiz)->chave) { // insere na direita
        if (insere(&(*raiz)->pDir, chave)) {
            if (balanceamento(raiz)) return false;
            else return true;
        }
    }
    return false; // valor já existe
}


int altura(Nodo *raiz) {
    if (!raiz) return 0;
    int esq = altura(raiz->pEsq);
    int dir = altura(raiz->pDir);

    if (esq > dir) return esq + 1;
    else return dir + 1;
}


bool freeArvore(Nodo *raiz) {
    if (raiz) {
        freeArvore(raiz->pEsq);
        freeArvore(raiz->pDir);
        free(raiz);
        return true;
    }
    return false;
}


bool verificaAVL(Nodo *raiz) {
    if (!raiz) return true;
    if (!verificaAVL(raiz->pEsq)) return false;
    if (!verificaAVL(raiz->pDir)) return true;

    int f = fb(raiz);

    if (( f > 1 ) || ( f < -1)) return false;
    else return true;
}


// balanceamento
int fb(Nodo *raiz) {
    if (!raiz) return 0;
    return altura(raiz->pEsq) - altura(raiz->pDir);
}


void rotEsquerda(Nodo **raiz) {
    Nodo *temp;
    temp = (*raiz)->pDir;
    (*raiz)->pDir = temp->pEsq;
    temp->pEsq = (*raiz);
    (*raiz) = temp;
}


void rotDireita(Nodo **raiz) {

    Nodo *temp;
    temp = (*raiz)->pEsq;
    (*raiz)->pEsq = temp->pDir;
    temp->pDir = (*raiz);
    (*raiz) = temp;
}


bool balanEsquerda(Nodo **raiz) {
    int fbe = fb((*raiz)->pEsq);
    if (fbe > 0) {
        if (PRINT_ROTACAO) printf("RR ");
        rotDireita(raiz);
        return true;
    }
    else if (fbe < 0) { // dupla direita
        if (PRINT_ROTACAO) printf("RL ");
        rotEsquerda(&((*raiz)->pEsq));
        rotDireita(raiz);
        return true;
    }
    return false;
}


bool balanDireita(Nodo **raiz) {
    int fbd = fb((*raiz)->pDir);
    if (fbd < 0) { // simples
        if (PRINT_ROTACAO) printf("LL ");
        rotEsquerda(raiz);
        return true;
    }
    else if (fbd > 0) { // dupla esquerda
        if (PRINT_ROTACAO) printf("LR ");
        rotDireita(&((*raiz)->pDir));
        rotEsquerda(raiz);
        return true;
    }
    return false;
}


bool balanceamento(Nodo **raiz) {
    int f = fb(*raiz);
    if (f > 1) return balanEsquerda(raiz);
    else if (f < -1) return balanDireita(raiz);
    else return false;
}


// auxiliar
Nodo *nodo(int chave) {
    Nodo *pTemp;
    pTemp = malloc(sizeof(Nodo));
    testMalloc(pTemp);
    pTemp->pDir = pTemp->pEsq = NULL;
    pTemp->chave = chave;
    return pTemp;
}


void printNos(Nodo *no) {
    // representação da árvore com parêteses (preordem)
    if (!no) return;
    printf("(%d", no->chave);
    printNos(no->pEsq);
    printNos(no->pDir);
    printf(")");
}


void printArvore(Nodo *raiz) {
    printNos(raiz);
    printf("\n");
}