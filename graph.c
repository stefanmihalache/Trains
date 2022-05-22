#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Oras *append_node(Oras *head, char *s)
{
    Oras *a;
    a = (Oras *)malloc(sizeof(Oras));
    if (a == NULL)
    {
        printf("Alocare esuata.\n");
        exit(1);
    }
    a->nume = strdup(s);
    a->next = NULL;

    if (head == NULL)
    {
        head = a;
        head->id = 0;
        return head;
    }
    else
    {
        Oras *aux = head;
        while (aux->next != NULL)
            aux = aux->next;
        aux->next = a;
        a->id = aux->id + 1;
        return head;
    }
}

Oras* searchOras(Oras *head, char *x)
{
    if (head == NULL)
        return NULL;

    while (head != NULL)
    {
        if ((strcmp(x, head->nume)) == 0)
            return head;
        head = head->next;
    }
    return NULL;
}

char* searchOrasID(Oras *head, int x)
{
    if (head == NULL)
        return NULL;

    while (head != NULL)
    {
        if (head->id==x)
            return head->nume;
        head = head->next;
    }
    return NULL;
}

Graph *create(int n)
{
    int i;
    Graph *g = (Graph *)malloc(sizeof(Graph));
    if (g == NULL)
    {
        printf(" no memory for this graph");
        return NULL;
    }

    g->a = (int **)malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        g->a[i] = (int *)calloc(n, sizeof(int));
    if (g->a == NULL)
    {
        printf(" no memory for this matrix");
        return NULL;
    }
    g->V = n;
    g->E = 0;
    return g;
}

void freelist(Oras**head)
{
    Oras* aux;
    while((*head)!=NULL)
    {
        aux=*head;
        *head=(*head)->next;
        free(aux);
    }
}