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

// questão 3
int sumidouro(int vertice, int n){
    int i, soma = 0;
    for(i=0;i<n;i++){
        soma += matrizadj[vertice][i];
    }
    // para verificar se é igual a zero
    return soma == 0;
}
int main(){
int n,m, i,j;
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

    // questão 4
    for(i=0;i<n;i++){
        if(sumidouro(i,n)){
            printf("O vertice %d é um sumidouro.\n", i);
        }else{
            printf("não tem sumidouro");
        }
    }
    //fim da questão 4
    return 0;
}