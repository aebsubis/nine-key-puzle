#include "Puzle.h"
#include <sstream>

// Constructor por defecto.
Puzle::Puzle()
{
	ruta = "";

	grande = NULL;
	medio = NULL;
	pequeno = NULL;
	matriz = NULL;

	tamano = 0;

	huecoX = 0;
	huecoY = 0;
}

// Constructor sobrecargado.
Puzle::Puzle(string ruta)
{
	this->ruta = ruta;

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

	matriz = NULL;

	tamano = 0;

	huecoX = 0;
	huecoY = 0;
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

		// Copiamos el tamaño.
		if(puzle.getTamano() > 0)
			setTamano(puzle.getTamano());
		else
			tamano = puzle.getTamano();
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

	if(matriz != NULL)
		delete matriz;
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

// Devuelve el tamaño del puzle.
int Puzle::getTamano() const
{
	return tamano;
}

// Establece el tamaño del puzle.
void Puzle::setTamano(int nuevoTamano)
{
	// Asignamos el nuevo tamaño.
	tamano = nuevoTamano;

	// Liberamos la matriz actual.
	if(matriz != NULL)
		delete matriz;
	
	// Reservamos la matriz del nuevo tamaño.
	matriz = new Matriz<Pieza>(tamano, tamano);

	// Establecemos el estado solucionado.
	solucionar();

	// Indicamos la posición del hueco.
	huecoX = tamano-1;
	huecoY = tamano-1;
}

// Remueve las fichas.
void Puzle::remover()
{
	string direccion = "";
	int numIntercambios = tamano*50;
	for(int i=0; i<numIntercambios; i++ )
	{
		int dirAleatoria = rand()%4;
		switch(dirAleatoria)
		{
			case 0:
				direccion = "derecha";
				break;
			case 1:
				direccion = "izquierda";
				break;
			case 2:
				direccion = "arriba";
				break;
			case 3:
				direccion = "abajo";
				break;
		}
		
		mover(direccion);

		/*
		int posx1 = rand()%tamano;
		int posy1 = rand()%tamano;
		int posx2 = rand()%tamano;
		int posy2 = rand()%tamano;

		intercambiar(posx1, posy1, posx2, posy2);
		*/
	}
}

// Soluciona el puzle.
void Puzle::solucionar()
{
	// Puzle solucionado
	for(int i=0; i<tamano; i++)
	{
		for(int j=0; j<tamano; j++)
		{
			matriz->getPunteroElemento(i,j)->setX(i);
			matriz->getPunteroElemento(i,j)->setY(j);
		}
	}
}

// Indica si el puzle está solucionado.
bool Puzle::solucionado() const
{
	// Puzle solucionado
	bool solucionado = true;
	for(int i=0; i<tamano && solucionado == true; i++)
	{
		for(int j=0; j<tamano && solucionado == true; j++)
		{
			if( (matriz->getElemento(i,j).getX() != i) || (matriz->getElemento(i,j).getY() !=j) )
				solucionado = false;
		}
	}

	return solucionado;
}

// Intercambia dos piezas.
void Puzle::intercambiar(int posx1, int posy1, int posx2, int posy2)
{
	Pieza pieza1 = matriz->getElemento(posx1, posy1);
	Pieza pieza2 = matriz->getElemento(posx2, posy2);
	matriz->setElemento(posx1, posy1, pieza2);
	matriz->setElemento(posx2, posy2, pieza1);

	// Comprobamos si hemos movido el hueco.
	if(posx1 == huecoX && posy1 == huecoY)
	{
		// Cambiamos el hueco.
		huecoX = posx2;
		huecoY = posy2;
	}
	else if(posx2 == huecoX && posy2 == huecoY)
	{
		huecoX = posx1;
		huecoY = posy1;
	}
}

// Mueve el hueco en la dirección indicada.
void Puzle::mover(string direccion)
{
	if(direccion == "arriba")
	{
		if(huecoY<tamano-1)
		{
			intercambiar(huecoX, huecoY, huecoX, huecoY+1);
		}
	}
	else if(direccion == "abajo")
	{
		if(huecoY>0)
		{
			intercambiar(huecoX, huecoY, huecoX, huecoY-1);
		}
	}
	else if(direccion == "derecha")
	{
		if(huecoX>0)
		{
			intercambiar(huecoX, huecoY, huecoX-1, huecoY);
		}
	}
	else if(direccion == "izquierda")
	{
		if(huecoX<tamano-1)
		{
			intercambiar(huecoX, huecoY, huecoX+1, huecoY);
		}
	}
	else
	{
		cout << "<Error>Puzle:mover - Dirección no permitida.";
	}
}
