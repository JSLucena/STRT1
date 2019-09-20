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
int num_preemp, num_trocas_cont;

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
			//	printf("tarefa %c slack %d\n", aux[k].id, (aux[k].d - aux[k].c));
				slack = aux[k].d - aux[k].c;
				LST = k;
				
			}
		}
		slack = 2049;
		Prontos[j] = aux[LST];
		aux[LST].d = 2050;
	}
//	printf("=========================\n");
	//for (int j = 0; j < n; j++)
	//	printf("tarefa %c slack %d\n", Prontos[j].id, (Prontos[j].d - Prontos[j].c));
}

void returningTasks(int tempo, int n)
{
	TAREFA nova_tarefa;
	TAREFA aux[MAX_N];
	int achou = 0;
	int j;
	for (int k = 0; k < n_proc; k++)
		aux[k] = Prontos[k];

	for (int i = 0; i < n; i++)
	{
		if (tempo % tarefas[i].p == 0)
		{
	//		printf("         tarefa %c , n_proc %d , achou  %d\n", tarefas[i].id,n_proc,achou);
			nova_tarefa.id = tarefas[i].id;
			nova_tarefa.p = tarefas[i].p + tempo;
			nova_tarefa.d = tarefas[i].d + tempo;
			nova_tarefa.c = tarefas[i].c;
			if (n_proc == 0)
			{

				num_preemp++;
				Prontos[n_proc] = nova_tarefa;
				n_proc++;
				achou = 1;


			}
			else
			
			{
				/*
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
				*/
				if(achou == 1)
				{
					Prontos[n_proc] = nova_tarefa;
				}
				else
				{
					Prontos[n_proc-1] = nova_tarefa;
				}
				n_proc++;
				
				
			}
		}
	}
	
	
}
TAREFA escalonador(TAREFA running, int tempo)
{
	TAREFA aux[MAX_N], t;
	TAREFA order;
	int i = 0, j;
	int min_slack;
	char last;
	//int deadline;
	if(n_proc == 0)
			return idle;
	
	if (n_proc == 1)
	{
		if(running.c == 0)
		{ 
			n_proc--;
			num_trocas_cont++;
		//	printf("].[\n");
			return idle;
		}
	//	else
		//	printf("]%c[\n",running.id);
		if(running.id == idle.id)
		{		
			t = Prontos[0];
			Prontos[0] = Prontos[1];
			return t;
		}
		else
		{
			return running;
		}
		

	}
	if (n_proc > 0)
	{
		if (running.c > 0)
		{
			Prontos[n_proc - 1] = running;
			last = running.id;
			
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
			if(Prontos[0].id != last && last != idle.id && tempo != 1)
			{
				num_preemp++;
				num_trocas_cont++;
			}

		}
		
			
		
			
		else
		{
			if(running.id != idle.id)
			{
				n_proc--;
			
			}
			num_trocas_cont++;
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



//		for (j = 0; j < n_proc; j++)
//	{
//		printf("]%c[", Prontos[j].id);
//	}
	
//	printf("\n");
	



		for (int k = 0; k < n_proc; k++)
			aux[k] = Prontos[k];
		for (i = 0; i < n_proc; i++)
		{
			Prontos[i] = aux[i + 1];
		}
		
		//else
		//{
		//	if()
		//}
		
		return t;
	}
}
int main() {
  TAREFA  executando;
  int n, t, i;
  
  char grade[MAX_T+1];
  

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
      
	for(int i = 1; i <= t+1; i++)
	{
		
		executando = escalonador(executando, i);
		executando.c--;
	//	printf("[%c] pr %d troca %d   %d \n",executando.id,num_preemp,num_trocas_cont,i);
		if(i != t+1)
		{
			if(i > executando.d)
			{
				if(executando.id != '.')
					grade[i-1] = executando.id+32;
				else
					grade[i-1] = '.';
			}
			else
				grade[i-1] = executando.id;
			returningTasks(i, n);
		}
	}
   // grade[0] = '.';
   // grade[1] = '.';
   // grade[2] = '.';
  //  grade[3] = '\0';
    // ...
    // RESULTADOS
		grade[t] = '\0';
    	printf("%s\n%d %d\n\n", grade, num_trocas_cont,num_preemp );
  }
  return 0;
}