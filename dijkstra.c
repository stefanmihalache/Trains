#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"
#include "dijkstra.h"


int isEmpty (stack_node*top)
{
    return top==NULL;
}
void push(stack_node**top,char *a)
{

    stack_node *newNode;
    newNode=(stack_node*)malloc(sizeof(stack_node));
    newNode->s=strdup(a);
    newNode->next=(*top);
    (*top)=newNode;
}

char* pop(stack_node**top)
{   
    if(isEmpty(*top)) return NULL;
    else
    {
    char* a;
    stack_node* temp;
    temp=*top;
    a=strdup(temp->s);

    *top=(*top)->next;
    free(temp);
    
    return a;
    }
}

void deleteStack (stack_node**top)
{
    stack_node*temp;
    while((*top)!=NULL)
    {
        temp=*top;
        *top=(*top)->next;
        free(temp);
    }

}

int minDistance(int dist[], int sps[], int V)
{
    int v, min = INF, min_index;
    for (v = 0; v < V; v++)
        if (sps[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            min_index = v;
        }
    return min_index;
}

void dijkstra(Graph *g, int s,Oras* head)
{
    int i, j, u;
    int dist[g->V];
    int sps[g->V];
    int prev[g->V];

    for (i = 0; i < g->V; i++)
    {
        dist[i] = INF;
        sps[i] = 0;
        prev[i]=-1;
    }

    dist[s] = 0;
    for (j = 0; j < g->V - 1; j++)
    {

        u = minDistance(dist, sps, g->V);    
        sps[u] = 1;
    
        for (i = 0; i < g->V; i++)
        {
            if (sps[i] == 0 && g->a[u][i] != 0 &&
                dist[u] != INF && dist[u] + g->a[u][i] < dist[i])
                {
                    dist[i] = dist[u] + g->a[u][i];
                    prev[i]=u;
                }
        }
    }
    
    FILE* f1;
    if((f1=fopen("ruta.txt","w"))==NULL)
    {
        printf("Fisierul nu poate fi deschis.\n");
        exit(1);
    }
    Oras* aux=searchOras(head,"Titu");
    fprintf(f1,"Drumul de cost minim de la orasul Titu la Bucuresti este de %d de km.",dist[aux->id]);
    fclose(f1);

    int max=dist[1],i_max;
    for(i=2;i<g->V;i++)
        if(dist[i]>max) 
        {
            max=dist[i];
            i_max=i;
        }

    stack_node *top=NULL;

    j=i_max;
    while(j!=-1)
    {
        push(&top,searchOrasID(head,j));
        j=prev[j];
    }

    
    if((f1=fopen("departe.txt","w"))==NULL)
    {
        printf("Fisierul nu poate fi deschis.\n");
        exit(1);
    }

    fprintf(f1,"Ruta ");
    while(top!=NULL)
        fprintf(f1,"%s-",pop(&top));
    fprintf(f1,"este cea mai lunga si are lungimea de %d km.",max);
    fclose(f1);
    deleteStack(&top);

}

void FW(Graph* g,Oras*head)
{   
    int i,j,k,max,i_max,j_max;
    int c[g->V][g->V];

    for(i=0;i<g->V;i++)
        for(j=0;j<g->V;j++)
        {   
            if(i==j) c[i][i]=0;
            else
            if(g->a[i][j]!=0) c[i][j]=g->a[i][j];
                else c[i][j] = INF;
        }

    for(k=0;k<g->V;k++)
        for(i=0;i<g->V;i++)
            for(j=0;j<g->V;j++)
                if(c[i][k] + c[k][j] < c[i][j]) c[i][j] =  c[i][k] + c[k][j];


    max=c[0][1];
	i_max=0;
	j_max=1;

	for(i=0;i<g->V;i++)
		for(j=0;j<g->V;j++)
			if(c[i][j]>max)
			{
				max=c[i][j];
				i_max=i;
				j_max=j;
			}

    FILE *f1;
    if((f1=fopen("drum_lung.txt","w"))==NULL)
    {
        printf("Fisierul nu poate fi deschis.\n");
        exit(1);
    }
	
	fprintf(f1,"Cele doua statii din graf aflate la distanta maxima de %d de km sunt: %s-%s",max,searchOrasID(head,i_max),searchOrasID(head,j_max));

    fclose(f1);
                
}