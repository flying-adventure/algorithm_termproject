#include <stdio.h>
#include <stdlib.h>

// 회의 구조체 정의
typedef struct {
    int start;
    int end;
} Meeting;

// 종료 시간 기준으로 정렬하기 위한 비교 함수
int compare(const void *a, const void *b) {
    Meeting *m1 = (Meeting *)a;
    Meeting *m2 = (Meeting *)b;
    if (m1->end == m2->end) {
        return m1->start - m2->start; // 종료 시간이 같으면 시작 시간으로 정렬
    }
    return m1->end - m2->end; // 종료 시간 기준 정렬
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("파일을 열 수 없습니다");
        return 1;
    }

    int n; //회의 개수
    fscanf(file, "%d", &n);

    Meeting meetings[n];
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d %d", &meetings[i].start, &meetings[i].end);
    }
    fclose(file);

    // 종료 시간 기준으로 정렬
    qsort(meetings, n, sizeof(Meeting), compare);

    int count = 0;    // 최대 회의 개수
    int last_end = 0; // 마지막으로 선택한 회의의 종료 시간

    for (int i = 0; i < n; i++) {
        if (meetings[i].start >= last_end) { // 현재 회의(meetings[i])의 시작 시간이 last_end 이후라면
            count++;
            last_end = meetings[i].end; //count를 1 증가시키고, last_end를 업데이트
        }
    }

    printf("%d\n", count);
    return 0;
}