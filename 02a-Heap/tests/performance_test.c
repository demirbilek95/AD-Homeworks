#include <stdio.h>
#include <string.h>
#include <binheap.h>
#include <time.h> 

#define MAX_SIZE 10000

int main() {

    time_t t;
    struct timespec requestStart, requestEnd;

    int *array = (int *)malloc(sizeof(int)*MAX_SIZE);

    srand((unsigned) time(&t));
    for (int k = 0; k < MAX_SIZE; k++)
    {
        array[k] = (rand() % 50);
    }

    float *maxA=(float *)malloc(sizeof(int)*MAX_SIZE);

    FILE *fp;
    fp = fopen("insert.txt","w");
    fprintf(fp,"Number_of_Elements\tTimes\n");

    for (int i = 10; i < MAX_SIZE; i+=10)
    {
        fprintf(fp,"%i \t",i);
        binheap_type *maxH=build_heap(maxA,0,MAX_SIZE,sizeof(int),geq_int);

        clock_gettime(CLOCK_REALTIME, &requestStart);
        for (int j = 0; j < i; ++j)
        {
            insert_value(maxH,&array[j]);
        }
        clock_gettime(CLOCK_REALTIME, &requestEnd);
        double accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

        fprintf(fp,"%f \n",accum);
        delete_heap(maxH);
    }

    free(maxA);
    free(array);
    
    fclose(fp);
  
    
}