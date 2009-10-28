#include <iostream>
#include "Juego.h"
#include "include/Juego.h"

using namespace std;

/* Función main.
 * Punto de entrada del programa.
 */
int main(int argc, char** argv)
{
	// Creamos el juego.
	Juego* juego = Juego::getInstancia();
	
	// Iniciamos.
	juego->iniciar();

	// liberamos.
	delete juego;
}

