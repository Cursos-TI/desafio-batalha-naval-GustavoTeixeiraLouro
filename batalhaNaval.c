/*
 * Batalha Naval em C (nível aventureiro)
// Entrega de trabalho para graduação em ADS (Escola Estácio) 
 *
 * Regras solicitadas:
 * - Tabuleiro 10x10 (matriz de inteiros)
 * - Posicionar 4 navios; pelo menos 2 deles na diagonal
 * - Exibir a matriz completa, onde 0 = vazio e 3 = ocupado por navio
 *
 * Observações de implementação:
 * - Os navios têm comprimentos: 5, 4, 3, 3 (padrão comum), mas todos os
 *   quadrados ocupados recebem o valor 3, conforme especificação.
 * - Orientações suportadas: horizontal, vertical, diagonal ↘ (down-right),
 *   diagonal ↗ (up-right).
 * - O posicionamento é aleatório e sem sobreposição.
 *
    * Feito por Gustavo Teixeira Louro
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10
#define EMPTY 0
#define OCCUPIED 3

typedef enum {
    HORIZONTAL = 0,
    VERTICAL   = 1,
    DIAG_DOWN  = 2, // ↘ (linha+1, col+1)
    DIAG_UP    = 3  // ↗ (linha-1, col+1)
} Orient;

static void init_board(int b[N][N]) {
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            b[i][j] = EMPTY;
}

static int rand_int(int a, int b) { // inclusive
    return a + rand() % (b - a + 1);
}

static bool fits(const int b[N][N], int r, int c, int len, Orient o) {
    switch (o) {
        case HORIZONTAL:
            if (c + len > N) return false;
            for (int k = 0; k < len; ++k) if (b[r][c+k] != EMPTY) return false;
            return true;
        case VERTICAL:
            if (r + len > N) return false;
            for (int k = 0; k < len; ++k) if (b[r+k][c] != EMPTY) return false;
            return true;
        case DIAG_DOWN:
            if (r + len > N || c + len > N) return false;
            for (int k = 0; k < len; ++k) if (b[r+k][c+k] != EMPTY) return false;
            return true;
        case DIAG_UP:
            if (r - (len-1) < 0 || c + len > N) return false;
            for (int k = 0; k < len; ++k) if (b[r-k][c+k] != EMPTY) return false;
            return true;
        default: return false;
    }
}

static void place(int b[N][N], int r, int c, int len, Orient o) {
    switch (o) {
        case HORIZONTAL:
            for (int k = 0; k < len; ++k) b[r][c+k] = OCCUPIED;
            break;
        case VERTICAL:
            for (int k = 0; k < len; ++k) b[r+k][c] = OCCUPIED;
            break;
        case DIAG_DOWN:
            for (int k = 0; k < len; ++k) b[r+k][c+k] = OCCUPIED;
            break;
        case DIAG_UP:
            for (int k = 0; k < len; ++k) b[r-k][c+k] = OCCUPIED;
            break;
    }
}

static bool place_ship_random(int b[N][N], int len, Orient forced_orient, bool force) {
    // Se force==true, usa exatamente 'forced_orient'. Caso contrário, sorteia.
    int attempts = 0;
    while (attempts++ < 10000) {
        Orient o = force ? forced_orient : (Orient)rand_int(0, 3);
        int r = rand_int(0, N-1);
        int c = rand_int(0, N-1);
        if (fits(b, r, c, len, o)) {
            place(b, r, c, len, o);
            return true;
        }
    }
    return false;
}

static void print_board(const int b[N][N]) {
    // Cabeçalho de colunas
    printf("   ");
    for (int j = 0; j < N; ++j) printf("%2d ", j+1);
    printf("\n");
    // Linhas
    for (int i = 0; i < N; ++i) {
    printf("%2d ", i+1);    // Cabeçalho de linhas
    for (int j = 0; j < N; ++j) {
        printf("%2d ", b[i][j]);
    }
    printf("\n");
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    int board[N][N];
    init_board(board);

    // Comprimentos escolhidos: 5,4,3,3
    int sizes[4] = {5,4,3,3};

    // Precisamos de pelo menos 2 navios diagonais.
    // Colocamos explicitamente dois diagonais (um ↘ e um ↗),
    // e os outros dois navios com orientação aleatória.
    if (!place_ship_random(board, sizes[0], DIAG_DOWN, true)) {
        fprintf(stderr, "Falha ao posicionar navio diagonal (↘).\n");
        return 1;
    }
    if (!place_ship_random(board, sizes[1], DIAG_UP, true)) {
        fprintf(stderr, "Falha ao posicionar navio diagonal (↗).\n");
        return 1;
    }
    // Restantes (orientação aleatória entre horizontal/vertical/diagonais)
    for (int i = 2; i < 4; ++i) {
        if (!place_ship_random(board, sizes[i], HORIZONTAL, false)) {
            fprintf(stderr, "Falha ao posicionar navio %d.\n", i+1);
            return 1;
        }
    }

    printf("==== BATALHA NAVAL - NIVEL AVENTUREIRO ====\n");
    printf("Matriz 10x10 com 0=livre e 3=ocupado por navio.\n\n");
    print_board(board);

    return 0;
}
