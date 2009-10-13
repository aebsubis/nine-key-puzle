#include "Puzle.h"


// Constructor por defecto.
Puzle::Puzle()
{
	ruta = "";
}

// Constructor sobrecargado.
Puzle::Puzle(string ruta)
{
	this->ruta = ruta;
}

// Destructor.
Puzle::~Puzle()
{
	// Liberar memoria.
}


// Obtiene la rulta.
string Puzle::getRuta() const
{
	return ruta;
}

// Establece la ruta.
void Puzle::setRuta(string ruta)
{
	this->ruta = ruta;
}
