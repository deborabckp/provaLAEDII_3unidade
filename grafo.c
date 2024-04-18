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

    // Quesão 2
    
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

    //Questão 07

     // Criando e abrindo o arquivo de saída
     
    FILE *arquivo_complementar = fopen("grafo_complementar.txt", "w");
    if (arquivo_complementar == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return 1;
    }

    // Gerando o grafo complementar
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j && matrizadj[i][j] == 0) {
                // Se i e j não são o mesmo vértice e não são adjacentes no grafo original,
                // então eles devem ser adjacentes no grafo complementar
                fprintf(arquivo_complementar, "%d %d\n", i, j);
            }
        }
    }

    // Fechando o arquivo de saída
    fclose(arquivo_complementar);

    printf("Grafo complementar gerado com sucesso e salvo em 'grafo_complementar.txt'.\n"); 
    //fim da questão 07

    return 0;
}