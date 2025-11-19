#include <stdio.h>

#define TAM 10          // Tamanho do tabuleiro (10x10)
#define NAVIO 3         // Valor usado para representar um navio
#define TAM_NAVIO 3     // Tamanho fixo de cada navio

//--------------------------------------------------------------
// Função: inicializa o tabuleiro com zeros (água).
//--------------------------------------------------------------
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tab[i][j] = 0;
        }
    }
}

//--------------------------------------------------------------
// Função: verifica se o navio pode ser posicionado sem sair
//         do tabuleiro e sem encostar em outro.
//--------------------------------------------------------------
int podeColocar(int tab[TAM][TAM], int linha, int coluna, 
                int dx, int dy) {

    for (int i = 0; i < TAM_NAVIO; i++) {
        int x = linha + i * dx;
        int y = coluna + i * dy;

        // Verifica limites
        if (x < 0 || x >= TAM || y < 0 || y >= TAM) {
            return 0; // inválido
        }

        // Verifica sobreposição
        if (tab[x][y] == NAVIO) {
            return 0;
        }
    }
    return 1; // Pode colocar
}

//--------------------------------------------------------------
// Função: posiciona um navio no tabuleiro usando dx/dy
// dx,dy:
//  horizontal → (0,1)
//  vertical   → (1,0)
//  diagonal ↘ → (1,1)
//  diagonal ↗ → (-1,1)
//--------------------------------------------------------------
void colocarNavio(int tab[TAM][TAM], int linha, int coluna, 
                  int dx, int dy) {

    for (int i = 0; i < TAM_NAVIO; i++) {
        int x = linha + i * dx;
        int y = coluna + i * dy;
        tab[x][y] = NAVIO;
    }
}

//--------------------------------------------------------------
// Função: exibe o tabuleiro formatado.
//--------------------------------------------------------------
void exibirTabuleiro(int tab[TAM][TAM]) {
    printf("\n=== TABULEIRO BATALHA NAVAL 10x10 ===\n\n");

    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

//--------------------------------------------------------------
// Função principal
//--------------------------------------------------------------
int main() {

    int tabuleiro[TAM][TAM];

    inicializarTabuleiro(tabuleiro);

    // POSICIONAMENTO DOS 4 NAVIOS ----------------------------

    // Navio 1 → horizontal (linha 2, coluna 1)
    if (podeColocar(tabuleiro, 2, 1, 0, 1)) {
        colocarNavio(tabuleiro, 2, 1, 0, 1);
    }

    // Navio 2 → vertical (linha 5, coluna 6)
    if (podeColocar(tabuleiro, 5, 6, 1, 0)) {
        colocarNavio(tabuleiro, 5, 6, 1, 0);
    }

    // Navio 3 → diagonal ↘ (linha 0, coluna 0)
    if (podeColocar(tabuleiro, 0, 0, 1, 1)) {
        colocarNavio(tabuleiro, 0, 0, 1, 1);
    }

    // Navio 4 → diagonal ↗ (linha 9, coluna 2)
    if (podeColocar(tabuleiro, 9, 2, -1, 1)) {
        colocarNavio(tabuleiro, 9, 2, -1, 1);
    }

    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
