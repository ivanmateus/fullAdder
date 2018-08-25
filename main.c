/*****************************************/
/* Autor: Ivan Mateus de Lima Azevedo    */
/* No. USP: 10525602                     */
/*****************************************/

//Inclusao das bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include "infcalc.h"

int main(int argc, char const *argv[])
{
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
