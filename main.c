#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "graph.h"
#include "dijkstra.h"

int main()
{
	struct dirent *entry;
	DIR *pDir;

	pDir = opendir("files");
	if (pDir == NULL)
	{
		printf("Cannot open directory\n");
		exit(1);
	}

	Oras *head = NULL, *aux, *aux1;

	entry = readdir(pDir);
	entry = readdir(pDir);

	int i = 0;
	FILE *f;
	char *buffer = (char *)malloc(40), *s = (char *)malloc(40);

	while ((entry = readdir(pDir)))
	{
		// printf("d_name: %s\n", entry->d_name);
		char filename[50] = "files/";

		strcat(filename, entry->d_name);
		//printf("filename: %s\n",filename);
		f = fopen(filename, "r");
		if (f == NULL)
		{
			printf("Fisierul nu a putut fi deschis\n");
			exit(1);
		}

		fgets(buffer, 40, f);
		buffer[strlen(buffer) - 1] = '\0';
		s = strtok(buffer, ",");

		while (!feof(f))
		{
			aux = searchOras(head, s);
			if (aux == NULL)
			{
				head = append_node(head, s);
				i++;
			}
			fgets(buffer, 40, f);
			buffer[strlen(buffer) - 1] = '\0';
			s = strtok(buffer, ",");
		}
		fclose(f);
	}
	closedir(pDir);

	// printf("%d\n", i);

	Graph *g = create(i);
	Graph *h = create(i);
	Graph *cost = create(i);

	pDir = opendir("files");
	if (pDir == NULL)
	{
		printf("Cannot open directory\n");
		exit(1);
	}

	entry = readdir(pDir);
	entry = readdir(pDir);

	int a1, a2, j = 0;


	while ((entry = readdir(pDir)))
	{
		char filename[50] = "files/";
		strcat(filename, entry->d_name);
		// printf("filename: %s\n", filename);

		f = fopen(filename, "r");
		if (f == NULL)
		{
			printf("Fisierul nu a putut fi deschis\n");
			exit(1);
		}

		fgets(buffer, 40, f);
		buffer[strlen(buffer) - 1] = '\0';

		s = strtok(buffer, ",");
		aux = searchOras(head, s);
		s = strtok(NULL, ", ");
		a1 = atoi(s);
		aux1 = NULL;

		while (!feof(f))
		{
			fgets(buffer, 40, f);
			buffer[strlen(buffer) - 1] = '\0';
			s = strtok(buffer, ",");
			aux1 = searchOras(head, s);
			s = strtok(NULL, ", ");
			a2 = atoi(s);

			if (aux1 != NULL)
			{
				g->a[(aux->id)][(aux1->id)] = g->a[(aux1->id)][(aux->id)] = 1;
				h->a[aux->id][aux1->id] = 1;
				cost->a[(aux->id)][(aux1->id)] = cost->a[(aux1->id)][(aux->id)] = a2-a1;
			}
			aux = aux1;
			a1 = a2;
		}

		fclose(f);
	}
	closedir(pDir);



	for (i = 0; i < g->V; i++)
		for (j = 0; j < g->V; j++)
		{
			g->E += g->a[i][j];
			h->E += h->a[i][j];
		}
	
	int min=cost->a[0][1],max=cost->a[0][1],i_min=0,j_min=1,i_max=0,j_max=1,km=0;

	//parcurgem doar triunghiul superior al matricei

	for(i=0;i<cost->V-1;i++)
		for(j=i+1;j<cost->V;j++)
			{	
				if(cost->a[i][j]>max)
				{
					max=cost->a[i][j];
					i_max=i;
					j_max=j;
				}
				if(cost->a[i][j] && cost->a[i][j]<min)
				{
					min=cost->a[i][j];
					i_min=i;
					j_min=j;
				}

				km+=cost->a[i][j];
			}
	
	FILE*f1;

	if((f1=fopen("min.txt","w"))==NULL)
	{
		printf("Fisierul nu a putut fi deschis.\n");
		exit(1);
	}
	fprintf(f1,"Ruta %s %s are distanta cea mai mica.",searchOrasID(head,i_min),searchOrasID(head,j_min));
	fclose(f1);

	if((f1=fopen("max.txt","w"))==NULL)
	{
		printf("Fisierul nu a putut fi deschis.\n");
		exit(1);
	}
	fprintf(f1,"Ruta %s %s are distanta cea mai mica.",searchOrasID(head,i_max),searchOrasID(head,j_max));
	fclose(f1);

	if((f1=fopen("total.txt","w"))==NULL)
	{
		printf("Fisierul nu a putut fi deschis.\n");
		exit(1);
	}
	fprintf(f1,"Avem %d km de cale ferata.",km);
	fclose(f1);

	dijkstra(cost,0,head);

	// pentru punctul 8 am folosit algoritmul Floyd-Warshall
	FW(cost,head);

	return 0;
}

