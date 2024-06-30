#include <stdio.h>
#include <stdlib.h>



int main()
{
    int n,m;
    scanf("%d %d", &n, &m);
    int ** arr =(int**) malloc(n * m * sizeof(int) + n * sizeof(int*));
    int* ptr = (int*) (arr + n);
    for(int i = 0; i < n; i++) {
        arr[i] = ptr + m * i;
    }
    for(int i = 0; i < n;i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &arr[i][j]);
        }
    }





    for(int i = 0; i < n;i++) {
        for(int j = 0; j < m; j++) {
            if(j == m -1)
              printf("%d", arr[i][j]);
            else    
                printf("%d ", arr[i][j]);
        }
    if(i != n - 1)
        printf("\n");   
    }


    free(arr);
    return 0;
}


