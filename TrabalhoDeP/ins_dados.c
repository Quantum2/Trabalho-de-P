#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "vector.h"
#include "ins_dados.h"
#include "util.h"

#define TEMPO_DE_PAUSA 2

typedef struct dados pessoa;
struct dados{
	int ID;
	int idade;
	char nome[100];
};

void menu(){
	int escolha;

	ClearScreen();

	printf("Escolha a opçao pretendida\n");
	printf("1 - Adicionar pessoas a configuracao\n");
	printf("2 - Not implemented\n");
	printf("3 - Mais do mesmo\n");

	scanf_s("%d", &escolha);

	switch (escolha)
	{
	case 1:
		if (welcome_conf() != 0){
			printf("Os dados inseridos sao invalidos, tente de novo\n");
			Sleep(TEMPO_DE_PAUSA * 1000);
		}
		menu();
		break;
	default:
		break;
	}	
}

int welcome_conf(){
	int n_pessoas, n_conjuntos, i;
	vector v1;
	vector_init(&v1);

	ClearScreen();

	printf("Bem vindo, quantas pessoas existem na simulacao ?\n");
	scanf_s("%d", &n_pessoas);
	printf("Quantos conjuntos a considerar ?\n");
	scanf_s("%d", &n_conjuntos);

	if (n_conjuntos < 3 && n_conjuntos >(n_pessoas / 2)){
		return 1;
	}

	for (i = 0; i < n_pessoas; i++){
		ClearScreen();
		pessoa temp;

		printf("Pessoa %d\n", i);
		printf("Nome : ");
		scanf_s("%s", &temp.nome);
		printf("Idade: ");
		scanf_s("%d", &temp.idade);

		temp.ID = i;

		vector_add(&v1, &temp);
	}

	return 0;
}