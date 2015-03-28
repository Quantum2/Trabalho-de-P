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

	printf("Escolha a opcao pretendida\n");
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
	int n_pessoas, n_conjuntos, i, escolha;
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
		pessoa *temp;
		temp = (pessoa *)malloc(sizeof(pessoa));

		printf("Pessoa %d\n", i + 1);
		printf("Nome : ");
		scanf("%s", temp->nome);
		printf("Idade: ");
		scanf("%d", &temp->idade);

		temp->ID = i + 1;

		vector_add(&v1, temp);
	}

	ClearScreen();

	printf("O que pretende fazer agora ?\n");
	printf("1 - Verificar os dados\n");
	printf("2 - Prosseguir para o jogo\n");
	printf("3 - Guardar os dados\n");
	scanf("%d", &escolha);

	switch (escolha)
	{
	case 1:
		ClearScreen();

		for (i = 0; i < vector_total(&v1); i++){
			printf("ID: %d \n", ((pessoa *)vector_get(&v1, i))->ID);
			printf("Nome : %s\n", ((pessoa *)vector_get(&v1, i))->nome);
			printf("Idade : %d\n", ((pessoa *)vector_get(&v1, i))->idade);
			printf("\n");
		}
		break;
	case 2:

		break;
	case 3:

		break;
	default:
		break;
	}

	return 0;
}