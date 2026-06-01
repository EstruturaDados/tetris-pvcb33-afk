#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5

// Estrutura da peça
typedef struct {
    int id;
    char tipo;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

int proximoId = 1;

// Gera uma peça aleatória
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.id = proximoId++;
    p.tipo = tipos[rand() % 4];

    return p;
}

// Inicializa a fila
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

// Enfileira uma peça
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
        printf("Fila cheia!\n");
        return;
    }

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

// Remove uma peça da fila
Peca dequeue(Fila *f) {
    Peca removida = {-1, ' '};

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return removida;
    }

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return removida;
}

// Exibe a fila
void mostrarFila(Fila *f) {
    printf("\n===== FILA DE PECAS =====\n");

    if (filaVazia(f)) {
        printf("Fila vazia!\n");
        return;
    }

    int pos = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        printf("%d. ID: %d | Tipo: %c\n",
               i + 1,
               f->itens[pos].id,
               f->itens[pos].tipo);

        pos = (pos + 1) % TAM_FILA;
    }

    printf("=========================\n");
}

int main() {
    srand(time(NULL));

    Fila fila;
    inicializarFila(&fila);

    // Inicializa a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        mostrarFila(&fila);

        printf("\n=== TETRIS STACK ===\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("3 - Visualizar fila\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                Peca removida = dequeue(&fila);

                if (removida.id != -1) {
                    printf("\nPeca jogada -> ID: %d | Tipo: %c\n",
                           removida.id,
                           removida.tipo);

                    // Insere automaticamente uma nova peça
                    enqueue(&fila, gerarPeca());

                    printf("Nova peca adicionada automaticamente!\n");
                }
                break;
            }

            case 2:
                if (!filaCheia(&fila)) {
                    enqueue(&fila, gerarPeca());
                    printf("Nova peca inserida!\n");
                } else {
                    printf("A fila ja possui 5 pecas.\n");
                }
                break;

            case 3:
                mostrarFila(&fila);
                break;

            case 0:
                printf("Encerrando o jogo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}