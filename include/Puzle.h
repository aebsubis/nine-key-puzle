#ifndef _PUZLE_H
#define	_PUZLE_H

#include <iostream>
#include <string>
#include "SDL.h"
#include "SDL/SDL_image.h"
#include "Matriz.h"
#include "Pieza.h"
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

	// Devuelve el tamaño del puzle.
	int getTamano() const;

	// Establece el tamaño del puzle.
	void setTamano(int nuevoTamano);

	// Remueve las piezas del puzle.
	void remover();

	// Soluciona el puzle.
	void solucionar();

	// Matriz de piezas.
	Matriz<Pieza> *matriz;

	// Indica si el puzle está solucionado.
	bool solucionado() const;

	// Intercambia dos piezas.
	void intercambiar(int posx1, int posy1, int posx2, int posy2);

	// Mueve el hueco en la dirección indicada.
	bool mover(string direccion);

	// Indica la coordenada del hueco;
	int huecoX;
	int huecoY;
	
private:

	// Tamaño del puzle NxN
	int tamano;

	// Ruta del puzle.
	string ruta;

	// Imagenes del puzle.
	SDL_Surface* grande;
	SDL_Surface* medio;
	SDL_Surface* pequeno;
};


#endif	/* _PUZLE_H */
