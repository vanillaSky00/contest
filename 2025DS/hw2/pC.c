#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

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


Token answer[MAXTOK];
int answer_len = 0;

static inline bool isOperator(char c) { 
    return c=='+'||c=='-'||c=='*'||c=='/'; 
}
 
static inline int precedency(char c) { 
    return (c == '+' || c == '-' ) ? 1 : (c == '*' || c == '/' ) ? 2 : -1; 
}

static inline long long apply(long long a, long long b, char op){
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    // assume integer division like C (b != 0 assumed for this task)
    return a / b;
}

void infixToPrefix() {
    int n = input_len;
    Token stack[n];
    int top = -1;
    int ansIdx = 0;

    // scan from right to left
    // number -> parenthesis -> operator
    for (int i = n - 1; i >= 0; i--) {
        Token token = input[i];

        if (token.type == 1) answer[ansIdx++] = token;
        else if (token.type == 3 && token.ch == ')') { 
            stack[++top] = token;
        }
        else if (token.type == 3 && token.ch == '(') {
            while (top != -1 && stack[top].ch != ')') {
                answer[ansIdx++] = stack[top--];
            }
            if (top != -1) top--; // pop ')'
        }
        else if (token.type == 2) {
            while (top != -1 && stack[top].type == 2 && 
                    precedency(stack[top].ch) > precedency(token.ch)) {
                answer[ansIdx++] = stack[top--];
            }
            stack[++top] = token;
        }
    }

    // pop the remaining ops
    while (top != -1) answer[ansIdx++] = stack[top--];

    // reverse
    for (int i = 0; i < ansIdx / 2; i++) {
        Token tmp = answer[i];
        answer[i] = answer[ansIdx - i - 1];
        answer[ansIdx - i - 1] = tmp;
    }

    answer_len = ansIdx;
}

void printResult(int res) {
    printf("%d\n", res);
    
    // print preorder
    for (int i = 0; i < answer_len; i++) {
        Token t = answer[i];
        if (t.type == 1) {
            printf("%d ", t.num);
        }
        else {
            printf("%c ", t.ch);
        }
    }
    printf("\n");
}

int evalPrefix() {
    long long stack[MAXTOK];
    int top = -1;
    int n = answer_len;
    for (int i = n - 1; i >= 0; i--) {
        if (answer[i].type == 1) {
            stack[++top] = answer[i].num;
        }
        else if (answer[i].type == 2) {
            long long x = stack[top--];
            long long y = stack[top--];
            stack[++top] = apply(x, y, answer[i].ch);
        }
    }
    return stack[0];
}

int main() {
    init();
    getInput();
    //test(); 

    infixToPrefix();
    int res = evalPrefix();

    printResult(res);
    return 0;
}