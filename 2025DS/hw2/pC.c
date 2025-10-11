#include <stdio.h>
#include <string.h>
#define MAXLEN 10005
#define MAXTOK 10005
typedef struct Token {
    int type;   // 1 = number, 2 = operator, 3 = parentheses
    char ch;    // operator or parentheses
    int num;    // number
} Token;
Token input[MAXTOK];
int input_len = 0;
void init() {
    for (int i = 0; i < MAXTOK; i++) {
        input[i].type = 0;
        input[i].ch = '\0';
        input[i].num = 0;
    }
}
void getInput() {
    char line[MAXLEN];
    fgets(line, sizeof(line), stdin);
    int len = strlen(line);
    for (int i = 0; i < len; i++) {
        char c = line[i];
        if (c == ' ')
            input_len += 1;
        else if ('0' <= c && c <= '9') {
            input[input_len].type = 1; // number
            input[input_len].num = input[input_len].num * 10 + (c - '0');
        } else if (c == '+' || c == '-' || c == '*' || c == '/') {
            input[input_len].type = 2; // operator
            input[input_len].ch = c;
        } else if (c == '(' || c == ')') {
            input[input_len].type = 3; // parentheses
            input[input_len].ch = c;
        } else {
            break; // end of line
        }
    }
    ++input_len;
}
void test() {
    printf("input length = %d\n", input_len);
    for (int i = 0; i < input_len; i++) {
        if (input[i].type == 1)
            printf("%d\n", input[i].num);
        else if (input[i].type == 2)
            printf("%c\n", input[i].ch);
        else
            printf("%c\n", input[i].ch);
    }
}
void printResult(int res) {
    printf("%d\n", res);
    // TODO: print preorder
    printf("\n");
}
int main() {
    init();
    getInput();
    test(); // TODO: for testing, remember to delete it before submitting
    int res = 0;
    // TODO: calculate result and transform the expression
    printResult(res);
    return 0;
}