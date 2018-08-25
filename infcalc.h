#ifndef INFCALC_H_
#define INFCALC_H_

//Definicao das constantes utilizadas
#define OK 1
#define ERRO 0

//Definicao da struct de lista encadeada
struct no{
	int dado;
	struct no *prox;
};

typedef struct no No;	//Definicao de um no da lista
typedef struct no* Lista;	//Definicao da lista em si

void somaBin(int carryIn, int bit1, int bit2, int *carryOut, int *sum);
Lista *criaLista();
No *criaNo(int dado);
int insereFim(Lista *li, int dado);
int charbin2int(char num);
Lista *strtoList(char *num, int *numLen);
Lista *somaBinList(Lista *num1, Lista *num2, int numLen1, int numLen2);
void imprimeLista(Lista* li);
int tamanhoLista(Lista* li);
void destroiLista(Lista *li);
Lista *InfCalc(int parcNum, int *tamSum);

#endif
