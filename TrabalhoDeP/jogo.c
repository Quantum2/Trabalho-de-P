#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "jogo.h"
#include "vector.h"
#include "ins_dados.h"
#include "util.h"

#define TAMANHO_DO_COMANDO 50

void comecarJogo(vector *vec){
	grupos* dis;

	ClearScreen();

	dis = distribuir(vec);
	mostrarConjuntos(dis);

	ClearScreen();

	jogo(dis, vec);
}

grupos* distribuir(vector *vec){
	grupos* dis;
	int i, j, rand, rand2, rand3, contador = 0;
	bool check = false;
	int** IDs;
	
	rand = randr(3, divisor(vector_total(vec), 2));
	dis = malloc(rand * sizeof(grupos));

	for (i = 0; i < rand; i++){
		rand2 = randr(0, vector_total(vec));
		rand3 = randr(0, vector_total(vec));
		do{
			rand2 = randr(0, vector_total(vec));
		} while (rand3 == rand2);
		vector_init(&dis[i].pessoas);

		dis[i].num_conjuntos = rand;

		vector_add(&dis[i].pessoas, vector_get(vec, rand2));
		vector_add(&dis[i].pessoas, vector_get(vec, rand3));
		dis[i].num_pessoas = 2;
	}

	IDs = (int **)malloc(dis[0].num_conjuntos*sizeof(int *));
	for (i = 0; i <= dis[0].num_pessoas;i++)
		IDs[i] = (int *)malloc(dis[0].num_pessoas*sizeof(int));

	for (i = 0; i < dis[0].num_conjuntos; i++){
		for (j = 0; j < dis[i].num_pessoas; j++){
			IDs[i][j] = ((pessoa *)vector_get(&dis[i].pessoas, j))->ID;
		}
	}

	do{
		for (i = 0; i < dis[0].num_conjuntos; i++){
			for (j = 0; j < dis[i].num_pessoas; j++){
				if (((pessoa *)vector_get(vec, contador))->ID == IDs[i][j])
					check = true;
			}
		}

		if (check == false){
			rand = randr(0, dis[0].num_conjuntos - 1);
			vector_add(&dis[rand].pessoas, vector_get(vec, contador));
			dis[rand].num_pessoas++;
		}

		check = false;
		contador++;
	} while (contador != vector_total(vec));

	return dis;
}

void mostrarConjuntos(grupos* dis){
	int i, j, num;

	num = dis[0].num_conjuntos;

	for (i = 0; i < num; i++){
		printf("Conjunto %d\n { ", i + 1);
		for (j = 0; j < dis[i].num_pessoas; j++){
			printf("%s ", ((pessoa *)vector_get(&dis[i].pessoas, j))->nome);
		}
		printf("}\n");
	}

	fflush(stdin);
	getchar();
}

float calcDispers(grupos* dis, int num_conjunto){
	float dispersao, temp, temp2 = 0;
	int j, k, pares = 0;

	for (j = 0; j < dis[num_conjunto].num_pessoas; j++){
		for (k = 0; k < dis[num_conjunto].num_pessoas; k++){
			if (k != j && k > j){
				temp = fabs((((pessoa *)vector_get(&dis[num_conjunto].pessoas, j))->idade) - (((pessoa *)vector_get(&dis[num_conjunto].pessoas, k))->idade));
				pares++;
			}
		}
		temp2 += temp;
	}

	dispersao = temp2 / pares;

	return dispersao;
}

void jogo(grupos* dis, vector *vec){
	int turno = 1, temp_int, y;
	char comando[TAMANHO_DO_COMANDO], temp[TAMANHO_DO_COMANDO], x[TAMANHO_DO_COMANDO];
	char* split;

	ClearScreen();
	fflush(stdin);

	printf("Jogador actual: %d\n", turno);
	printf("Para comandos disponiveis escreva 'help'\n");
	fgets(comando, TAMANHO_DO_COMANDO, stdin);
	strtok(comando, "\n");
	strcpy(temp, comando);

	split = strtok(comando, " ");

	if (strcmp(temp, "help") == 0){
		ajuda();
		fflush(stdin);
		jogo(dis, vec);
	}
	else if (strcmp(temp, "menu") == 0)
		menu();
	else if (strcmp(temp, "sair") == 0)
		system("exit");
	else if (strcmp(split, "disp") == 0){
		split = strtok(temp, " ");
		split = strtok(NULL, " \n");
		temp_int = atoi(split);
		temp_int--;
		printf("A dispersao do grupo %d e %f\n", temp_int + 1, calcDispers(dis, temp_int));
		fflush(stdin);
		getchar();
		jogo(dis, vec);
	}
	else if (strcmp(split, "inserir") == 0){
		split = strtok(temp, " ");
		split = strtok(NULL, " \n");
		strcpy(x, split);
		split = strtok(NULL, " \n");
		y = atoi(split);

		inserirPessoa(dis, vec, x, y);
	}
	else if (strcmp(temp, "conjuntos") == 0){
		ClearScreen();
		mostrarConjuntos(dis);
		jogo(dis, vec);
	}
	else if (strcmp(temp, "pessoas") == 0){
		ClearScreen();
		conf_actual(vec);
		jogo(dis, vec);
	}
	else{
		jogo(dis, vec);
	}
}

void ajuda(){
	ClearScreen();
	printf("disp <x> - Calcular a dispersao do conjunto X\n");
	printf("conjuntos - Mostra todos os conjuntos existentes\n");
	printf("pessoas - Mostrar todas as pessoas na base de dados\n");
	printf("inserir <x> <y> - Inserir a pessoa com o nome X no conjunto Y\n");
	printf("eliminar <x> <y> - Eliminar a pessoa com o nome X do conjunto Y\n");
	printf("transf <x> <y> - Transferir a pessoa com o nome X para o conjunto Y\n");
	printf("menu - Voltar ao menu\n");
	printf("sair - Para terminar a execucao do jogo\n");
	printf("\nPara voltar ao jogo, pressione qualquer tecla...\n");

	fflush(stdin);
	getchar();
}

void inserirPessoa(grupos* dis, vector *vec, char nome[], int id_conjunto){
	int ID, i, j;
	bool check = false;
	pessoa* temp;

	for (i = 0; i < vector_total(vec); i++){
		if (strcmp(nome, ((pessoa *)vector_get(vec, i))->nome) == 0)
			ID = i;
	}

	temp = malloc(sizeof(pessoa));

	for (i = 0; i < dis[id_conjunto].num_pessoas; i++){
		if (((pessoa *)vector_get(&dis[id_conjunto].pessoas, i))->ID == temp->ID)
			check = true;
	}

	if (!check){

	}
}