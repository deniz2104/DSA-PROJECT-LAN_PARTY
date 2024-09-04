#include "../header/list.h"

//functie pentru calcularea mediei aritmetice
float media_aritmetica(NodeA* head,int nr_jucatori)  {
int s=0;
for(int i=0; i<nr_jucatori; i++)    {
    s+=head->jucator[i].points;
}
return (float)s/nr_jucatori;
}

//functie pentru adaugare in lista
void add_at_beginning(NodeA** head, FILE *filename)      {
    int nr_jucatori, puncte_jucator, i;
    NodeA* newNodeA = (NodeA*)malloc(sizeof(NodeA));
    newNodeA->nume_echipa = (char*)malloc(Nr_Max * sizeof(char));
    fscanf(filename, "%d", &nr_jucatori);
    fgets(newNodeA->nume_echipa, Nr_Max, filename);
    (newNodeA->nume_echipa)++; //incrementez ca sa nu mai am spatiu la inceput
    newNodeA->nume_echipa[strcspn(newNodeA->nume_echipa,"\n")-1] = '\0';
    if(newNodeA->nume_echipa[strlen(newNodeA->nume_echipa)-1]==' ') newNodeA->nume_echipa[strlen(newNodeA->nume_echipa)-1]='\0';
    newNodeA->nr_jucatori = nr_jucatori;
    newNodeA->jucator=(struct Player*)malloc(newNodeA->nr_jucatori*sizeof(struct Player));
    for (i = 0; i < newNodeA->nr_jucatori; i++) {
        newNodeA->jucator[i].firstName = (char*)malloc(Nr_Max * sizeof(char));
        newNodeA->jucator[i].secondName = (char*)malloc(Nr_Max * sizeof(char));
        fscanf(filename, "%s", newNodeA->jucator[i].firstName);
        fscanf(filename, "%s", newNodeA->jucator[i].secondName);
        fscanf(filename, "%d", &puncte_jucator);
        newNodeA->jucator[i].points = puncte_jucator;
    }
    newNodeA->score=media_aritmetica(newNodeA,newNodeA->nr_jucatori);
newNodeA->next=*head;
*head=newNodeA;
}

void add_at_beginning_ultimele_8_echipe(NodeA** head,char* team,float score){
    NodeA* newNodeA=(NodeA*)malloc(sizeof(NodeA));
    newNodeA->nume_echipa=strdup(team);
    newNodeA->score=score;
    newNodeA->next=*head;
    *head=newNodeA;
}

void completare_lista(NodeA** head,int index,int numar_echipe,FILE* filename)    {
    while(index<numar_echipe)
            {
            add_at_beginning(&(*head),filename);
            index++;
            }
}

//functie pentru punerea in fisier a numelor echipelor
void printfile(NodeA** head,FILE* filename,const char* file)     {
    filename=fopen(file,"w");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }
    NodeA *iter=*head;
    while(iter->next!=NULL)
        {   
            fprintf(filename,"%s",iter->nume_echipa);
            fprintf(filename,"\n");
            iter=iter->next;
        }
        fclose(filename);
}

//functie pentru a verifica daca un numar este multiplu de 2
int multiplu_de_2(int numar_echipe)     {
    while(numar_echipe>1 && numar_echipe%2==0 )
        numar_echipe/=2;
    if(numar_echipe!=1) return 0;
    else  return 1;
}

//functie pentru stergerea unui nod
void stergere_element_lista(NodeA** head, char* nume_echipa)     {
    if (*head == NULL) return;


    NodeA* headcopy = *head;
    NodeA* prev = NULL;

    if (strcmp(headcopy->nume_echipa, nume_echipa) == 0) {
        *head = headcopy->next;
        free(headcopy);
        return;
    }

    while (headcopy != NULL && strcmp(headcopy->nume_echipa, nume_echipa) != 0) {
        prev = headcopy;
        headcopy = headcopy->next;
    }

    if (headcopy == NULL) return;

    prev->next = headcopy->next;
    free(headcopy);
}

//functie care calculeaza care e echipa cu media minima din lista
void min(NodeA** head) {
    
    float min = INT_MAX;
    NodeA* min_NodeA = NULL;

    NodeA* iter_gasire_minim = *head;
    while (iter_gasire_minim != NULL) {
        float avg = media_aritmetica(iter_gasire_minim, iter_gasire_minim->nr_jucatori);
        
        if (avg < min && fabs(min-avg)>epsilon) {
            min = avg;
            min_NodeA = iter_gasire_minim;
        }

        iter_gasire_minim = iter_gasire_minim->next;
    }

        if (min_NodeA != NULL)  stergere_element_lista(&(*head),min_NodeA->nume_echipa);
}

//functie pentru modificarea listei pana la 2^n
void modificare_lista(NodeA **head,int *numar_echipe)    {
while(multiplu_de_2(*numar_echipe)!=1)  {
        min(&(*head));
        (*numar_echipe)--;
    }
}
