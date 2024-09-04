#ifndef LISTB_H
#define LISTB_H

struct listaB {
    int nr_jucatori;
    float score;
    char *nume_echipa;
    struct Player* jucator;
    struct listaB* next;
};
typedef struct listaB NodeB;

#endif