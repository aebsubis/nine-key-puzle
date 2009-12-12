#include <SDL/SDL_events.h>
#include <sstream>
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
			if (event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_LEFT)
			{
				// Decrementamos el nivel.
				int nivel = juego->getNivel()-1;
				if(nivel > 1)
					juego->setNivel(nivel);
			}
			else if (event.key.keysym.sym == SDLK_KP6 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Incrementamos el nivel.
				int nivel = juego->getNivel()+1;
				if(nivel < 10)
					juego->setNivel(nivel);
			}
			else if (event.key.keysym.sym == SDLK_2)
			{
				// Establecemos el nivel a 2x2.
				juego->setNivel(2);
			}
			else if (event.key.keysym.sym == SDLK_3)
			{
				// Establecemos el nivel a 3x3.
				juego->setNivel(3);
			}
			else if (event.key.keysym.sym == SDLK_4)
			{
				// Establecemos el nivel a 4x4.
				juego->setNivel(4);
			}
			else if (event.key.keysym.sym == SDLK_5)
			{
				// Establecemos el nivel a 5x5.
				juego->setNivel(5);
			}
			else if (event.key.keysym.sym == SDLK_6)
			{
				// Establecemos el nivel a 6x6.
				juego->setNivel(6);
			}
			else if (event.key.keysym.sym == SDLK_7)
			{
				// Establecemos el nivel a 7x7.
				juego->setNivel(7);
			}
			else if (event.key.keysym.sym == SDLK_8)
			{
				// Establecemos el nivel a 8x8.
				juego->setNivel(8);
			}
			else if (event.key.keysym.sym == SDLK_9)
			{
				// Establecemos el nivel a 9x9.
				juego->setNivel(9);
			}
			else if (event.key.keysym.sym == SDLK_KP_ENTER || event.key.keysym.sym == SDLK_RETURN || event.key.keysym.sym == SDLK_KP5)
			{
				// Carga el puzzleActual al nivel actual.
				juego->cargarPuzzle(juego->getNivel());
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
				if(zona(mouse_x, mouse_y, 0, 0, 35, 25))
				{
					// Cambiamos el sonido.
					juego->activarDesactivarSonido();
				}
				else if(zona(mouse_x, mouse_y, 0, 0, 240, 240))
				{
					// Elegimos el puzzle de arriba.
					juego->puzzleSiguiente();
				}
				else if(zona(mouse_x, mouse_y, 0, 240, 240, 360))
				{
					// Carga el puzzleActual al nivel actual.
					juego->cargarPuzzle(juego->getNivel());
				}
				else if(zona(mouse_x, mouse_y, 0, 360, 240, 600))
				{
					// Elegimos el puzzle de abajo.
					juego->puzzleAnterior();
				}
				

				if(juego->dibujarNiveles == true)
				{
					if(zona(mouse_x, mouse_y, 250, 50, 750, 505))
					{
						// Carga el puzzleActual al nivel actual.
						juego->cargarPuzzle(juego->getNivel());
					}
					else if(zona(mouse_x, mouse_y, 275, 510, 300, 600))
					{
						// Desactivamos el dibujado de los niveles.
						juego->dibujarNiveles = false;
						juego->delayNivel = 500;
					}

					else if(zona(mouse_x, mouse_y, 322, 523, 424, 553))
					{
						// Establecemos el nivel 2.
						juego->setNivel(2);
					}
					else if(zona(mouse_x, mouse_y, 437, 523, 539, 553))
					{
						// Establecemos el nivel 3.
						juego->setNivel(3);
					}
					else if(zona(mouse_x, mouse_y, 552, 523, 654, 553))
					{
						// Establecemos el nivel 4.
						juego->setNivel(4);
					}
					else if(zona(mouse_x, mouse_y, 667, 523, 769, 553))
					{
						// Establecemos el nivel 5.
						juego->setNivel(5);
					}
					else if(zona(mouse_x, mouse_y, 322, 563, 424, 593))
					{
						// Establecemos el nivel 6.
						juego->setNivel(6);
					}
					else if(zona(mouse_x, mouse_y, 437, 563, 539, 593))
					{
						// Establecemos el nivel 7.
						juego->setNivel(7);
					}
					else if(zona(mouse_x, mouse_y, 552, 563, 654, 593))
					{
						// Establecemos el nivel 8.
						juego->setNivel(8);
					}
					else if(zona(mouse_x, mouse_y, 667, 563, 769, 593))
					{
						// Establecemos el nivel 9.
						juego->setNivel(9);
					}
				}
				else
				{
					if(zona(mouse_x, mouse_y, 350, 200, 650, 400))
					{
						// Carga el puzzleActual al nivel actual.
						juego->cargarPuzzle(juego->getNivel());
					}
					else if(zona(mouse_x, mouse_y, 775, 510, 800, 600))
					{
						// Actuvamos el dibujado de los niveles.
						juego->dibujarNiveles = true;
						juego->delayNivel = 500;
					}
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
	// Decrementamos el delay hasta 0.
	if(juego->delay>0)
		juego->delay = juego->delay - 10;
	if(juego->delay<0)
		juego->delay = juego->delay + 10;

	// Decrementamos el delayNivel hasta 0.
	if(juego->delayNivel>0)
		juego->delayNivel = juego->delayNivel - 25;
	if(juego->delayNivel<0)
		juego->delayNivel = juego->delayNivel + 25;

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
	// Rectángulo de posición.
	SDL_Rect posicion;

	// Limpiar pantalla
	SDL_FillRect(juego->getSuperficie("screen"), 0, SDL_MapRGB(juego->getSuperficie("screen")->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(juego->getSuperficie("fondoMenu"), NULL, juego->getSuperficie("screen"), NULL);

	// Activar/Desactivar sonido.
	posicion.x = 0;
	posicion.y = 0;
	if(juego->sonido == true)
		SDL_BlitSurface(juego->getSuperficie("mute"), NULL, juego->getSuperficie("screen"), &posicion);
	else
		SDL_BlitSurface(juego->getSuperficie("unmute"), NULL, juego->getSuperficie("screen"), &posicion);

	// Logotipo.
	posicion.x = 0;
	posicion.y = 580;
	SDL_BlitSurface(juego->getSuperficie("logotipo"), NULL, juego->getSuperficie("screen"), &posicion);
	
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


	// Dibujamos el botón de comenzar.
	posicion.x = 350;
	posicion.y = 200;
	SDL_BlitSurface(juego->getSuperficie("comenzar"), NULL, juego->getSuperficie("screen"), &posicion);

	// Dibujamos el panel de niveles.
	SDL_Rect posicionPanel;
	if(juego->dibujarNiveles == true)
	{
		// El panel se está mostrando.
		posicionPanel.x = 270 + juego->delayNivel;
		posicionPanel.y = 505;
	}
	else
	{
		// El panel se está ocultando.
		posicionPanel.x = 770 - juego->delayNivel;
		posicionPanel.y = 505;

	}
	SDL_BlitSurface(juego->getSuperficie("panelNivel"), NULL, juego->getSuperficie("screen"), &posicionPanel);

	// Dibujamos los botones.
	for(int i=0; i<8; i++)
	{
		// Calculamos la posición del boton.
		int fila = i/4;
		int columna = i%4;
		SDL_Rect posicion;
		posicion.x = posicionPanel.x + 50 + 115 * columna;
		posicion.y = posicionPanel.y + 15 + 40 * fila;

		stringstream nivel;
		nivel << i+2;

		if(juego->nivel == i+2)
			SDL_BlitSurface(juego->getSuperficie("nivel" + nivel.str()+"on"), NULL, juego->getSuperficie("screen"), &posicion);
		else
			SDL_BlitSurface(juego->getSuperficie("nivel" + nivel.str()), NULL, juego->getSuperficie("screen"), &posicion);
	}

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
