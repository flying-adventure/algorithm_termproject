#include <stdio.h>
#include <stdlib.h>

// 회의 정보를 저장할 구조체 정의
typedef struct {
    int start;
    int end;
} Meeting;

// 종료 시간을 기준으로 정렬, 종료 시간이 같으면 시작 시간을 기준으로 정렬
int compare(const void* a, const void* b) {
    Meeting* m1 = (Meeting*)a;
    Meeting* m2 = (Meeting*)b;
    if (m1->end == m2->end)
        return m1->start - m2->start;
    return m1->end - m2->end;
}

// 이진 탐색: 이전 겹치지 않는 회의를 찾음
int binarySearch(Meeting meetings[], int index) {
    int left = 0, right = index - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (meetings[mid].end <= meetings[index].start) {
            if (mid == index - 1 || meetings[mid + 1].end > meetings[index].start)
                return mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // 겹치지 않는 회의가 없을 경우
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    // 메모리 동적 할당
    Meeting* meetings = (Meeting*)malloc(N * sizeof(Meeting));
    if (meetings == NULL) {
        printf("Memory allocation failed.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < N; i++) {
        fscanf(file, "%d %d", &meetings[i].start, &meetings[i].end);
    }
    fclose(file);

    // 회의를 종료 시간 기준으로 정렬
    qsort(meetings, N, sizeof(Meeting), compare);

    // DP 배열 동적 할당
    int* dp = (int*)malloc(N * sizeof(int));
    if (dp == NULL) {
        printf("Memory allocation failed.\n");
        free(meetings);
        return 1;
    }

    dp[0] = 1; // 첫 번째 회의는 선택 가능
    for (int i = 1; i < N; i++) {
        // 선택하지 않는 경우
        int exclude = dp[i - 1];

        // 선택하는 경우
        int include = 1;
        int lastNonConflicting = binarySearch(meetings, i);
        if (lastNonConflicting != -1) {
            include += dp[lastNonConflicting];
        }

        // 최댓값 선택
        dp[i] = (exclude > include) ? exclude : include;
    }

    // 결과 출력
    printf("%d\n", dp[N - 1]);

    // 메모리 해제
    free(meetings);
    free(dp);

    return 0;
}
