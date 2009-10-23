#include <sstream>
#include <SDL/SDL_video.h>
#include <SDL/SDL_keysym.h>
#include "Juego.h"

// Instancia de la clase.
Juego* Juego::instancia = NULL;

////////////////////////////////////////////
//////////// FUNCIONES PÚBLICAS ////////////
////////////////////////////////////////////

/// getInstancia
Juego* Juego::getInstancia()
{
	if(instancia == NULL)
		instancia = new Juego;
	return instancia;
}

// Destructor.
Juego::~Juego()
{
	// Borramos la instancia.
	if(instancia != NULL)
	{
		// Finaliza el juego y libera toda la memoria.
		finalizar();

		delete instancia;
		instancia = NULL;
	}
}

// Inicia el juego.
void Juego::iniciar()
{
	// Inicializamos el juego.
	inicializar();

	while(salir==false)
	{
		// Reiniciamos el iterador.
		iteracionAnterior = SDL_GetTicks();

		// Bucle del sonido de fondo.
		if(sonidos["fondo"]->reproduciendose() == false)
			reproducirSonido("fondo");

		while (SDL_GetTicks() - iteracionAnterior < 100)
		{
			// Procesamos los eventos del menú.
			eventos();

			// Actualizamos el menu.
			actualizar();

			// Hacemos un render.
			render();
		}
	}
}

// Procesa los eventos.
void Juego::eventos()
{
	// Procesa los eventos.
	estado->eventos(this);
}

// Actualiza.
void Juego::actualizar()
{
	// Actualiza.
	estado->actualizar(this);
}

// Hace un render.
void Juego::render()
{
	// Hace un render.
	estado->render(this);
}

// Modifica el estado del juego.
void Juego::setEstado(Estado<Juego>* estado)
{
	this->estado = estado;
}

// Establece como puzle actual el puzle anterior.
void Juego::puzzleAnterior()
{
	if(numPuzleActual == 0)
		numPuzleActual = puzles.size()-1;
	else
		numPuzleActual--;

	// Añadimos el delay de 140.
	delay = 140;

	// Reproducimos el sonido.
	reproducirSonido("menu");
}

// Establece como puzle actual el puzzle siguiente.
void Juego::puzzleSiguiente()
{
	// Elegimos el puzle de arriba.
	if((unsigned)numPuzleActual == puzles.size()-1)
		numPuzleActual = 0;
	else
		numPuzleActual++;

	// Añadimos el delay de -140.
	delay = -140;

	// Reproducimos el sonido.
	reproducirSonido("menu");
}

////////////////////////////////////////////
//////////// FUNCIONES PRIVADAS ////////////
////////////////////////////////////////////

// Constructor por defecto.
Juego::Juego()
{
	// Estado.
	estado = NULL;

	// Variables de SDL.
	SURFscreen = NULL;
	SURFfondo = NULL;
	SURFfondo2 = NULL;
	SURFsaliendo = NULL;
	SURFcompletado = NULL;
	SURFreloj = NULL;
	SURFtexto = NULL;
	FONTfuente = NULL;

	// Iniciamos el temporizador.
	temporizadorEscape = 0;
	iteracionAnterior = 0;
	temporizadorReloj = 0;
	temporizadorJuego = 0;

	// Mejor número de movimientos del puzle.
	mejorMovimiento = 0;

	// Mejor tiempo del puzle.
	mejorTiempo = 0;

	// Movimientos realizados.
	contadorMovimientos = 0;

	// Frame inicial.
	frameAnimacionReloj = 0;

	// Tiempo de escape.
	tiempoEscape = 3000;

	// Tiempo de delay.
	delay = 0;

	// Inicializamos la semilla del rand.
	srand(time(NULL));
}

// Reproduce el sonido que recibe por parámetro.
void Juego::reproducirSonido(string sonido)
{
	// Obtenemos el sonido.
	Sonido* snd = sonidos[sonido];

	// Comprobamos si el sonido existe.
	if(snd!=NULL)
	{
		// Reproducimos el sonido.
		snd->reproducir();
	}
	else
	{
		// Mostramos el mensaje de error.
		cout << "<Error> No se pudo reproducir el sonido " << sonido << "." << endl;

		// Forzamos la salida.
		exit(0);
	}
}

///////////////////////////////////////////
//////////// GETTERS & SETTERS ////////////
///////////////////////////////////////////

// Indica si se debe salir.
bool Juego::getSalir()
{
	return salir;
}

// Establece si se debe salir.
void Juego::setSalir(bool salir)
{
	this->salir = salir;
}

/////////////////////////////////////////
//////////// INICIALIZADORES ////////////
/////////////////////////////////////////

// Inicializa el juego.
void Juego::inicializar()
{
	// Estado inicial en el menú.
	estado = Juego_EstadoMenu::getInstancia();

	// No se desea salir.
	salir = false;
	
	// Inicializamos SDL.
	inicializaSDL();

	// Inicializa el sonido.
	inicializaSonido();

	// Inicializa los puzzles.
	inicializaPuzzles();
}

// Inicializa SDL
void Juego::inicializaSDL()
{
	// Iniciar SDL.
	if (SDL_Init (SDL_INIT_VIDEO & SDL_INIT_AUDIO) < 0)
	{
		printf ("No se pudo iniciar SDL: %s\n", SDL_GetError ());
		exit (1);
	}

	// Establecemos un nombre y un icono para la ventana creada.
	SDL_WM_SetCaption ((char *) "Nine-Key Puzzle", (char *) "Nine-Key Puzzle");

	// Activamos el modo de vídeo.
	SURFscreen = SDL_SetVideoMode (800, 600, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (SURFscreen == NULL)
	{
		printf ("No se puede inicializar el modo gráfico: %s\n", SDL_GetError ());
		exit (1);
	}

	// Cargamos la imagen de fondo.
	SURFfondo = IMG_Load("data/fondo.jpg");
	if (SURFfondo == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen de fondo2.
	SURFfondo2 = IMG_Load("data/fondo2.jpg");
	if (SURFfondo2 == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen de completado.
	SURFcompletado = IMG_Load("data/completado.png");
	if (SURFcompletado == NULL)
	{
		printf("No se pudi cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen del reloj.
	SURFreloj = IMG_Load("data/reloj.jpg");
	if (SURFreloj == NULL)
	{
		printf("No se pudi cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Inicializamos SDL_ttf
	if (TTF_Init() < 0)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	// Texto saliendo.
	FONTfuente = TTF_OpenFont("data/dejavu.ttf",12);
	if (FONTfuente == NULL)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	SURFsaliendo = TTF_RenderText_Blended(FONTfuente, "Saliendo...", color);

	// Repetición de teclas.
	SDL_EnableKeyRepeat(100, 100);

	// Inicializamos los temporizadores.
	iteracionAnterior = SDL_GetTicks();
	temporizadorReloj = SDL_GetTicks();
}

// Inicializa el sonido.
void Juego::inicializaSonido()
{
	// Inicializamos los sonidos.
	sonidos["intercambiar"] = new Sonido("data/intercambiar.wav");
	sonidos["seleccionar"] = new Sonido("data/seleccionar.wav");
	sonidos["menu"] = new Sonido("data/menu.wav");
	sonidos["remover"] = new Sonido("data/remover.wav");
	sonidos["victoria"] = new Sonido("data/victoria.wav");
	sonidos["fondo"] = new Sonido("data/fondo.wav");
}

// Inicializa los puzzles.
void Juego::inicializaPuzzles()
{
	Directorio directorio("puzles");
	list<string> nombreDirectorios = directorio.getNombreDirectorios();
	list<string>::iterator pos = nombreDirectorios.begin();
	while (pos != nombreDirectorios.end())
	{
		string ruta = *pos;
		if(ruta[0] != '.')
		{
			// Añadimos el puzle.
			Puzle* puzle = new Puzle(ruta);
			puzles.push_front(puzle);
		}
		pos++;
	}

	// Número de puzle actual.
	numPuzleActual = 0;

	if(puzles.size() == 0)
	{
		// Mostramos unmensaje de error.
		cout << "<Error> No se ha cargado ningún puzle." << endl;

		// Forzamos la salida.
		exit(0);
	}
}

///////////////////////////////////////
//////////// FINALIZADORES ////////////
///////////////////////////////////////

// Finaliza el juego.
void Juego::finalizar()
{
	// Liberar los puzles.
	finalizaPuzzles();

	// Liberar los sonidos.
	finalizaSonido();

	// Liberar SDL.
	finalizaSDL();
}

// Finaliza SDL.
void Juego::finalizaSDL()
{
	// Liberar la memoria de SDL.
	SDL_Quit();
}

// Finaliza el sonido.
void Juego::finalizaSonido()
{
	// PENDIENTE
}

// Finaliza los puzles.
void Juego::finalizaPuzzles()
{
	// Libera los puzzles.
	list<Puzle*>::iterator pos = puzles.begin();
	while( pos != puzles.end())
	{
		Puzle* puzle = *pos;
		delete puzle;
		pos++;
	}
	puzles.clear();
}

//////////////////////////////////////////////
//////////// FUNCIONES AUXILIARES ////////////
//////////////////////////////////////////////

// Devuelve el tiempo en formato (dd:)(hh:)mm:ss
string Juego::formatoTiempo(Uint32 tiempo)
{
	char msg[30] = "0";
	char cDias[4] = "0";
	char cHoras[3] = "0";
	char cMinutos[3] = "0";
	char cSegundos[3] = "0";

	Uint32 tiempoTranscurrido = tiempo/1000;

	int dias = (tiempoTranscurrido/86400)%365;
	int horas = (tiempoTranscurrido/3600)%24;
	int minutos = (tiempoTranscurrido/60)%60;
	int segundos = tiempoTranscurrido%60;

	if(segundos < 10)
		sprintf(cSegundos, "0%d", segundos);
	else
		sprintf(cSegundos, "%d", segundos);

	if(minutos < 10)
		sprintf(cMinutos, "0%d", minutos);
	else
		sprintf(cMinutos, "%d", minutos);

	if(horas < 10)
		sprintf(cHoras, "0%d", horas);
	else
		sprintf(cHoras, "%d", horas);

	if(dias < 10)
		sprintf(cDias, "0%d", dias);
	else
		sprintf(cDias, "%d", dias);


	if(horas > 0)
	{
		if(dias > 0)
		{
			sprintf(msg, "%s:%s:%s:%s",cDias, cHoras, cMinutos, cSegundos);
		}
		else
		{
			sprintf(msg, "%s:%s:%s", cHoras, cMinutos, cSegundos);

		}
	}
	else
	{
		sprintf(msg, "%s:%s", cMinutos, cSegundos);
	}

	return msg;
}












































void Juego::dibujarProgresoSalir()
{
	// Mostramos el tiempo restante para salir.
	if(temporizadorEscape != 0)
	{
		// Obtenemos el porcentaje completado.
		float tiempoTranscurrido = SDL_GetTicks() - temporizadorEscape;
		float porcentajeCompletado = tiempoTranscurrido/tiempoEscape;

		if(porcentajeCompletado >= 0.1)
		{
			// Variables locales.
			SDL_Rect rectangulo;

			// Fondo.
			rectangulo.h = 20;
			rectangulo.w = 100;
			rectangulo.x = 650;
			rectangulo.y = 15;
			SDL_FillRect (SURFscreen, &rectangulo, SDL_MapRGB (SURFscreen->format, 0, 100, 0));

			// Superficie.
			rectangulo.h = 20;
			rectangulo.w = 100 * porcentajeCompletado;
			rectangulo.x = 650;
			rectangulo.y = 15;
			SDL_FillRect (SURFscreen, &rectangulo, SDL_MapRGB (SURFscreen->format, 255, 0, 0));

			// Texto.
			rectangulo.h = SURFsaliendo->h;
			rectangulo.w = SURFsaliendo->w;
			rectangulo.x = rectangulo.x+20;
			rectangulo.y = rectangulo.y+2;
			SDL_BlitSurface(SURFsaliendo, NULL, SURFscreen, &rectangulo);
		}
	}
}

// Devuelve el mejor tiempo del puzle.
Uint32 Juego::getMejorTiempo(string rutaPuzle)
{
	int leido = false;
	Uint32 mejorTiempo = 0;

	#ifdef WIN32

	WIN32_FIND_DATA findFileData;
	HANDLE hFind;

	string rutaPuzleAux = rutaPuzle + "/*";
	hFind = FindFirstFile(rutaPuzleAux.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			string nombre = string(findFileData.cFileName);
			if(nombre == "estatisticas.txt")
			{
				leido = true;
				ifstream fichero;
				string ruta = rutaPuzle + "/" + nombre;
				fichero.open(ruta.c_str(), ios::in);
				if (fichero.is_open())
				{
					try
					{
						fichero >> mejorTiempo;
					}
					catch(...)
					{
						// El fichero no se puede leer.
					}
					fichero.close();
				}
				else
				{
					// El fichero no se puede leer.
				}
			}
		}
		while (FindNextFile(hFind, &findFileData) != 0 && leido == false);
	}

	#else

	DIR* dp = NULL;
	struct dirent* dirp = NULL;
	// Abrimos el directorio.
    if ((dp  = opendir(rutaPuzle.c_str())) != NULL)
    {
		// Leemos todas las entradas.
		while ((dirp = readdir(dp)) != NULL && leido == false)
		{
			string nombre = string(dirp->d_name);
			if(nombre=="estadisticas.txt")
			{
				leido = true;
				ifstream fichero;
				string ruta = rutaPuzle + "/" + nombre;
				fichero.open(ruta.c_str(), ios::in);

				if (fichero.is_open())
				{
					// Si podemos leer, es un fichero. Si no, es un directorio.
					try
					{
						fichero >> mejorTiempo;
					}
					catch(...)
					{
						// El fichero no se puede leer.
					}
					fichero.close();
				}
			}
		}

		// Cerramos el directorio.
		closedir(dp);
	}

	#endif

	return mejorTiempo;
}

// Devuelve los mejores movimientos del puzle.
int Juego::getMejorMovimiento(string rutaPuzle)
{
	int leido = false;
	int mejorMovimiento = 0;

	#ifdef WIN32

	WIN32_FIND_DATA findFileData;
	HANDLE hFind;

	string rutaPuzleAux = rutaPuzle + "/*";
	hFind = FindFirstFile(rutaPuzleAux.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			string nombre = string(findFileData.cFileName);
			if(nombre == "estatisticas.txt")
			{
				leido = true;
				ifstream fichero;
				string ruta = rutaPuzle + "/" + nombre;
				fichero.open(ruta.c_str(), ios::in);
				if (fichero.is_open())
				{
					try
					{
						fichero >> mejorMovimiento;
						fichero >> mejorMovimiento;
					}
					catch(...)
					{
						// El fichero no se puede leer.
					}
					fichero.close();
				}
				else
				{
					// El fichero no se puede leer.
				}
			}
		}
		while (FindNextFile(hFind, &findFileData) != 0 && leido == false);
	}

	#else

	DIR* dp = NULL;
	struct dirent* dirp = NULL;
	// Abrimos el directorio.
    if ((dp  = opendir(rutaPuzle.c_str())) != NULL)
    {
		// Leemos todas las entradas.
		while ((dirp = readdir(dp)) != NULL && leido == false)
		{
			string nombre = string(dirp->d_name);
			if(nombre=="estadisticas.txt")
			{
				leido = true;
				ifstream fichero;
				string ruta = rutaPuzle + "/" + nombre;
				fichero.open(ruta.c_str(), ios::in);

				if (fichero.is_open())
				{
					// Si podemos leer, es un fichero. Si no, es un directorio.
					try
					{
						fichero >> mejorMovimiento;
						fichero >> mejorMovimiento;
					}
					catch(...)
					{
						// El fichero no se puede leer.
					}
					fichero.close();
				}
			}
		}

		// Cerramos el directorio.
		closedir(dp);
	}

	#endif

	return mejorMovimiento;
}

void Juego::cargarPuzle(int tamano)
{
	// Seleccionamos el puzle actual.
	list<Puzle*>::iterator pos = puzles.begin();
	int explorandoPosicion = 0;
	bool encontrado = false;
	while( pos != puzles.end() && encontrado == false)
	{
		if(explorandoPosicion == numPuzleActual)
		{
			puzleActual = *pos;
			encontrado = true;
		}
		pos++;
		explorandoPosicion++;
	}

	if(encontrado == true)
	{
		// Dificultad facil.
		puzleActual->setTamano(tamano);

		// Removemos el puzle.
		puzleActual->remover();

		// Pasamos a jugar.
		setEstado(Juego_EstadoJugando::getInstancia());

		// Reproducimos el sonido.
		reproducirSonido("remover");

		// Obtenemos el mejor tiempo del puzle.
		mejorTiempo = getMejorTiempo("puzles/"+puzleActual->getRuta());

		// Obtenemos la mejor cantidad de movimientos del puzle.


		// Iniciamos el contador de tiempo.
		temporizadorJuego = SDL_GetTicks();

		// Reiniciamos los movimientos.
		contadorMovimientos = 0;
	}
	else
	{
		cout << "<Error>Juego::cargarPuzle - Puzle no encontrado.";
		salir = true;
	}
}

// Establece el valor del mejor tiempo.
void Juego::setMejorTiempo(string ruta, Uint32 mejorTiempo)
{

}

// Establece el valor del mejor movimiento.
void Juego::setMejorMovimiento(string ruta, int mejorMovimiento)
{

}




