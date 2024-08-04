#include <stdio.h>
#include<stdlib.h>
#include <math.h>
#include <asm-generic/types.h>
#include <time.h>
#include "Attention.h"
#include "testing.h"
#define ARR_SIZE 9
#define L_BOUND 0
#define U_BOUND 3

//word array containing 4 word arrays
__u8 wordArr1[4][3] = {{1, 0, 0},
                   {0, 1, 0},
                   {1, 1, 0},
                   {0, 0, 1}};


//dot matrix ops for weights and value arrays -> Attention = weights @ values
void Attention(double Weights[4][4], __u8 Value[4][3], double Attention[4][3]){
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0; j < 3; j++){
            Attention[i][j] = 0;
            for(__u8 k = 0; k < 3; k++){
                Attention[i][j] += Weights[i][k] * Value[k][j];
            }
        }
    }

}



  
void main(){
    //weight matrices
    __u8 W_Q[ARR_SIZE];
    __u8 W_K[ARR_SIZE];
    __u8 W_V[ARR_SIZE];

    //random array generation
    weightArray(W_Q, ARR_SIZE);
    weightArray(W_K, ARR_SIZE);
    weightArray(W_V, ARR_SIZE);
    
    //Getting actual array sizes
    size_t size1 = sizeof(W_Q)/sizeof(W_Q[0]);
    size_t size2 = sizeof(W_K)/sizeof(W_K[0]);
    size_t size3 = sizeof(W_V)/sizeof(W_V[0]);
    

    //testing if that works
    testArray(W_Q, size1);
    testArray(W_K, size2);
    testArray(W_V, size3);

    //Keys, Queries and Values
    __u8 QueryArr[4][3];
    __u8 KeyArr[4][3];
    __u8 ValArr[4][3];

    //Allocation and testing
    qkvGeneration(wordArr1, W_Q, QueryArr);
    qkvGeneration(wordArr1, W_K, KeyArr);
    qkvGeneration(wordArr1, W_V, ValArr);

    //Key Arr
    __u8 ScoreArr[4][4];
    __u8 KeyTrans[3][4];
    Scoring(KeyArr, QueryArr, ScoreArr);

    double WeightExample[4][4];
    double AttentionExample[4][3];
    Weights(ScoreArr, WeightExample);
    
    Attention(WeightExample, ValArr, AttentionExample);
    //Scoring(KeyTrans);
    //test
    testArray2by2(AttentionExample);
    //testArray2by2(KeyArr);
    //test
    //Weights(KeyArr);
}



