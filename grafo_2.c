#include <stdio.h>
#include <stdlib.h>

#define TAM 3771

// Questão 2: Calcular o grau de um vértice
int matrizadj[TAM][TAM];

int gVertice(int vertice, int n) {
    int i, grauVert = 0;
    for (i = 0; i < n; i++) {
        if (matrizadj[vertice][i]) {
            grauVert++;
        }
    }
    return grauVert;
}

// Questão 3: Verificar vértices isolados
void verIsolado(int n) {
    int i, isolado = 0;
    for (i = 0; i < n; i++) {
        if (gVertice(i, n) == 0) {
            printf("Vértice %d está isolado\n", i);
            isolado = 1;
        }
    }
    if (!isolado) {
        printf("Não existe vértice isolado.\n");
    }
}

// Questão 4: Verificar se há um sumidouro
void sumidouro(int n, int m, int **matriz) {
    int i, aux[n], j;
    int temSumidouro = 0; // Variável de sinalização
    for (i = 0; i < n; i++) {
        aux[i] = 0;
        for (j = 0; j < m; j++) {
            aux[i] += matriz[i][j];
        }
        if (aux[i] == 0) {
            printf("%d = sumidouro\n", i);
            temSumidouro = 1;
        }
    }
    if (!temSumidouro) {
        printf("Não há sumidouro.\n");
    }
}

// Questão 5: Verificar se há um vértice fonte
void font(int n, int m, int **matriz) {
    int i, aux[n], j;
    int fonte = 0;
    for (j = 0; j < m; j++) {
        aux[j] = 0;
        for (i = 0; i < n; i++) {
            aux[j] += matriz[i][j];
        }
        if (aux[j] == 0) {
            printf("%d = vértice fonte\n", j);
            fonte = 1;
        }
    }
    if (!fonte) {
        printf("Não há vértice fonte.\n");
    }
}

// Questão 6: Calcular graus de emissão e recepção
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

// Questão 7: Gerar grafo complementar
void grafoComplementar(int n) {
    FILE *arquivo_complementar = fopen("dados_grafo_complementar.txt", "w");
    if (arquivo_complementar == NULL) {
        printf("Erro ao criar o arquivo de saída.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (matrizadj[i][j] == 0) {
                fprintf(arquivo_complementar, "%d %d\n", i, j);
            }
        }
    }

    fclose(arquivo_complementar);
    printf("Grafo complementar gerado com sucesso.\n");
}

// Questão 8: Inverter a direção das arestas
void inverterGrafo(int n, const char *arquivoSaida) {
    FILE *arquivo = fopen(arquivoSaida, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s para gravação.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrizadj[i][j] == 1) {
                fprintf(arquivo, "%d %d\n", j, i); // Inverte a direção
            }
        }
    }

    fclose(arquivo);
}

// Função principal para executar todas as questões
int main() {
    int n, m, i, j, a;
    FILE *arq = fopen("dados_matriz.txt", "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        return 1;
    }

    fscanf(arq, "%d %d", &n, &m);

    // Alocar e preencher a matriz de adjacência
    int **matriz = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        matriz[i] = (int *)malloc(m * sizeof(int));
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            fscanf(arq, "%d", &matrizadj[i][j]);
        }
    }

    fclose(arq);

    // Chamar as funções para cada questão
    int grauVertice = gVertice(0, n); // Questão 2
    verIsolado(n); // Questão 3
    sumidouro(n, m, matriz); // Questão 4
    font(n, m, matriz); // Questão 5
    grausEmissaoRecepcao(n, matriz); // Questão 6
    grafoComplementar(n); // Questão 7
    inverterGrafo(n, "dados_grafos_invertido.txt"); // Questão 8

    // Liberação de memória
    for (i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
