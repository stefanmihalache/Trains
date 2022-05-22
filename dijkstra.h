#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#define INF 99999

typedef struct node{
	
	char *s;
	struct node *next;
} stack_node;


int minDistance(int dist[], int sps[], int V);
void dijkstra(Graph *g, int s,Oras* head);

void push(stack_node**top,char *a);
char* pop(stack_node**top);
void deleteStack (stack_node**top);
int isEmpty (stack_node*top);
void FW(Graph* cost,Oras*head);

#endif