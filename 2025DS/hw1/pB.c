#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000000

static int freq[MAXN + 1];
static long long prefCnt[MAXN + 1];

int main() {
    int n, k;
    if(scanf("%d %d", &n, &k) != 2) exit(EXIT_FAILURE);

    int maxNum = -1;
    for (int i = 0; i < n; i++) {
        int num; scanf("%d", &num);
        if (num > MAXN) num = MAXN;// boundary safty
        freq[num]++;
        maxNum = (maxNum > num) ? maxNum : num;
    }

    // no team can join
    if (k > maxNum) {
        printf("0\n");
        return 0;
    }

    for (int i = 1; i <= maxNum; i++) {
        prefCnt[i] = prefCnt[i-1] + freq[i]; 
    }

    long long bestAns = -1;
    for (int i = k; i <= maxNum; i++) {
        long long ans = 0;
        // blocks [i*j, (j+1)*i-1], for j >= 1
        for (int j = 1; j * i <= maxNum; j++) {
            int L = i * j;
            int R = (j + 1) * i - 1;
            if (R > maxNum) R = maxNum;
            long long rangeCnt = prefCnt[R] - prefCnt[L - 1];
            ans += 1LL * i * j * rangeCnt; // each contributes j*t
          
        }
        bestAns = (bestAns > ans) ? bestAns : ans;
    }

    printf("%lld\n", bestAns);
    return 0;
}