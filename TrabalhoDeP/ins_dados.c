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
	printf("1 - Criar a configuracao\n");
	printf("2 - Modificar a configuracao\n");
	printf("3 - Mostrar a configuracao actual\n");
	printf("4 - Jogar !\n");
	printf("5 - Sair !\n");

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
	case 3:
		ClearScreen();
		conf_actual();
		menu();
	case 5:
		system("exit");
		break;
	default:
		printf("Essa opcao nao existe, tente de novo\n");
		Sleep(TEMPO_DE_PAUSA * 1000);
		menu();
		break;
	}	
}

void conf_actual(){
	FILE *fp;
	int size, i;
	fp = fopen("db.bin", "r");

	fread(&size,sizeof(int),1,fp);
	pessoa *db = (pessoa *)malloc(size * sizeof(pessoa));

	fread(db, sizeof(pessoa), size, fp);

	for (i = 0; i < size; i++){
		printf("%d \n", db[i].ID);
	}

	scanf("%c");
}

void gravar_conf(vector vec, int size){
	FILE *fp;
	int i;
	pessoa *db = (pessoa *)malloc(size * sizeof(pessoa));

	for (i = 0; i < size; i++){
		db[i].ID = ((pessoa *)vector_get(&vec, i))->ID;
		db[i].idade = ((pessoa *)vector_get(&vec, i))->idade;
		strcpy(db[i].nome, ((pessoa *)vector_get(&vec, i))->nome);
	}

	fp = fopen("db.bin", "w");

	if (fp != NULL) {
		fwrite(&size, sizeof(int), 1, fp);
		fwrite(db, size * sizeof(pessoa), 1, fp);
		fclose(fp);
	}
	else{
		printf("Ocorreu um erro ao tentar gravar o ficheiro !\n");
		menu();
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

	if (n_conjuntos < 3 || n_conjuntos > (n_pessoas / 2)){
		ClearScreen();
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
	printf("3 - Guardar os dados e voltar ao menu\n");
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
		scanf("%c");
		
		break;
	case 2:
		
		break;
	case 3:
		gravar_conf(v1, vector_total(&v1));
		menu();
		break;
	default:
		break;
	}

	return 0;
}