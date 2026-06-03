#include <stdio.h>
#include <string.h>

// --- Definição Variáveis Globais
#define MAX_TERRITORIO 30 // quantidade de caracteres
#define COR_TROPAS 10

// --- Estrutura que representa um território
struct Territorio {
    char nome[MAX_TERRITORIO];
    char cor[COR_TROPAS];
    int tropas;
};

// --- MAIN ---
int main() {

    //  Vetor para armazenar os 5 territórios
    struct Territorio territorios[5];

    // Cadastro dos territórios
    printf("=== CADASTRO DE TERRITORIOS ===\n\n");

    for (int i = 0; i < 5; i++) {

        printf("Territorio %d\n", i + 1);

        printf("Nome: ");
        scanf(" %29[^\n]", territorios[i].nome);

        printf("Cor do exercito: ");
        scanf(" %9s", territorios[i].cor);

        printf("Quantidade de tropas: ");
        scanf("%d", &territorios[i].tropas);

        printf("\n");
    }

    // Exibição dos territórios cadastrados
    printf("\n=== TERRITORIOS CADASTRADOS ===\n\n");

    for (int i = 0; i < 5; i++) {

        printf("TERRITORIO %d:\n", i + 1);
        printf("- Nome: %s\n", territorios[i].nome);
        printf("- Dominado por: Exercito %s\n", territorios[i].cor);
        printf("- Tropas: %d\n\n", territorios[i].tropas);
    }

    return 0;
}