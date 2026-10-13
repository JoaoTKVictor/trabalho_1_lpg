#include <stdio.h>
#include "../includes/set.h";

void insertSet(int m, int n, int *currentSet, int matrix[m][n]) {
    if (*currentSet == m - 1) {
        int action = 0;
        printf("A matriz já atingiu o limite de conjuntos (linhas).\nVocê deseja remover um conjunto?\n1 - Sim\n2 - Não\n");
        scanf("%d", &action);

        while (action < 1 || action > 2) {
            printf("Escolha uma opção válida:\n1 - Sim\n2 - Não\n");
            scanf("%d", &action);
        }
    }

    for (int i = 0; i < n; i++) {
        matrix[*currentSet][i] = 0;
    }

    (*currentSet)++;
}

void removeRepeatedElement(int *sizeV, int v[*sizeV], int idxRemove) {
    for (int i = idxRemove; i < *sizeV - 1; i++) {
        v[i] = v[i + 1];
    }
    (*sizeV)--;
}

void checkRepetitions(int sizeSet, int set[sizeSet], int *sizeVNewEl, int newElements[*sizeVNewEl]) {
    for (int i = 0; i < *sizeVNewEl; i++) {
        for (int j = i + 1; j < *sizeVNewEl; j++) {
            if (newElements[i] == newElements[j]) {
                removeRepeatedElement(sizeVNewEl, newElements, j);
                j--;
            }
        }
    }

    for (int i = 0; i < *sizeVNewEl; i++) {
        for (int j = 0; j < sizeSet; j++) {
            if (newElements[i] == set[j]) {
                removeRepeatedElement(sizeVNewEl, newElements, i);
                i--;
                break;
            }
        }
    }
}
