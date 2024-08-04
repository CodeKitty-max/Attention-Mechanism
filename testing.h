#include <stdio.h>
#include <asm-generic/types.h>

__u8 testArray2by2(double genArray[4][3]){
    for(__u8 i = 0; i < 4; i++){
        for(__u8 j = 0;  j < 3; j++){
            printf("%f ", genArray[i][j]);
        }
    }
    printf("\n");
}

//Testing if above arrays have generated anything
__u8 testArray(__u8 *Arr, size_t size){
    for(__u8 i = 0; i < size; i++){
        printf("%d", Arr[i]);
    }
    //delineator
    __u8 del[] = "***********";
    printf("\n");
    printf("%s\n", del);
}
