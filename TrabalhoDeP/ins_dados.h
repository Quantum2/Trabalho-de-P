#ifndef INS_DADOS
#define INS_DADOS

typedef struct dados pessoa;
struct dados{
	int ID;
	int idade;
	char nome[100];
};

void menu();
vector* conf_actual(vector *vec);
void gravar_conf(vector vec, int size);
int welcome_conf();

#endif