#include <sstream>
#include <SDL/SDL_video.h>
#include <SDL/SDL_keysym.h>
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
	SURFfondo2 = NULL;
	SURFsaliendo = NULL;
	SURFcompletado = NULL;
	SURFreloj = NULL;
	SURFtiempo = NULL;
	SURFmovimientos = NULL;
	FONTfuente = NULL;

	// Iniciamos el temporizador.
	temporizadorEscape = 0;
	iteracionAnterior = 0;
	temporizadorReloj = 0;
	temporizadorJuego = 0;

	// Movimientos realizados.
	contadorMovimientos = 0;

	// Frame inicial.
	frameAnimacionReloj = 0;
	
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

	// Cargamos los sonidos.
	sIntercambiar.cargar("data/intercambiar.wav");
	sSeleccionar.cargar("data/seleccionar.wav");
	sMenu.cargar("data/menu.wav"); // Cambiar.
	sRemover.cargar("data/remover.wav");
	sVictoria.cargar("data/victoria.wav");
	sFondo.cargar("data/fondo.wav");

	// Repetición de teclas.
	SDL_EnableKeyRepeat(100, 100);

	// Inicializamos los temporizadores.
	iteracionAnterior = SDL_GetTicks();
	temporizadorReloj = SDL_GetTicks();
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
			else if (event.key.keysym.sym == SDLK_KP2 || event.key.keysym.sym == SDLK_DOWN)
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
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
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
			else if (event.key.keysym.sym == SDLK_KP9 || event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Pulsada tecla 9.

				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(temporizadorEscape == 0)
					temporizadorEscape = SDL_GetTicks();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_RIGHT)
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
					puzleActual->setTamano(3);

					// Removemos el puzle.
					puzleActual->remover();

					// Pasamos a jugar.
					estado = 1;

					// Reproducimos el sonido.
					sRemover.reproducir();

					// Iniciamos el contador de tiempo.
					temporizadorJuego = SDL_GetTicks();

					// Reiniciamos los movimientos.
					contadorMovimientos = 0;
				}
				else
				{
					cout << "<Error>Juego:eventosMenu - Juego no encontrado.";
					salir = true;
				}
			}
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
					// Dificultad media.
					puzleActual->setTamano(4);

					// Removemos el puzle.
					puzleActual->remover();

					// Pasamos a jugar.
					estado = 1;

					// Reproducimos el sonido.
					sRemover.reproducir();

					// Iniciamos el contador de tiempo.
					temporizadorJuego = SDL_GetTicks();

					// Reiniciamos los movimientos.
					contadorMovimientos = 0;
				}
				else
				{
					cout << "<Error>Juego:eventosMenu - Juego no encontrado.";
					salir = true;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP6)
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
					// Dificultad dificil.
					puzleActual->setTamano(5);

					// Removemos el puzle.
					puzleActual->remover();

					// Pasamos a jugar.
					estado = 1;

					// Reproducimos el sonido.
					sRemover.reproducir();

					// Iniciamos el contador de tiempo.
					temporizadorJuego = SDL_GetTicks();

					// Reiniciamos los movimientos.
					contadorMovimientos = 0;
				}
				else
				{
					cout << "<Error>Juego:eventosMenu - Juego no encontrado.";
					salir = true;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP9 || event.key.keysym.sym == SDLK_ESCAPE)
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
			if (event.key.keysym.sym == SDLK_KP9 || event.key.keysym.sym == SDLK_ESCAPE)
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

			}
			else if (event.key.keysym.sym == SDLK_KP2 || event.key.keysym.sym == SDLK_DOWN)
			{
				// Soltada tecla 2.
				if(puzleActual->mover("abajo"))
				{
					// Reproducimos el sonido.
					sIntercambiar.reproducir();

					// Incrementamos los movimientos.
					contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP3)
			{
				// Soltada tecla 3.

			}
			else if (event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_LEFT)
			{
				// Soltada tecla 4.
				if(puzleActual->mover("izquierda"))
				{
					// Reproducimos el sonido.
					sIntercambiar.reproducir();

					// Incrementamos los movimientos.
					contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP5)
			{
				// Soltada tecla 5.

			}
			else if (event.key.keysym.sym == SDLK_KP6 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Soltada tecla 6.
				if(puzleActual->mover("derecha"))
				{
					// Reproducimos el sonido.
					sIntercambiar.reproducir();

					// Incrementamos los movimientos.
					contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP7)
			{
				// Soltada tecla 7.

			}
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
			{
				// Soltada tecla 8.
				if(puzleActual->mover("arriba"))
				{
					// Reproducimos el sonido.
					sIntercambiar.reproducir();

					// Incrementamos los movimientos.
					contadorMovimientos++;
				}
			}
			if (event.key.keysym.sym == SDLK_KP9 || event.key.keysym.sym == SDLK_ESCAPE)
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

	// Actualizamos el frame del reloj.
	if(SDL_GetTicks() - temporizadorReloj > 400)
	{
		// Actualizamos el temporizador.
		temporizadorReloj = SDL_GetTicks();

		// Incrementamos el frame.
		frameAnimacionReloj++;

		// Comprobamos si se ha pasado.
		if(frameAnimacionReloj>3)
			frameAnimacionReloj = 0;
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
	// Rectángulo de posición.
	SDL_Rect posicion;

	// Rectángulo de corte.
	SDL_Rect corte;
	
	// Limpiar pantalla
	SDL_FillRect(SURFscreen, 0, SDL_MapRGB(SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(SURFfondo2, NULL, SURFscreen, NULL);

	// Comprobamos si está solucionado.
	bool solucionado = puzleActual->solucionado();

	// Dibujamos el reloj.
	corte.w = 50;
	corte.h = 50;
	corte.x = 50*frameAnimacionReloj;
	corte.y = 0;
	posicion.x = 18;
	posicion.y = 45;
	SDL_BlitSurface(SURFreloj, &corte, SURFscreen, &posicion);

	// Dibujamos las estadísticas.
	char msg[100] = "0";
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	Uint32 tiempoTranscurrido = (SDL_GetTicks() - temporizadorJuego)/1000;
	int horas = tiempoTranscurrido/3600;
	int minutos = (tiempoTranscurrido/60)%60;
	int segundos = tiempoTranscurrido%60;

	posicion.x = 80;
	posicion.y = 65;
	sprintf(msg, "%d:%d:%d", horas, minutos, segundos);
	SURFtiempo = TTF_RenderText_Blended(FONTfuente, msg, color);
	SDL_BlitSurface(SURFtiempo, NULL, SURFscreen, &posicion);

	posicion.x = 18;
	posicion.y = 95;
	sprintf(msg,"Movimientos: %d",contadorMovimientos);
	SURFmovimientos = TTF_RenderText_Blended(FONTfuente, msg, color);
	SDL_BlitSurface(SURFmovimientos, NULL, SURFscreen, &posicion);

	// Dibujamos el puzle actual.
	for(int i=0; i<puzleActual->getTamano(); i++)
	{
		for(int j=0; j<puzleActual->getTamano(); j++)
		{
			if( (solucionado == true) || ( (i != puzleActual->huecoX ) || ( j != puzleActual->huecoY) ) )
			{
				// Calculamos la superficie de corte.
				corte.w = 500 / puzleActual->getTamano();
				corte.h = 500 / puzleActual->getTamano();
				corte.x = (500 / puzleActual->getTamano())*puzleActual->matriz->getElemento(i,j).getX();
				corte.y = (500 / puzleActual->getTamano())*puzleActual->matriz->getElemento(i,j).getY();

				// Calculamos la posición de la pieza.
				posicion.x = 250 + corte.w*i;
				posicion.y = 50 + corte.h*j ;

				// Dibujamos la pieza.
				SDL_BlitSurface(puzleActual->getGrande(), &corte, SURFscreen, &posicion);
			}
		}
	}

	// Dibujamos la miniatura del puzle en juego.
	posicion.x = 18;
	posicion.y = 350;

	// Dibujamos la miniatura.
	SDL_BlitSurface(puzleActual->getMedio(), NULL, SURFscreen, &posicion);


	// Dibujamos el progreso de salir.
	dibujarProgresoSalir();

	// Visualizamos que el puzle está solucionado.
	if(solucionado)
	{
		// Mostramos el texto "Completado".
		SDL_Rect rectangulo;
		rectangulo.x = 300;
		rectangulo.y = 280;
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
