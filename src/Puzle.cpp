#include "Puzle.h"


// Constructor por defecto.
Puzle::Puzle()
{
	ruta = "";

	// Puzle solucionado
	int contador = 1;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			estado[i][j] = contador;
			contador++;
		}
	}
}

// Constructor sobrecargado.
Puzle::Puzle(string ruta)
{
	this->ruta = ruta;

	// Puzle solucionado
	int contador = 1;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			estado[i][j] = contador;
			contador++;
		}
	}
}

// Constructor de copia.
Puzle::Puzle(const Puzle& puzle)
{
	*this = puzle;
}

// Operador de asignación.
Puzle& Puzle::operator=(const Puzle& puzle)
{
	if (this != &puzle)
	{
		this->ruta = puzle.ruta;
		for(int i=0; i<3; i++)
		{
			for(int j=0; j<3; j++)
			{
				estado[i][j] = puzle.estado[i][j];
			}
		}

	}
	return *this;
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

// Remueve las fichas.
void Puzle::remover()
{

}


void Puzle::dibujar() const
{
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			cout << estado[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "----" << endl;
	cout << endl;
}
