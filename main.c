#include <stdio.h>
#include "TMatriz.h"

int main() {
/*
    printf("-- Teste da Matriz --\n");
    printf("Cole os dados abaixo (4 4, depois as triplas):\n");
    /* Dados Colados:
        4 4
        1 1 50.0
        2 1 10.0
        2 3 20.0
        4 1 -30.0
        4 3 -60.0
        4 4 5.0 f

    //le/cria
    TMatriz* A = LeMatriz();

    //imprimindo
    if (A != NULL) {
        printf("\nMatriz Lida:\n");
        ImprimeMatriz(A);
    } else {
        printf("Erro ao ler matriz\n");
    }

*/
    printf("=== O GRANDE TESTE DA SOMA ===\n");
    TMatriz* A = Inicia(4, 4);
    TMatriz* B = Inicia(4, 4);

    Insere(A, 1, 1, 10.0);
    Insere(A, 1, 2, 20.0);
    Insere(B, 1, 2, 5.0);
    Insere(B, 1, 3, 30.0);
    Insere(A, 2, 3, 50.0);
    Insere(B, 2, 3, -50.0);
    Insere(B, 2, 1, 99.0);
    Insere(A, 3, 1, 77.0);

    printf("\nMatriz A:\n");
    ImprimeMatriz(A);
    printf("\nMatriz B:\n");
    ImprimeMatriz(B);

    printf("\n--- Executando SomaMatriz(A, B) ---\n");
    TMatriz* C = SomaMatriz(A, B);

    if (C == NULL) {
        printf("ERRO: Dimensoes incompativeis ou erro de memoria.\n");
    } else {
        printf("\nMatriz C (Resultado):\n");
        ImprimeMatriz(C);
    }
    return 0;
}
