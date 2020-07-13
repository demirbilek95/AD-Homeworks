#include "dijkstra.h"
#include <stdio.h>
#include <time.h>
#include "binheap.h"

int main()
{
    //Performance Test
    time_t t;
    int size2 = 50000;
    struct timespec requestStart, requestEnd;

    unsigned int *adj_matrix2 = (unsigned int *)malloc(sizeof(unsigned int)*size2*size2);
      
    srand((unsigned) time(&t));

    for (size_t i = 0; i < size2; i++){
        for (size_t j = 0; j < size2; j++){
            if ((i+j) < 25000){
                adj_matrix2[i*size2+j] = ((int)rand()%100);
            }
        }
    }

    graph g3;
    g3.weights = adj_matrix2;
    g3.v = (Node *)malloc(sizeof(Node)*size2);
    
    graph g4;
    g4.weights = adj_matrix2;
    g4.v = (Node *)malloc(sizeof(Node)*size2);

    FILE *fp;
    fp = fopen("benchmark/output.txt","w");
    fprintf(fp,"Size\tArray\tHeap");
    printf("Size\tArray\tHeap");

    for (int i = 0; i < 10; i++)
    {
        g3.size = size2 / (1 << (10-i));
        g4.size = size2 / (1 << (10-i));

        fprintf(fp,"\n%d",g3.size);
        printf("\n%d",g3.size);

        clock_gettime(CLOCK_REALTIME, &requestStart);
        array_dijkstra(&g3,0);
        clock_gettime(CLOCK_REALTIME, &requestEnd);

        double accum1 = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
      
        fprintf(fp,"\t%lf",accum1);
        printf("\t%lf",accum1);

        clock_gettime(CLOCK_REALTIME, &requestStart);
        heap_dijkstra(&g4,0);
        clock_gettime(CLOCK_REALTIME, &requestEnd);

        double accum2 = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

        fprintf(fp,"\t%lf",accum2);
        printf("\t%lf",accum2);
    }

    free(adj_matrix2);
    free(g3.v);
    free(g4.v);   
    fclose(fp);

    // Just to check correctness of algorithms (lecture notes were used), uncomment to see the results
    /*unsigned int size = 6;
    unsigned int *adj_matrix = (unsigned int *)malloc(sizeof(unsigned int)*size*size);

    for (size_t i = 0; i < size*size; i++){
        adj_matrix[i] = INF;
    }

    adj_matrix[size*0+1] = 1;
    adj_matrix[size*0+2] = 5;
    adj_matrix[size*1+5] = 15;
    adj_matrix[size*2+3] = 2;
    adj_matrix[size*3+4] = 1;
    adj_matrix[size*4+1] = 3;

    graph g1;
    g1.size = size;
    g1.weights = adj_matrix;
    g1.v = (Node *)malloc(sizeof(Node)*size);

    printf("Graph Before Dijkstra Algorithms\n");
    print_graph(&g1);

    array_dijkstra(&g1,0);
    printf("\nGraph After Array Dijkstra\n");
    print_graph(&g1);

    graph g2;
    g2.size = size;
    g2.weights = adj_matrix;
    g2.v = (Node *)malloc(sizeof(Node)*size);

    heap_dijkstra(&g2,0);
    printf("\nGraph After Heap Dijkstra \n");
    print_graph(&g1);

    free(g1.v);
    free(g2.v);
    free(adj_matrix);*/
  
}