#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define tam 3771
int matriz[tam][tam];
// para ler o arquivo original
// Questão 1
void lerGrafoInicial(int *linha,int *col){
    int i,j;
    FILE *arq =fopen("dados_matriz.txt","r");
    fscanf(arq,"%d %d",linha,col);
    for(i = 0; i < *linha; i++) {
        for(j = 0; j < *col; j++) {
            fscanf(arq, "%d", &matriz[i][j]);
        }
    }
    fclose(arq);
}

void totalLinhaColuna(){
    int linha, col;
    lerGrafoInicial(&linha, &col);
    printf("total de linha = %d\ntotal de coluna = %d\n", linha, col);
}

void verticeMaiorGrau() {
    int i, j, max = -1, vertice = -1;
    int grau[tam] = {0};

    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            grau[i] += matriz[i][j];
        }
    }

    for(i = 0; i < tam; i++) {
        if(grau[i] > max) {
            max = grau[i];
            vertice = i;
        }
    }

    printf("O vertice de maior grau e %d com grau %d\n", vertice, max);
}
// fim da questão 1
// Questão 2 
int gVertice(int vertice, int n) {
    int i, grauVert = 0;
    for (i = 0; i < n; i++) {
        if (matriz[vertice][i]) {
            grauVert++;
        }
    }
    return grauVert;
}

void gravarGrausVertices(int n) {
    int i;
    FILE *arquivo = fopen("dados_grafos_graus.txt","w");
    for(i=0; i<n; i++){
        int grauVert = gVertice(i,n);
        fprintf(arquivo, "%d %d\n", i, grauVert);
    }
    fclose(arquivo);
}
// Fim da questão 2

// questão 3
void verIsolado(){
    int i, j;
    int eIsolado;

    for(i = 0; i < tam; i++) {
        eIsolado = 1;
        for(j = 0; j < tam; j++) {
            if(matriz[i][j] != 0) {
                eIsolado = 0;
                break;
            }
        }
        if(eIsolado) {
            printf("O vertice %d e isolado.\n", i);
            return;
        }
    }
    printf("Nao existe vertices isolado nesse grafo\n");
}
// fim da questão 3

// Questão 4

void sumidouro(int n, int m, int matriz[tam][tam]){
    int i, aux[n],j;
    int temSumidouro = 0;
    for(i=0;i<n;i++){
        aux[i] = 0;
        for(j=0;j<m;j++){
            aux[i] += matriz[i][j];
        }
        if(aux[i] == 0){
            printf("%d = sumidouro\n",i);
            temSumidouro = 1;
            return;
        }
    }
    printf("Nao tem sumidouro.\n");
}
// fim da Questão 4

//questão 5
void font(int n, int m, int matriz[tam][tam]){
    int i, aux[n],j;
    int fonte = 0;
    for(j=0;j<m;j++){
        aux[j] = 0;
        for(i=0;i<n;i++){
            aux[j] += matriz[i][j];
        }
        if(aux[j] == 0){
            printf("%d = vertice fonte\n",j);
            fonte = 1;
            return;
        }
    }
    printf("Nao tem vertice fonte.\n");
}
//fim da função questão 5

// questão 6
void grauEmissao(int n) {
    FILE *arquivo = fopen("dados_grafos_emissao.txt", "w");
   

    for (int i = 0; i < n; i++) {
        int grauEmissao = 0;
        for (int j = 0; j < n; j++) {
            grauEmissao += matriz[i][j];
        }
        fprintf(arquivo, "%d %d\n", i, grauEmissao); 
    }

    fclose(arquivo);
}


void grauRecepcao(int n) {
    FILE *arquivo = fopen("dados_grafos_recepcao.txt", "w");
    

    for (int i = 0; i < n; i++) {
        int grauRecepcao = 0;
        for (int j = 0; j < n; j++) {
            grauRecepcao += matriz[j][i];
        }
        fprintf(arquivo, "%d %d\n", i, grauRecepcao); 
    }

    fclose(arquivo);
}

// fim da questao 6

// questão 7

void grafoComplemetar(int linha, int coluna, int matriz[tam][tam]){
    FILE *arquivo = fopen("dados_grafo_complementar.txt", "w");

    fprintf(arquivo, "%d %d\n", linha, coluna);

    for (int i = 0; i < linha; i++){
        for (int j = 0; j < coluna; j++){
            if (matriz[i][j] == 0){
                fprintf(arquivo, "%d ", 1);
            }else{
                fprintf(arquivo, "%d ", 0);
            }
        }
        fprintf(arquivo, "\n");
    }
    fclose(arquivo);
}

//fim questão 7

// Questão 8: Inverter a direção das arestas
void inverterGrafo(int n, const char *arquivoSaida) {
    FILE *arquivo = fopen(arquivoSaida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para gravaçao.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == 1) {
                fprintf(arquivo, "%d %d\n", j, i); // Inverte a direção
            }
        }
    }

    fclose(arquivo);
}
// fim da questão 8

// questão 10

void verticesMultiplosDeCinco(int n) {
    FILE *arquivo = fopen("dados_grafo_gerador.txt", "w");
   

    for (int i = 0; i < n; i++) {
        if (i % 5 == 0) { 
            fprintf(arquivo, "%d\n", i); 
        }
    }

    fclose(arquivo);
}

// fim da questão 10

//questão 11
// Função para verificar se um conjunto de vértices forma um clique
bool formaClique(int vertices[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = i + 1; j < tamanho; j++) {
            if (matriz[vertices[i]][vertices[j]] == 0) {
                return false;
            }
        }
    }
    return true;
}

// Função recursiva do algoritmo de Bron-Kerbosch
void bronKerbosch(int* r, int* p, int* x, int rSize, int pSize, int xSize, int* maiorClique, int* tamanhoMaiorClique) {
    if (pSize == 0 && xSize == 0) {
        if (rSize > *tamanhoMaiorClique) {
            *tamanhoMaiorClique = rSize;
            for (int i = 0; i < rSize; i++) {
                maiorClique[i] = r[i];
            }
        }
        return;
    }

    for (int i = 0; i < pSize; i++) {
        int v = p[i];
        int* rNovo = (int*)malloc((rSize + 1) * sizeof(int));
        int* pNovo = (int*)malloc(pSize * sizeof(int));
        int* xNovo = (int*)malloc(xSize * sizeof(int));

        for (int j = 0; j < rSize; j++) {
            rNovo[j] = r[j];
        }
        rNovo[rSize] = v;

        int pNovoSize = 0;
        int xNovoSize = 0;

        for (int j = 0; j < pSize; j++) {
            if (matriz[v][p[j]] == 1) {
                pNovo[pNovoSize++] = p[j];
            }
        }

        for (int j = 0; j < xSize; j++) {
            if (matriz[v][x[j]] == 1) {
                xNovo[xNovoSize++] = x[j];
            }
        }

        bronKerbosch(rNovo, pNovo, xNovo, rSize + 1, pNovoSize, xNovoSize, maiorClique, tamanhoMaiorClique);

        free(rNovo);
        free(pNovo);
        free(xNovo);

        p[i] = p[pSize - 1];
        x[xSize++] = v;
        pSize--;
    }
}

// Função para encontrar o maior clique em um grafo
void encontrarMaiorClique(int n) {
    int* maiorClique = (int*)malloc(n * sizeof(int));
    int tamanhoMaiorClique = 0;

    int* r = (int*)malloc(n * sizeof(int));
    int* p = (int*)malloc(n * sizeof(int));
    int* x = (int*)malloc(n * sizeof(int));

    int rSize = 0;
    int pSize = n;
    int xSize = 0;

    for (int i = 0; i < n; i++) {
        p[i] = i;
    }

    bronKerbosch(r, p, x, rSize, pSize, xSize, maiorClique, &tamanhoMaiorClique);

    printf("O maior clique tem tamanho %d e inclui os vertices:\n", tamanhoMaiorClique);
    for (int i = 0; i < tamanhoMaiorClique; i++) {
        printf("%d ", maiorClique[i]);
    }
    printf("\n");

    free(maiorClique);
    free(r);
    free(p);
    free(x);
}

//fim da questão 11

int main(){
    int linha,coluna;
    // questão 1
    lerGrafoInicial(&linha,&coluna);
    totalLinhaColuna();
    verticeMaiorGrau();
    // Fim da Questão 1
    
    // Questão 2
    gravarGrausVertices(linha);
    // Fim da Questão 2

    // questão 3
    verIsolado();
     //  fim da questão 3

     // questão 4
    sumidouro(linha,coluna, matriz);
     //  fim da questão 4

    //  questão 5
    font(linha,coluna,matriz);
    // fim da questão 5

    // questão 6
    grauEmissao(linha);
    grauRecepcao(linha);
    // fim questão 6

    // questão 7
    grafoComplemetar(linha,coluna,matriz);
    // fim questão 7

    // questão 8
    inverterGrafo(linha,"dados_grafos_invertido.txt");
    // fim questão 8

    // questão 10
 verticesMultiplosDeCinco(linha);
 // fim da questão 10

 // questão 11
 encontrarMaiorClique(linha);
 // fim da questão 11

    return 0;
}
