#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

/* Samantha DeLorenzo */
/* I pledge my honor that I have abided by the Stevens Honor System. */



int gen_input(int SIZE, float *input_matrix) {
    //generates numbers for input matrix
    time_t t;
    
    srand((unsigned) time(&t));
    
    for (int i = 0; i < SIZE; i++) {
        input_matrix[i] = 1000*(1.0 * rand()) / RAND_MAX;
    }
    
    return 0;

}


int transpose(int INPUT_SIZE, int BLOCK_SIZE, float *input_matrix, float *output_matrix) {
    //transposes input matrix and stores result in output matrix
    //times how long it takes in seconds to transpose the matrix
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    
    printf("Time Start in Seconds: %f\n", (double)start.tv_sec);
    
    for (int i = 0; i < INPUT_SIZE; i+=BLOCK_SIZE) {
        for (int j = 0; j < INPUT_SIZE; j+=BLOCK_SIZE) {
            for (int x = i; x < BLOCK_SIZE+i; x++) {
                for (int y = j; y < BLOCK_SIZE+j; y++) {
                    output_matrix[y*INPUT_SIZE+x] = input_matrix[x*INPUT_SIZE+y];
                }
            }
            
        }
    }
    
    gettimeofday(&end, NULL);
    double diff = ((double)(end.tv_usec-start.tv_usec) / 1000000) + (double)(end.tv_sec - start.tv_sec);
    printf("Time End in Seconds: %f\n\n", (double)end.tv_sec + diff);
    printf("Time Diff in Seconds: %f\n\n", diff);

    
    return 0;
}

int print_matrix(int INPUT_SIZE, float *matrix, int SIZE) {
    //prints matrix in row & column format
    int counter = 1;
    int max_spaces = 12;
    
    for (int i = 0; i < SIZE; i++) {
        if (counter == INPUT_SIZE) {
            printf("%*f\n", max_spaces, matrix[i]);
            counter = 1;
        }
        else {
            printf("%*f ", max_spaces, matrix[i]);
            counter++;
        }
    }
    
    return 0;
    
}


int main(int argc, char **argv) {
    
    if (argc != 3) {
        fprintf(stderr, "Wrong number of command-line arguments\n");
        return -1;
    }
    
    int INPUT_SIZE = atoi(argv[1]);
    int BLOCK_SIZE = atoi(argv[2]);
    int SIZE = INPUT_SIZE*INPUT_SIZE;
    
    if (BLOCK_SIZE > INPUT_SIZE) {
        perror("Block size cannot larger than the matrix width");
        return -1;
    }
    
    float *input_matrix = (float *) malloc(SIZE*sizeof(float));
    float *output_matrix = (float *) malloc(SIZE*sizeof(float));
    
    gen_input(SIZE, input_matrix);
    
    /*uncomment to print input and output matrix */
    
    //printf("Input Matrix\n");
    //print_matrix(INPUT_SIZE, input_matrix, SIZE);
    printf("\n");
    transpose(INPUT_SIZE, BLOCK_SIZE, input_matrix, output_matrix);
    //printf("Output Matrix\n");
    //print_matrix(INPUT_SIZE, output_matrix, SIZE);
    
    
    free(input_matrix);
    free(output_matrix);
    
    
    
    return 0;
}
