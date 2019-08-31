#include <stdio.h>

#define MAX_N 26
#define MAX_T 2048

typedef struct {
  char id;
  int c;
  int p;
  int d;
} TAREFA;

TAREFA Prontos[MAX_N];

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


void escalonador()
{

}
int main() {
  TAREFA tarefas[MAX_N];
  int n, t, i;
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
	for(int i = 0; i < t; i++)
	{

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