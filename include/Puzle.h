#ifndef _PUZLE_H
#define	_PUZLE_H

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL/SDL_image.h"
using namespace std;

/* Clase puzle.
 *
 */
class Puzle
{
public:

	// Constructor por defecto.
	Puzle();

	// Constructor sobrecargado.
	Puzle(string ruta);

	/// Constructor de copia.
	Puzle(const Puzle& puzle);

	// Operador de asignación.
	Puzle& operator=(const Puzle& puzle);

	// Destructor.
	~Puzle();

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

	// Devuelve la superficie de la pieza seleccionada.
	SDL_Surface* getPieza(int numPieza) const;

	// Remueve las piezas del puzle.
	void remover();

	// Matriz del estado puzle.
	int estado[3][3];

	// Indica si el puzle está solucionado.
	bool solucionado() const;

private:

	// Ruta del puzle.
	string ruta;

	// Imagenes del puzle.
	SDL_Surface* grande;
	SDL_Surface* medio;
	SDL_Surface* pequeno;
	SDL_Surface* piezas[9];
};


#endif	/* _PUZLE_H */

