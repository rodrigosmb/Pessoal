#include <stdio.h>

int N;
int M;
int delta;

int main() {
    scanf("%d", &N);
    scanf("%d", &M);
    delta = N - M;
    printf("%d\n", delta);
    return 0;
}