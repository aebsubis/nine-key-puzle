#include <list>
#include <SDL/SDL_video.h>
#include <SDL/SDL_events.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Juego.h"
#include "Directorio.h"

// Constructor por defecto.
Juego::Juego()
{
	// Estado inicial.
	estado = 0;

	// No se desea salir.
	salir = false;

	// Cargamos todos los puzles.
	cargarPuzles();

	// Primer puzle.
	puzleActual = 0;

	// Variables de SDL.
	SURFscreen = NULL;
	//SURFtexto = NULL;
	SURFfondo = NULL;
	//FONTfuente = NULL;

	// Iniciamos el temporizador.
	temporizador = 0;
}

// Destructor.
Juego::~Juego()
{
	// Liberar la memoria.
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
	SDL_WM_SetCaption ((char *) "ME Puzle", (char *) "ME Puzle");

	// Activamos el modo de vídeo.
	SURFscreen = SDL_SetVideoMode (800, 600, 24, SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (SURFscreen == NULL)
	{
		printf ("No se puede inicializar el modo gráfico: %s\n", SDL_GetError ());
		exit (1);
	}

	// Cargamos la imagen de fondo.
	SURFfondo = SDL_LoadBMP("data/fondo.bmp");
	if (SURFfondo == NULL)
	{
		printf("No pude cargar gráfico: %s\n", SDL_GetError());
		exit(1);
	}
	
	// Inicializamos SDL_ttf
	if (TTF_Init() < 0)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	// Cargamos el tipo de fuente.
	FONTfuente = TTF_OpenFont("data/dejavu.ttf",12);
	if (FONTfuente == NULL)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	// Cargamos los sonidos.
	intercambiar.cargar("data/intercambiar.wav");
	seleccionar.cargar("data/seleccionar.wav");
	menu.cargar("data/menu.wav");

	// Repetición de teclas.
	SDL_EnableKeyRepeat(100, 100);

	//Inicializamos los timers
	//frameAnterior = SDL_GetTicks();
	//iteracionAnterior = SDL_GetTicks();
}

// Inicia el juego.
void Juego::iniciar()
{
	// Inicializamos SDL.
	inicializaSDL();

	while(salir==false)
	{
		switch(estado)
		{
			case 0:
			{
				// Procesamos los eventos del menú.
				eventosMenu();

				// Actualizamos el menu.
				actualizarMenu();

				// Hacemos un render.
				renderMenu();
			}
			break;
			case 1:
			{
				// Procesamos los eventos del juego.
				eventosJuego();

				// Actualizamos el juego.
				actualizarJuego();

				// Hacemos un render.
				renderJuego();
			}
			break;
			default:
			{
				cout << "<Error>Juego:iniciar - Estado inválido";
				salir = true;
			}
		}
		
	}
}

// Procesa los eventos del menú.
void Juego::eventosMenu()
{
	SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_KP1)
			{
				// Pulsada tecla 1.

			}
			else if (event.key.keysym.sym == SDLK_KP2)
			{
				// Elegimos el puzle de abajo.
				if(puzleActual == 0)
					puzleActual = puzles.size()-1;
				else
					puzleActual--;

				// Reproducimos el sonido.
				menu.reproducir();

			}
			else if (event.key.keysym.sym == SDLK_KP3)
			{
				// Pulsada tecla 3.

			}
			else if (event.key.keysym.sym == SDLK_KP4)
			{
				// Pulsada tecla 4.

			}
			else if (event.key.keysym.sym == SDLK_KP5)
			{
				// Seleccionamos el puzle actual y pasamos a jugar.
				estado = 1;

				// Reproducimos el sonido.
				seleccionar.reproducir();

			}
			else if (event.key.keysym.sym == SDLK_KP6)
			{
				// Pulsada tecla 6.

			}
			else if (event.key.keysym.sym == SDLK_KP7)
			{
				// Pulsada tecla 7.

			}
			else if (event.key.keysym.sym == SDLK_KP8)
			{
				// Elegimos el puzle de arriba.
				if((unsigned)puzleActual == puzles.size()-1)
					puzleActual = 0;
				else
					puzleActual++;

				// Reproducimos el sonido.
				menu.reproducir();

			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Pulsada tecla 9.

				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(temporizador == 0)
					temporizador = SDL_GetTicks();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP9)
			{
				// Soltada tecla 9.

				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				temporizador = 0;
			}

		}
		else if (event.type == SDL_QUIT)
		{
			salir = true;
		}
	}
}

// Actualiza el menú.
void Juego::actualizarMenu()
{
	// Comprobamos si la tecla de forzar salida lleva pulsada suficiente tiempo
	if(temporizador != 0)
	{
		if(SDL_GetTicks() - temporizador > 4000)
			salir = true;

	}
}

// Hace un render del menú.
void Juego::renderMenu()
{
	// Limpiar pantalla
	SDL_FillRect(SURFscreen, 0, SDL_MapRGB(SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(SURFfondo, NULL, SURFscreen, NULL);

	// Dibujamos el listado de puzles.
	list<Puzle>::iterator pos;
	pos = puzles.begin();
	int explorandoPosicion = 0;
	while( pos != puzles.end())
	{
		Puzle activo = *pos;

		// Calculamos la posición que toca.
		SDL_Rect posicion;
		posicion.x = 50;
		posicion.y = 250 - 150*(explorandoPosicion - puzleActual);

		// Obtenemos la ruta del puzle.
		string rutaImagen = "puzles/"+activo.getRuta()+"/pequeno.bmp";

		// Cargamos la miniatura.
		SDL_Surface *miniatura = SDL_LoadBMP(rutaImagen.c_str());
		if (miniatura == NULL)
		{
			printf("No pude cargar gráfico: %s\n", SDL_GetError());
			exit(1);
		} ;

		// Dibujamos la miniatura.
		SDL_BlitSurface(miniatura, NULL, SURFscreen, &posicion);

		if(explorandoPosicion == puzleActual)
		{
			// También lo dibujamos en grande.
			posicion.x = 250;
			posicion.y = 50;
		
			// Obtenemos la ruta del puzle.
			string rutaImagen = "puzles/"+activo.getRuta()+"/grande.bmp";

			// Cargamos la miniatura.
			SDL_Surface *imagen = SDL_LoadBMP(rutaImagen.c_str());
			if (imagen == NULL)
			{
				printf("No pude cargar gráfico: %s\n", SDL_GetError());
				exit(1);
			} ;
			// Dibujamos la imagen.
			SDL_BlitSurface(imagen, NULL, SURFscreen, &posicion);
		}

		explorandoPosicion++;
		pos++;
	}

	


	// Refrescamos la pantalla.
	SDL_Flip (SURFscreen);
}

// Procesa los eventos del juego.
void Juego::eventosJuego()
{
SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_KP1)
			{
				// Pulsada tecla 1.

			}
			else if (event.key.keysym.sym == SDLK_KP2)
			{
				// Pulsada tecla 2.

			}
			else if (event.key.keysym.sym == SDLK_KP3)
			{
				// Pulsada tecla 3.

			}
			else if (event.key.keysym.sym == SDLK_KP4)
			{
				// Pulsada tecla 4.

			}
			else if (event.key.keysym.sym == SDLK_KP5)
			{
				// Pulsada tecla 5.

			}
			else if (event.key.keysym.sym == SDLK_KP6)
			{
				// Pulsada tecla 6.

			}
			else if (event.key.keysym.sym == SDLK_KP7)
			{
				// Pulsada tecla 7.

			}
			else if (event.key.keysym.sym == SDLK_KP8)
			{
				// Pulsada tecla 8.

			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Pulsada tecla 9.

				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				temporizador = SDL_GetTicks();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP9)
			{
				// Soltada tecla 9.

				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				temporizador = 0;
			}

		}
		else if (event.type == SDL_QUIT)
		{
			salir = true;
		}
	}
}

// Actualiza el juego.
void Juego::actualizarJuego()
{

}

// Hace un render del juego.
void Juego::renderJuego()
{
	// Limpiar pantalla
	SDL_FillRect(SURFscreen, 0, SDL_MapRGB(SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(SURFfondo, NULL, SURFscreen, NULL);

	// Dibujamos el puzle actual.
	

	// Refrescamos la pantalla.
	SDL_Flip (SURFscreen);
}


// Carga los puzles.
void Juego::cargarPuzles()
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
			Puzle puzle(ruta);
			puzles.push_front(puzle);
			
		}
		pos++;
	}
}
