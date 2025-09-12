#include <stdio.h>
#define BUF_SIZE 1 << 16

char buf[BUF_SIZE];
int idx = 0, nbytes = 0;

int read_int() {
    int x = 0, neg = 0;
    while (1) {
        if (idx >= nbytes) {
            nbytes = fread(buf, 1, BUF_SIZE, stdin);
            idx = 0;
            if (nbytes == 0) return 0; // EOF
        }
        char c = buf[idx++];
        if (c == '-') neg = 1;
        else if (c >= '0' && c <= '9') {
            x = x * 10 + (c - '0');
        } else if (x > 0 || neg) break;
    }
    return neg ? -x : x;
}

int main() {
    int t = read_int();
    while (t--) {
        int n = read_int();
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += read_int();
        }
        printf("%lld\n", sum);
    }
    return 0;
}
