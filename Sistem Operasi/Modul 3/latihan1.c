#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>

int faktorial(int x) {
    if (x == 0 || x == 1) return 1;
    else return x*faktorial(x-1);
}

void *fungsiGaul(void *argx){
    int x;
    x = (int) argx;
    int hasil = faktorial(x);

    printf("%d! = %d\n", x, hasil);

}

void swap(int* xp, int* yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Function to perform Selection Sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}

int main (int argc, char *argv[]) {

    // check parameter if correct
    char* p;
    errno = 0;
    int arg[100];
    for (int i = 1; i < argc; i++) {
        arg[i-1] = strtol(argv[i], &p, 10);

        if (*p != '\0' || errno != 0){
            printf("Invalid input\n");
            return 1;
        }
    }

    //sort ascending argument
    selectionSort(arg,argc-1);

    // main program
    pthread_t myThread[argc-1];
    int iter;

    for (int i = 0;  i < argc-1; i++) {
        iter = pthread_create(&myThread[i],NULL, fungsiGaul, (void *)arg[i]);
        if (iter){
            fprintf(stderr,"Error - pthread_create() return code: %d\n",iter);
            exit(EXIT_FAILURE);
        }

    }


    for(int i = 0 ; i < argc-1; i++){
        pthread_join(myThread[i], NULL);
    }



    return 0;

}
