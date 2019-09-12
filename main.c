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


TAREFA escalonador(TAREFA running, int* n, int tempo)
{
  TAREFA aux[MAX_N], t;
  int i = 0, j;
  if(running.c <= 0)
  {
   
      t = Prontos[0];
      printf("%d\n",*n);
      printf("estou aqui");
      *n--;
      printf("%d\n",*n);
      for(int k = 0; k<*n;k++) 
        Prontos[k] = Prontos[k+1];
      return t;
      
  }
  for(int k = 0; k<*n;k++)
    aux[k] = Prontos[k];
  if((running.d - running.c) < (Prontos[0].d - aux[0].c))
    return running;
  for(i = 0;i<*n;i++)
  {
      if((running.d - running.c) < (aux[i].d - aux[i].c))
      {
        break;
      }
  }
  Prontos[i] = running;
  for(j = i+1;j<*n;j++)
  {
    Prontos[j] = aux[j-1]; 
  }

  
   t = Prontos[0];
  for(int k = 0; k<*n;k++)
    aux[k] = Prontos[k];
  for(i = 1; i<*n;i++)
  {
    Prontos[i] = aux[i-1];
  }

  return t;
}

int main() {
  TAREFA  executando;
  int n, t, i;
  int n_proc;
  char grade[MAX_T+1];
  int num_preemp, num_trocas_cont;
  
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
      
	for(int i = 1; i < t; i++)
	{
      executando.c--;
      printf("%c-%d==%d\n",executando.id,executando.c,n_proc);
      executando = escalonador(executando, &n_proc, t);
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