#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// use bidirectionalBFS can further optimize
static int solve(char** maze, int n, int m) {
    
    // find B for starting and E for ending
    // make the teleport hole mapping
    int start = 1, end = -1;
    int holes[26][2]; //  magic hole appears at most 2 times
    for (int i = 0; i < 26; i++) holes[i][0] = holes[i][1] = -1;

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < m; c++) {
            char ch = maze[r][c];
            if (ch == 'B') start = r * m + c;
            else if (ch == 'E') end = r * m + c;
            else if (ch >= 'A' && ch <= 'Z') {
                if (holes[ch - 'A'][0] == -1) holes[ch - 'A'][0] = r * m + c;
                else holes[ch - 'A'][1] = r * m + c;
            }
        }
    }

    if (start == -1 || end == -1) return -1;


    int* q = (int*) malloc(sizeof(int) * (n * m));
    bool* seen = (bool*) calloc(n * m, sizeof(bool));
    int front = 0, rear = 0;
    q[rear++] = start;
    seen[start] = true;

    printf("start:%d, end:%d\n", start, end);
    int dis = 0;
    int directions[5] = {0, -1, 0, 1, 0}; 
    
    while (rear > front) {
        int size = rear - front;
        printf("layer\n");
        while (size-- > 0) {
            int at = q[front++];
            int ar = at / m;
            int ac = at % m;
            printf("(%d,%d)\n", ar, ac);
            if (at == end) {
                free(q);
                free(seen);
                return dis;
            }

            for (int i = 1; i < 5; i++) {
                int nr = ar + directions[i - 1];
                int nc = ac + directions[i];
                int idx;
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && seen[idx = nr * m + nc] == false) {
                    char nei = maze[nr][nc];
                    if ((nei >= 'A' && nei <= 'Z') || nei == '.') {
                        q[rear++] = idx;
                        seen[idx] = true; 
                    }
                } 
            }

            // magic holes as a neighbor also
            int ch = maze[ar][ac];
            if (ch >= 'A' && ch <= 'Z') {
                for (int i = 0; i < 2; i++) {
                    int hole = holes[ch - 'A'][i];
                    if (hole != -1 && hole != at && seen[hole] == false) {
                        q[rear++] = hole;
                        seen[hole] = true;
                    }
                }
            }
        }
        dis++; // add here to avoid additional 1
    }

    free(q);
    free(seen);
    return -1;
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    char** maze = (char**) malloc(sizeof(char*) * n);
    for (int i = 0; i < n; i++) {
        maze[i] = (char*) malloc(sizeof(char) * (m + 1));
    }
    
    for (int i = 0; i < n; i++) {
        scanf("%s", maze[i]); // %c would read '\n'
    }

    int res = solve(maze, n, m);

    for (int i = 0; i < n; i++) free(maze[i]);
    free(maze);

    printf("\nmin cost: %d\n", res);
    return res;
}