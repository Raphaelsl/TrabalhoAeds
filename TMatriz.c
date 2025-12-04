#include "TMatriz.h"
TMatriz* Inicia(int m, int n){
    TMatriz* pMatriz = (TMatriz*) malloc(sizeof(TMatriz));
    pMatriz->numColuna = n;
    pMatriz->numLinha = m;
    pMatriz->primeiro = (TCelula*) malloc(sizeof(TCelula));
    pMatriz->primeiro->direita =  pMatriz->primeiro;
    pMatriz->primeiro->abaixo =  pMatriz->primeiro;
    //ponteiro auxiliar
    TCelula* ultimo = pMatriz->primeiro;
    for(int i = 1; i<=n;i++){
        TCelula* novaCelula = (TCelula*) malloc(sizeof(TCelula));
        novaCelula->linha = -1;
        novaCelula->coluna = i;
        novaCelula->abaixo = novaCelula;
        //encadeamento
        ultimo->direita = novaCelula;
        novaCelula->direita = pMatriz->primeiro;
        ultimo = novaCelula;
    }
    ultimo = pMatriz->primeiro;
    for(int j = 1; j<=m ;j++){
        TCelula* novaCelula = (TCelula*) malloc(sizeof(TCelula));
        novaCelula->linha = j;
        novaCelula->coluna = -1;
        novaCelula->direita = novaCelula;
        //encadeamento
        ultimo->abaixo = novaCelula;
        novaCelula->abaixo = pMatriz->primeiro;
        ultimo = novaCelula;
    }
    return pMatriz;
}

//Buscar Linha Cabeça pra Inserir
TCelula* obterCabecaLinha(TMatriz* pMatriz, int x) {
    TCelula* atualLinha = pMatriz->primeiro;
    for(int i = 0; i < x; i++ ){
        //atualiza para onde "abaixo" aponta até encontrar a linha certa
        atualLinha = atualLinha->abaixo;
    }
    return atualLinha;
}
//Buscar Coluna Cabeça pra inserir
TCelula* obterCabecaColuna(TMatriz* pMatriz, int y){
    TCelula* atualColuna = pMatriz->primeiro;
     for(int j = 0; j < y; j++ ){
        //atualiza para onde "direita" aponta até encontrar a coluna certa
        atualColuna = atualColuna->direita;
    }
    return atualColuna;
}

int Insere(TMatriz* pMatriz, int x, int y, double valor){
    //receber cabeças Lin/Col
    TCelula* cabecaLinha = obterCabecaLinha(pMatriz, x);
    TCelula* cabecaColuna = obterCabecaColuna(pMatriz, y);

    //criar cabecas auxiliares para encontar a Lin/Col anterior que quero inserir a novaCelula
    TCelula* celulaAuxiliarLinha = cabecaLinha;
        while(celulaAuxiliarLinha->direita->coluna != -1 && celulaAuxiliarLinha->direita->coluna < y){
        celulaAuxiliarLinha = celulaAuxiliarLinha->direita;
    }

    TCelula* celulaAuxiliarColuna = cabecaColuna;
        while(celulaAuxiliarColuna->abaixo->linha != -1 && celulaAuxiliarColuna->abaixo->linha< x){
        celulaAuxiliarColuna = celulaAuxiliarColuna->abaixo;
    }

    //Inserindo a celula
    if(celulaAuxiliarLinha->direita->coluna == y && celulaAuxiliarLinha->direita->coluna != -1){
        //caso ja exista a celula, apenas trocando o valor
        celulaAuxiliarLinha->direita->valor = valor;
    }
    else{
        //caso nao exista, tem que ser criada e passar seus "parametros"
        TCelula* novaCelula = (TCelula*) malloc(sizeof(TCelula));
        novaCelula->linha = x;
        novaCelula->coluna = y;
        novaCelula->valor = valor;

        //inserindo a novaCelula na Matriz
        novaCelula->direita = celulaAuxiliarLinha->direita;
        celulaAuxiliarLinha->direita = novaCelula;
        novaCelula->abaixo = celulaAuxiliarColuna->abaixo;
        celulaAuxiliarColuna->abaixo = novaCelula;
    }
    return 1;
}
TMatriz* LeMatriz(){
    int m = 0;//linha
    int n = 0;//coluna
    int i = 0;
    int j = 0;
    double valor = 0;
    scanf("%d", &m);
    scanf("%d", &n);
    TMatriz* pMatriz = Inicia(m,n);
    //verificando quando scan consegue ler(retorna 1 a cada numero), logo para inserir preciso ler 3 valores
    while(scanf("%d %d %lf", &i, &j,&valor) == 3){
        //verificando se o elemento é diferente de 0
        if(valor != 0.0){
        Insere(pMatriz, i, j, valor);
        }
    }
    return pMatriz;
}
void ImprimeMatriz(TMatriz* pMatriz){
    //percorrendo a Matriz
    for(int i = 1; i <= pMatriz->numLinha; i++){
        //celula auxiliar para encontrar meu elemento percorrendoa Matriz
        TCelula* cabecaLinha = obterCabecaLinha(pMatriz, i);
        TCelula* celulaAuxiliarLinha = cabecaLinha->direita;
        for(int j = 1; j <= pMatriz->numColuna; j++){
            //verifica se estou na coluna j e se nao estou em uma colunaCabeça
            if(celulaAuxiliarLinha->coluna == j && celulaAuxiliarLinha->coluna != -1){
                //printando o elemento e avançando minha celula auxiliar
                printf("%.1lf ", celulaAuxiliarLinha->valor);
                celulaAuxiliarLinha = celulaAuxiliarLinha->direita;
            }
            else{
                //caso nao tenha elemento
                printf("0.0 ");
            }
        }
        printf("\n");
    }
}
void ApagaMatriz(TMatriz* pMatriz){
    for(int i = 0; i < pMatriz->numLinha; i++){
        TCelula* cabecaLinha = obterCabecaLinha(pMatriz, i);
        TCelula* atual = cabecaLinha->direita;
        TCelula* prox;
        while(atual->coluna != -1 ){
            prox = atual->direita;
            free(atual);
            atual = prox;
        }
        cabecaLinha->direita = cabecaLinha;
    }
}
TMatriz* SomaMatriz(TMatriz* pMatrizA, TMatriz* pMatrizB){
    printf("Somando");
    if(pMatrizA->numColuna != pMatrizB->numColuna || pMatrizA->numLinha != pMatrizB->numLinha){
        return 0;
    }
        TMatriz* pMatrizC = Inicia(pMatrizA->numLinha,pMatrizA->numColuna);
        for(int i = 1; i < pMatrizA->numLinha; i++){
            TCelula* atualA = obterCabecaLinha(pMatrizA, i)->direita;
            TCelula* atualB = obterCabecaLinha(pMatrizB, i)->direita;
            while(atualA->coluna!=-1 || atualB->coluna != -1){
                if((atualA->coluna != -1)&&(atualB->coluna == -1 || atualA->coluna < atualB->coluna)){
                    Insere(pMatrizC,i,atualA->coluna,atualA->valor);
                    atualA = atualA->direita;
                }
                else if((atualB->coluna != -1)&&(atualA->coluna == -1 || atualA->coluna > atualB->coluna)){
                    Insere(pMatrizC,i,atualB->coluna,atualB->valor);
                    atualB = atualB->direita;
                }
                else{
                    double valorTotal = atualA->valor + atualB->valor;
                    if(valorTotal != 0.0){
                    Insere(pMatrizC, i, atualA->coluna,valorTotal);
                    }
                    atualA = atualA->direita;
                    atualB = atualB->direita;
                }
            }
        }
    return pMatrizC;
}
