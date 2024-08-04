#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <asm-generic/types.h>
#include <time.h>
#define ARR_SIZE 9
#define L_BOUND 0
#define U_BOUND 3

//Random array generator(for k, q, v weights)
__u8 weightArray(__u8 *buff, __u8 count){
    __u8 i;
    
    //need it to generate 9 vals for a 3 by 3 matrix
    for(i = 0; i < count; i++){
        //generating numbers within upper and lower bounds
        __u8 val = rand() % (U_BOUND - L_BOUND +1);
        buff[i] = val;
        //printf("%d", Array[i]);
    }

}

//Generation of Queries, Keys and Values
__u8 qkvGeneration(__u8 word[4][3], __u8 *Arr, __u8 genArray[4][3]){
    //Just MatMul(underwhelming)
    //(Gonna check time and try to optimize)
    //__u8 genArray[4][3]; //Gonna be a 4 by 3 matrix 

    //Arranging into a 3 by 3 matrix
    __u8 matrix[3][3];
    for(__u8 i = 0; i < 3; i++ ){
        for(__u8 j = 0; j < 3; j++){
            matrix[i][j] = Arr[i * 3 + j];
        }
    }

    //Matmul
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0; j < 3; j++){
            genArray[i][j] = 0;
            for(__u8 k = 0; k < 3; k++){
                genArray[i][j] += word[i][k] * matrix[k][j];
            }
        }
    }
    for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d ", genArray[i][j]);
            }
}
    printf("\n");
}

//scoring the query vector against the key vectors
void Scoring(__u8 KeyArr[4][3],  __u8 QueryArr[4][3], __u8 Scores[4][4]){
    __u8 keyArrTranspose[3][4]; 
   //Transposing Key vector
    for(__u8 i = 0; i < 3; i++){
        for(__u8 j = 0; j < 4; j++){
            keyArrTranspose[i][j] = KeyArr[j][i]; 
        }
    }

   
    //Post transpose makes Key Matrix a 3 by 4 matrix
    //Score Matrix will hence result in a 4 by 4 matrix
    //Matmul for the Queries and Transposed Keys
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0; j < 4; j++){
            Scores[i][j] = 0;
            for(__u8 k = 0; k < 3; k++){
                Scores[i][j] += QueryArr[i][k] * keyArrTranspose[k][j]; 
            }
        }
    }
}

double expo(double val){
    if (val > 80) val = 80;
    return exp(val); 
}



//Double score takes the Score array and converts it into an array 
double Weights (__u8 Score[4][4], double Weights[4][4]){
    double keysShape1 = sqrt(3);

    //converting vals in arrays into doubles
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0; j < 4; j++){
           Weights[i][j] = (double) Score[i][j]; 
           Weights[i][j] = Weights[i][j] / keysShape1;
        }
    }
    //softmax implementation
    double sum = 0;
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0; j < 4; j++){
           Weights[i][j] = exp(Weights[i][j]);
            sum +=Weights[i][j];
        }
    }
    if(sum==0){sum=0.001;
    }
   for(__u8 n = 0; n < 4; n++){
        for(__u8 m = 0; m < 4; m++){
            Weights[n][m] =  (Weights[n][m]/sum);
        }
    }
}