#ifndef SET
#define SET

void insertSet(int m, int n, int *currentSet, int matrix[]);
void checkRepetitions(int matrix[], int v[]);
void removeRepeatedElement(int sizeV, int v[sizeV], int idxRemove);
void insertElements(int n, int *currentElement, int v[]);
void removeSet(int m, int n, int *currentSet, int idxRemSet, int v[]);

#endif