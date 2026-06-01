#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM_FILA 5
#define TAM_PILHA 3

// Estrutura da peça
typedef struct {
    int id;
    char tipo;
} Peca;

// Fila Circular
typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int quantidade;
} Fila;

// Pilha
typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

int proximoId = 1;

// Gera peça aleatória
Peca gerarPeca() {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    p.id = proximoId++;
    p.tipo = tipos[rand() % 4];

    return p;
}

// ================= FILA =================

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->quantidade = 0;
}

int filaVazia(Fila *f) {
    return f->quantidade == 0;
}

int filaCheia(Fila *f) {
    return f->quantidade == TAM_FILA;
}

void enqueue(Fila *f, Peca p) {
    if (filaCheia(f))
        return;

    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->quantidade++;
}

Peca dequeue(Fila *f) {
    Peca removida = {-1, ' '};

    if (filaVazia(f))
        return removida;

    removida = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->quantidade--;

    return removida;
}

void mostrarFila(Fila *f) {
    printf("\n===== FILA DE PECAS =====\n");

    int pos = f->inicio;

    for (int i = 0; i < f->quantidade; i++) {
        printf("%d. ID:%d Tipo:%c\n",
               i + 1,
               f->itens[pos].id,
               f->itens[pos].tipo);

        pos = (pos + 1) % TAM_FILA;
    }
}

// ================= PILHA =================

void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

int pilhaCheia(Pilha *p) {
    return p->topo == TAM_PILHA - 1;
}

void push(Pilha *p, Peca peca) {
    if (pilhaCheia(p)) {
        printf("\nPilha de reserva cheia!\n");
        return;
    }

    p->topo++;
    p->itens[p->topo] = peca;
}

Peca pop(Pilha *p) {
    Peca removida = {-1, ' '};

    if (pilhaVazia(p)) {
        printf("\nNenhuma peca reservada!\n");
        return removida;
    }

    removida = p->itens[p->topo];
    p->topo--;

    return removida;
}

void mostrarPilha(Pilha *p) {
    printf("\n===== PILHA DE RESERVA =====\n");

    if (pilhaVazia(p)) {
        printf("Vazia\n");
        return;
    }

    for (int i = p->topo; i >= 0; i--) {
        printf("ID:%d Tipo:%c\n",
               p->itens[i].id,
               p->itens[i].tipo);
    }
}

// ================= MAIN =================

int main() {

    srand(time(NULL));

    Fila fila;
    Pilha pilha;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preenche a fila com 5 peças
    for (int i = 0; i < TAM_FILA; i++) {
        enqueue(&fila, gerarPeca());
    }

    int opcao;

    do {
        mostrarFila(&fila);
        mostrarPilha(&pilha);

        printf("\n===== TETRIS STACK =====\n");
        printf("1 - Jogar peca\n");
        printf("2 - Reservar peca\n");
        printf("3 - Usar peca reservada\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {

        case 1: {
            Peca jogada = dequeue(&fila);

            printf("\nPeca jogada -> ID:%d Tipo:%c\n",
                   jogada.id,
                   jogada.tipo);

            enqueue(&fila, gerarPeca());
            break;
        }

        case 2: {
            if (pilhaCheia(&pilha)) {
                printf("\nReserva cheia!\n");
            } else {

                Peca reservada = dequeue(&fila);
                push(&pilha, reservada);

                printf("\nPeca reservada -> ID:%d Tipo:%c\n",
                       reservada.id,
                       reservada.tipo);

                enqueue(&fila, gerarPeca());
            }
            break;
        }

        case 3: {
            Peca usada = pop(&pilha);

            if (usada.id != -1) {
                printf("\nPeca reservada utilizada -> ID:%d Tipo:%c\n",
                       usada.id,
                       usada.tipo);
            }
            break;
        }

        case 0:
            printf("\nEncerrando jogo...\n");
            break;

        default:
            printf("\nOpcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}