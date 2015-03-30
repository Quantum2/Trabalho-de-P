#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
#include "util.h"

#define BACKGROUND_COLOR 7
#define FOREGROUND_COLOR 0

void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X *csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
		)) return;

	/* Move the cursor home */
	SetConsoleCursorPosition(hStdOut, homeCoords);
}

void definirBackground(){
	char comando[30] = "color ";
	sprintf(comando, "color %d%d", FOREGROUND_COLOR, BACKGROUND_COLOR);
	system(comando);
}

unsigned int
randr(unsigned int min, unsigned int max)
{
	double scaled = (double)rand() / RAND_MAX;

	return (max - min + 1)*scaled + min;
}

unsigned int 
divisor(unsigned int dividend, unsigned int divisor)
{
	return (dividend + (divisor / 2)) / divisor;
}