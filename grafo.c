#include <stdio.h>
#include <stdlib.h>

#define tam 3771
// questão 2
int matrizadj[tam][tam];
int gVertice( int vertice, int n){
    int i, grauVert = 0;
    for (i = 0; i < n; i++) {
        if (matrizadj[vertice][i]) {
            grauVert++;
        }
    }
    return grauVert;
}
// fim da funcção da questão 2
// questao 3
void verIsolado(int n){
    int i, isolado = 0;
    for(i = 0;i< n; i++){
        if (gVertice(i,n) == 0){
            printf("vertice %d esta isolado\n");
            isolado = 1;
        }
    }
    if(!isolado){
        printf("nao existe vertice isolados.\n");
    }
}
// fim da funcão da questao 3
// questão 4

void sumidouro(int n, int m, int **matriz){
    int i, aux[n],j;
    int temSumidouro = 0; // Variável de sinalização
    for(i=0;i<n;i++){
        aux[i] = 0;
        for(j=0;j<m;j++){
            aux[i] += matriz[i][j];
        }
        if(aux[i] == 0){
            printf("%d = sumidouro\n",i);
            temSumidouro = 1; 
            break;
        }
    }
    if(!temSumidouro){
        printf("Não tem sumidouro.\n");
    }
}

//questão 5
void font(int n, int m, int **matriz){
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
            break;
        }
    }
    if(!fonte){
        printf("Não tem vertice fonte.\n");
    }
}


//fim da função questão 5
int main(){
int n,m, i,j,**matriz;
int *grauVertice;
int a, maiorGrau = 0,verticeMaxGrau;
    
    FILE *arq = fopen("dados_matriz.txt","r");
    fscanf(arq,"%d %d", &n,&m);
    printf("n = %d\nm = %d\n",n,m);
    // como são acumaladores precisa que inicialize com valor zero
    grauVertice = calloc(n,sizeof(int));
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            fscanf(arq, "%d", &a);
           // preencher a matriz para depois verificar o grau, faz parte da questão 2
            matrizadj[i][j] = a; 
            //parte da questão2
            grauVertice[i] += a;
        }
        if(grauVertice[i] > maiorGrau){
            maiorGrau = grauVertice[i];
            verticeMaxGrau = i;
        }
    }
    printf("O vertice com o maior grau e o vertice %d com grau %d\n", verticeMaxGrau, maiorGrau);

    free(grauVertice);

    // Questão 2
    
    FILE *arquivo = fopen("dados_grafos_graus.txt","w");
    for(i=0;i<n;i++){
        int grauVert = gVertice(i,n);
         fprintf(arquivo, "%d %d\n", i, grauVert);
    }
    fclose(arquivo);
    // fim da questao 2
    // questao 3 chamando a função
    verIsolado(n);
    // fim da questão 3
    // questão 4
    matriz = (int **)malloc(n * sizeof(int *));
    for(i = 0; i < n; i++)
    matriz[i] = (int *)malloc(m * sizeof(int));
    sumidouro(n,m,matriz);
    for(i = 0; i < n; i++)
        free(matriz[i]);
    free(matriz);
    //fim da questão 4
    //questão 5
    matriz = (int **)malloc(n * sizeof(int *));
    for(i=0;i<n;i++)
    matriz[i] = (int *)malloc(m * sizeof(int));
    font(n,m,matriz);
    for(i = 0; i < n; i++)
    free(matriz[i]);
    //fim da questão 5

//questão 6
void grausEmissaoRecepcao(int n, int **matriz) {
    int i, j;
    int *grau_emissao = (int *)calloc(n, sizeof(int));
    int *grau_recepcao = (int *)calloc(n, sizeof(int));

    // Calcular graus de emissão e recepção
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (matriz[i][j] == 1) {
                grau_emissao[i]++; // Aresta saindo de i
                grau_recepcao[j]++; // Aresta chegando a j
            }
        }
    }

    // Gravar graus de emissão em um arquivo
    FILE *arquivo_emissao = fopen("dados_grafo_emissao.txt", "w");
    if (arquivo_emissao == NULL) {
        printf("Erro ao criar o arquivo de emissão.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(arquivo_emissao, "%d %d\n", i, grau_emissao[i]);
    }

    fclose(arquivo_emissao);

    // Gravar graus de recepção em um arquivo
    FILE *arquivo_recepcao = fopen("dados_grafos_recepcao.txt", "w");
    if (arquivo_recepcao == NULL) {
        printf("Erro ao criar o arquivo de recepção.\n");
        return;
    }

    for (i = 0; i < n; i++) {
        fprintf(arquivo_recepcao, "%d %d\n", i, grau_recepcao[i]);
    }

    fclose(arquivo_recepcao);

    free(grau_emissao);
    free(grau_recepcao);
}

//fim da questão 6

    //Questão 07
#define MAX_VERTICES 3771 // Defina o número máximo de vértices conforme necessário

int main();
    FILE *arquivo_entrada = fopen("dados_matriz.txt", "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    // Ler a matriz de adjacência do arquivo
    fscanf(arquivo_entrada, "%d", &n);
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(arquivo_entrada, "%d", &matrizadj[i][j]);
        }
    }

    fclose(arquivo_entrada);

    FILE *arquivo_complementar = fopen("dados_grafo_complementar.txt", "w");
    if (arquivo_complementar == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Gerando o grafo complementar
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) { // Evitar processamento duplicado
            if (matrizadj[i][j] == 0) {
                // Se i e j não são adjacentes no grafo original,
                // então eles devem ser adjacentes no grafo complementar
                fprintf(arquivo_complementar, "%d %d\n", i, j);
            }
        }
    }

    // Fechando o arquivo de saída
    fclose(arquivo_complementar);

    printf("Grafo complementar gerado com sucesso e salvo em 'dados_grafo_complementar.txt'.\n");
   //Fim da questao 07
    return 0;
}

//questão 8 

void lerMatrizAdjacencia(int n, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(arquivo, "%d", &matrizadj[i][j]);
        }
    }

    fclose(arquivo);
}

// Função para inverter a direção das arestas
void inverterGrafo(int n, const char *arquivoSaida) {
    FILE *arquivo = fopen(arquivoSaida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para gravação.\n", arquivoSaida);
        exit(1);
    }

    // Inverter a matriz de adjacência
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrizadj[i][j] == 1) {
                fprintf(arquivo, "%d %d\n", j, i); // Inverte a direção
            }
        }
    }

    fclose(arquivo);
}

int main() {
    int n; // Número de vértices
    
    // Ler número de vértices do arquivo
    FILE *arquivoEntrada = fopen("dados_matriz.txt", "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    fscanf(arquivoEntrada, "%d", &n);

    fclose(arquivoEntrada);

    // Carregar matriz de adjacência
    lerMatrizAdjacencia(n, "dados_matriz.txt");

    // Inverter a direção das arestas e salvar no novo arquivo
    inverterGrafo(n, "dados_grafos_invertido.txt");

    return 0;
}
