#include "../header/trees.h"

BST* newNode(float score,char *team_of_linked_list){
    BST *node = (BST*)malloc(sizeof(BST));
    node->team=strdup(team_of_linked_list);
    node->score=score;
    node->height = 1;
    node->left = node->right = NULL;

    return node;
}

int height(BST *node){
    if(node == NULL)
        return 1;
    return node->height;
}

int maxx(int a,int b){
    return(a>b)? a:b;
}

BST* insertBST(BST *node, float team_score, char* team_of_list) {

    if (node == NULL) {
        node=newNode(team_score, team_of_list);
        return node;
    }

    if (team_score < node->score) {
        node->left = insertBST(node->left, team_score, team_of_list);
    } else if (team_score > node->score) {
        node->right = insertBST(node->right, team_score, team_of_list);
    } else {
        if (strcmp(team_of_list, node->team) > 0) {
            node->right = insertBST(node->right, team_score, team_of_list);
        } else {
            node->left = insertBST(node->left, team_score, team_of_list);
        }
    }

    node->height = 1 + maxx(height(node->left), height(node->right));
    return node;
}

int getBalance(BST *node){
    if(node == NULL)
        return 0;
    return (height(node->left) - height(node->right));
}

BST *leftRotation(BST *x){
    BST *y = x->right;
    BST *T2 = y->left;
 
    y->left = x;
    x->right = T2;
 
    x->height = 1 +maxx(height(x->left), height(x->right));
    y->height = 1 +maxx(height(y->left), height(y->right));
 
    return y;
}

BST *rightRotation(BST *y){
    BST *x = y->left;
    BST *T2 = x->right;
 
    x->right = y;
    y->left = T2;
 
    y->height = 1 +maxx(height(y->left), height(y->right));
    x->height = 1 +maxx(height(x->left), height(x->right));
 
    return x;
}

BST *LRRotation(BST *Z){
    Z->left = leftRotation(Z->left);
    return rightRotation(Z);
}

BST *RLRotation(BST *Z){
    Z->right = rightRotation(Z->right);
    return leftRotation(Z);
}

BST* insertAVL(BST* node,float score,char* team_of_bst) {
    if(node == NULL) return newNode(score,team_of_bst);
    
    if(score < node->score)
        node->left = insertAVL(node->left,score,team_of_bst);
    else if(score> node->score)
        node->right = insertAVL(node->right,score,team_of_bst);
    else
        if(strcmp(team_of_bst, node->team) > 0)
            node->right = insertAVL(node->right,score,team_of_bst);
        else
            node->left = insertAVL(node->left,score,team_of_bst);

    node->height = 1 +maxx(height(node->left), height(node->right));

    int balance = getBalance(node);

    if(balance > 1) { 
        if(score< node->left->score)
            return rightRotation(node);
                else if(score == node->left->score) {
                    if(strcmp(team_of_bst, node->left->team) < 0) 
                        return rightRotation(node);
            }
    }

    if(balance < -1) {
        if(score> node->right->score)
            return leftRotation(node);
        else if(score == node->right->score) {
            if(strcmp(team_of_bst, node->right->team) > 0) 
                return leftRotation(node);
        }
    }

    if(balance > 1 && score > node->left->score)
        return LRRotation(node);
    if(balance < -1 && score < node->right->score)
        return RLRotation(node);

    return node;
}


void transformAVL(BST **AVL, BST *root){
    if(root){
        transformAVL(AVL, root->right);
        *AVL = insertAVL(*AVL,root->score,root->team);
        transformAVL(AVL, root->left);
    }
}

void displayTeamsFromLevel(BST *root,FILE* filename){
    if(root){
        displayTeamsFromLevel(root->right,filename);
        if(root->height == 2)   fprintf(filename, "%s\n", root->team);
        displayTeamsFromLevel(root->left,filename);
    }
}

void displayLevelTwo(BST* root,const char* file){
    FILE* filename=fopen(file,"a");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }
    fprintf(filename,"\nTHE LEVEL 2 TEAMS ARE:\n");
    displayTeamsFromLevel(root,filename);
    fclose(filename);
}

void displayTeamsAndPoints(BST *root,FILE* filename){
    if(root){
        displayTeamsAndPoints(root->right,filename);
        fprintf(filename,"%-34s-  %.2f\n", root->team, root->score);
        displayTeamsAndPoints(root->left,filename);
    }
}

void displayBSTToFile(BST* root,const char* file) {
    FILE* filename = fopen(file, "a");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }
    fprintf(filename, "\nTOP 8 TEAMS:\n");
    displayTeamsAndPoints(root,filename);
    fclose(filename);
}





