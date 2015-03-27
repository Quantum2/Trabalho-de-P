#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "vector.h"
#include "ins_dados.h"

#define TEMPO_DE_PAUSA 2

int main(int argc, char *argv[]){
	if (welcome_conf() != 0){
		printf("Os dados inseridos sao invalidos, tente de novo\n");
		Sleep(TEMPO_DE_PAUSA * 1000);
	}

	return 0;
}