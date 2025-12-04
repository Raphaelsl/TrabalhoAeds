
#include <stdio.h>
#include <stdlib.h>

typedef struct TCelula{
    struct TCelula* direita;
    struct TCelula* abaixo;
    int coluna,linha;
    double valor;
}TCelula;
typedef struct TMatriz{
    TCelula* primeiro;
    int numColuna,numLinha;

}TMatriz;
TMatriz* Inicia(int m, int n);
int Insere(TMatriz* pMatriz, int x, int y, double valor);
TMatriz* LeMatriz();
void ImprimeMatriz(TMatriz* pMatriz);
TMatriz* SomaMatriz(TMatriz* pMatrizA, TMatriz* pMatrizB);
void ApagaMatriz(TMatriz* pMatriz);

