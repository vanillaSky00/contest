#include <stdio.h>
#include <string.h>
#define MAXN 2000005

static int L[MAXN], R[MAXN], val[MAXN];
enum { HEAD = 0, TAIL = 1};
static inline void link(int a, int b) { R[a] = b; L[b] = a;} // a <-> b

int main(void){
    int n, t;
    if (scanf("%d %d", &n, &t) != 2) return 0;
    int numOfElement = n;

// sentinel: HEAD <-> node2 <-> node3 <-> ... <-> nodeN+1 <-> TAIL
    L[HEAD] = -1; L[TAIL] = HEAD;
    R[HEAD] = TAIL; R[TAIL] = -1;

    int next_id = 2;
    for (int i = 0; i < n; i++) {
        int id = next_id++;
        scanf("%d", &val[id]);
        // insert before tail
        link(L[TAIL], id);
        link(id, TAIL);
    } 

    while (t--){
        char op[4];
        scanf("%s", op);
        int k, x;

        if (op[0] == 'H' && op[1] == '\0') {
            numOfElement++;
            scanf("%d", &x);         
            int id = next_id++;
            val[id] = x;
            link(id, R[HEAD]);
            link(HEAD, id);
        }
        else if (op[0] == 'T' && op[1] == '\0') {
            numOfElement++;
            scanf("%d", &x);             
            int id = next_id++;
            val[id] = x;
            link(L[TAIL], id);
            link(id, TAIL);
        } 
        else if (op[0] == 'A') {
            numOfElement++;
            scanf("%d %d", &k, &x); k++;// real node start 2
            int id = next_id++;
            val[id] = x;
            link(id, R[k]);
            link(k, id);
        }
        else if (op[0] == 'B') {
            numOfElement++;
            scanf("%d %d", &k, &x); k++;// real node start 2
            int id = next_id++;
            val[id] = x;
            link(L[k], id);
            link(id, k);
        }
        else if (op[0] == 'D') {
            numOfElement--;
            scanf("%d", &k); k++;// real node start 2   
            link(L[k], R[k]);
        }
        else if (op[0] == 'M' && op[1] == 'H') {
            scanf("%d", &k); k++;// real node start 2   
            link(L[k], R[k]);
            link(k, R[HEAD]);
            link(HEAD, k);
        }
        else if (op[0] == 'M' && op[1] == 'T') {
            scanf("%d", &k); k++;// real node start 2   
            link(L[k], R[k]);
            link(L[TAIL], k);
            link(k, TAIL);
        }
    }

    if (numOfElement == 0) {
        printf("EMPTY\nEMPTY\n");
        return 0;
    }

    // print head -> tail
    for (int i = R[HEAD]; i != TAIL; i = R[i]) {
        if (i != R[HEAD]) putchar(' ');
        printf("%d", val[i]);
    }
    putchar('\n');

    // print tail -> head
    for (int i = L[TAIL]; i != HEAD; i = L[i]) {
        if (i != L[TAIL]) putchar(' ');
        printf("%d", val[i]);
    }
    putchar('\n');
    return 0;
}