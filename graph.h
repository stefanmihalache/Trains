#ifndef GRAPH_H
#define GRAPH_H

typedef struct 
{
int V;
int E;
int **a;
} Graph;

typedef struct o
{
    char* nume;
    int id;
    struct o* next;
} Oras;
/**
 * @brief Adauga un oras s la capatul listei
 */
Oras* append_node(Oras*head, char* s);
/**
 * @brief Creeaza un graf cu n varfuri 
 */
Graph* create (int n);
/**
 * @param head  inceputul listei 
 * @param x  numele orasului care trebuie cautat
 * @return NULL daca nu il gaseste sau pointer la nodul din lista
 */
Oras* searchOras(Oras* head,char* x);
/**
 * @brief returneaza numele orasului cu id ul x 
 */
char* searchOrasID(Oras *head, int x);
void freelist(Oras**head);

#endif