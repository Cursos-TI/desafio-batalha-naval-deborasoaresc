#include <stdio.h>

#define TAM 10        // tamanho do tabuleiro
#define NAVIO 3       // valor que representa navio no tabuleiro
#define HABILIDADE 5  // valor que representa área de habilidade ao exibir
#define TAM_H 5       // tamanho das matrizes de habilidade (5x5)
#define TAM_NAVIO 3   // tamanho fixo dos navios

// Inicializa o tabuleiro com 0 (água)
void inicializarTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tab[i][j] = 0;
}

// Função helper: tenta posicionar navio com direção dx,dy (i.e., (linha + k*dx, coluna + k*dy))
// Retorna 1 se colocado com sucesso, 0 caso contrário (fora ou sobreposição)
int posicionarNavio(int tab[TAM][TAM], int linha, int coluna, int dx, int dy) {
    // validação de limites e sobreposição
    for (int k = 0; k < TAM_NAVIO; k++) {
        int x = linha + k * dx;
        int y = coluna + k * dy;
        if (x < 0 || x >= TAM || y < 0 || y >= TAM) return 0; // fora
        if (tab[x][y] == NAVIO) return 0; // sobreposição
    }
    // colocar
    for (int k = 0; k < TAM_NAVIO; k++) {
        int x = linha + k * dx;
        int y = coluna + k * dy;
        tab[x][y] = NAVIO;
    }
    return 1;
}

// Gera matriz de habilidade "cone" (TAM_H x TAM_H) em cone apontando para baixo.
// A origem da matriz é o topo central (linha 0) e a área se amplia nas linhas abaixo.
// Representamos com 1 onde afeta e 0 onde não afeta.
void gerarCone(int cone[TAM_H][TAM_H]) {
    int centro = TAM_H / 2; // por exemplo para 5x5 centro = 2
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            // condicionais: em cada linha i, colunas do centro-i até centro+i são afetadas
            // mas não permitimos colunas fora do range 0..TAM_H-1
            if (j >= centro - i && j <= centro + i)
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Gera matriz "cruz": linha central e coluna central têm 1 (formato de cruz).
void gerarCruz(int cruz[TAM_H][TAM_H]) {
    int centro = TAM_H / 2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (i == centro || j == centro) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }
}

// Gera matriz "octaedro" vista frontal — forma de losango (diamante).
// Usamos a distância Manhattan <= centro como critério para formar o losango.
void gerarOctaedro(int oct[TAM_H][TAM_H]) {
    int centro = TAM_H / 2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            int dist = abs(i - centro) + abs(j - centro);
            if (dist <= centro) oct[i][j] = 1;
            else oct[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade (hmat) no overlay global (overlay) centrando-a em (origLinha, origColuna)
// A matriz de habilidade tem dimensão TAM_H x TAM_H e índice central = TAM_H/2 => corresponde ao ponto de origem.
// Valida limites: só escreve em overlay quando coordenadas dentro do tabuleiro.
// overlay é matriz de 0/1 que indica presença de efeito de habilidade naquele tabuleiro.
void aplicarHabilidadeNoOverlay(int overlay[TAM][TAM], int hmat[TAM_H][TAM_H], int origLinha, int origColuna) {
    int origemCentro = TAM_H / 2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (hmat[i][j] == 1) {
                // calcular coordenada no tabuleiro onde essa célula da habilidade vai cair
                int x = origLinha + (i - origemCentro);
                int y = origColuna + (j - origemCentro);
                // valida limites
                if (x >= 0 && x < TAM && y >= 0 && y < TAM) {
                    overlay[x][y] = 1; // marca que ali existe efeito de habilidade
                }
            }
        }
    }
}

// Exibe o tabuleiro com prioridade visual: NAVIO (3) aparece sobre overlay,
// caso contrário, se overlay=1 exibimos HABILIDADE (5), senão exibimos água (0).
void exibirTabuleiroComHabilidades(int tab[TAM][TAM], int overlay[TAM][TAM]) {
    printf("\n=== TABULEIRO (0=agua, 3=navio, 5=habilidade) ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tab[i][j] == NAVIO) {
                printf("%d ", NAVIO);
            } else if (overlay[i][j] == 1) {
                printf("%d ", HABILIDADE);
            } else {
                printf("%d ", 0);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    int tabuleiro[TAM][TAM];
    int overlay[TAM][TAM]; // guarda 1 quando alguma habilidade afeta a célula

    // Inicializações
    inicializarTabuleiro(tabuleiro);
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            overlay[i][j] = 0;

    // Posicionamento de navios (4 navios de tamanho 3) - reuso das escolhas anteriores
    // Navio horizontal: linha 2, col 1  (0-indexado)
    if (!posicionarNavio(tabuleiro, 2, 1, 0, 1)) {
        printf("Erro ao posicionar navio horizontal.\n");
    }
    // Navio vertical: linha 5, col 6
    if (!posicionarNavio(tabuleiro, 5, 6, 1, 0)) {
        printf("Erro ao posicionar navio vertical.\n");
    }
    // Navio diagonal ↘ (linha 0,col 0)
    if (!posicionarNavio(tabuleiro, 0, 0, 1, 1)) {
        printf("Erro ao posicionar navio diagonal ↘.\n");
    }
    // Navio diagonal ↗ (linha 9,col 2) -> direction dx=-1,dy=1
    // nosso posicionarNavio só aceita dx,dy inteiros; ele funciona com dx=-1
    if (!posicionarNavio(tabuleiro, 9, 2, -1, 1)) {
        printf("Erro ao posicionar navio diagonal ↗.\n");
    }

    // 1) Gerar as matrizes de habilidade (5x5) usando loops aninhados e condicionais
    int cone[TAM_H][TAM_H];
    int cruz[TAM_H][TAM_H];
    int octaedro[TAM_H][TAM_H];

    gerarCone(cone);        // cone apontando para baixo (origem no topo do bloco 5x5)
    gerarCruz(cruz);        // cruz com centro no bloque 5x5
    gerarOctaedro(octaedro);// losango usando Manhattan <= centro

    // 2) Definir pontos de origem no tabuleiro (linha,coluna) para cada habilidade
    // (0-indexed). Você pode alterar estes valores conforme desejar.
    int origemConeLinha = 1, origemConeColuna = 4;    // cone com topo aproximadamente na linha 1
    int origemCruzLinha = 6, origemCruzColuna = 3;    // cruz com centro na posição (6,3)
    int origemOctLinha = 4, origemOctColuna = 8;      // octaedro centrado em (4,8)

    // 3) Aplicar habilidades sobre o overlay (validação de limites feita internamente)
    aplicarHabilidadeNoOverlay(overlay, cone, origemConeLinha,    origemConeColuna);
    aplicarHabilidadeNoOverlay(overlay, cruz, origemCruzLinha,    origemCruzColuna);
    aplicarHabilidadeNoOverlay(overlay, octaedro, origemOctLinha, origemOctColuna);

    // 4) Exibir MATRIZ DAS HABILIDADES (opcional, para debug/visualização)
    // Exibir o cone 5x5
    printf("Matriz - Cone (1=afeta,0=nao):\n");
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            printf("%d ", cone[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Exibir a cruz 5x5
    printf("Matriz - Cruz (1=afeta,0=nao):\n");
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            printf("%d ", cruz[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // Exibir o octaedro 5x5
    printf("Matriz - Octaedro (1=afeta,0=nao):\n");
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            printf("%d ", octaedro[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    // 5) Exibir o tabuleiro final com marcação das áreas de habilidade
    exibirTabuleiroComHabilidades(tabuleiro, overlay);

    return 0;
}
