#ifndef _PIEZA_H
#define	_PIEZA_H

#include <iostream>
using namespace std;

/* Clase PIEZA.
 *
 */
class Pieza
{
public:

	// Constructor por defecto.
	Pieza();

	/// Constructor de copia.
	Pieza(const Pieza& pieza);

	// Operador de asignación.
	Pieza& operator=(const Pieza& pieza);

	// Destructor.
	~Pieza();

	// Obtiene la coordenada x.
	int getX() const;

	// Establece la coordenada x.
	void setX(int nuevoX);

	// Obtiene la coordenada y.
	int getY() const;

	// Establece la coordenada y.
	void setY(int nuevoY);

private:

	// Coordenada x
	int coordenadaX;

	// Coordenada y.
	int coordenadaY;
};


#endif	/* _PIEZA_H */

