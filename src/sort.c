#include "sort.h"

void bucket_sort(int arr[], size_t n){
    //int *tmp = malloc(sizeof(int) * n);

    int arr_max = arr[0] + 1;
    for(unsigned i = 1; i < n; ++i){
        if(arr_max < arr[i] + 1)
            arr_max = arr[i] + 1;
    }

    int *count = calloc(arr_max, sizeof(*count));

    for(unsigned i = 0; i < n; i++){
        (count[arr[i]])++;
    }

    for(int i = 0,j = 0; i < arr_max; i++){
        for(; count[i] > 0; (count[i])--)
            arr[j++] = i;
    }
    free(count);
}

