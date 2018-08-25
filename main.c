/*****************************************/
/* Autor: Ivan Mateus de Lima Azevedo    */
/* No. USP: 10525602                     */
/*****************************************/

//Inclusao das bibliotecas
#include <stdio.h>
#include <stdlib.h>

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

//Funcao que realiza a soma entre dois bits considerando o carry de entrada
//(um somador completo)
void somaBin(int carryIn, int bit1, int bit2, int *carryOut, int *sum)
{
	int x = (((!bit1) && bit2) || ((!bit2) && bit1));

	*carryOut = ((carryIn && (bit1 || bit2)) || (bit1 && bit2));
	*sum = (((!x) && carryIn) || ((!carryIn) && x));
}

//Construtor da lista
Lista *criaLista()
{
	Lista *li = (Lista *)malloc(sizeof(Lista));

	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Funcao que cria um no novo
No *criaNo(int dado)
{
	No *no = (No *)malloc(sizeof(No));

    if(no == NULL){
        return ERRO;
	}
    no->dado = dado;
    no->prox = NULL;
	return no;
}

//Funcao que insere os nos no fim da lista
int insereFim(Lista *li, int dado)
{
	if(li == NULL){
		return ERRO;
	}
	No *no = criaNo(dado);
	No *aux = *li;

	if(*li == NULL){	//Se a lista for vazia, insere no inicio
		*li = no;
	}else{
		while(aux->prox != NULL){	//Procura ate o ultimo
			aux = aux->prox;
		}
		aux->prox = no;	//Insere depois do ultimo
	}
	return OK;
}

//Transforma o valor do bit de char para int
int charbin2int(char num){
	return (num - '0');
}

//Passa os valores da string para a lista encadeada
Lista *strtoList(char *num, int *numLen)
{
	int msb = 0;
	int aux = 0;
	int i = 0;
	Lista *numList = criaLista();

	if(*numLen == 0){	//Se o tamanho for nulo, aponta pra NULL
		return NULL;
	}
	while(i < *numLen){	//Enquanto nao chegar no fim da string
		if(num[i] == '1'){
			msb = i + 1;	//Guarda o msb (most significant bit) nao nulo
		}
		++i;
	}
	if(*numLen != msb){	//Se ele nao for o ultimo da string, muda o tamanho dela
		*numLen = msb;
	}
	i = 0;
	while(i < msb){	//Enquanto nao chegar ate o msb nao nulo
		aux = charbin2int(num[i]);	//Transforma o valor do bit de char para int
		insereFim(numList, aux);	//Insere na lista encadeada
		++i;
	}
	return numList;
}

//Funcao que soma dois numeros
Lista *somaBinList(Lista *num1, Lista *num2, int numLen1, int numLen2)
{
	int lower = 0;
	int greater = 0;
	int i = 0;
	int carryIn = 0;
	int carryOut = 0;
	int sum = 0;
	No *aux1 = *num1;
	No *aux2 = *num2;
	Lista *result = criaLista();

	if(numLen1 < numLen2){	//Se o primeiro numero for menor
		lower = numLen1;	//Define como menor
		greater = numLen2;	//E o outro como maior
	}else{	//Senao, ao contrario
		lower = numLen2;
		greater = numLen1;
	}
	while(i < lower){	//Enquanto nao chegar no ultimo numero do menor
		somaBin(carryIn, aux1->dado, aux2->dado, &carryOut, &sum);	//Soma os bits
		carryIn = carryOut;	//Guarda o carry
		insereFim(result, sum);	//Insere o resultado da soma
		aux1 = aux1->prox;	//Proximo bit
		aux2 = aux2->prox;	//Proximo bit
		++i;
	}
	if(lower == numLen1){	//Se o menor for o primeiro numero
		while(i < greater){
			somaBin(carryIn, 0, aux2->dado, &carryOut, &sum);	//Ele ja terminou, entao soma com zero
			carryIn = carryOut;
			insereFim(result, sum);
			aux2 = aux2->prox;
			++i;
		}
	}else{	//Senao, faca ao contrario
		while(i < greater){
			somaBin(carryIn, aux1->dado, 0, &carryOut, &sum);
			carryIn = carryOut;
			insereFim(result, sum);
			aux1 = aux1->prox;
			++i;
		}
	}
	if(carryIn == 1){	//Se no fim o carry for um, insira na lista
		insereFim(result, carryIn);
	}
	return result;
}

//Funcao que imprime a lista
void imprimeLista(Lista* li)
{
    if(li == NULL){	//Se a lista estiver vazia, nao imprime nada
        return;
	}
    No* no = *li;

    while(no != NULL){	//Enquanto nao chegar no fim da lista
        printf("%d",no->dado);	//Imprime
        no = no->prox;
    }
}

//Funcao que calcula o tamanho da lista
int tamanhoLista(Lista* li)
{
    if(li == NULL){	//Se a lista estiver vazia, seu tamanho e zero
        return 0;
	}
    int cont = 0;
    No* no = *li;

    while(no != NULL){	//Enquanto nao chegar ao fim da lista
        ++cont;	//Incrementa o contador do numero de bits
        no = no->prox;
    }
    return cont;
}

//Apaga a lista
void destroiLista(Lista *li)
{
	//Se a lista estiver vazia, retorna NULL
	if(li == NULL){
		return;
	}
	if(*li == NULL){
		return;
	}
	No *aux = *li;

	while(aux != NULL){	//Enquanto nao chegar ao fim
		*li = aux->prox;	//Guarda o endereco do proximo
		free(aux);	//Libera o atual
		aux = *li;	//E segue para o proximo
	}
}

//Funcao que roda o programa, somando
//um total de parcNum (numero de parcelas) numeros
//e retornando a lista com o resultado final da soma
Lista *InfCalc(int parcNum, int *tamSum)
{
	int i = 0;
	int tam1 = 0;
	int tam2 = 0;
	int tamAux = 0;
	char *num1 = NULL;
	char *num2 = NULL;
	char *numAux = NULL;
	Lista *bin1 = NULL;
	Lista *bin2 = NULL;
	Lista *binAux = NULL;
	Lista *sum = criaLista();

	//Le os dois primeiros numeros
	scanf("%d", &tam1);
	num1 = (char *)calloc(tam1, sizeof(char));
	scanf("%s", num1);
	bin1 = strtoList(num1, &tam1);
	free(num1);

	scanf("%d", &tam2);
	num2 = (char *)calloc(tam2, sizeof(char));
	scanf("%s", num2);
	bin2 = strtoList(num2, &tam2);
	free(num2);

	//Soma os dois e calcula o tamanho final da soma
	sum = somaBinList(bin1, bin2, tam1, tam2);
	*tamSum = tamanhoLista(sum);

	while(i < (parcNum - 2)){	//E enquanto houver mais numeros (se nao forem somente dois)
		//Guarda os dados do proximo numero em variaveis auxiliares
		scanf("%d", &tamAux);
		numAux = (char *)calloc(tamAux, sizeof(char));
		scanf("%s", numAux);
		binAux = strtoList(numAux, &tamAux);
		free(numAux);

		//E soma esse numero com o resultado da soma dos anteriores
		sum = somaBinList(sum, binAux, *tamSum, tamAux);
		*tamSum = tamanhoLista(sum);
		++i;
	}
	destroiLista(bin1);
	destroiLista(bin2);
	destroiLista(binAux);
	return sum;
}

int main(int argc, char const *argv[]) {

	int parcNum = 0;
	int tamSum = 0;
	Lista *sum = criaLista();

	scanf("%d", &parcNum);
	sum = InfCalc(parcNum, &tamSum);
	printf("%d ", tamSum);
	imprimeLista(sum);
	destroiLista(sum);
	printf("\n");

	return 0;
}
