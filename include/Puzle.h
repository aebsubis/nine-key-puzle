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

	// Destructor.
	~Puzle();

	// Obtiene la rulta.
	string getRuta() const;

	// Establece la ruta.
	void setRuta(string ruta);

private:

	string ruta;
};


#endif	/* _PUZLE_H */

