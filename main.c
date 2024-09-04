#include "header/list.h"
#include "header/stack_and_queue.h"
#include "header/trees.h"

#define NUMBER_OF_TASKS 5

int main(int argc,char *argv[])  {
    if(argc<4) exit ( 1 ); 
    int nr_echipe,iteratie_echipe_lista=0,task;
    char *inputfile=argv[1],*datafile=argv[2],*outfile=argv[3];
    FILE *inputFile,*dataFile,*outFile;
    inputFile = fopen(inputfile, "r"),dataFile = fopen(datafile, "r"),outFile = fopen(outfile, "w");
    if (inputFile == NULL || dataFile == NULL || outFile == NULL) return 1; 
    fscanf(dataFile,"%d",&nr_echipe);
    NodeA* head_lista_jucatori=NULL;
    NodeB* eight_teams=NULL;
    head_lista_jucatori=(NodeA*) malloc(sizeof(NodeA));
    eight_teams=(NodeB*)malloc(sizeof(NodeB));
    Queue* coada_matchuri=creare_coada();
    BST* root=NULL;
    BST* AVL=NULL;
    S* winners=creare_stiva();
    S* losers=creare_stiva();
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            completare_lista(&head_lista_jucatori,iteratie_echipe_lista,nr_echipe,dataFile);
            printfile(&head_lista_jucatori,outFile,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            modificare_lista(&head_lista_jucatori,&nr_echipe);
            printfile(&head_lista_jucatori,outFile,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1) {
            printfile(&head_lista_jucatori,outFile,outfile);
            afisare_rezultate_meciuri(&head_lista_jucatori,&eight_teams,coada_matchuri,&winners,&losers,&nr_echipe,outFile,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1){
            deletelastElem(&eight_teams);
            NodeB* head=eight_teams;
            while(head!=NULL){
                root=insertBST(root,head->score,head->nume_echipa);
                head=head->next;
            }
            displayBSTToFile(root,outfile);
    }
    fscanf(inputFile,"%d",&task);
    if(task==1){
        transformAVL(&AVL,root);    
        displayLevelTwo(AVL,outfile);
}
    return 0;   
}