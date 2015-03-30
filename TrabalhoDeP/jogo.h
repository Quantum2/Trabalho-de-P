#ifndef JOGO_INIT
#define JOGO_INIT
#include "vector.h"

typedef struct conjuntos grupos;
struct conjuntos{
	vector pessoas;
	int quantidade;
};

void comecarJogo(vector *vec);
grupos distribuir(vector *vec);

#endif