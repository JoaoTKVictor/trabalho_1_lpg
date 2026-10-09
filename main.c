#include <stdio.h>

void initializeVector(int m, int n, int matrix[m][n], int currentPosBySet[m]) {
    for (int i = 0; i < m; i++) {
        currentPosBySet[i] = 0;
        for (int j = 0; j < n; j++) {
            matrix[i][j] = 0;
        }
    }
}

int main() {
    unsigned int M = -1, N = -1;
    printf("Olá, seja bem-vindo!\nPor favor, informe a quantidade de colunas e linhas que você deseja para a matriz.\nExemplo: 5 4.");
    scanf("%d %d", &M, &N);
    while(M <= 0 && N <= 0) {
        printf("Por favor, informe um valor válido para linhas e colunas (um valor maior que zero).\n");
        scanf("%d %d", &M, &N);
    }
    int matrix;
    int countSet = 0;
    int currentPosBySet[M];
    int option = -1;

    while(option != 0) {
        printf("Digite o número da ação desejada:\n1 - Inserir elementos em um conjunto\n");
    }

    return 0;
}