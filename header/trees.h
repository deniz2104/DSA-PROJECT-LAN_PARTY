#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
typedef struct BST{
    char* team;
    float score;
    int height;
    struct BST *left, *right;
}BST;

BST *newNode(float score,char* team);
int height(BST* root);
BST *insertBST(BST *node,float team_score,char* team_of_list);
int maxx(int a,int b);
void displayTeamsAndPoints(BST *root, FILE* filename);
void displayBSTToFile(BST* root,const char* file);
int getBalance(BST *node);
BST *leftRotation(BST *x);
BST *rightRotation(BST *y);
BST *LRRotation(BST *Z);
BST *RLRotation(BST *Z);
void transformAVL(BST **AVL, BST *root);
BST* insertAVL(BST* node,float score,char* team_of_bst);
void displayTeamsFromLevel(BST *root,FILE* filename);
void displayLevelTwo(BST* root,const char* file);