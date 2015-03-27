#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "ins_dados.h"

int welcome_conf(){
	int n_pessoas, n_conjuntos;
	vector v1;

	printf("Bem vindo, quantas pessoas existem na simulacao ?\n");
	scanf_s("%d", &n_pessoas);
	printf("Quantos conjuntos a considerar ?\n");
	scanf_s("%d", &n_conjuntos);
	if (n_conjuntos < 3 && n_conjuntos >(n_pessoas / 2)){
		return 1;
	}
}