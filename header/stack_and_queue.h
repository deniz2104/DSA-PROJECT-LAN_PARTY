#ifndef STACK_AND_QUEUE_H
#define STACK_AND_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "listA.h"
#include "listB.h"  

#define desired_number_in_bst 8
#define Nr_Max 100

struct Match {
    char *team1, *team2;
    float score1, score2;
};

struct elem_queue {
    struct Match match;
    struct elem_queue* next;
};

typedef struct elem_queue node;

struct Q {
    node *front, *rear;
};

typedef struct Q Queue;
typedef struct Match match;

struct stackNode {
    char *team;
    float score;
    struct stackNode* next;
};
typedef struct stackNode S;

int isEmpty_stack(S* stack);
int isEmpty_coada(Queue* q);
Queue* creare_coada();
S* creare_stiva();
void creare_din_lista(NodeA** head, Queue* q);
void creare_echipe_din_stack(S** stack, Queue *q);
void stergere_lista(NodeA** head);
void creare_queue_echipe(Queue* q, char* team_front, char* team_rear, float score_front, float score_rear);
void print_queue_to_file(Queue*q, FILE* filename, const char* file, int* round);
void print_stack_to_file(S* stacktop, FILE* filename, const char* file, int* round);
void delete_stack(S** stack);
void add_at_beginning_ultimele_8_echipe(NodeB** head, char* team, int score);
void copy_queue_to_linked_list(Queue *q, NodeB** newhead);
void afisare_rezultate_meciuri(NodeA** head, NodeB** head_of_8member_linked_list, Queue* q, S** winners, S** losers, int* number_of_teams, FILE* filename, const char* file);
void adaugare_in_stiva_de_invingatori_si_invinsi(Queue *q, S** winners, S** losers);
void pop(S** stack);
void push(S** stack, char* nume_echipa, float score);
void stergere_queue(Queue *q);
void deletelastElem(NodeB** head);
#endif
