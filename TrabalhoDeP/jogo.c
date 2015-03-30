#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "jogo.h"
#include "vector.h"
#include "ins_dados.h"
#include "util.h"


void comecarJogo(vector *vec){
	grupos* dis;

	ClearScreen();

	dis = distribuir(vec);
	mostrarConjuntos(dis);
}

grupos* distribuir(vector *vec){
	grupos* dis;
	int i, j, rand, rand2, rand3;
	
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

	for (i = 0; i < rand; i++){
		for (j = 0; j < rand; j++){

		}
	}

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

	scanf_s("%d");
}