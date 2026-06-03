#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TERRITORIO 30
#define MAX_COR        10
#define TAM_MISSAO    100

typedef struct {
    char nome[MAX_TERRITORIO];
    char cor[MAX_COR];
    int  tropas;
} Territorio;

void pausar() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("\nPressione Enter para continuar...");
    getchar();
}

// Le os dados de cada territorio
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    printf("\n=== CADASTRO DE TERRITORIOS ===\n");

    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d\n", i + 1);
        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);
        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// Exibe o estado atual do mapa
void exibirMapa(Territorio *mapa, int quantidade) {

    printf("\n=== MAPA ATUAL ===\n\n");

    for (int i = 0; i < quantidade; i++) {
        printf("%d - %s\n",         i + 1, mapa[i].nome);
        printf("    Cor:    %s\n",   mapa[i].cor);
        printf("    Tropas: %d\n\n", mapa[i].tropas);
    }
}

// Sorteia uma missao e copia para o buffer do jogador
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

// Exibe a missao sorteada
void exibirMissao(char missao[]) {
    printf("\n====================================\n");
    printf("  MISSAO SORTEADA\n");
    printf("  %s\n", missao);
    printf("====================================\n");
}

// Verifica se a condicao da missao foi atingida
int verificarMissao(char *missao, Territorio *mapa, int tamanho) {

    int totalTropas       = 0;
    int territoriosFortes = 0;
    int territoriosFracos = 0;

    for (int i = 0; i < tamanho; i++) {
        totalTropas += mapa[i].tropas;
        if (mapa[i].tropas >= 3) territoriosFortes++;
        if (mapa[i].tropas <= 1) territoriosFracos++;
    }

    if (strcmp(missao, "Possuir 10 tropas") == 0)
        return totalTropas >= 10;

    if (strcmp(missao, "Possuir 15 tropas") == 0)
        return totalTropas >= 15;

    if (strcmp(missao, "Ter 2 territorios fortes") == 0)
        return territoriosFortes >= 2;

    if (strcmp(missao, "Ter 3 territorios fortes") == 0)
        return territoriosFortes >= 3;

    if (strcmp(missao, "Possuir 2 territorios fracos") == 0)
        return territoriosFracos >= 2;

    return 0;
}

// Simula o combate entre dois territorios com dados
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("Ataque (%s): %d | Defesa (%s): %d\n",
           atacante->nome, dadoAtacante,
           defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("VITORIA DO ATAQUE! %s foi conquistado.\n", defensor->nome);

        strcpy(defensor->cor, atacante->cor);

        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) tropasTransferidas = 1;

        defensor->tropas  = tropasTransferidas;
        atacante->tropas -= tropasTransferidas;

        if (atacante->tropas < 1) atacante->tropas = 1;

    } else {
        if (atacante->tropas > 1) atacante->tropas--;
        printf("VITORIA DA DEFESA! O atacante perdeu 1 tropa.\n");
    }

    pausar();
}

// Libera a memoria alocada dinamicamente
void liberarMemoria(Territorio *mapa, char *missaoJogador) {
    free(mapa);
    free(missaoJogador);
}

int main() {

    srand(time(NULL));

    char *missoes[] = {
        "Possuir 10 tropas",
        "Possuir 15 tropas",
        "Ter 2 territorios fortes",
        "Ter 3 territorios fortes",
        "Possuir 2 territorios fracos"
    };

    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    int quantidadeTerritorios;
    printf("Informe a quantidade de territorios: ");
    scanf("%d", &quantidadeTerritorios);

    Territorio *territorios =
        (Territorio *)calloc(quantidadeTerritorios, sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    char *missaoJogador = (char *)malloc(TAM_MISSAO * sizeof(char));

    if (missaoJogador == NULL) {
        printf("Erro ao alocar memoria!\n");
        free(territorios);
        return 1;
    }

    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    cadastrarTerritorios(territorios, quantidadeTerritorios);
    exibirMapa(territorios, quantidadeTerritorios);

    int atacanteEscolhido;
    int defensorEscolhido;

    printf("\n--- FASE DE ATAQUE ---\n");

    while (1) {

        printf("\nEscolha o territorio atacante (1 a %d, ou 0 para sair): ",
               quantidadeTerritorios);
        scanf("%d", &atacanteEscolhido);

        if (atacanteEscolhido == 0) break;

        printf("Escolha o territorio defensor (1 a %d): ",
               quantidadeTerritorios);
        scanf("%d", &defensorEscolhido);

        if (atacanteEscolhido < 1 || atacanteEscolhido > quantidadeTerritorios ||
            defensorEscolhido < 1 || defensorEscolhido > quantidadeTerritorios) {
            printf("Territorio invalido!\n");
            continue;
        }

        if (atacanteEscolhido == defensorEscolhido) {
            printf("Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }

        Territorio *atacante = &territorios[atacanteEscolhido - 1];
        Territorio *defensor = &territorios[defensorEscolhido - 1];

        if (strcmp(atacante->cor, defensor->cor) == 0) {
            printf("Nao e permitido atacar territorios da mesma cor!\n");
            continue;
        }

        atacar(atacante, defensor);

        if (verificarMissao(missaoJogador, territorios, quantidadeTerritorios)) {
            printf("\n====================================\n");
            printf("  MISSAO CUMPRIDA!\n");
            printf("  Missao: %s\n", missaoJogador);
            printf("  VOCE VENCEU O JOGO!\n");
            printf("====================================\n");
            break;
        }

        exibirMapa(territorios, quantidadeTerritorios);
    }

    liberarMemoria(territorios, missaoJogador);
    printf("\nJogo encerrado e memoria liberada.\n");

    return 0;
}