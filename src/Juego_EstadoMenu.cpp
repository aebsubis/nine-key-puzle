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
				// Elegimos el puzzle de arriba.
				juego->puzzleAnterior();
			}
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
			{
				// Elegimos el puzzle de abajo.
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
				// Carga el puzzleActual a tamaño 2x2.
				juego->cargarPuzzle(2);
			}
			else if (event.key.keysym.sym == SDLK_3 || event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Carga el puzzleActual a tamaño 3x3.
				juego->cargarPuzzle(3);
			}
			else if (event.key.keysym.sym == SDLK_4 || event.key.keysym.sym == SDLK_KP5)
			{
				// Carga el puzzleActual a tamaño 4x4.
				juego->cargarPuzzle(4);
			}
			else if (event.key.keysym.sym == SDLK_5 || event.key.keysym.sym == SDLK_KP6)
			{
				// Carga el puzzleActual a tamaño 4x4.
				juego->cargarPuzzle(5);
			}
			else if (event.key.keysym.sym == SDLK_6)
			{
				// Carga el puzzleActual a tamaño 6x6.
				juego->cargarPuzzle(6);
			}
			else if (event.key.keysym.sym == SDLK_7)
			{
				// Carga el puzzleActual a tamaño 7x7.
				juego->cargarPuzzle(7);
			}
			else if (event.key.keysym.sym == SDLK_8)
			{
				// Carga el puzzleActual a tamaño 8x8.
				juego->cargarPuzzle(8);
			}
			else if( event.key.keysym.sym == SDLK_9)
			{
				// Carga el puzzleActual a tamaño 9x9.
				juego->cargarPuzzle(9);
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				juego->temporizadorEscape = 0;
			}
		}
		else if(event.type == SDL_MOUSEMOTION)
		{
			int mouse_x, mouse_y;

			SDL_GetMouseState(&mouse_x, &mouse_y);
			if ( (mouse_x < 32) && (mouse_y < 32) )
			{
				//cout << "loool" << endl;
			}

		}
		else if(event.type == SDL_MOUSEBUTTONDOWN)
		{
			if(event.button.button == SDL_BUTTON_LEFT)
			{
				// Obtenemos las coordenadas del ratón.
				int mouse_x, mouse_y;
				SDL_GetMouseState(&mouse_x, &mouse_y);

				// Comprobamos a que zona pertenecen.
				if(zona(mouse_x, mouse_y, 0, 0, 240, 240))
				{
					// Elegimos el puzzle de arriba.
					juego->puzzleSiguiente();
				}
				else if(zona(mouse_x, mouse_y, 0, 240, 240, 360))
				{
					// Carga el puzzleActual a tamaño 3x3.
					juego->cargarPuzzle(3);
				}
				else if(zona(mouse_x, mouse_y, 0, 360, 240, 600))
				{
					// Elegimos el puzzle de abajo.
					juego->puzzleAnterior();
				}
			}
			else if(event.button.button == SDL_BUTTON_RIGHT)
			{

			}
			else if(event.button.button == SDL_BUTTON_MIDDLE)
			{

			}
			else if(event.button.button == SDL_BUTTON_WHEELUP)
			{
				// Elegimos el puzzle de abajo.
				juego->puzzleAnterior();
			}
			else if(event.button.button == SDL_BUTTON_WHEELDOWN)
			{
				// Elegimos el puzzle de arriba.
				juego->puzzleSiguiente();
			}
		}
		else if(event.type == SDL_QUIT)
		{
			juego->setSalir(true);
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
	SDL_FillRect(juego->getSuperficie("screen"), 0, SDL_MapRGB(juego->getSuperficie("screen")->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(juego->getSuperficie("fondoMenu"), NULL, juego->getSuperficie("screen"), NULL);

	// Dibujamos el listado de puzzles.
	if(juego->puzzles.size() > 0)
	{
		// Iterador de la lista.
		list<Puzzle*>::iterator pos;

		// Almacena la posición del puzzle que estamos explorando en la lista.
		int explorandoPosicion;

		// Almacena la posición de la miniatura inicial.
		int miniaturaInicial;

		// Almacena el número de la miniatura que se está dibujando.
		int numMiniatura;

		// Buscamos la posición de la miniatura inicial.
		miniaturaInicial = juego->numPuzzleActual-3;
		while(miniaturaInicial<0)
		{
			miniaturaInicial = juego->puzzles.size() + miniaturaInicial;
		}

		// Nos desplazamos hasta la miniatura inicial.
		pos = juego->puzzles.begin();
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
			Puzzle* activo = *pos;

			// Calculamos la posición de la miniatura.
			SDL_Rect posicion;

			if(numMiniatura>0)
			{
 				posicion.x = 50 + 35*abs(numMiniatura) - juego->delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->getSuperficie("screen"), &posicion);
			}
			else if(numMiniatura < 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + juego->delay*0.25;
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->getSuperficie("screen"), &posicion);
			}
			else if(numMiniatura == 0)
			{
				posicion.x = 50 + 35*abs(numMiniatura) + abs((int)(juego->delay*0.25));
				posicion.y = 250 - 150*(numMiniatura) + juego->delay;

				// Dibujamos la miniatura.
				SDL_BlitSurface(activo->getPequeno(), NULL, juego->getSuperficie("screen"), &posicion);

				// También lo dibujamos en grande.
				posicion.x = 250;
				posicion.y = 50;
				SDL_Rect corte;
				corte.x = 0;
				corte.y = 0;
				corte.w = 500;
				corte.h = 500;

				// Dibujamos la imagen.
				SDL_BlitSurface(activo->getGrande(), &corte, juego->getSuperficie("screen"), &posicion);
			}

			numMiniatura++;
			explorandoPosicion++;
			pos++;

			// Si hemos completado la lista, empezamos de 0.
			if(pos == juego->puzzles.end())
			{
				explorandoPosicion = 0;
				pos = juego->puzzles.begin();
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
	SDL_Flip (juego->getSuperficie("screen"));
}

// Comprueba si una coordenada se encuentra en un zona.
bool Juego_EstadoMenu::zona(int posicion_x, int posicion_y, int origen_x, int origen_y, int destino_x, int destino_y)
{
	return (posicion_x >= origen_x && posicion_x <= destino_x) && (posicion_y >= origen_y && posicion_y <= destino_y);
}
