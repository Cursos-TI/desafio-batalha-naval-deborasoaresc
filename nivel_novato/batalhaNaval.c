#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.

#include <stdio.h>

int main() {

    // -------------------------------
    // 1. DECLARAÇÃO DO TABULEIRO 10x10
    // -------------------------------
    int tabuleiro[10][10];

    // Inicializando tudo com 0 (água)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // -------------------------------
    // 2. NAVIOS (Vetores unidimensionais)
    // -------------------------------
    // Cada navio tem tamanho fixo 3
    int navio_horizontal[3] = {3, 3, 3};
    int navio_vertical[3] = {3, 3, 3};

    // -------------------------------
    // 3. POSICIONAMENTO NO TABULEIRO
    // -------------------------------

    // Coordenadas iniciais escolhidas (fixas para este nível)
    int linha_horizontal = 2;
    int coluna_horizontal = 1;

    int linha_vertical = 5;
    int coluna_vertical = 7;

    // --- Validando posições horizontais ---
    // Navio HORIZONTAL ocupa: (linha, col), (linha, col+1), (linha, col+2)
    if (coluna_horizontal + 2 < 10) {
        for (int i = 0; i < 3; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = navio_horizontal[i];
        }
    } else {
        printf("Erro: navio horizontal não cabe no tabuleiro.\n");
        return 1;
    }

    // --- Validando posições verticais ---
    // Navio VERTICAL ocupa: (linha, col), (linha+1, col), (linha+2, col)
    if (linha_vertical + 2 < 10) {
        for (int i = 0; i < 3; i++) {
            // Verifica se já existe navio na posição (evitar sobreposição)
            if (tabuleiro[linha_vertical + i][coluna_vertical] != 0) {
                printf("Erro: os navios iriam se sobrepor!\n");
                return 1;
            }
            tabuleiro[linha_vertical + i][coluna_vertical] = navio_vertical[i];
        }
    } else {
        printf("Erro: navio vertical não cabe no tabuleiro.\n");
        return 1;
    }

    // -------------------------------
    // 4. EXIBINDO O TABULEIRO COMPLETO
    // -------------------------------
    printf("\n===== TABULEIRO BATALHA NAVAL (10x10) =====\n\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}

