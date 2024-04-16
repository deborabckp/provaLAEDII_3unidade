#include <stdio.h>
#include <stdlib.h>

#define tam 3771
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
            grauVertice[i] += a;
        }
        if(grauVertice[i] > maiorGrau){
            maiorGrau = grauVertice[i];
            verticeMaxGrau = i;
        }
    }

    printf("O vertice com o maior grau e o vertice %d com grau %d\n", verticeMaxGrau, maiorGrau);

    free(grauVertice);
    
    return 0;
}