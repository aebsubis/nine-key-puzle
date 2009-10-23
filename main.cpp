#include <iostream>
#include "Juego.h"
#include "include/Juego.h"

using namespace std;

/* Función main.
 * Punto de entrada del programa.
 */
int main(int argc, char** argv)
{
	Juego* juego = Juego::getInstancia();
	juego->iniciar();
}

