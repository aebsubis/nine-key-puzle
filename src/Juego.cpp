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

// Establece como puzzle actual el puzzle anterior.
void Juego::puzzleAnterior()
{
	if(numPuzzleActual == 0)
		numPuzzleActual = puzzles.size()-1;
	else
		numPuzzleActual--;

	// Añadimos el delay de 140.
	delay = 140;

	// Reproducimos el sonido.
	reproducirSonido("menu");
}

// Establece como puzzle actual el puzzle siguiente.
void Juego::puzzleSiguiente()
{
	// Elegimos el puzzle de arriba.
	if((unsigned)numPuzzleActual == puzzles.size()-1)
		numPuzzleActual = 0;
	else
		numPuzzleActual++;

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

	// Fuente del texto.
	FONTfuente = NULL;

	// Iniciamos el temporizador.
	temporizadorEscape = 0;
	iteracionAnterior = 0;
	temporizadorReloj = 0;

	// Tiempo transcurrido.
	contadorTiempo = 0;

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

void Juego::cargarPuzzle(int tamano)
{
	// Seleccionamos el puzzle actual.
	list<Puzzle*>::iterator pos = puzzles.begin();
	int explorandoPosicion = 0;
	bool encontrado = false;
	while( pos != puzzles.end() && encontrado == false)
	{
		if(explorandoPosicion == numPuzzleActual)
		{
			puzzleActual = *pos;
			encontrado = true;
		}
		pos++;
		explorandoPosicion++;
	}

	if(encontrado == true)
	{
		// Dificultad facil.
		puzzleActual->setTamano(tamano);

		// Removemos el puzzle.
		puzzleActual->remover();

		// Pasamos a jugar.
		setEstado(Juego_EstadoJugando::getInstancia());

		// Reproducimos el sonido.
		reproducirSonido("remover");

		// Iniciamos el contador de tiempo.
		contadorTiempo = SDL_GetTicks();

		// Reiniciamos los movimientos.
		contadorMovimientos = 0;
	}
	else
	{
		cout << "<Error>Juego::cargarPuzzle - Puzzle no encontrado.";
		salir = true;
	}
}

///////////////////////////////////////////
//////////// GETTERS & SETTERS ////////////
///////////////////////////////////////////

// Indica si se debe salir.
bool Juego::getSalir() const
{
	return salir;
}

// Establece si se debe salir.
void Juego::setSalir(bool salir)
{
	this->salir = salir;
}

// Devuelve la superficie.
SDL_Surface* Juego::getSuperficie(string nombre)
{
	return superficies[nombre];
}

// Establece la superficie.
void Juego::setSuperficie(string nombre, SDL_Surface* superficie)
{
	SDL_Surface* sup = superficies[nombre];
	if(sup != NULL)
		SDL_FreeSurface(sup);

	superficies[nombre] = superficie;
}

// Devuelve la fuente.
TTF_Font* Juego::getFuente() const
{
	return FONTfuente;
}

// Establece la fuente.
void Juego::setFuente(TTF_Font* fuente)
{
	this->FONTfuente = fuente;
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

	// Inicializamos las superficies.
	superficies["screen"] = NULL;
	superficies["fondoMenu"] = NULL;
	superficies["fondoJuego"] = NULL;
	superficies["saliendo"] = NULL;
	superficies["completado"] = NULL;
	superficies["reloj"] = NULL;
	
	// Activamos el modo de vídeo.
	superficies["screen"] = SDL_SetVideoMode (800, 600, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (superficies["screen"] == NULL)
	{
		printf ("No se puede inicializar el modo gráfico: %s\n", SDL_GetError ());
		exit (1);
	}

	// Cargamos la imagen de fondo.
	superficies["fondoMenu"] = IMG_Load("data/fondo.jpg");
	if (superficies["fondoMenu"] == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen de fondo2.
	superficies["fondoJuego"] = IMG_Load("data/fondo2.jpg");
	if (superficies["fondoJuego"] == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen de completado.
	superficies["completado"] = IMG_Load("data/completado.png");
	if (superficies["completado"] == NULL)
	{
		printf("No se pudi cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}

	// Cargamos la imagen del reloj.
	superficies["reloj"] = IMG_Load("data/reloj.jpg");
	if (superficies["reloj"] == NULL)
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
	superficies["saliendo"] = TTF_RenderText_Blended(FONTfuente, "Saliendo...", color);

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
	Directorio directorio("puzzles");
	list<string> nombreDirectorios = directorio.getNombreDirectorios();
	list<string>::iterator pos = nombreDirectorios.begin();
	while (pos != nombreDirectorios.end())
	{
		string ruta = *pos;
		if(ruta[0] != '.')
		{
			// Añadimos el puzzle.
			Puzzle* puzzle = new Puzzle(ruta);
			puzzles.push_front(puzzle);
		}
		pos++;
	}

	// Número de puzzle actual.
	numPuzzleActual = 0;

	if(puzzles.size() == 0)
	{
		// Mostramos unmensaje de error.
		cout << "<Error>Juego::inicializaPuzzles - No se ha cargado ningún puzzle." << endl;

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
	// Liberar los puzzles.
	finalizaPuzzles();

	// Liberar los sonidos.
	finalizaSonido();

	// Liberar SDL.
	finalizaSDL();
}

// Finaliza SDL.
void Juego::finalizaSDL()
{
	// Liberamos las superficies.
	superficies.clear();

	// Liberar la memoria de SDL.
	SDL_Quit();
}

// Finaliza el sonido.
void Juego::finalizaSonido()
{
	// Liberamos los sonidos.
	sonidos.clear();
}

// Finaliza los puzzles.
void Juego::finalizaPuzzles()
{
	// Libera los puzzles.
	list<Puzzle*>::iterator pos = puzzles.begin();
	while( pos != puzzles.end())
	{
		Puzzle* puzzle = *pos;
		delete puzzle;
		pos++;
	}
	puzzles.clear();
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

// Dibuja la barra de progreso para salir.
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
			SDL_FillRect (superficies["screen"], &rectangulo, SDL_MapRGB (superficies["screen"]->format, 0, 100, 0));

			// Superficie.
			rectangulo.h = 20;
			rectangulo.w = 100 * porcentajeCompletado;
			rectangulo.x = 650;
			rectangulo.y = 15;
			SDL_FillRect (superficies["screen"], &rectangulo, SDL_MapRGB (superficies["screen"]->format, 255, 0, 0));

			// Texto.
			rectangulo.h = superficies["saliendo"]->h;
			rectangulo.w = superficies["saliendo"]->w;
			rectangulo.x = rectangulo.x+20;
			rectangulo.y = rectangulo.y+2;
			SDL_BlitSurface(superficies["saliendo"], NULL, superficies["screen"], &rectangulo);
		}
	}
}
