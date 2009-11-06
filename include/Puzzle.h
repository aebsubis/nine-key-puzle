#ifndef _PUZZLE_H
#define	_PUZZLE_H

#include <iostream>
#include <string>
#include <map>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include "Matriz.h"
#include "Pieza.h"
using namespace std;

/* Clase puzzle.
 *
 */
class Puzzle
{
public:

	// Constructor por defecto.
	Puzzle();

	// Constructor sobrecargado.
	Puzzle(string ruta);

	/// Constructor de copia.
	Puzzle(const Puzzle& puzzle);

	// Operador de asignación.
	Puzzle& operator=(const Puzzle& puzzle);

	// Destructor.
	~Puzzle();

	// Obtiene la rulta.
	string getRuta() const;

	// Establece la ruta.
	void setRuta(string ruta);

	// Devuelve la superficie de la imagen pequeña.
	SDL_Surface* getPequeno() const;

	// Devuelve la superficie de la imagen mediana.
	SDL_Surface* getMedio() const;

	// Devuelve la superficie de la imagen grande.
	SDL_Surface* getGrande() const;

	// Devuelve el tamaño del puzzle.
	int getTamano() const;

	// Establece el tamaño del puzzle.
	void setTamano(int nuevoTamano);

	// Remueve las piezas del puzzle.
	void remover();

	// Soluciona el puzzle.
	void solucionar();

	// Matriz de piezas.
	Matriz<Pieza> *matriz;

	// Indica si el puzzle está solucionado.
	bool solucionado() const;

	// Intercambia dos piezas.
	void intercambiar(int posx1, int posy1, int posx2, int posy2);

	// Mueve el hueco en la dirección indicada.
	bool mover(string direccion);

	// Devuelve el mejor tiempo del nivel actual.
	Uint32 getMejorTiempo();

	// Establece el mejor tiempo del nivel actual.
	void setMejorTiempo(Uint32 mejorTiempo);

	// Devuelve la mejor cantidad de movimientos del nivel actual.
	int getMejorMovimiento();
	
	// Establece la mejor cantidad de movimientos del nivel actual.
	void setMejorMovimiento(int mejorMovimiento);

	// Carga las estadísticas del puzzle desde el fichero de texto.
	void cargarEstadisticas();

	// Guarda las estadísticas del puzzle en el fichero de texto.
	void guardarEstadisticas();

	// Devuelve el falor de f del puzzle.
	int getF();
	
	// Indica la coordenada del hueco;
	int huecoX;
	int huecoY;
	
private:

	// Tamaño del puzzle NxN
	int tamano;

	// Ruta del puzzle.
	string ruta;

	// Imagenes del puzzle.
	SDL_Surface* grande;
	SDL_Surface* medio;
	SDL_Surface* pequeno;

	// Almacena el mejor tiempo de cada tamaño de puzzle.
	map<int, Uint32> mejorTiempo;

	// Almacena la mejor cantidad de movimientos de cada tamaño de puzzle.
	map<int, int> mejorMovimiento;
};


#endif	/* _PUZZLE_H */
