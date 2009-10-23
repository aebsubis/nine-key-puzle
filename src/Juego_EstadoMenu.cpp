#include <SDL/SDL_events.h>

#include "Juego_EstadoMenu.h"

// Instancia de la clase.
Juego_EstadoMenu* Juego_EstadoMenu::instancia = NULL;

/// getInstancia
Juego_EstadoMenu* Juego_EstadoMenu::getInstancia()
{
	if(instancia == NULL)
		instancia = new Juego_EstadoMenu;
	return instancia;
}

// Constructor por defecto.
Juego_EstadoMenu::Juego_EstadoMenu()
{

}

// Destructor
Juego_EstadoMenu::~Juego_EstadoMenu()
{

}

// Captura los eventos del menú.
void Juego_EstadoMenu::eventos(Juego* juego)
{
	SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		if (event.type == SDL_KEYDOWN) // Se ha pulsado una tecla
		{
			if (event.key.keysym.sym == SDLK_KP2 || event.key.keysym.sym == SDLK_DOWN)
			{
				// Elegimos el puzle de abajo.
				juego->puzzleAnterior();
			}
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
			{
				// Elegimos el puzle de arriba.
				juego->puzzleSiguiente();
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if (juego->temporizadorEscape == 0)
					juego->temporizadorEscape = SDL_GetTicks();
			}
			else if( event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Al pulsar el escape se sale directamente sin esperar.
				juego->setSalir(true);
			}
		}
		else if (event.type == SDL_KEYUP) // Se ha soltado una tecla
		{
			if (event.key.keysym.sym == SDLK_2)
			{
				// Carga el puzleActual a tamaño 2x2.
				juego->cargarPuzle(2);
			}
			else if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Carga el puzleActual a tamaño 3x3.
				juego->cargarPuzle(3);
			}
			else if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP5)
			{
				// Carga el puzleActual a tamaño 4x4.
				juego->cargarPuzle(4);
			}
			else if (event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP6)
			{
				// Carga el puzleActual a tamaño 4x4.
				juego->cargarPuzle(5);
			}
			else if (event.key.keysym.sym == SDLK_6)
			{
				// Carga el puzleActual a tamaño 6x6.
				juego->cargarPuzle(6);
			}
			else if (event.key.keysym.sym == SDLK_7)
			{
				// Carga el puzleActual a tamaño 7x7.
				juego->cargarPuzle(7);
			}
			else if (event.key.keysym.sym == SDLK_8)
			{
				// Carga el puzleActual a tamaño 8x8.
				juego->cargarPuzle(8);
			}
			else if( event.key.keysym.sym == SDLK_9)
			{
				// Carga el puzleActual a tamaño 9x9.
				juego->cargarPuzle(9);
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				juego->temporizadorEscape = 0;
			}
		}
	}
}

// Actualiza el menú.
void Juego_EstadoMenu::actualizar(Juego* juego)
{
	// Comprobamos si la tecla de forzar salida lleva pulsada suficiente tiempo
	if(juego->temporizadorEscape != 0)
	{
		if(SDL_GetTicks() - juego->temporizadorEscape > (unsigned)juego->tiempoEscape)
		{
			juego->temporizadorEscape = 0;
			juego->setSalir(true);
		}
	}
}

// Hace un render del menú.
void Juego_EstadoMenu::render(Juego* juego)
{
	// Limpiar pantalla
	SDL_FillRect(juego->SURFscreen, 0, SDL_MapRGB(juego->SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(juego->SURFfondo, NULL, juego->SURFscreen, NULL);

	// Dibujamos el listado de puzles.
	if(juego->puzles.size() > 0)
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
		miniaturaInicial = juego->numPuzleActual-3;
		while(miniaturaInicial<0)
		{
			miniaturaInicial = juego->puzles.size() + miniaturaInicial;
		}

		// Nos desplazamos hasta la miniatura inicial.
		pos = juego->puzles.begin();
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
 				posicion.x = 50 + 35*abs(numMiniatura) - juego->delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->SURFscreen, &posicion);
			}
			else if(numMiniatura < 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + juego->delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->SURFscreen, &posicion);
			}
			else if(numMiniatura == 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + abs((int)(juego->delay*0.25));
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->SURFscreen, &posicion);

				// También lo dibujamos en grande.
				posicion.x = 250;
				posicion.y = 50;
				SDL_Rect corte;
				corte.x = 0;
				corte.y = 0;
				corte.w = 500;
				corte.h = 500;

				// Dibujamos la imagen.
				SDL_BlitSurface(activo->getGrande(), &corte, juego->SURFscreen, &posicion);
			}

			numMiniatura++;
			explorandoPosicion++;
			pos++;

			// Si hemos completado la lista, empezamos de 0.
			if(pos == juego->puzles.end())
			{
				explorandoPosicion = 0;
				pos = juego->puzles.begin();
			}
		}

	}

	// Decrementamos el delay hasta 0.
	if(juego->delay>0)
		juego->delay = juego->delay - 10;
	if(juego->delay<0)
		juego->delay = juego->delay + 10;

	// Dibujamos el progreso de salir.
	juego->dibujarProgresoSalir();

	// Refrescamos la pantalla.
	SDL_Flip (juego->SURFscreen);
}
