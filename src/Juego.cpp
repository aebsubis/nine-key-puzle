#include <sstream>
#include <SDL/SDL_video.h>
#include "Juego.h"

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
	numPuzleActual = 0;

	// Variables de SDL.
	SURFscreen = NULL;
	SURFfondo = NULL;
	SURFsaliendo = NULL;
	SURFcompletado = NULL;
	SURFtranslucida = NULL;

	// Iniciamos el temporizador.
	temporizadorEscape = 0;
	iteracionAnterior = 0;
	
	// Tiempo de escape.
	tiempoEscape = 3000;

	// Tiempo de delay.
	delay = 0;

	// Selecciones a 0.
	fichaSeleccionada1 = 0;
	fichaSeleccionada2 = 0;
}

// Destructor.
Juego::~Juego()
{
	// Liberar los puzles.
	list<Puzle*>::iterator pos = puzles.begin();
	while( pos != puzles.end())
	{
		Puzle* puzle = *pos;
		delete puzle;
		pos++;
	}
	puzles.clear();

	// Liberar la memoria de SDL.
	SDL_Quit();
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

	// Creamos la superficie translúcida.
	SURFtranslucida = IMG_Load("data/translucida.png");
	if (SURFtranslucida == NULL)
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
	
	TTF_Font* FONTfuente = NULL;
	SDL_Color color;

	// Texto saliendo.
	FONTfuente = TTF_OpenFont("data/dejavu.ttf",12);
	if (FONTfuente == NULL)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	color.r = 0;
	color.g = 0;
	color.b = 0;
	SURFsaliendo = TTF_RenderText_Blended(FONTfuente, "Saliendo...", color);

	// Texto completado.
	FONTfuente = TTF_OpenFont("data/dejavu.ttf",80);
	if (FONTfuente == NULL)
	{
		printf("No se pudo iniciar SDL_ttf: %s\n",SDL_GetError());
		exit(1);
	}

	color.r = 0;
	color.g = 155;
	color.b = 0;
	SURFcompletado = TTF_RenderText_Blended(FONTfuente, "COMPLETADO", color);


	// Cargamos los sonidos.
	sIntercambiar.cargar("data/intercambiar.wav");
	sSeleccionar.cargar("data/seleccionar.wav");
	sMenu.cargar("data/menu.wav");
	sRemover.cargar("data/remover.wav");
	sVictoria.cargar("data/victoria.wav");
	sFondo.cargar("data/fondo.wav");

	// Repetición de teclas.
	SDL_EnableKeyRepeat(100, 100);	
}

// Inicia el juego.
void Juego::iniciar()
{
	// Inicializamos SDL.
	inicializaSDL();

	while(salir==false)
	{
		// Reiniciamos el iterador.
		iteracionAnterior = SDL_GetTicks();
		
		// Bucle del sonido de fondo.
		if(sFondo.reproduciendose() == false)
			sFondo.reproducir();

		switch(estado)
		{
			case 0:
			{
				while (SDL_GetTicks() - iteracionAnterior < 100)
				{
					// Procesamos los eventos del menú.
					eventosMenu();

					// Actualizamos el menu.
					actualizarMenu();

					// Hacemos un render.
					renderMenu();
				}
			}
			break;
			case 1:
			{
				while (SDL_GetTicks() - iteracionAnterior < 100)
				{
					// Procesamos los eventos del juego.
					eventosJuego();

					// Actualizamos el juego.
					actualizarJuego();

					// Hacemos un render.
					renderJuego();
				}
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
				if(numPuzleActual == 0)
					numPuzleActual = puzles.size()-1;
				else
					numPuzleActual--;

				// Añadimos el delay de 140.
				delay = 140;
				
				// Reproducimos el sonido.
				sMenu.reproducir();

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
				// Elegimos el puzle de arriba.
				if((unsigned)numPuzleActual == puzles.size()-1)
					numPuzleActual = 0;
				else
					numPuzleActual++;

				// Añadimos el delay de -140.
				delay = -140;

				// Reproducimos el sonido.
				sMenu.reproducir();

			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Pulsada tecla 9.

				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(temporizadorEscape == 0)
					temporizadorEscape = SDL_GetTicks();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP5)
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
					// Removemos el puzle.
					puzleActual->remover();

					// Pasamos a jugar.
					estado = 1;

					// Reproducimos el sonido.
					sRemover.reproducir();
				}
				else
				{
					cout << "<Error>Juego:eventosMenu - Juego no encontrado.";
					salir = true;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Soltada tecla 9.

				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				temporizadorEscape = 0;
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
	if(temporizadorEscape != 0)
	{
		if(SDL_GetTicks() - temporizadorEscape > (unsigned)tiempoEscape)
		{
			temporizadorEscape = 0;
			salir = true;
		}
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
	if(puzles.size() > 0)
	{
		// Iterador de la lista.
		list<Puzle*>::iterator pos;

		// Almacena la posición del puzle que estamos explorando en la lista.
		int explorandoPosicion;

		// Almacena la posición de la miniatura inicial.
		int miniaturaInicial;

		// Almacena el número de la miniatura que se está dibujando.
		int numMiniatura;

		// Buscamos la posición de la miniatura inicial.
		miniaturaInicial = numPuzleActual-3;
		while(miniaturaInicial<0)
		{
			miniaturaInicial = puzles.size() + miniaturaInicial;
		}

		// Nos desplazamos hasta la miniatura inicial.
		pos = puzles.begin();
		explorandoPosicion = 0;
		bool encontrado = false;
		while( encontrado == false)
		{
			if(explorandoPosicion == miniaturaInicial)
			{
				encontrado = true;
			}
			else
			{
				explorandoPosicion++;
				pos++;
			}
		}

		// Dibujamos las 7 miniaturas del menú
		numMiniatura = -3;
		while( numMiniatura <= 3 )
		{
			// Obtenemos el puzzle de la lista que estamos explorando.
			Puzle* activo = *pos;

			// Calculamos la posición de la miniatura.
			SDL_Rect posicion;
			
			if(numMiniatura>0)
			{
 				posicion.x = 50 + 35*abs(numMiniatura) - delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, SURFscreen, &posicion);
			}
			else if(numMiniatura < 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, SURFscreen, &posicion);
			}
			else if(numMiniatura == 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + abs((int)(delay*0.25));
				posicion.y = 250 - 150*(numMiniatura) + delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, SURFscreen, &posicion);

				// También lo dibujamos en grande.
				posicion.x = 250;
				posicion.y = 50;

				// Dibujamos la imagen.
				SDL_BlitSurface(activo->getGrande(), NULL, SURFscreen, &posicion);
			}

			numMiniatura++;
			explorandoPosicion++;
			pos++;

			// Si hemos completado la lista, empezamos de 0.
			if(pos==puzles.end())
			{
				explorandoPosicion = 0;
				pos=puzles.begin();
			}
		}
	
	}

	// Decrementamos el delay hasta 0.
	if(delay>0)
		delay = delay - 10;
	if(delay<0)
		delay = delay + 10;

	// Dibujamos el progreso de salir.
	dibujarProgresoSalir();

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
			if (event.key.keysym.sym == SDLK_KP9)
			{
				// Pulsada tecla 9.

				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(temporizadorEscape == 0)
					temporizadorEscape = SDL_GetTicks();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP1)
			{
				// Soltada tecla 1.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 1;
				}
				else
				{
					fichaSeleccionada2 = 1;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP2)
			{
				// Soltada tecla 2.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 2;
				}
				else
				{
					fichaSeleccionada2 = 2;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP3)
			{
				// Soltada tecla 3.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 3;
				}
				else
				{
					fichaSeleccionada2 = 3;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP4)
			{
				// Soltada tecla 4.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 4;
				}
				else
				{
					fichaSeleccionada2 = 4;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP5)
			{
				// Soltada tecla 5.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 5;
				}
				else
				{
					fichaSeleccionada2 = 5;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP6)
			{
				// Soltada tecla 6.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 6;
				}
				else
				{
					fichaSeleccionada2 = 6;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP7)
			{
				// Soltada tecla 7.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 7;
				}
				else
				{
					fichaSeleccionada2 = 7;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			else if (event.key.keysym.sym == SDLK_KP8)
			{
				// Soltada tecla 8.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 8;
				}
				else
				{
					fichaSeleccionada2 = 8;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

			}
			if (event.key.keysym.sym == SDLK_KP9)
			{
				// Soltada tecla 9.
				if(fichaSeleccionada1 == 0)
				{
					fichaSeleccionada1 = 9;
				}
				else
				{
					fichaSeleccionada2 = 9;
					intercambiar(fichaSeleccionada1, fichaSeleccionada2);
				}

				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				temporizadorEscape = 0;
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
	// Comprobamos si la tecla de forzar salida lleva pulsada suficiente tiempo
	if(temporizadorEscape != 0)
	{
		if(SDL_GetTicks() - temporizadorEscape > (unsigned)tiempoEscape)
		{
			temporizadorEscape = 0;
			estado = 0;
		}
	}

	// Comprobamos si el puzle está solucionado.
	if(puzleActual->solucionado() == true)
	{
		// Reproducimos el sonido de victoria.
		sVictoria.reproducir();

		// Hacemos un render con el texto de la victoria.
		renderJuego();

		// Detenemos el juego durante un tiempo.
		iteracionAnterior = SDL_GetTicks();

		// Detenemos la partida 100 ms.
		while (SDL_GetTicks() - iteracionAnterior < 3000){  }

		// Volvemos al menú.
		estado = 0;
	}
}

// Hace un render del juego.
void Juego::renderJuego()
{
	// Limpiar pantalla
	SDL_FillRect(SURFscreen, 0, SDL_MapRGB(SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(SURFfondo, NULL, SURFscreen, NULL);

	// Dibujamos el puzle actual.
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{

			// Calculamos la posición de la pieza.
			SDL_Rect posicion;
			posicion.x = 200 + 200*j;
			posicion.y = 200*i;

			// Dibujamos la pieza.
			SDL_BlitSurface(puzleActual->getPieza(puzleActual->estado[i][j]), NULL, SURFscreen, &posicion);

		}
	}

	// Dibujamos la superficie translúcida si la ficha1 ha sido seleccionada.
	if(fichaSeleccionada1 != 0)
	{
		int contador = 1;
		bool dibujado = false;
		for(int i=2; i>=0 && dibujado == false; i--)
		{
			for(int j=0; j<3 && dibujado == false; j++)
			{
				if(contador == fichaSeleccionada1)
				{
					SDL_Rect posicion;
					posicion.x = 200 + 200*j;
					posicion.y = 200*i;
					SDL_BlitSurface(SURFtranslucida, NULL, SURFscreen, &posicion);
					dibujado = true;
				}
				contador++;
			}
		}
	}

	// Dibujamos el progreso de salir.
	dibujarProgresoSalir();

	// Comprobamos si el puzle está solucionado.
	if(puzleActual->solucionado() == true)
	{
		// Mostramos el texto "Puzle resuelto".

		SDL_Rect rectangulo;
		rectangulo.h = SURFcompletado->h;
		rectangulo.w = SURFcompletado->w;
		rectangulo.x = 210;
		rectangulo.y = 250;
		SDL_BlitSurface(SURFcompletado, NULL, SURFscreen, &rectangulo);
	}
	
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
			Puzle* puzle = new Puzle(ruta);
			puzles.push_front(puzle);
			
		}
		pos++;
	}
}

// Intercambia dos fichas.
void Juego::intercambiar(int posicionInicio, int posicionDestino)
{
	int contador = 1;
	int piezaInicio = 0;
	int piezaDestino = 0;
	for(int i=2; i>=0; i--)
	{
		for(int j=0; j<3; j++)
		{
			if(contador == posicionInicio)
				piezaInicio = puzleActual->estado[i][j];

			if(contador == posicionDestino)
				piezaDestino = puzleActual->estado[i][j];
			contador++;
		}
	}

	contador = 1;
	for(int i=2; i>=0; i--)
	{
		for(int j=0; j<3; j++)
		{
			if(contador == posicionInicio)
				puzleActual->estado[i][j] = piezaDestino;

			if(contador == posicionDestino)
				puzleActual->estado[i][j] = piezaInicio;
			contador++;
		}
	}

	// Reproducimos el sonido de intercambiar fichas.
	sIntercambiar.reproducir();

	// Reiniciamos las fichas seleccionadas.
	fichaSeleccionada1 = 0;
	fichaSeleccionada2 = 0;
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
