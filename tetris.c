// Tetris Stack - tema3
// Nível novato

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAM_FILA 5 //tamanho fixo da fila

typedef struct { //estrutura da peça
    int id;
    char tipo;
} Peca;

typedef struct {
    Peca fila[TAM_FILA]; //estrutura da fila circular
    int inicio;
    int fim;
    int quantidade;
} Fila;

void inicializarFila(Fila *f) { //inicializa a fila vazia
    f->inicio = 0;
    f->fim = -1;
    f->quantidade = 0;
}

int estaVazia(Fila *f) { //verifica se a fila está vazia
    return f->quantidade == 0;
}

int estaCheia(Fila *f) { //verifica se a fila está cheia
    return f->quantidade == TAM_FILA;
}

Peca gerarPeca(int id) {
    char tipos[] = {'I', 'O', 'T', 'L'};
    Peca nova;
    nova.id = id;
    nova.tipo = tipos[rand() % 4]; // escolhe aleatoriamente o tipo
    return nova;
}

void enfileirar(Fila *f, Peca p) { // Insere uma nova peça no final da fila (enqueue)
    if (estaCheia(f)) {
        printf("\nA fila está cheia! Não é possível inserir mais peças.\n");
        return;
    }
    f->fim = (f->fim + 1) % TAM_FILA;
    f->fila[f->fim] = p;
    f->quantidade++;
}

Peca desenfileirar(Fila *f) { // Remove a peça da frente da fila (dequeue)
    Peca removida = {-1, '?'};
    if (estaVazia(f)) {
        printf("\nA fila está vazia! Nenhuma peça para jogar.\n");
        return removida;
    }
    removida = f->fila[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;
    return removida;
}

void mostrarFila(Fila *f) { // Exibe o estado atual da fila
    printf("\nFila atual de peças:\n");
    if (estaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    int i, idx;
    for (i = 0; i < f->quantidade; i++) {
        idx = (f->inicio + i) % TAM_FILA;
        printf("Posição %d → Peça ID:%d | Tipo:%c\n", i + 1, f->fila[idx].id, f->fila[idx].tipo);
    }
}

int main() {
    Fila fila;
    int opcao;
    int contadorID = 1;
    Peca p;
    srand(time(NULL));

    inicializarFila(&fila);

    // Inicializa a fila com 5 peças automáticas
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(contadorID++));
    }

    do {
        printf("\n====== TETRIS STACK - NÍVEL NOVATO ======\n");
        printf("1. Jogar peça (remover da frente)\n");
        printf("2. Inserir nova peça\n");
        printf("3. Visualizar fila\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                p = desenfileirar(&fila);
                if (p.id != -1)
                    printf("Peça jogada: ID:%d | Tipo:%c\n", p.id, p.tipo);
                break;
            case 2:
                if (!estaCheia(&fila)) {
                    enfileirar(&fila, gerarPeca(contadorID++));
                    printf("Nova peça adicionada à fila!\n");
                } else {
                    printf("Não é possível adicionar, a fila está cheia!\n");
                }
                break;
            case 3:
                mostrarFila(&fila);
                break;
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}