#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include "vector.h"
#include "ins_dados.h"
#include "util.h"
#include "jogo.h"

#define TEMPO_DE_PAUSA 2

void menu(){
	int escolha;
	vector* v1 = malloc(sizeof(vector));

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
		v1 = conf_actual(v1);
		menu();
	case 4:
		ClearScreen();
		v1 = conf_actual(v1);
		comecarJogo(v1);
		break;
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

vector* conf_actual(vector *vec){
	FILE *fp;
	int size, i;
	vector_init(vec);
	fp = fopen("db.bin", "r");

	fread(&size,sizeof(int),1,fp);
	pessoa *db = (pessoa *)malloc(size * sizeof(pessoa));

	fread(db, sizeof(pessoa), size, fp);

	for (i = 0; i < size; i++){
		printf("ID: %d \n", db[i].ID);
		printf("Nome : %s \n", db[i].nome);
		printf("Idade : %d \n", db[i].idade);

		vector_add(vec, &db[i]);
	}

	fflush(stdin);
	getchar();
	fclose(fp);
	return vec;
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
	int n_pessoas, n_conjuntos, i, escolha, gravar_e;
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

	if (n_pessoas < 5){
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
	printf("1 - Verificar e guardar os dados\n");
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
		printf("Pretende gravar os dados ?\n");
		printf("1 - Sim\n2 - Nao\n");
		scanf("%d", &gravar_e);
		if (gravar_e == 1){
			gravar_conf(v1, vector_total(&v1));
		}
		menu();
		break;
	case 2:
		gravar_conf(v1, vector_total(&v1));
		comecarJogo(&v1);
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