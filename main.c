#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_N 26
#define MAX_T 2048

typedef struct {
  char id;
  int c;
  int p;
  int d;
} TAREFA;


TAREFA tarefas[MAX_N], Prontos[MAX_N];
int n_proc;
TAREFA idle;


void startOrder(int n, TAREFA tarefas[])
{
	int slack = 2049;
	int LST;
	int k;
	TAREFA aux[MAX_N];
	for (int j = 0; j < n; j++)
		aux[j] = tarefas[j];

	for (int j = 0; j < n; j++)
	{
		for (k = 0; k < n; k++)
		{
			if (aux[k].d - aux[k].c <= slack)
			{
				printf("tarefa %c slack %d\n", aux[k].id, (aux[k].d - aux[k].c));
				slack = aux[k].d - aux[k].c;
				LST = k;
				
			}
		}
		slack = 2049;
		Prontos[j] = aux[LST];
		aux[LST].d = 2050;
	}
	printf("=========================\n");
	for (int j = 0; j < n; j++)
		printf("tarefa %c slack %d\n", Prontos[j].id, (Prontos[j].d - Prontos[j].c));
}

void returningTasks(int tempo, int n)
{
	TAREFA nova_tarefa;
	TAREFA aux[MAX_N];
	int j;
	for (int k = 0; k < n_proc; k++)
		aux[k] = Prontos[k];

	for (int i = 0; i < n; i++)
	{
		if (tempo % tarefas[i].p == 0)
		{
		//	printf("tarefa %c\n", tarefas[i].id);
			nova_tarefa.id = tarefas[i].id;
			nova_tarefa.p = tarefas[i].p + tempo;
			nova_tarefa.d = tarefas[i].d + tempo;
			nova_tarefa.c = tarefas[i].c;
			if (n_proc == 1 || n_proc == 0)
			{
				Prontos[0] = nova_tarefa;
				n_proc++;

			}
			else
			{
				for (j = 0; i < n_proc; i++)
				{
					if ((nova_tarefa.d - nova_tarefa.c - tempo) < (Prontos[j].d - Prontos[j].c - tempo))
						break;
				}
				Prontos[j] = nova_tarefa;
				for (j = j + 1; j < n_proc; j++)
				{
					Prontos[j] = aux[j - 1];
				}
				n_proc++;
				
			}
		}
	}
	for (j = 0; j < n_proc - 1; j++)
	{
		printf("]%c[", Prontos[j].id);
	}
	printf("\n");
	
}
TAREFA escalonador(TAREFA running, int tempo)
{
	TAREFA aux[MAX_N], t;
	TAREFA order;
	int i = 0, j;
	int min_slack;
	
	/*
	if(running.c <= 0)
	{

	  //  printf("estou aqui");
		t = Prontos[0];
		for(int k = 0; k<n_proc-1;k++)
		  Prontos[k] = Prontos[k+1];
		n_proc--;
		if (n_proc == 0)
			return idle;
		return t;

	}
	if (n_proc == 1)
	{
		return running;
	}

	for(int k = 0; k<n_proc;k++)
	  aux[k] = Prontos[k];
	if((running.d - running.c - tempo) < (Prontos[0].d - Prontos[0].c - tempo))
	  return running;
	else if ((running.d - running.c - tempo) == (Prontos[0].d - Prontos[0].c - tempo))
	{
		if (running.id < Prontos[0].id)
		{
			return running;
		}
	}
	for(i = 0;i<n_proc-1;i++)
	{
		if((running.d - running.c - tempo) < (aux[i].d - aux[i].c - tempo))
		{
		  break;
		}
		else if ((running.d - running.c - tempo) == (aux[i].d - aux[i].c - tempo))
		{
			if (running.id < Prontos[0].id)
			{
				break;
			}
		}
	}

	//printf(" %d %c", i,running.id);
	Prontos[i] = running;

	if (i != n_proc - 1)
	{
		for (j = i + 1; j < n_proc; j++)
		{
			Prontos[j] = aux[j - 1];
		}
	}

	 t = Prontos[0];
	for(int k = 0; k<n_proc;k++)
	  aux[k] = Prontos[k];
	for(i = 0; i<n_proc;i++)
	{
	  Prontos[i] = aux[i+1];
	}
   */
	if (n_proc == 1)
	{
		if(running.c == 0)
		{ 
			n_proc--;
			return idle;
		}
				
		return running;

	}
	if (n_proc > 0)
	{
		if (running.c > 0)
		{
			Prontos[n_proc - 1] = running;

			for (int i = 0; i < n_proc; i++)
			{
				for (int j = 1; j < n_proc; j++)
				{
					if ((Prontos[j].d - Prontos[j].c - tempo) < (Prontos[i].d - Prontos[i].c - tempo))
					{
						order = Prontos[j];
						Prontos[j] = Prontos[i];
						Prontos[i] = order;
					}
					else if ((Prontos[j].d - Prontos[j].c - tempo) == (Prontos[i].d - Prontos[i].c - tempo))
					{
						if (Prontos[j].id < Prontos[i].id)
						{
							order = Prontos[j];
							Prontos[j] = Prontos[i];
							Prontos[i] = order;
						}
					}
				}

			}

		}
		else
		{
			n_proc--;
			
			for (int i = 0; i < n_proc; i++)
			{
				for (int j = 1; j < n_proc; j++)
				{
					if ((Prontos[j].d - Prontos[j].c - tempo) < (Prontos[i].d - Prontos[i].c - tempo))
					{
						order = Prontos[j];
						Prontos[j] = Prontos[i];
						Prontos[i] = order;
					}
					else if ((Prontos[j].d - Prontos[j].c - tempo) == (Prontos[i].d - Prontos[i].c - tempo))
					{
						if (Prontos[j].id < Prontos[i].id)
						{
							order = Prontos[j];
							Prontos[j] = Prontos[i];
							Prontos[i] = order;
						}
					}
				}

			}
		}
		t = Prontos[0];
		for (int k = 0; k < n_proc; k++)
			aux[k] = Prontos[k];
		for (i = 0; i < n_proc; i++)
		{
			Prontos[i] = aux[i + 1];
		}
		return t;
	}
}
int main() {
  TAREFA  executando;
  int n, t, i;
  
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;

  idle.id = '.';
  idle.d = 0;
  idle.p = 0;
  idle.c = 0;


  while (1) {
    // LEITURA
    scanf("%d%d", &n, &t);
    if (n==0 || t==0)
       break;
    for (i=0; i<n; ++i) {
       tarefas[i].id = 'A' + i;
       scanf("%d%d%d", &(tarefas[i].c), &(tarefas[i].p), &(tarefas[i].d) );
    }
    // SIMULACAO


    num_preemp = 0;
    num_trocas_cont = 0;
	startOrder(n, tarefas);
	executando = Prontos[0];
	for(int k = 0; k<n;k++) 
      Prontos[k] = Prontos[k+1];
      n_proc = n;
      
	for(int i = 1; i <= t; i++)
	{
		
		executando = escalonador(executando, i);
		executando.c--;
		printf("%c-%d==%d##%d     ",executando.id,executando.c,n_proc,i);
		returningTasks(i, n);
      
	}
    grade[0] = '.';
    grade[1] = '.';
    grade[2] = '.';
    grade[3] = '\0';
    // ...
    // RESULTADOS
    printf("%s\n%d %d\n\n", grade, num_preemp, num_trocas_cont);
  }
  return 0;
}