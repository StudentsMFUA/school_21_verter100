#include <stdio.h>
#include <stdlib.h>
/*
    1 6 7
    2 5 8
    3 4 9
*/
void sort_vertical(int **matrix, int n, int m, int **result_matrix);

/*
    1 2 3
    6 5 4
    7 8 9
*/
//void sort_horizontal(int **matrix, int n, int m, int **result_matrix);


void input(int **matrix, int *n, int *m);
void output(int **matrix, int n, int m);


int main()
{
    int n,m;
    scanf("%d %d", &n, &m);
    int ** arr = malloc(n * m * sizeof(int) + n * sizeof(int*));
    int* ptr = (int*) (arr + n);
    for(int i = 0; i < n; i++) {
        arr[i] = ptr + m * i;
    }
    int ** arr2 = malloc(n * m * sizeof(int) + n * sizeof(int*));
    int* ptr2 = (int*) (arr2 + n);
    for(int i = 0; i < n; i++) {
        arr2[i] = ptr2 + m * i;
    }
    input(arr, &n, &m);
    sort_vertical(arr, n, m, arr2);
    output(arr2, n, m);
    
   // sort_horizontal(matrix, n, m, result);
    //output(result, n, m);
    free(arr);
    free(arr2);
    return 0;
}

void input(int **matrix, int *n, int *m) {
    for(int i = 0; i < *n;i++) {
        for(int j = 0; j < *m; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
}
void output(int **matrix, int n, int m) {
    for(int i = 0; i < n;i++) {
        for(int j = 0; j < m; j++) {
            if(j == m -1)
              printf("%d", matrix[i][j]);
            else    
                printf("%d ", matrix[i][j]);
        }
    if(i != n - 1)
        printf("\n");   
    }
}
void sort_vertical(int **matrix, int n, int m, int **result_matrix) {
    int temp;
    for(int**ptr = matrix; ptr - matrix < n * m; ptr++) {
        for(int**ptr2 = ptr+1; ptr2 - 1 - matrix < n * m; ptr2++) {
            if(**ptr< **ptr2) {
                temp = **ptr;
                **ptr = **ptr2;
                **ptr2 = temp;
            }
        }
    }

    for(int **ptr = matrix, **ptr2 = result_matrix; ptr - matrix < n * m; ptr++, ptr2++)
        **ptr2 = **ptr;
}