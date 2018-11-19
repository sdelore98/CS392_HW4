#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/time.h>

/* Samantha DeLorenzo */
/* I pledge my honor that I have abided by the Stevens Honor System. */



int gen_input(int SIZE, float *input_matrix) {
    time_t t;
    
    srand((unsigned) time(&t));
    
    for (int i = 0; i < SIZE; i++) {
        input_matrix[i] = 1000*(1.0 * rand()) / RAND_MAX;
    }
    
    return 0;

}


int transpose(int HEIGHT, int WIDTH, int BLOCK_SIZE, float *input_matrix, float *output_matrix) {
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    
    printf("Time Start in Seconds: %f\n", (double)start.tv_sec);
    
    for (int i = 0; i < HEIGHT; i+=BLOCK_SIZE) {
        for (int j = 0; j < WIDTH; j+=BLOCK_SIZE) {
            for (int x = i; x < BLOCK_SIZE+i; x++) {
                if (x >= HEIGHT) {
                    break;
                }
                for (int y = j; y < BLOCK_SIZE+j; y++) {
                    if (y >= WIDTH) {
                        break;
                    }
                    output_matrix[y*HEIGHT+x] = input_matrix[x*WIDTH+y];
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

int print_matrix(int WIDTH, float *matrix, int SIZE) {
    int counter = 1;
    int max_spaces = 12;
    
    for (int i = 0; i < SIZE; i++) {
        if (counter == WIDTH) {
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
    
    if (argc != 4) {
        fprintf(stderr, "Wrong number of command-line arguments\n");
        return -1;
    }
    
    int HEIGHT = atoi(argv[1]);
    int WIDTH = atoi(argv[2]);
    int BLOCK_SIZE = atoi(argv[3]);
    int SIZE = HEIGHT*WIDTH;
    
    float *input_matrix = (float *) malloc(SIZE*sizeof(float));
    float *output_matrix = (float *) malloc(SIZE*sizeof(float));
    
    gen_input(SIZE, input_matrix);
    
    /*uncomment to print input and output matrix */
    
    //printf("Input Matrix\n");
    //print_matrix(WIDTH, input_matrix, SIZE);
    printf("\n");
    transpose(HEIGHT, WIDTH, BLOCK_SIZE, input_matrix, output_matrix);
    //printf("Output Matrix\n");
    //print_matrix(HEIGHT, output_matrix, SIZE);
    
    
    free(input_matrix);
    free(output_matrix);
    
    
    
    return 0;
}
