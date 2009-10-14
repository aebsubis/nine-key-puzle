#ifndef _PUZLE_H
#define	_PUZLE_H

#include <iostream>
#include <string>
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

	// Remueve las piezas del puzle.
	void remover();

	// Dibuja el puzle.
	void dibujar() const;

private:

	// Ruta del puzle.
	string ruta;

	// Matriz del estado puzle.
	int estado[3][3];
};


#endif	/* _PUZLE_H */

