#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* root, int value) {
    if (root == NULL)
        return createNode(value);

    if (value < root->value)
        root->left = insert(root->left, value);
    else
        root->right = insert(root->right, value);

    return root;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int left = height(root->left);
    int right = height(root->right);

    return (left > right ? left : right) + 1;
}

int widthLevel(Node* root, int level) {
    if (root == NULL)
        return 0;

    if (level == 1)
        return 1;

    return widthLevel(root->left, level - 1) +
        widthLevel(root->right, level - 1);
}

int treeWidth(Node* root) {
    int h = height(root);
    int maxWidth = 0;

    for (int i = 1; i <= h; i++) {
        int w = widthLevel(root, i);

        if (w > maxWidth)
            maxWidth = w;
    }

    return maxWidth;
}

void printTree(Node* root, int level) {
    if (root == NULL)
        return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++)
        printf("   ");

    printf("%d\n", root->value);

    printTree(root->left, level + 1);
}

int main() {
    Node* root = NULL;

    int values[] = { 50, 30, 70, 20, 40, 60, 80, 10, 25 };
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    printf("Tree:\n");
    printTree(root, 0);

    printf("\nTree width: %d\n", treeWidth(root));

    return 0;
}
