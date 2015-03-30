#ifndef JOGO_INIT
#define JOGO_INIT
#include "vector.h"

typedef struct conjuntos grupos;
struct conjuntos{
	vector pessoas;
	int num_pessoas;
	int num_conjuntos;
};

void comecarJogo(vector *vec);
grupos* distribuir(vector *vec);
void mostrarConjuntos(grupos* dis);

#endif