#include "Puzzle.h"
#include <fstream>

// Constructor por defecto.
Puzzle::Puzzle()
{
	ruta = "";

	grande = NULL;
	medio = NULL;
	pequeno = NULL;
	matriz = NULL;

	// Tamaño del puzzle.
	tamano = 0;

	// Posición del hueco.
	huecoX = 0;
	huecoY = 0;

	// Inicializamos los mejores tiempos y movimientos.
	for(int i=0; i<10; i++)
	{
		mejorTiempo[i]= 3600000;
		mejorMovimiento[i] = 999;
	}
}

// Constructor sobrecargado.
Puzzle::Puzzle(string ruta)
{
	this->ruta = ruta;

	// Cargamos las imágenes.
	string rutaImagen = "";
	
	rutaImagen = "puzzles/"+ruta+"/grande.jpg";
	grande = IMG_Load(rutaImagen.c_str());
	if (grande == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};

	rutaImagen = "puzzles/"+ruta+"/medio.jpg";
	medio = IMG_Load(rutaImagen.c_str());
	if (medio == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};

	rutaImagen = "puzzles/"+ruta+"/pequeno.jpg";
	pequeno = IMG_Load(rutaImagen.c_str());
	if (pequeno == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	};

	// Matriz del puzzle.
	matriz = NULL;

	// Tamaño del puzzle.
	tamano = 0;

	// Posición del hueco.
	huecoX = 0;
	huecoY = 0;

	// Inicializamos los mejores tiempos y movimientos.
	for(int i=0; i<10; i++)
	{
		mejorTiempo[i]= 3600000;
		mejorMovimiento[i] = 999;
	}
}

// Constructor de copia.
Puzzle::Puzzle(const Puzzle& puzzle)
{
	grande = NULL;
	medio = NULL;
	pequeno = NULL;
	matriz = NULL;
	*this = puzzle;
}

// Operador de asignación.
Puzzle& Puzzle::operator=(const Puzzle& puzzle)
{
	if (this != &puzzle)
	{
		// Copiamos la ruta.
		ruta = puzzle.ruta;
		
		// Cargamos las imágenes.
		/*
		string rutaImagen = "";

		rutaImagen = "puzzles/"+ruta+"/grande.jpg";
		grande = IMG_Load(rutaImagen.c_str());
		if (grande == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};

		rutaImagen = "puzzles/"+ruta+"/medio.jpg";
		medio = IMG_Load(rutaImagen.c_str());
		if (medio == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};

		rutaImagen = "puzzles/"+ruta+"/pequeno.jpg";
		pequeno = IMG_Load(rutaImagen.c_str());
		if (pequeno == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		};
		*/
		// Copiamos el tamaño.
		setTamano(puzzle.getTamano());

		// Copiamos la matriz.
		// Puzzle solucionado
		for(int i=0; i<tamano; i++)
		{
			for(int j=0; j<tamano; j++)
			{
				matriz->getPunteroElemento(i,j)->setX(puzzle.matriz->getPunteroElemento(i,j)->getX());
				matriz->getPunteroElemento(i,j)->setY(puzzle.matriz->getPunteroElemento(i,j)->getY());
			}
		}

		huecoX = puzzle.huecoX;
		huecoY = puzzle.huecoY;
		
	}
	return *this;
}

// Destructor.
Puzzle::~Puzzle()
{
	// Liberar memoria.
	SDL_FreeSurface(grande);
	SDL_FreeSurface(medio);
	SDL_FreeSurface(pequeno);

	if(matriz != NULL)
		delete matriz;

	// Liberamos los mejores movimientos.
	mejorMovimiento.clear();

	// Liberamos los mejores tiempos.
	mejorTiempo.clear();
}


// Obtiene la rulta.
string Puzzle::getRuta() const
{
	return ruta;
}

// Establece la ruta.
void Puzzle::setRuta(string ruta)
{
	this->ruta = ruta;
}

// Devuelve la superficie de la imagen pequeña.
SDL_Surface* Puzzle::getPequeno() const
{
	return pequeno;
}

// Devuelve la superficie de la imagen mediana.
SDL_Surface* Puzzle::getMedio() const
{
	return medio;
}

// Devuelve la superficie de la imagen grande.
SDL_Surface* Puzzle::getGrande() const
{
	return grande;
}

// Devuelve el tamaño del puzzle.
int Puzzle::getTamano() const
{
	return tamano;
}

// Establece el tamaño del puzzle.
void Puzzle::setTamano(int nuevoTamano)
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
void Puzzle::remover()
{
	// Indica la dirección del movimiento.
	string direccion = "";

	// Número de intento de remover.
	int intentoRemover = 1;

	do{

		// Removemos el puzzle.
		int numIntercambios = tamano*tamano*50/intentoRemover;
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
		}
		// Incrementamos los intentos de remover el puzzle.
		intentoRemover++;

	}while(solucionado());
}

// Soluciona el puzzle.
void Puzzle::solucionar()
{
	// Puzzle solucionado
	for(int i=0; i<tamano; i++)
	{
		for(int j=0; j<tamano; j++)
		{
			matriz->getPunteroElemento(i,j)->setX(i);
			matriz->getPunteroElemento(i,j)->setY(j);
		}
	}
}

// Indica si el puzzle está solucionado.
bool Puzzle::solucionado() const
{
	// Puzzle solucionado
	bool solucionado = true;
	for(int i=0; i<tamano && solucionado == true; i++)
	{
		for(int j=0; j<tamano && solucionado == true; j++)
		{
			if( (matriz->getElemento(i,j).getX() != i) || (matriz->getElemento(i,j).getY() != j) )
				solucionado = false;
		}
	}

	return solucionado;
}

// Intercambia dos piezas.
void Puzzle::intercambiar(int posx1, int posy1, int posx2, int posy2)
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
bool Puzzle::mover(string direccion)
{
	if(direccion == "arriba")
	{
		if(huecoY<tamano-1)
		{
			intercambiar(huecoX, huecoY, huecoX, huecoY+1);
			return true;
		}
	}
	else if(direccion == "abajo")
	{
		if(huecoY>0)
		{
			intercambiar(huecoX, huecoY, huecoX, huecoY-1);
			return true;
		}
	}
	else if(direccion == "derecha")
	{
		if(huecoX>0)
		{
			intercambiar(huecoX, huecoY, huecoX-1, huecoY);
			return true;
		}
	}
	else if(direccion == "izquierda")
	{
		if(huecoX<tamano-1)
		{
			intercambiar(huecoX, huecoY, huecoX+1, huecoY);
			return true;
		}
	}
	else
	{
		cout << "<Error>Puzzle:mover - Dirección no permitida.";
	}
	return false;
}

// Devuelve el mejor tiempo del nivel actual.
Uint32 Puzzle::getMejorTiempo()
{
	return mejorTiempo[getTamano()];
}

// Establece el mejor tiempo del nivel actual.
void Puzzle::setMejorTiempo(Uint32 mejorTiempo)
{
	this->mejorTiempo[getTamano()] = mejorTiempo;
}

// Devuelve la mejor cantidad de movimientos del nivel actual.
int Puzzle::getMejorMovimiento()
{
	return mejorMovimiento[getTamano()];
}

// Establece la mejor cantidad de movimientos del nivel actual.
void Puzzle::setMejorMovimiento(int mejorMovimiento)
{
	this->mejorMovimiento[getTamano()] = mejorMovimiento;
}

// Carga las estadísticas del puzzle desde el fichero de texto.
void Puzzle::cargarEstadisticas()
{
	if(ruta!="")
	{
		// Stream del fichero
		ifstream f;

		// Ruta del fichero.
		string fichero = "puzzles/"+ruta+"/estadisticas.txt";

		// Abrimos el fichero.
		f.open(fichero.c_str(),ios::in);
		if( f.is_open() )
		{
			// Leemos las estadísticas.
			for(int i=0; i<10; i++)
			{
				// Leemos el mejor tiempo.
				Uint32 tiempo = 0;
				f >> tiempo;

				// Guardamos el mejor tiempo.
				mejorTiempo[i]= tiempo;

				// Leemos el mejor movimiento.
				int movimiento = 0;
				f >> movimiento;

				// Guardamos el mejor movimiento.
				mejorMovimiento[i] = movimiento;
			}
			
			// Cerramos el fichero.
			f.close();
		}
	}
}

// Guarda las estadísticas del puzzle en el fichero de texto.
void Puzzle::guardarEstadisticas()
{
	if(ruta!="")
	{
		// Stream del fichero
		ofstream f;

		// Ruta del fichero.
		string fichero = "puzzles/"+ruta+"/estadisticas.txt";

		// Abrimos el fichero.
		f.open(fichero.c_str(),ios::out);
		if( f.is_open() )
		{
			// Escribimos las estadísticas.
			for(int i=0; i<10; i++)
			{
				// Escribimos el mejor tiempo.
				Uint32 tiempo = mejorTiempo[i];
				f << tiempo;

				// Espacio
				char espacio = ' ';
				f << espacio;
				
				// Escribimos el mejor movimiento.
				int movimiento = mejorMovimiento[i];
				f << movimiento;

				// Salto de línea.
				f << endl;
			}

			// Cerramos el fichero.
			f.close();
		}
	}
}

// Devuelve el falor de f del puzzle.
int Puzzle::getF()
{
	// Número de piezas mal colocadas.
	int piezasMal = 0;
	for(int i=0; i<tamano; i++)
	{
		for(int j=0; j<tamano; j++)
		{
			if( (matriz->getElemento(i,j).getX() != i) || (matriz->getElemento(i,j).getY() != j) )
				piezasMal++;
		}
	}

	return piezasMal;
}
