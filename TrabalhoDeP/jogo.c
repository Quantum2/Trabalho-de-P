#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "jogo.h"
#include "vector.h"
#include "ins_dados.h"
#include "util.h"


void comecarJogo(vector *vec){
	distribuir(vec);
}

grupos distribuir(vector *vec){
	grupos dis;
	int i, rand;
	
	rand = randr(3, (vector_total(vec) / 2));

	//return dis;
}