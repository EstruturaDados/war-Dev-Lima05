#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// --- Definição de constantes ---
#define MAX_TERRITORIO 30
#define COR_TROPAS 10

// --- Estrutura que representa um território ---
typedef struct {
    char nome[MAX_TERRITORIO];
    char cor[COR_TROPAS];
    int tropas;
} Territorio;

// --- Função para cadastrar os territórios ---
void cadastrarTerritorios(Territorio *mapa, int quantidade) {

    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    for (int i = 0; i < quantidade; i++) {

        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Cor do exercito: ");
        scanf("%9s", mapa[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);

        printf("\n");
    }
}

// --- Função para exibir os territórios ---
void exibirTerritorios(Territorio *mapa, int quantidade) {

    printf("\n=== MAPA ATUAL ===\n\n");

    for (int i = 0; i < quantidade; i++) {

        printf("TERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", mapa[i].nome);
        printf("- Dominado por: Exercito %s\n", mapa[i].cor);
        printf("- Tropas: %d\n\n", mapa[i].tropas);
    }
}

// --- Função de ataque ---
void atacar(Territorio *atacante, Territorio *defensor) {

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\n--- RESULTADO DA BATALHA ---\n");

    printf("O atacante %s rolou um dado e tirou: %d\n",
           atacante->nome, dadoAtacante);

    printf("O defensor %s rolou um dado e tirou: %d\n",
           defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {

        printf("\nVITORIA DO ATAQUE!\n");

        // O defensor muda de dono
        strcpy(defensor->cor, atacante->cor);

        // O defensor recebe metade das tropas do atacante
        defensor->tropas = atacante->tropas / 2;

        if (defensor->tropas < 1) {
            defensor->tropas = 1;
        }

        printf("O territorio %s foi conquistado!\n",
               defensor->nome);

    } else {

        printf("\nDEFESA BEM-SUCEDIDA!\n");

        if (atacante->tropas > 1) {
            atacante->tropas--;
        }

        printf("O atacante perdeu 1 tropa.\n");
    }
}

// --- Função para liberar memória ---
void liberarMemoria(Territorio *mapa) {
    free(mapa);
}

// --- Programa principal ---
int main() {

    srand(time(NULL));

    int quantidadeTerritorios;

    printf("Informe a quantidade de territorios: ");
    scanf("%d", &quantidadeTerritorios);

    // Alocação dinâmica de memória
    Territorio *territorios =
        (Territorio *)calloc(quantidadeTerritorios,
                             sizeof(Territorio));

    if (territorios == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    cadastrarTerritorios(territorios, quantidadeTerritorios);

    exibirTerritorios(territorios, quantidadeTerritorios);

    int atacanteEscolhido;
    int defensorEscolhido;

    printf("\n--- FASE DE ATAQUE ---\n");

    while (1) {

        printf("\nTerritorios disponiveis:\n");

        for (int i = 0; i < quantidadeTerritorios; i++) {
            printf("%d - %s (%s | %d tropas)\n",
                   i + 1,
                   territorios[i].nome,
                   territorios[i].cor,
                   territorios[i].tropas);
        }

        printf("\nEscolha o territorio atacante (1 a %d, ou 0 para sair): ",
               quantidadeTerritorios);

        scanf("%d", &atacanteEscolhido);

        if (atacanteEscolhido == 0) {
            break;
        }

        if (atacanteEscolhido < 1 ||
            atacanteEscolhido > quantidadeTerritorios) {

            printf("Territorio invalido!\n");
            continue;
        }

        printf("Escolha o territorio defensor (1 a %d): ",
               quantidadeTerritorios);

        scanf("%d", &defensorEscolhido);

        if (defensorEscolhido < 1 ||
            defensorEscolhido > quantidadeTerritorios) {

            printf("Territorio invalido!\n");
            continue;
        }

        if (atacanteEscolhido == defensorEscolhido) {
            printf("Um territorio nao pode atacar a si mesmo!\n");
            continue;
        }

        Territorio *atacante =
            &territorios[atacanteEscolhido - 1];

        Territorio *defensor =
            &territorios[defensorEscolhido - 1];

        if (strcmp(atacante->cor, defensor->cor) == 0) {

            printf("\nNao e permitido atacar um territorio da mesma cor!\n");
            continue;
        }

        atacar(atacante, defensor);

        printf("\n=== ESTADO ATUAL DOS TERRITORIOS ===\n");
        exibirTerritorios(territorios, quantidadeTerritorios);
    }

    liberarMemoria(territorios);

    printf("\nJogo encerrado e memoria liberada. Ate a proxima!\n");

    return 0;
}