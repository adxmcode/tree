#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Node {
    int* data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int* data);
struct Node* insert(struct Node* root, int* data);
bool findPath(struct Node* node, int* start, int* finish);
bool findPathHelper(struct Node* root, int* destination);
bool isThere(struct Node* root, int* data);

struct Node* createNode(int* data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    if(!newNode) {
        exit(1);
    }
    newNode->data = malloc(sizeof(data) + 1);
    if(!newNode->data) {
        exit(1);
    }
    *(newNode->data) = *data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insert(struct Node* root, int* data) {
    if (root == NULL) {
        return createNode(data);
    }

    if(*data < *(root->data)) {
        root->left = insert(root->left, data);
    } 
    else if (*data > *(root->data)) {
        root->right = insert(root->right, data);
    }
    return root;
}

bool findPath(struct Node* root, int* start, int* finish){
   if(root == NULL){
       printf("list empty\n");
       return false;
   }
    
   bool startTest = isThere(root, start);
   bool finishTest = isThere(root, finish);
   if(startTest && finishTest){
       printf("path from %d to %d: ", *start, *finish);
       return findPathHelper(root, finish);
   }
    else{
      printf("start or destination node not found\n");
      return false;
    }
}

bool findPathHelper(struct Node* root, int* destination) {
    if(root == NULL){
        return false;
    }

    printf("%d", *(root->data));

    if(*(root->data) == *destination){
        printf("->NULL\n");
        return true;
    }

    printf("->");

    if (*destination < *(root->data)) {
        return findPathHelper(root->left, destination);
    }
    else{
        return findPathHelper(root->right, destination);
    }
}

bool isThere(struct Node* root, int* data){
    if(root == NULL){
        return false;
    }
    if(*data == *(root->data)){
        return true;
    }
    else if (data < root->data){
        return isThere(root->left, data);
    }
    else{
        return isThere(root->right, data);
    }
}

int main() {
    struct Node* tree = NULL;
    int putIn = 0;
    printf("insert numbers into the tree. enter -1 to stop \n");
    while(putIn != -1) {
        scanf(" %d", &putIn);
        tree = insert(tree, &putIn);
    }
    printf("Would you like to find the path from one node to another? (y/n) \n");
    char answer;
    scanf(" %c", &answer);
    while(answer == 'y') {
        int start, finish;
        printf("enter the starting node \n");
        scanf(" %d", &start);
        printf("enter the destination node \n");
        scanf(" %d", &finish);
        findPath(tree, &start, &finish);
        printf("\nWould you like to try another path? (y/n) \n");
        scanf(" %c", &answer);
    }
    printf("See you next time!");
}