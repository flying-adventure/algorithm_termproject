#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define min(A,B) A < B ? A : B


int main() {

    int n, i;       //n은 총 금액을 의미한다.
    FILE *fr = fopen("input.txt", "r");

    if (fr == NULL) {
        printf("FILE doesn't exist.");
        return 0;
    }

    fscanf(fr, "%d", &n);
    fclose(fr);

    //n이 음수일 경우 에러로 판단하여 탈출
    if (n < 0) {
        printf("Error total cash cannot be negative integer");
        return 0;
    }

    //n이 100000을 넘어갈 경우 에러로 판단하여 탈출
    if (n > 100000) {
        printf("Error total cash cannot be over 100,000");
    }

    //dp[n]은 n원을 거슬러 줄 경우의 최소 동전 개수를 의미
    //n열까지의 arr를 가지도록 동적할당
    int* dp = (int*)calloc(n + 1, sizeof(int));

    //dp값 초기화 시키기(-1은 2원과 5원으로는 줄 수 없는 상태를 의미)
    for (i = 0; i < n + 1; i++) {
        dp[i] = -1;
    }

    //2원일 경우와 5원일 경우 각각 2원, 5원만 거슬러 주면 되므로 1로, 
    //4원의 경우 2원 2개를 주면 되므로 2로 초기화
    dp[2] = 1;
    dp[4] = 2;
    dp[5] = 1;


    //dp 계산
    for (i = 3; i < n + 1; i++) {

        // arr[n - 2] + 1과 arr[n - 5] + 1 중 더 작은 걸 arr[n]
        // dp[i]가 -1이 나오는 경우는 제외
        if(dp[i - 2] != -1) {
            dp[i] = dp[i - 2] + 1;
        }
        
        if((dp[i - 5] != -1) && i > 5) {
            dp[i] = min(dp[i], dp[i - 5] + 1);
        }
    }

    if(dp[n] == -1) {
        printf("거스름돈을 줄 수 없습니다.\n");
    }
    else {
        printf("%d\n", dp[n]);
    }

    free(dp);

    return 0;
}