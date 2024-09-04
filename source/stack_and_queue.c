#include "../header/stack_and_queue.h"

Queue* creare_coada()     {
    Queue *q=(Queue*)malloc(sizeof(Queue));
    q->front=q->rear=NULL;
    return q;
}

S* creare_stiva()   {
    S* stacktop=NULL;
    return stacktop;
}

int isEmpty_stack(S* stack){
    return stack==NULL;
}

int isEmpty_coada(Queue *q){
    return (q->front==NULL);
}

void pop(S** stack)     {
    S* nod_temporar=*stack;
    *stack=(*stack)->next;
    free(nod_temporar);

}

void push(S** stack,char* nume_echipa,float score)    {
    S* newNode=(S*)malloc(sizeof(S));
    newNode->team=(char*)malloc(sizeof(char)*Nr_Max);
    newNode->team=strdup(nume_echipa);
    newNode->score=score;
    newNode->next=*stack;
    *stack=newNode;
}

void stergere_queue(Queue *q)   {
    node* aux;
    while(!isEmpty_coada(q))
    {
        aux=q->front;
        q->front=q->front->next;
        free(aux);
    }
    free(q);
}

void creare_queue_echipe(Queue* q, char* team_front, char* team_rear,float score_front,float score_rear)   {
    struct Match match;

    match.team1=strdup(team_front);
    match.team2=strdup(team_rear);
    match.score1=score_front;
    match.score2=score_rear;

    node* newNode = (node*)malloc(sizeof(node));
    newNode->match = match;
    newNode->next = NULL;

    if (q->rear == NULL) 
        q->front = q->rear = newNode;
    else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void creare_din_lista(NodeA** head, Queue* q)    {
    NodeA* current = *head;
    while (current != NULL && current->next != NULL)
    {
        creare_queue_echipe(q, current->nume_echipa, current->next->nume_echipa,current->score,current->next->score);
        current = current->next->next;
    }
}

void creare_echipe_din_stack(S** stack,Queue *q){
    S* stacktop=*stack;
    while(stacktop!=NULL && stacktop->next!=NULL){
        creare_queue_echipe(q,stacktop->team,stacktop->next->team,stacktop->score,stacktop->next->score);
        stacktop=stacktop->next->next;
    }
}
void stergere_lista(NodeA** head){
    NodeA *current=*head;
    NodeA *temporar=NULL;

    while(current!=NULL)
    {
        temporar=current->next;
        free(current);
        current=temporar;
    }
    *head=NULL;
}


void print_queue_to_file(Queue* q,FILE* filename,const char* file,int *round){
    filename=fopen(file,"a");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }
    fprintf(filename,"\n--- ROUND NO:%d\n",*round);
    node *temp=q->front;
    while(temp!=NULL){
        fprintf(filename,"%-33s-%33s",temp->match.team1,temp->match.team2);
        fprintf(filename,"\n");
        temp=temp->next;
    }
    fclose(filename);
}

void print_stack_to_file(S* stacktop,FILE* filename,const char* file,int* round){
    filename=fopen(file,"a");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }
    fprintf(filename,"\nWINNERS OF ROUND NO:%d\n",*round);
    S* stack=stacktop;
    while(stack!=NULL)
    {
        fprintf(filename,"%-33s -  %.2f\n",stack->team,stack->score);
        stack=stack->next;
    }
    fclose(filename);
}

void adaugare_in_stiva_de_invingatori_si_invinsi(Queue *q,S** winners,S** losers){
    node* temp=q->front;
    while(temp!=NULL){
        if(temp->match.score1>temp->match.score2){
            push(winners,temp->match.team1,temp->match.score1+1);
            push(losers,temp->match.team2,temp->match.score2);
        }
        else if(temp->match.score1<temp->match.score2){
            push(winners,temp->match.team2,temp->match.score2+1);
            push(losers,temp->match.team1,temp->match.score1);
        }
        else{
            push(losers,temp->match.team1,temp->match.score1);
            push(winners,temp->match.team2,temp->match.score2+1);
            }
        temp=temp->next;
    }
}

void delete_stack(S** stack){
    S* stackTop;
    while((*stack)!=NULL){
        stackTop=*stack;
        *stack=(*stack)->next;
        free(stackTop);
    }
}

void copy_queue_to_linked_list(Queue *q,NodeB** newhead){
    node* temp=q->front;
    while(temp!=NULL){
            add_at_beginning_ultimele_8_echipe(&(*newhead),temp->match.team1,temp->match.score1);
            add_at_beginning_ultimele_8_echipe(&(*newhead),temp->match.team2,temp->match.score2);
            temp=temp->next;
    }
}

void afisare_rezultate_meciuri(NodeA** head,NodeB** head_of_8member_linked_list,Queue* q, S** winners, S** losers, int* number_of_teams, FILE* filename, const char* file) {
    int round = 1;
    filename = fopen(file, "a");
    if (!filename) {
        fprintf(stderr, "Error opening file %s\n", file);
        return;
    }

    int copy_number_of_teams=*number_of_teams;


    while (round <= log2(*number_of_teams)) {
        if (round == 1) {
            creare_din_lista(&(*head), q);
            stergere_lista(&(*head));
        }
        if(copy_number_of_teams==desired_number_in_bst){
            copy_queue_to_linked_list(q,&(*head_of_8member_linked_list));
        }

        print_queue_to_file(q, filename, file,&round);
        adaugare_in_stiva_de_invingatori_si_invinsi(q, &(*winners), &(*losers));
        print_stack_to_file((*winners), filename, file,&round);

        delete_stack(&(*losers));
        stergere_queue(q);
        Queue* new=creare_coada();
        q=new;
        creare_echipe_din_stack(&(*winners), q);
        delete_stack(&(*winners));
        round++;
        copy_number_of_teams/=2;
    }
    fclose(filename);
}

void deletelastElem(NodeB** head){
    if (*head == NULL) {
        printf("Lista este goala\n");
        return;
    }

    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    NodeB* current = *head;
    while (current->next->next != NULL) {
        current = current->next;
    }

    free(current->next);
    current->next = NULL;
}
