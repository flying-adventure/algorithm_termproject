#include <stdio.h>
#include <stdlib.h>

// 회의 정보를 저장할 구조체를 정의함.
typedef struct {
    int start;
    int end;
} Meeting;

// 회의 종료 시간을 기준으로 정렬, 종료 시간이 같으면 시작 시간을 기준으로 정렬
int compare(const void* a, const void* b) {
    Meeting* m1 = (Meeting*)a;
    Meeting* m2 = (Meeting*)b;
    if (m1->end == m2->end)
        return m1->start - m2->start;
    return m1->end - m2->end;
}

// 이진 탐색, 이전 겹치지 않는 회의를 찾음
int binarySearch(Meeting meetings[], int dp[], int index) {
    int left = 0, right = index - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (meetings[mid].end <= meetings[index].start) {
            if (meetings[mid + 1].end <= meetings[index].start)
                left = mid + 1;
            else
                return mid;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    FILE* file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Failed to open input.txt\n");
        return 1;
    }

    int N;
    fscanf(file, "%d", &N);

    Meeting meetings[N];
    for (int i = 0; i < N; i++) {
        fscanf(file, "%d %d", &meetings[i].start, &meetings[i].end);
    }
    fclose(file);

    // 회의를 종료 시간 기준으로 정렬
    qsort(meetings, N, sizeof(Meeting), compare);

    // DP 배열 선언 & 초기화
    int dp[N];
    dp[0] = 1; // 첫 번째 회의는 항상 선택 가능하게

    for (int i = 1; i < N; i++) {
        // 현재 회의를 포함하지 X 경우
        int exclude = dp[i - 1];

        // 현재 회의를 포함 O 경우
        int include = 1;
        int lastNonConflicting = binarySearch(meetings, dp, i);
        if (lastNonConflicting != -1) {
            include += dp[lastNonConflicting];
        }

        // 최댓값 선택
        dp[i] = (exclude > include) ? exclude : include;
    }

    // 최댓값 출력
    printf("\n result: %d\n", dp[N - 1]);
    return 0;
}
