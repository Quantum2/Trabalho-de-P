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

	dis = distribuir(vec);
}

grupos* distribuir(vector *vec){
	grupos* dis;
	int i, rand, rand2, rand3;
	
	rand = randr(3, divisor(vector_total(vec), 2));
	dis = malloc(rand * sizeof(grupos));

	for (i = 0; i < rand; i++){
		rand2 = randr(0, vector_total(vec));
		do{
			rand2 = randr(0, vector_total(vec));
		} while (rand3 = rand2);
		vector_init(&dis[i].pessoas);

		vector_add(&dis[i].pessoas, vector_get(vec, rand2));
		vector_add(&dis[i].pessoas, vector_get(vec, rand3));
	}

	return dis;
}