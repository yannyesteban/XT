#include<iostream>
#include<conio.h>

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdlib.h>
using namespace std;
#define ESC 27

int main() {

	CONSOLE_CURSOR_INFO info_cursor;
	info_cursor.bVisible = FALSE;
	info_cursor.dwSize = 100;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info_cursor);

	//system("color 0F");//ejemplo 
	
	char key=100;
	int particula[2] = {}, i;

	while (true) {
		//Condiciones de las teclas presionadas
		if (key == ESC)exit(0);
		if (key == 'w')(particula[0] > 0) ? particula[0]-- : printf("\a");
		if (key == 'a')(particula[1] > 0) ? particula[1]-- : printf("\a");
		if (key == 's')(particula[0] < 24) ? particula[0]++ : printf("\a");
		if (key == 'd')(particula[1] < 9) ? particula[1]++ : printf("\a");

		//Dibuja los saltos y la particula segun su posición
		for (i = 0; i < 250; i++) {
			if ((particula[0] * 10) + particula[1] == i) {
				cout << "O";
				break; //Dejar de digujar los saltos
			} else {
				cout << "\t";
			}
		}

		//Espera que se posicióne una tecla y limpia el 'esenario'
		key = _getch();
		system("cls");
		//printf("[x=%d, y=%d]", particula[0], particula[1]); //Ubicacion de la particula.
	}
	return 0;
}
/*

	0 = Negro
	1= Azul
	2= Verde
	3= Aguamarina
	4= Rojo
	5= Púrpura
	6= Amarillo
	7= Blanco
	8= Gris
	9= Azul Claro
	A= Verde Claro
	B= Aguamarina Claro
	C= Rojo Claro
	D= Púrpura Claro
	E= Amarillo Claro
	F= Blanco Brillante

*/


#define KEY_UP_1 '\x75' /* cursor hacia arriba */
#define KEY_UP_2 '\x48' /* cursor hacia arriba */

#define KEY_LEFT_1 '\x6C' /* cursor hacia la izquierda */
#define KEY_LEFT_2 '\x4C' /* cursor hacia la izquierda */

#define KEY_RIGHT_1 '\x72' /* cursor hacia la derecha */
#define KEY_RIGHT_2 '\x52' /* cursor hacia la derecha */

#define KEY_DOWN_1 '\x64' /* cursor hacia abajo */
#define KEY_DOWN_2 '\x44' /* cursor hacia abajo */

int main3(void)

{
	while (!_kbhit());
	switch (_getch()) /* Teclas: 'u', 'U', 'l', 'L', 'r', 'R', 'd', 'D', otras */
	{
	case KEY_UP_1: case KEY_UP_2:
		puts("arriba");
		break;
	case KEY_LEFT_1: case KEY_LEFT_2:
		puts("iz");
		break;
	case KEY_RIGHT_1: case KEY_RIGHT_2:
		puts("der");
		break;
	case KEY_DOWN_1: case KEY_DOWN_2:
		puts("abajo");
		break;
	default: puts("No valido");
	}

	return EXIT_SUCCESS;
}