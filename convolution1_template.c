#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct matrix {
    int o_val;
    int n_val;
};
typedef struct matrix Matrix;


int main(int argc, char *argv[]) {
    FILE *file1, *file2, *file3;
    int i = 0;
    int filter[5][5];
    Matrix** data;
    int j, k, l, m;
    int val;
    int iter;

    if (argc < 5) {
    	printf("Usage: ./convolution1 data1.txt filter1.txt temp111 1\n");
    	return 1;
    }
    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
    if ((file1 == NULL) || (file2 == NULL)) {
    	printf("Error: Files cannot open\n");
    	return 1;
    }
    iter = atoi(argv[4]);
    if (iter == 0) {
    	printf("Error: Invalid iteration\n");
    	return 1;
    }  
    file3 = fopen(argv[3], "w");
    data = (Matrix**) malloc(sizeof(Matrix*)*1024);
    for (i = 0; i < 1024; i++) {
        data[i] = (Matrix*) malloc(sizeof(Matrix)*1024);
    }


    i = 0;
    do {
        j = 0;
        do {
            if (j == 1023) {
                fscanf(file1, "%d\n", &val);
                data[i][j].o_val = val;
//                printf("%d\n", data[i][j]);
            }
            else {
                fscanf(file1, "%d,", &val);
                data[i][j].o_val = val;
//                printf("%d ", data[i][j]);
            }
            j = j + 1;
        } while (j < 1024);
        i = i + 1;
    } while (i < 1024);

    i = 0;
    do {
        int j = 0;
        do {
            if (j == 4) {
                fscanf(file2, "%d\n", &val);
                filter[i][j] = val;
//                printf("%d\n", filter[i][j]);
            }
            else {
                fscanf(file2, "%d,", &val);
                filter[i][j] = val;
//               printf("%d ", filter[i][j]);
            }
            j = j + 1;
        } while (j < 5);
        i = i + 1;
    } while (i < 5);




// Your code is here  
int temp = 0;
for (i = 0; i < iter; i++){
        for (j = 0; j <1024; j++){
            for (k = 0; k <1024; k++)
                temp = 0;

                for (l = 0; l < 5; l++){
                    for (m = 0; m < 5; m++){
                        int d1, d2;

                        d1 = l - 2;
                        d2 = m - 2;
                        if ((j + d1 >= 0) && (j + d1 < 1024) && (k + d2 >= 0) && (k + d2 < 1024)){
                            temp = temp + data[j+d1][k+d2].o_val * filter[4-l][4-m];
                        }
                    }
                }

                temp = temp / 16;
                if (temp > 16){
                    data[j][k].n_val = 16;
                }
                else if (temp < -16){
                    data[j][k].n_val = -16;
                }
                else{
                    data[j][k].n_val = temp;
                }
            }
        }

        for (j = 0; j < 1024; j++){
            for (k = 0; k < 1024; k++){
                data[j][k].o_val = data[j][k].n_val;
            }
        }
// end of my code


    for (i = 0; i < 1024; i++) {
        for (j = 0; j < 1024; j++) {
            fprintf(file3, "%d ", data[i][j].n_val);
        }
        fprintf(file3, "\n");
    }

    for (i = 0; i < 1024; i++) {
        free(data[i]);
    }
    free(data);
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 0;
}



    