#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* treeNode;
    int depth;   
} StackNode;

typedef struct Stack {
    StackNode data[100];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}


void push(Stack* stack, TreeNode* treeNode, int depth) {
    stack->data[++(stack->top)].treeNode = treeNode;
    stack->data[stack->top].depth = depth;
}


StackNode pop(Stack* stack) {
    return stack->data[(stack->top)--];
}


void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else if (direction == 1) {
        node->right = newNode;
    }
}


void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

// 노드 합 구하기 
int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    initStack(&stack);
    push(&stack, root, 1);  

    int sum = 0;

    while (!isEmpty(&stack)) {
        StackNode current = pop(&stack);
        TreeNode* node = current.treeNode;
        sum += node->data;

        if (node->right) push(&stack, node->right, current.depth + 1);
        if (node->left) push(&stack, node->left, current.depth + 1);
    }

    return sum;
}

// 노드 개수 구하기 
int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    initStack(&stack);
    push(&stack, root, 1);  
    int count = 0;

    while (!isEmpty(&stack)) {
        StackNode current = pop(&stack);
        TreeNode* node = current.treeNode;
        count++;

        if (node->right) push(&stack, node->right, current.depth + 1);
        if (node->left) push(&stack, node->left, current.depth + 1);
    }

    return count;
}

// 트리 높이 구하기 
int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    initStack(&stack);

    
    push(&stack, root, 1);

    int maxDepth = 0;

    
    while (!isEmpty(&stack)) {
        StackNode current = pop(&stack);
        TreeNode* node = current.treeNode;
        int currentDepth = current.depth;

        
        if (currentDepth > maxDepth) {
            maxDepth = currentDepth;
        }

        
        if (node->left) {
            push(&stack, node->left, currentDepth + 1);
        }
        if (node->right) {
            push(&stack, node->right, currentDepth + 1);
        }
    }

    return maxDepth;
}

// 노드의 수 구하기 
int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    Stack stack;
    initStack(&stack);
    push(&stack, root, 1);  

    int leafCount = 0;

    while (!isEmpty(&stack)) {
        StackNode current = pop(&stack);
        TreeNode* node = current.treeNode;

        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }
        else {
            if (node->right) push(&stack, node->right, current.depth + 1);
            if (node->left) push(&stack, node->left, current.depth + 1);
        }
    }

    return leafCount;
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);

    int sum = GetSumOfNodes(root);
    int numberOfNodes = GetNumberOfNodes(root);
    int height = GetHeightOfTree(root);
    int leafNodes = GetNumberOfLeafNodes(root);

    printf("Sum of nodes: %d\n", sum);
    printf("Number of nodes: %d\n", numberOfNodes);
    printf("Height of Tree: %d\n", height);
    printf("Number of leaf nodes: %d\n", leafNodes);

    return 0;
}
