#include <stdio.h>
#include <stdlib.h>

void destroy_array_2d(int*** ptr, int height) {
    if (ptr == NULL) {
        return;
    }
    int** local_ptr = *ptr;
    if (local_ptr != NULL && height > 0) {
        for (int i = 0; height > i; i++) {
            if (*(local_ptr + i) != NULL) {
                free(*(local_ptr + i));
                *(local_ptr + i) = NULL;
            }
        }
        free(local_ptr);
        *ptr = NULL;
    }
    
}
int create_array_2d_2(int*** ptr, int width, int height) {
    if (width <= 0 || height <= 0 || ptr == NULL) {
        return 1;
    }
    int** local_ptr = NULL;
    local_ptr = (int**)calloc(height, sizeof(int*)); //rzutownaie na wsakżnik na wskaźnik plus alokacaj pamięi dla kolejnych wierszy * ilość pamięci o wielkości wskażnika int
    if (local_ptr == NULL) {
        //printf("Failed to allocate memory");
        return 2;
    }
    for (int i = 0; height > i; i++) {
        *(local_ptr + i) = NULL;
        *(local_ptr + i) = calloc(width, sizeof(int));
        if (*(local_ptr + i) == NULL) {
            destroy_array_2d(&local_ptr, height);
            return 2;
        }
    }
    *(ptr) = local_ptr;
    return 0;
}
int matrix_read(int** ptr, int width, int height) {
    if (height <= 0 || width <= 0 || ptr == NULL) {
        return 1;
    }
    printf("Podaj wartości: ");
    for (int i = 0; height > i; i++) {
        for (int j = 0; width > j; j++) {
            int temp;
            int check = scanf("%d", &temp);
            if (check != 1) {
                return 2;
            }
            *(*(ptr + i) + j) = temp;
        }
    }
    return 0;
}
void display_array_2d(int** ptr, int width, int height) {
    if (height <= 0 || width <= 0 || ptr == NULL) {
        return;
    }
    for (int i = 0; height > i; i++) {
        if (*(ptr + i) != NULL) {
            for (int j = 0; width > j; j++) {
                int temp = *(*(ptr + i) + j);
                printf("%d ", temp);
            }
            printf("\n");
        }
    }
}
int sum_array_2d(int** ptr, int width, int height) {
    if (ptr == NULL || width <= 0 || height <= 0) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; height > i; i++) {
        sum += sum_row(*(ptr + i), width);
    }
    return sum;
}
int sum_row(int* ptr, int width) {
    if (ptr == NULL || width <= 0) {
        return -1;
    }
    int sum = 0;
    for (int i = 0; i < width; i++) {
        sum += *(ptr + i);
    }
    return sum;
}
int main()
{
    int** ptr = NULL;
    int check = 0;
    int height = 0;
    int width = 0;
    printf("Podaj szerokosc i wysokosc: ");
    check = scanf("%d %d", &width, &height);
    if (check != 2) {
        printf("incorrect input");
        return 1;
    }
    if (width <= 0 || height <= 0) {
        printf("incorrect input data");
        return 2;
    }

    check = create_array_2d_2(&ptr, width, height);
    if (check == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    else if (check == 1) {
        printf("incorrect input data");
        return 1;
    }



    check = matrix_read(ptr, width, height);
    if (check == 1) {
        printf("incorrect input data");
        destroy_array_2d(&ptr, height);
        return 8;
    }
    else if (check == 2) {
        printf("incorrect input");
        destroy_array_2d(&ptr, height);
        return 1;
    }

    display_array_2d(ptr, width, height);
    for (int i = 0; height > i; i++) {
        printf("%d\n", sum_row(*(ptr + i), width));
    }
        
    printf("%d\n", sum_array_2d(ptr, width,height));
  

    destroy_array_2d(&ptr, height);
    return 0;
}