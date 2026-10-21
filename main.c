#include <stdio.h>
#include <math.h>

void initializeVector(int m, int n, int matrix[m][n], int currentPosBySet[m]) {
    for (int i = 0; i < m; i++) {
        currentPosBySet[i] = 0;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
}

// Busca sequencial: olha só os 'size' primeiros elementos do vetor.
// Retorna a posição onde o valor foi encontrado ou -1 se não existe.
int sequentialSearch(int vector[], int size, int value) {
    for (int i = 0; i < size; i++) {
        if (vector[i] == value) {
            return i;
        }
    }
    return -1;
}

// Mostra uma linha da matriz no formato "Conjunto 0 = 2 4 8 9" (ou "vazio")
void printSet(int m, int n, int matriz[m][n], int currentPosBySet[m], int c) {
    printf("Conjunto %d =", c);
    if (currentPosBySet[c] == 0) {
        printf(" vazio");
    } else {
        for (int i = 0; i < currentPosBySet[c]; i++) {
            printf(" %d", matriz[c][i]);
        }
    }
    printf("\n");
}

// Opção 1: criar um novo conjunto vazio
int createSet(int m, int countSet) {
    if (countSet < m) {
        countSet++;
        printf("Conjunto %d criado com sucesso!\n", countSet - 1);
    } else {
        printf("Erro: limite de %d conjuntos atingido!\n", m);
    }
    return countSet;
}

// Opção 2: inserir dados em um conjunto
void insertData(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    int c = -1;
    printf("Em qual conjunto você deseja inserir? ");
    scanf("%d", &c);
    if (c < 0 || c >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c);
    } else if (currentPosBySet[c] >= n) {
        printf("Erro: o conjunto %d já está cheio (limite de %d valores)!\n", c, n);
    } else {
        for (int i = currentPosBySet[c]; i < n; i++) {
            int elemento = 0;
            printf("Digite o elemento %d (caso deseje parar digite 0): ", i);
            scanf("%d", &elemento);
            if (elemento == 0) {
                currentPosBySet[c] = i;
                break;
            }
            // só insere se o valor ainda não está nos i elementos já inseridos
            if (sequentialSearch(matriz[c], i, elemento) == -1) {
                matriz[c][i] = elemento;
                currentPosBySet[c] = i + 1;
            } else {
                printf("Valor repetido! Um conjunto não pode ter valores iguais.\n");
                i--;
            }
        }
        if (currentPosBySet[c] == n) {
            printf("O conjunto %d atingiu o limite de %d valores.\n", c, n);
        }
    }
}

// Opção 3: remover um conjunto
int removeSet(int m, int n, int matriz[m][n], int currentPosBySet[m], double med[m], double std[m], int countSet) {
    int c = -1;
    printf("Qual conjunto você deseja remover? ");
    scanf("%d", &c);
    if (c < 0 || c >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c);
    } else {
        for (int i = 0; i < n; i++) {
            matriz[c][i] = 0;
        }
        currentPosBySet[c] = 0;
        // move os conjuntos de baixo "para cima" (até a penúltima linha usada, para não sair da matriz)
        for (int i = c; i < countSet - 1; i++) {
            for (int j = 0; j < n; j++) {
                matriz[i][j] = matriz[i + 1][j];
            }
            currentPosBySet[i] = currentPosBySet[i + 1];
            med[i] = med[i + 1];
            std[i] = std[i + 1];
        }
        // a última linha usada ficou duplicada, então zera ela
        for (int j = 0; j < n; j++) {
            matriz[countSet - 1][j] = 0;
        }
        currentPosBySet[countSet - 1] = 0;
        med[countSet - 1] = 0;
        std[countSet - 1] = 0;
        countSet--;
        printf("Conjunto %d removido com sucesso!\n", c);
    }
    return countSet;
}

// Opção 4: união entre dois conjuntos
int unionSets(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    int c1 = -1;
    printf("Qual o conjunto 1 da união? ");
    scanf("%d", &c1);
    int c2 = -1;
    printf("Qual o conjunto 2 da união? ");
    scanf("%d", &c2);
    if (c1 < 0 || c1 >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c1);
    } else if (c2 < 0 || c2 >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c2);
    } else if (countSet >= m) {
        printf("Erro: limite de %d conjuntos atingido! Não há espaço para a união.\n", m);
    } else {
        // antes de criar, conta quantos elementos a união terá:
        // todos os de c1 + os de c2 que não estão em c1
        int tamanho = currentPosBySet[c1];
        for (int i = 0; i < currentPosBySet[c2]; i++) {
            if (sequentialSearch(matriz[c1], currentPosBySet[c1], matriz[c2][i]) == -1) {
                tamanho++;
            }
        }
        if (tamanho > n) {
            printf("Erro: a união teria %d valores e o limite é %d. Conjunto não criado.\n", tamanho, n);
        } else {
            int novo = countSet;
            countSet++;
            for (int i = 0; i < currentPosBySet[c1]; i++) {
                matriz[novo][i] = matriz[c1][i];
            }
            currentPosBySet[novo] = currentPosBySet[c1];
            for (int i = 0; i < currentPosBySet[c2]; i++) {
                if (sequentialSearch(matriz[c1], currentPosBySet[c1], matriz[c2][i]) == -1) {
                    matriz[novo][currentPosBySet[novo]] = matriz[c2][i];
                    currentPosBySet[novo]++;
                }
            }
            printf("União criada como conjunto %d.\n", novo);
        }
    }
    return countSet;
}

// Opção 5: intersecção entre dois conjuntos
int intersectionSets(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    int c1 = -1;
    printf("Qual o conjunto 1 da intersecção? ");
    scanf("%d", &c1);
    int c2 = -1;
    printf("Qual o conjunto 2 da intersecção? ");
    scanf("%d", &c2);
    if (c1 < 0 || c1 >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c1);
    } else if (c2 < 0 || c2 >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c2);
    } else if (countSet >= m) {
        printf("Erro: limite de %d conjuntos atingido! Não há espaço para a intersecção.\n", m);
    } else {
        int novo = countSet;
        countSet++;
        // fica com os elementos de c1 que também estão em c2
        for (int i = 0; i < currentPosBySet[c1]; i++) {
            if (sequentialSearch(matriz[c2], currentPosBySet[c2], matriz[c1][i]) != -1) {
                matriz[novo][currentPosBySet[novo]] = matriz[c1][i];
                currentPosBySet[novo]++;
            }
        }
        printf("Intersecção criada como conjunto %d.\n", novo);
    }
    return countSet;
}

// Opção 6: mostrar um conjunto, dado o seu índice
void showSet(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    int c = -1;
    printf("Qual conjunto você deseja mostrar? ");
    scanf("%d", &c);
    if (c < 0 || c >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c);
    } else {
        printSet(m, n, matriz, currentPosBySet, c);
    }
}

// Opção 7: mostrar todos os conjuntos
void showAllSets(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    if (countSet == 0) {
        printf("Ainda não existe nenhum conjunto! Use a opção 1 para criar um.\n");
    } else {
        printf("Temos %d %s:\n", countSet, countSet == 1 ? "conjunto" : "conjuntos");
        for (int i = 0; i < countSet; i++) {
            printSet(m, n, matriz, currentPosBySet, i);
        }
    }
}

// Opção 8: busca por um valor
void searchValue(int m, int n, int matriz[m][n], int currentPosBySet[m], int countSet) {
    int valor = 0;
    printf("Qual valor você deseja buscar? ");
    scanf("%d", &valor);
    if (valor == 0) {
        printf("Erro: o zero não é um valor válido nos conjuntos!\n");
    } else if (countSet == 0) {
        printf("Ainda não existe nenhum conjunto! Use a opção 1 para criar um.\n");
    } else {
        int encontrou = 0;
        for (int i = 0; i < countSet; i++) {
            if (sequentialSearch(matriz[i], currentPosBySet[i], valor) != -1) {
                if (encontrou == 0) {
                    printf("Conjuntos que contêm o valor %d:\n", valor);
                }
                printf("Conjunto %d\n", i);
                encontrou = 1;
            }
        }
        if (encontrou == 0) {
            printf("Nenhum conjunto contém o valor %d.\n", valor);
        }
    }
}

// Opção 9: calcular média e desvio padrão de um conjunto (e guardar em med e std)
void calculateMeanStd(int m, int n, int matriz[m][n], int currentPosBySet[m], double med[m], double std[m], int countSet) {
    int c = -1;
    printf("De qual conjunto você deseja calcular a média e o desvio padrão? ");
    scanf("%d", &c);
    if (c < 0 || c >= countSet) {
        printf("Erro: conjunto %d não foi criado!\n", c);
    } else if (currentPosBySet[c] == 0) {
        printf("Erro: o conjunto %d está vazio, não dá para calcular!\n", c);
    } else {
        int tam = currentPosBySet[c];
        double soma = 0;
        for (int i = 0; i < tam; i++) {
            soma += matriz[c][i];
        }
        med[c] = soma / tam;

        // desvio padrão amostral (divide por tam - 1), como no exemplo dos slides
        double somaQuad = 0;
        for (int i = 0; i < tam; i++) {
            somaQuad += (matriz[c][i] - med[c]) * (matriz[c][i] - med[c]);
        }
        if (tam > 1) {
            std[c] = sqrt(somaQuad / (tam - 1));
        } else {
            std[c] = 0;
        }
        printf("Conjunto %d: med = %.2f; std = %.2f\n", c, med[c], std[c]);
    }
}

int main() {
    int M = -1, N = -1;
    printf("Olá, seja bem-vindo!\nPor favor, informe a quantidade de linhas (conjuntos) e colunas (valores por conjunto) que você deseja para a matriz.\n");
    if (scanf("%d %d", &M, &N) != 2) {
        M = -1;
        N = -1;
        while (getchar() != '\n');   // descarta o que foi digitado de errado
    }
    while(M <= 0 || N <= 0) {
        printf("Por favor, informe um valor válido para linhas e colunas (um valor maior que zero).\n");
        if (scanf("%d %d", &M, &N) != 2) {
            M = -1;
            N = -1;
            while (getchar() != '\n');
        }
    }

    int matriz[M][N];
    int countSet = 0;
    int currentPosBySet[M];
    double med[M];
    double std[M];
    int option = -1;

    initializeVector(M, N, matriz, currentPosBySet);
    for (int i = 0; i < M; i++) {
        med[i] = 0;
        std[i] = 0;
    }

    while(option != 10) {
        printf("\nGerenciamento de Conjuntos\nDigite o número da ação desejada:\n1. Criar um novo conjunto vazio. \n2. Inserir dados em um conjunto. \n3. Remover um conjunto. \n4. Fazer a união entre dois conjuntos. \n5. Fazer a intersecção entre dois conjuntos. \n6. Mostrar um conjunto, dado o seu índice. \n7. Mostrar todos os conjuntos. \n8. Busca por um valor. \n9. Calcular a média e o desvio padrão de um conjunto. \n10. Sair do programa. \nEscolha uma opção: ");
        scanf("%d", &option);

        if(option == 1){
            countSet = createSet(M, countSet);
        }
        else if(option == 2){
            insertData(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 3){
            countSet = removeSet(M, N, matriz, currentPosBySet, med, std, countSet);
        }
        else if(option == 4){
            countSet = unionSets(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 5){
            countSet = intersectionSets(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 6){
            showSet(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 7){
            showAllSets(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 8){
            searchValue(M, N, matriz, currentPosBySet, countSet);
        }
        else if(option == 9){
            calculateMeanStd(M, N, matriz, currentPosBySet, med, std, countSet);
        }
        else if(option != 10){
            printf("Opção inválida! Escolha um número de 1 a 10.\n");
        }
    }

    printf("Programa encerrado. Até logo!\n");
    return 0;
}