#include "Pieza.h"

// Constructor por defecto.
Pieza::Pieza()
{
	coordenadaX = 0;
	coordenadaY = 0;
}

/// Constructor de copia.
Pieza::Pieza(const Pieza& pieza)
{
	*this = pieza;
}

// Operador de asignación.
Pieza& Pieza::operator=(const Pieza& pieza)
{
	if (this != &pieza)
	{
		coordenadaX = pieza.coordenadaX;
		coordenadaY = pieza.coordenadaY;
	}
	return *this;
}

// Destructor.
Pieza::~Pieza()
{

}

// Obtiene la coordenada x.
int Pieza::getX() const
{
	return coordenadaX;
}

// Establece la coordenada x.
void Pieza::setX(int nuevoX)
{
	coordenadaX = nuevoX;
}

// Obtiene la coordenada y.
int Pieza::getY() const
{
	return coordenadaY;
}

// Establece la coordenada y.
void Pieza::setY(int nuevoY)
{
	coordenadaY = nuevoY;
}
