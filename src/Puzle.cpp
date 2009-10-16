#include "Puzle.h"
#include <sstream>

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

	grande = NULL;
	medio = NULL;
	pequeno = NULL;
	for(int i=0; i<9; i++)
		piezas[i] = NULL;
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

	// Cargamos las imágenes.
	string rutaImagen = "";
	
	rutaImagen = "puzles/"+ruta+"/grande.jpg";
	grande = IMG_Load(rutaImagen.c_str());
	if (grande == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};

	rutaImagen = "puzles/"+ruta+"/medio.jpg";
	medio = IMG_Load(rutaImagen.c_str());
	if (medio == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};

	rutaImagen = "puzles/"+ruta+"/pequeno.jpg";
	pequeno = IMG_Load(rutaImagen.c_str());
	if (pequeno == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};
	
	// Cargamos las piezas.
	for(int i=0; i<9; i++)
	{
		std::ostringstream stm;
		stm << i+1;
		rutaImagen = "puzles/"+ruta+"/"+stm.str()+".jpg";
		piezas[i] = IMG_Load(rutaImagen.c_str());
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

		// Cargamos las imágenes.
		string rutaImagen = "";

		rutaImagen = "puzles/"+ruta+"/grande.jpg";
		grande = IMG_Load(rutaImagen.c_str());
		if (grande == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};

		rutaImagen = "puzles/"+ruta+"/medio.jpg";
		medio = IMG_Load(rutaImagen.c_str());
		if (medio == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};

		rutaImagen = "puzles/"+ruta+"/pequeno.jpg";
		pequeno = IMG_Load(rutaImagen.c_str());
		if (pequeno == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};

		// Cargamos las piezas.
		for(int i=0; i<9; i++)
		{
			std::ostringstream stm;
			stm << i+1;
			rutaImagen = "puzles/"+ruta+"/"+stm.str()+".jpg";
			piezas[i] = IMG_Load(rutaImagen.c_str());
		}

	}
	return *this;
}

// Destructor.
Puzle::~Puzle()
{
	// Liberar memoria.
	SDL_FreeSurface(grande);
	SDL_FreeSurface(medio);
	SDL_FreeSurface(pequeno);
	for(int i=0; i<9; i++)
		SDL_FreeSurface(piezas[i]);
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

// Devuelve la superficie de la imagen pequeña.
SDL_Surface* Puzle::getPequeno() const
{
	return pequeno;
}

// Devuelve la superficie de la imagen mediana.
SDL_Surface* Puzle::getMedio() const
{
	return medio;
}

// Devuelve la superficie de la imagen grande.
SDL_Surface* Puzle::getGrande() const
{
	return grande;
}

// Devuelve la superficie de la pieza seleccionada.
SDL_Surface* Puzle::getPieza(int numPieza) const
{
	if(numPieza>0 && numPieza<=9)
		return piezas[numPieza-1];
	else
		return NULL;
}

// Remueve las fichas.
void Puzle::remover()
{
	// Creamos un vector ordenado del 1 al 9.
	int fichas[9];
	for(int i = 0; i<9; i++)
		fichas[i] = i+1;

	int numIntercambios = 50;
	for(int i=0; i<numIntercambios; i++)
	{
		int pos1 = rand()%9;
		int pos2 = rand()%9;
		int aux = 0;
		
		// Intercambiamos las 2 posiciones.
		aux = fichas[pos2];
		fichas[pos2] = fichas[pos1];
		fichas[pos1] = aux;
	}

	// Asignamos la nueva distribución.
	int contador = 0;
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			estado[i][j] = fichas[contador];
			contador++;
		}
	}
}

// Soluciona el puzle.
void Puzle::solucionar()
{
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

// Indica si el puzle está solucionado.
bool Puzle::solucionado() const
{
	// Puzle solucionado
	bool solucionado = true;
	int contador = 1;
	for(int i=0; i<3 && solucionado == true; i++)
	{
		for(int j=0; j<3 && solucionado == true; j++)
		{
			if(estado[i][j] != contador)
				solucionado = false;
			contador++;
		}
	}

	return solucionado;
}

