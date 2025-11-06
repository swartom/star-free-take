#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct sigma {
    uint8_t gamma;
    uint32_t x;
} sigma;

#define COUNT 1
#define MAX_GRAPH 100000
int MAX_WORD;
double P = .5;

int write_file(sigma* data,char* file) {
    FILE *fptr;
    fptr = fopen(file, "w");
    int test = 0;
    for(int i = MAX_WORD - 1; i > 0; i --) {
        switch (data[i].gamma) {
            case 'A':
                if( test++ == 0)
                    fprintf(fptr, "%d",data[i].x);
                else
                    fprintf(fptr, "\n%d",data[i].x);
                break;
            default:
                fprintf(fptr, " %d",data[i].x);
                break;
        }
    }
    fclose(fptr);
    return 0;
}

int write_file_degree(int* data,char* file) {
    FILE *fptr;
    fptr = fopen(file, "w");
    for(int i = 0; i < MAX_WORD; i ++) {
        fprintf(fptr, "%d %d\n",i+1,data[i]);
    }
    fclose(fptr);
    return 0;
}







int main(int argc, char* argv[]) {


    int d = 1;

    sscanf(argv[1],"%d", &d);
    MAX_WORD = MAX_GRAPH*d;
    sscanf(argv[2], "%lf", &P);

    double n = 0;


    double get_random() {
        unsigned int myRandomData[1];
        arc4random_buf(myRandomData, sizeof myRandomData);
        srand(myRandomData[0]); // randomize seed
        return (double)rand() / (double)RAND_MAX;
    }

    /* double get_random() { return (double)rand() / (double)RAND_MAX; } */
    sigma* data = malloc(sizeof(sigma) * MAX_WORD);

    for (int j = 0; j < COUNT; j ++){
        for(int i = 0; i < MAX_WORD; i ++) {
            n = get_random();
            if (n > P)
                data[i].gamma = 'A';
            else
                data[i].gamma = 'L';

            n = get_random();
            data[i].x = (uint32_t) (n * MAX_GRAPH);
        }
        data[MAX_WORD-1].gamma = 'A';
        char buffer[20];
        sprintf(buffer, "graph%d.adjlist", j);
        write_file(data,buffer);

    }
    free(data);
}
