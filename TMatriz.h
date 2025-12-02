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
