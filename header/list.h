#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include "listA.h" 

#define Nr_Max 100
#define epsilon 0.000001

// No need to redefine the struct listaA here

void add_at_beginning (NodeA **head, FILE* filename);
void printfile (NodeA** head, FILE* filename, const char* file);
void completare_lista (NodeA** head, int index, int numar_echipe, FILE *filename);
void stergere_element_lista (NodeA** head, char* nume_echipa);
void min (NodeA** head);
void modificare_lista (NodeA** head, int *numar_echipe);
float media_aritmetica (NodeA* head, int nr_jucatori);
int multiplu_de_2 (int numar_echipe);

#endif 
