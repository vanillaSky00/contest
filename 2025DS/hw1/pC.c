#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char c;
    struct Node *left, *right;
} Node;

Node* createNode(char c){
    Node* n = (Node*)malloc(sizeof(*n));
    n->c = c; 
    n->left = n->right = NULL;
    return n;
}

Node* insertAfter(Node* cur, char ch){
    Node* n = createNode(ch);
    n->left = cur;
    n->right = cur->right;

    if (cur->right) cur->right->left = n;
    cur->right = n;
    return n;  // cursor should end up AFTER inserted char
}

void deleteAt(Node** cur, Node* dummy){
    if (*cur == dummy) return; // nothing to the left -> ignore

    Node* del = *cur;
    Node* L = del->left;
    Node* R = del->right;
    if (L) L->right = R;
    if (R) R->left  = L;
    *cur = L;  // stay immediately after new left char
    free(del);
}

void moveCursor(Node** cur, Node* dummy, int dir){ // 0=L, 1=R
    if (dir == 0) { // L
        if (*cur != dummy) *cur = (*cur)->left;// ignore at beginning
    } else { // R
        if ((*cur)->right) *cur = (*cur)->right;// ignore at end
    }
}

int main(void){
    char str[256];
    if (scanf("%255s", str) != 1) return 0;

    int M;
    if (scanf("%d", &M) != 1) return 0;

    Node* dummy  = createNode('@');
    Node* cursor = dummy;// cursor = node to the LEFT of cursor position

    for (int i = 0; str[i]; ++i) cursor = insertAfter(cursor, str[i]);

    while (M--){
        char cmd;
        scanf(" %c", &cmd);// read one non-space char
        if (cmd == 'L')       moveCursor(&cursor, dummy, 0);
        else if (cmd == 'R')  moveCursor(&cursor, dummy, 1);
        else if (cmd == 'I') { char ch; scanf(" %c", &ch); cursor = insertAfter(cursor, ch); }
        else if (cmd == 'D')  deleteAt(&cursor, dummy);
    }

    // 'head' may have been deleted.
    for (Node* p = dummy->right; p; p = p->right) putchar(p->c);
    putchar('\n');
    return 0;
}

// wrong::
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// typedef struct Node {
//     char c;
//     struct Node* left;
//     struct Node* right;
// } Node;

// Node* createNode(char c);
// Node* insertAfter(Node* cursor, char c);
// void deleteAt(Node** cursor, Node* dummy);
// void moveCursor(Node** cursor, Node* dummy, int mode);

// int main() {
//     char str[256];
//     if (scanf("%255s", str) != 1) return 0;

//     int t = 0;
//     if (scanf("%d", &t) != 1) return 0;

//     Node* dummy = createNode('@');//dummy head
//     Node* cursor = dummy;

//     for(int i = 0; str[i]; i++) {cursor = insertAfter(cursor, str[i]);}

//     while(t--) {
//         char cmd;
//         scanf(" %c", &cmd);
//         switch (cmd) {
//             case 'L': moveCursor(&cursor, dummy, 0); break;
//             case 'R': moveCursor(&cursor, dummy, 1); break;
//             case 'I': {
//                 char ch;
//                 scanf(" %c", &ch);             // see notes on " %c" below
//                 cursor = insertAfter(cursor, ch);
//                 break;
//             }
//             case 'D': deleteAt(&cursor, dummy); break;
//             default:  /* ignore invalid command */ break;
//         }
//     }

//     for (Node* p = dummy->right; p; p = p->right) putchar(p->c);
//     putchar('\n');
//     return 0;
// }


// Node* createNode(char c) {
//     Node* newNode = (Node*) malloc(sizeof(*newNode));
//     newNode->c = c;
//     newNode->left = NULL;
//     newNode->right = NULL;
//     return newNode;
// }

// Node* insertAfter(Node* cursor, char c) {
//     Node* new = createNode(c);
//     new->right = cursor->right;
//     new->left = cursor;

//     cursor->right = new;
//     if (new->right) new->right->left = new;
//     return new;
// }

// void deleteAt(Node** cursor, Node* dummy) {
//     if (!cursor || !*cursor || *cursor == dummy) return;

//     Node* deletedNode = *cursor;
//     // then move cursor first, forward since it is a deletion


//     Node* L = deletedNode->left;
//     Node* R = deletedNode->right;
//     if (L) L->right = deletedNode->right;
//     if (R) R->left = deletedNode->left;
//     //*cursor = (*cursor)->left;
//     *cursor = L ? L : R;//just guard
//     free(deletedNode);
// }

// void moveCursor(Node** cursor, Node* dummy, int mode) {// 0 move left 
//     if (cursor == NULL) return;
//     if (mode == 0) {// be careful if cursor == dummy
//         if ((*cursor)->left != NULL) {
//             (*cursor) = (*cursor)->left;
//         }
//     }
//     else {
//         if ((*cursor)->right != NULL) {
//             (*cursor) = (*cursor)->right;
//         }
//     }
// }