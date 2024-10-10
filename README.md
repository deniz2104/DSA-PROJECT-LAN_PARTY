## Compilare:
```bash
make build
```

## Executare:
```bash
make run
```

## Rularea checker-ului
Pentru a verifica funcționarea checker-ului va trebui sa descărcați codul sursă , după aceasta deschideți un terminal in folderul in care se află toate folderele necesare si scrieți următoarea comandă:
```bash
./checker.sh
```
## Descriere:

Facultatea de Automatica si Calculatoare prin LSAC organizează in fiecare semestru un LAN Party la care participă toți studenții care vor sa își testeze abilitățile la un anumit joc. Se dorește realizarea unei soluții software(program executabil) ce poate automatiza acest proces.

## Obictivele proiectului:

-   Ințelegerea conceptului de funcționare și implementare a unor structuri de date(precum liste, stive, cozi, arbori binari de căutare)
-   Operarea cu aceste structuri de date
-   Implementarea unei funcționalități practice folosind aceste concepte

## Cerințe:

1.  Se va crea o listă cu informațiile din fișierul d.in(lista se va forma prin adaugarea elementelor la inceput - O(1)).

2.  Se vor elimina din lista anterior creată, echipele cu cel mai mic punctaj de echipă (informațiile despre modul de calcul al acestui punctaj se găsesc în cadrul secțiunii Detalii Tehnice) astfel incat in lista sa ramana n echipe (unde n maxim si n este putere a lui 2).  
În cazul în care mai multe echipe au acelasi scor se elimina prima echipă gasita in lista. Dupa fiecare eliminare se va relua parcurgerea listei de la cap.
    
3.  Se vor implementa structurile de date necesare pentru a se efectua meciurile:
    -   Se va crea o coadă în care se vor pune meciurile dintre echipe.
    -   Echipele vor forma meciuri în ordinea în care se află în lista de la punctul anterior, primele două echipe vor forma primul meci (și așa mai departe).
    -   Se vor crea două stive - una pentru învinși și una pentru câștigători - ce vor conține echipele ce au pierdut, respectiv, au câștigat meciul anterior.
    -   Se vor introduce în stivă echipele în funcție de rezultatul obținut și se va adauga un punct la punctajul de echipă al echipelor ce au câștigat.
    -   In cazul unui meci in care ambele echipe au acelasi punctaj, se va alege prima echipa adaugata in meciul disputat.
    -   Se vor șterge echipele ce se găsesc în stiva de învinși. (la finalul fiecărei etape; ex: dintr-o runda cu 8 echipe, stergerea se face dupa ce au fost eliminate toate echipele. In acest caz, dupa ce au fost eliminate 4 dintre echipe, se vor sterge. In runda urmatoare, pe acest exemplu, se vor adauga 2 echipe in stiva de invinsi, dupa care o sa fie eliberata din nou - stiva de invinsi -.)
    -   Din stiva de câștigători se vor extrage echipele și se va umple din nou coada de meciuri formându-se meciuri cu echipele consecutive (prima echipă scoasă din stivă va juca cu a doua echipa scoasă din stivă primul meci).
    -   Se vor repeta pașii enumerați pana la aflarea echipelor de pe primele 8 locuri, care vor fi salvate intr-o alta lista, dupa aflarea acestora se vor continua meciurile pana la aflarea echipei castigatoare.

4.  Se va realiza un clasament al ultimelor 8 echipe (salvate la subpunctul anterior) sub forma unui BST(Binary Search Tree). Acesta va fi ordonat după punctajul pe echipă și i se va afișa conținutul în ordine descrescătoare(in cazul in care doua echipe au acelasi punctaj se vor ordona in functie de nume, descrescator).
    
5.  Se va realiza un arbore de tip AVL cu ultimele 8 echipe (salvate la subpunctul 3, dar sortate ca la subpunctul 4) si se vor afisa echipele de pe nivelul 2 al arborelui.

## Organizarea proiectului:
In primul rand,vom creea mai multe structuri,folosite cu diverse scopuri:
-   o structura Player in care se va retine numele prenumele si punctele
-   o structura lista in care vom tine evidenta numarului de jucatori,score-ul,numelui echipei,un pointer pentru elementul urmator
-   o structura match in care se vor gasi detaliile legate despre coada de match-uri
-   o coada propriu-zisa unde se vor gasi elemente de tip match si pointerii front si rear
-   o structura pentru memorarea informatiilor despre stiva de castigatori,respectiv invinsi
-   o structura de tip arbore binar unde vom avea campurile score,numele echipei (pentru ca task-ul 5 solicita prelucrarea unui AVL am introdus si height);

Pentru un aspect modularizat,am decis sa separ in headere si fisiere separate(ex: list.c list.h trees.c trees.h ...)
Am introdus toate bibliotecile relevante in main,respectiv in alte fisiere .c unde aveam nevoie de mai multe biblioteci

# Rezolvarea task-urilor:

## TASK 1:

Functia `add_at_beginning(NodeA** head,FILE* filename)`:
-   vom creea un nod nou de tip Node* in care vom stoca informatiile pe care le vom citi din fisierul pe care il deschidem
-   vom adauga elementele la inceput conform cerintei

Functia `completare_lista(NodeA** head,int numar_echipe,FILE* filename)`:
-   va completa lista in functie de numarul de echipe care este transmis ca parametru

Functia `printfile(NodeA** head,FILE* filename,const char* file)` 
-   deschide fisierul de out si se pun in fisier numele din echipe din lista conform cerintei
-   se inchide fisierul

## TASK 2:

Functia `media_aritmetica(NodeA *head,int nr_jucatori)`:
-   calculeaza score-ul initial pentru fiecare echipa

Functia `stergere_element_lista(NodeA** headm,char* nume_echipa)`:
- va elimina echipa aferenta cerintei si sunt incluse toate cazurile:
- cazul in care capul de lista este gol
- cazul in care este primul element
- cazul in care se afla oriunde altundeva 
- vom sterge elementul cu ajutorul functiei free si vom realiza legaturile intre nodul de dinainte si nodul de dupa nodul sters
- va fi apelata (&(*head),....) in functia min care gaseste echipa cu score ul cel mai mic iar fabs(min-avg)>epsilon,unde epsilon=0.000001 acopera cazul in care trebuie sa fie eliminata prima echipa si nu mai trebuie o a doua parcurgere

Functia `modificare_lista(NodeA** head,int *numar_echipe)`
-   va apela cele doua functii:multiplu_de_2 prin care se verifica daca numarul de echipe este multiplu de 2(conditie de stop)
si functia min prin care se va elimina echipa cu score ul minim 
-   numar_echipe este transmis prin referinta deoareece i se va modifica valoarea

## TASK 3:
Functia `creare_din_lista(NodeA** head,Queue* q)` folosita pentru a parcurge lista de echipe si a le introduce in coada. 
In interiorul acestei functii ma folosesc de functia `creare_queue_echipe(...)` pentru a adauga elemente noi in coada.

Functia `creare_echipe_din_stack(...)` folosita cu un scop identic,in urma deciderii stack-ului de invingatori.

Functiile `print_queue_to_file(...)` respectiv `print_stack_to_file(...)` folosite pentru a afisa in fisierul de out cu formatul necesar care sunt folosite in functia principala a acestui task `afisare_rezultate_meciuri(...)`.

Functia `afisare_rezultate_meciuri(...)` este folosita pentru a afisa in fisierul de out stiva de invingatori si coada cu meciuri :
-   in cazul in care este prima runda se va creea coada din lista,apoi o vom sterge
-   printam coada in fisierul de out
-   adaugam in stiva de invingatori si de invinsi in functie de caz
-   printam stiva in fisierul de out
-   stergem stiva de invinsi
-   stergem coada
-   creem o coada noua in care vom pune stiva de invingatori
-   stergem stiva de castigatori
-   cand ajungem la numarul de 8 atunci vom copia coada intr-o lista speciala

## TASK 4:
Functia `BST* newNode(...)` este implementata pentru un arbore care stocheaza informatii despre numele echipei,score-ul si inaltimea(fiind vorba la task-ul 5 de un AVL).

Functia `BST* insertBST(...)` folosita pentru a insera in BST acoperind edge case-ul in care este acelasi scor si se va lua in functie de numele echipei.

Functia `displayTeamsAndPoints(...)` folosita pentru a afisa in outfile.

## TASK 5:
Functia `BST* insertAVL(...)` care are implementarea de la functia `BST* insertBST(...)` plus actualizarea inaltimii nodului curent.In plus contine informatia daca arborele este balansat.In functie de factorul de echilibru se vor efectua rotatiile necesare.

Functia recursiva `transformAVL(...)` care parcurge arborele intr-o inordine inversa va insera intr-un AVL nou format elementele din arborele vechi.

Functia `displayLevelTwo(...)` folosita pentru a afisa echipa aflata pe nivelul 2 in outfile.


## PROBLEME SI BUG-URI INTALNITE
-   In cazul multor echipe existau endline-uri si whitespaces la final in fisier
-   Avand in vedere ca in struct_and_queue.h am nevoie si de structura listei am decis sa fac doua headere separate listA.h si listB.h pe care le-am folosit in diferite parti pentru nu a avea eroarea "redefinition of struct..."




