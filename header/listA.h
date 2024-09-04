#ifndef LISTA_H
#define LISTA_H

struct Player {
    char* firstName;
    char* secondName;
    int points;
};

struct listaA {
    int nr_jucatori;
    float score;
    char *nume_echipa;
    struct Player* jucator;
    struct listaA* next;
};
typedef struct listaA NodeA;

#endif 
