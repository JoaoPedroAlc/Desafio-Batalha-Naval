
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TAMANHO 8
#define NAVIOS 5

// Símbolos do jogo
#define AGUA '~'
#define NAVIO 'N'
#define ACERTO 'X'
#define ERRO 'O'

typedef struct {
    char tabuleiro[TAMANHO][TAMANHO];
    char visivel[TAMANHO][TAMANHO];
    int naviosRestantes;
    int tentativas;
} Jogo;

void inicializarJogo(Jogo *jogo) {
    // Inicializar tabuleiros
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            jogo->tabuleiro[i][j] = AGUA;
            jogo->visivel[i][j] = AGUA;
        }
    }
    
    jogo->naviosRestantes = NAVIOS;
    jogo->tentativas = 0;
    
    // Posicionar navios aleatoriamente
    srand(time(NULL));
    int naviosPosicionados = 0;
    
    while (naviosPosicionados < NAVIOS) {
        int linha = rand() % TAMANHO;
        int coluna = rand() % TAMANHO;
        
        if (jogo->tabuleiro[linha][coluna] == AGUA) {
            jogo->tabuleiro[linha][coluna] = NAVIO;
            naviosPosicionados++;
        }
    }
}

void mostrarTabuleiro(Jogo *jogo) {
    printf("\n  ");
    for (int i = 0; i < TAMANHO; i++) {
        printf(" %d", i + 1);
    }
    printf("\n");
    
    for (int i = 0; i < TAMANHO; i++) {
        printf("%c ", 'A' + i);
        for (int j = 0; j < TAMANHO; j++) {
            printf(" %c", jogo->visivel[i][j]);
        }
        printf("\n");
    }
}

void mostrarLegenda() {
    printf("\n=== LEGENDA ===\n");
    printf("%c = Água\n", AGUA);
    printf("%c = Acerto!\n", ACERTO);
    printf("%c = Erro (água)\n", ERRO);
    printf("===============\n");
}

int lerCoordenadas(int *linha, int *coluna) {
    char entrada[10];
    printf("\nDigite as coordenadas (ex: A1, B5): ");
    
    if (scanf("%s", entrada) != 1) {
        return 0;
    }
    
    // Converter letra para número
    char letraLinha = toupper(entrada[0]);
    if (letraLinha < 'A' || letraLinha > 'A' + TAMANHO - 1) {
        return 0;
    }
    *linha = letraLinha - 'A';
    
    // Converter número da coluna
    int numColuna = atoi(&entrada[1]);
    if (numColuna < 1 || numColuna > TAMANHO) {
        return 0;
    }
    *coluna = numColuna - 1;
    
    return 1;
}

int fazerTiro(Jogo *jogo, int linha, int coluna) {
    // Verificar se já foi atirado nesta posição
    if (jogo->visivel[linha][coluna] != AGUA) {
        printf("Você já atirou nesta posição!\n");
        return 0;
    }
    
    jogo->tentativas++;
    
    if (jogo->tabuleiro[linha][coluna] == NAVIO) {
        jogo->visivel[linha][coluna] = ACERTO;
        jogo->naviosRestantes--;
        printf("\n🎯 ACERTOU! Navio atingido!\n");
        return 1;
    } else {
        jogo->visivel[linha][coluna] = ERRO;
        printf("\n💧 ERROU! Só água aqui...\n");
        return 0;
    }
}

void mostrarEstatisticas(Jogo *jogo) {
    printf("\n=== ESTATÍSTICAS ===\n");
    printf("Tentativas: %d\n", jogo->tentativas);
    printf("Navios restantes: %d\n", jogo->naviosRestantes);
    printf("==================\n");
}

void mostrarResultadoFinal(Jogo *jogo) {
    printf("\n🎉 PARABÉNS! Você afundou todos os navios!\n");
    printf("Total de tentativas: %d\n", jogo->tentativas);
    
    if (jogo->tentativas <= 10) {
        printf("⭐ EXCELENTE! Você é um almirante!\n");
    } else if (jogo->tentativas <= 20) {
        printf("⭐ BOM TRABALHO! Você é um capitão!\n");
    } else {
        printf("⭐ MISSÃO CUMPRIDA! Você é um marinheiro!\n");
    }
}

int main(void) {
    Jogo jogo;
    int linha, coluna;
    
    printf("🚢 ===== BATALHA NAVAL ===== 🚢\n");
    printf("Encontre e afunde %d navios no oceano!\n", NAVIOS);
    
    inicializarJogo(&jogo);
    mostrarLegenda();
    
    while (jogo.naviosRestantes > 0) {
        mostrarTabuleiro(&jogo);
        mostrarEstatisticas(&jogo);
        
        if (!lerCoordenadas(&linha, &coluna)) {
            printf("❌ Coordenadas inválidas! Use formato A1, B2, etc.\n");
            // Limpar buffer de entrada
            while (getchar() != '\n');
            continue;
        }
        
        fazerTiro(&jogo, linha, coluna);
    }
    
    mostrarTabuleiro(&jogo);
    mostrarResultadoFinal(&jogo);
    
    return 0;
}
