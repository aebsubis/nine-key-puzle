#include "Juego_EstadoJugando.h"

// Instancia de la clase.
Juego_EstadoJugando* Juego_EstadoJugando::instancia = NULL;

/// getInstancia
Juego_EstadoJugando* Juego_EstadoJugando::getInstancia()
{
	if(instancia == NULL)
		instancia = new Juego_EstadoJugando;
	return instancia;
}

// Constructor por defecto.
Juego_EstadoJugando::Juego_EstadoJugando()
{

}

// Destructor
Juego_EstadoJugando::~Juego_EstadoJugando()
{

}

// Captura los eventos del juego.
void Juego_EstadoJugando::eventos(Juego* juego)
{
SDL_Event event;

	while (SDL_PollEvent (&event))
	{
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(juego->temporizadorEscape == 0)
					juego->temporizadorEscape = SDL_GetTicks();
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Al pulsar el escape pasamos al estado menú sin esperar.
				juego->setEstado(Juego_EstadoMenu::getInstancia());
			}
			else if (event.key.keysym.sym == SDLK_q)
			{
				// Efectúa un movimiento con el algoritmo irrevocable.
				juego->resolverIrrevocable();
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP2 || event.key.keysym.sym == SDLK_DOWN)
			{
				// Movemos la pieza de abajo al hueco.
				juego->mover("abajo");
			}
			else if (event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_LEFT)
			{
				// Movemos la pieza de la izquierda al hueco.
				juego->mover("izquierda");
			}
			else if (event.key.keysym.sym == SDLK_KP6 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Movemos la pieza de la derecha al hueco.
				juego->mover("derecha");
			}
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
			{
				// Movemos la pieza de arriba al hueco.
				juego->mover("arriba");
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				juego->temporizadorEscape = 0;
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
				else if(zona(mouse_x, mouse_y, 70, 10, 170, 30))
				{
					// Al pulsar abandonar pasamos al estado menú sin esperar.
					juego->setEstado(Juego_EstadoMenu::getInstancia());
				}
				else
				{
					// Comprobamos a que zona pertenecen.
					int tamano = 500 / juego->puzzleActual->getTamano();
					bool encontrado = false;
					for(int i=0; i<juego->puzzleActual->getTamano() && encontrado == false; i++)
					{
						for(int j=0; j<juego->puzzleActual->getTamano() && encontrado == false; j++)
						{
							if( (i == juego->puzzleActual->huecoX+1 ) && ( j == juego->puzzleActual->huecoY)  )
							{
								// Calculamos la posición de la pieza.
								int origen_x = 250 + tamano*i;
								int origen_y = 50 + tamano*j ;
								int destino_x = origen_x + tamano;
								int destino_y = origen_y + tamano;

								if(zona(mouse_x, mouse_y, origen_x, origen_y, destino_x, destino_y))
								{
									encontrado = true;
									// Movemos la pieza de la derecha al hueco.
									juego->mover("izquierda");
								}
							}
							else if( (i == juego->puzzleActual->huecoX-1 ) && ( j == juego->puzzleActual->huecoY) )
							{
								// Calculamos la posición de la pieza.
								int origen_x = 250 + tamano*i;
								int origen_y = 50 + tamano*j ;
								int destino_x = origen_x + tamano;
								int destino_y = origen_y + tamano;

								if(zona(mouse_x, mouse_y, origen_x, origen_y, destino_x, destino_y))
								{
									encontrado = true;
									// Movemos la pieza de la izquierda al hueco.
									juego->mover("derecha");
								}
							}
							else if( (i == juego->puzzleActual->huecoX ) && ( j == juego->puzzleActual->huecoY+1)  )
							{
								// Calculamos la posición de la pieza.
								int origen_x = 250 + tamano*i;
								int origen_y = 50 + tamano*j ;
								int destino_x = origen_x + tamano;
								int destino_y = origen_y + tamano;

								if(zona(mouse_x, mouse_y, origen_x, origen_y, destino_x, destino_y))
								{
									encontrado = true;
									// Movemos la pieza de la abajo al hueco.
									juego->mover("arriba");
								}
							}
							else if( (i == juego->puzzleActual->huecoX ) && ( j == juego->puzzleActual->huecoY-1)  )
							{
								// Calculamos la posición de la pieza.
								int origen_x = 250 + tamano*i;
								int origen_y = 50 + tamano*j ;
								int destino_x = origen_x + tamano;
								int destino_y = origen_y + tamano;

								if(zona(mouse_x, mouse_y, origen_x, origen_y, destino_x, destino_y))
								{
									encontrado = true;
									// Movemos la pieza de la arriba al hueco.
									juego->mover("abajo");
								}
							}
						}
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
				/*
				// Pasamos al estado historial.
				juego->setEstado(Juego_EstadoHistorial::getInstancia());
				
				// Incrementamos la posición del historial.
				juego->avanzarHistorial();
				 */
			}
			else if(event.button.button == SDL_BUTTON_WHEELDOWN)
			{
				// Decrementamos la posición del historial.
				//juego->retrocederHistorial();
			}
		}
		else if(event.type == SDL_QUIT)
		{
			juego->setSalir(true);
		}
	}
}

// Actualiza el juego.
void Juego_EstadoJugando::actualizar(Juego* juego)
{
	// Comprobamos si la tecla de forzar salida lleva pulsada suficiente tiempo
	if(juego->temporizadorEscape != 0)
	{
		if(SDL_GetTicks() - juego->temporizadorEscape > (unsigned)juego->tiempoEscape)
		{
			// Reiniciamos el temporizador de escape.
			juego->temporizadorEscape = 0;

			// Pasamos al estado menú.
			juego->setEstado(Juego_EstadoMenu::getInstancia());
		}
	}

	// Actualizamos el frame del reloj.
	if(SDL_GetTicks() - juego->temporizadorReloj > 400)
	{
		// Actualizamos el temporizador.
		juego->temporizadorReloj = SDL_GetTicks();

		// Incrementamos el frame.
		juego->frameAnimacionReloj++;

		// Comprobamos si se ha pasado.
		if(juego->frameAnimacionReloj>3)
			juego->frameAnimacionReloj = 0;
	}

	// Comprobamos si el puzzle está solucionado.
	if(juego->puzzleActual->solucionado() == true)
	{
		// Reproducimos el sonido de victoria.
		juego->reproducirSonido("victoria");

		// Hacemos un render con el texto de la victoria.
		juego->render();

		// Guardamos las estadísticas (si son mejores).
		Uint32 tiempoTranscurrido = SDL_GetTicks() - juego->contadorTiempo;
		if(tiempoTranscurrido < juego->puzzleActual->getMejorTiempo())
			juego->puzzleActual->setMejorTiempo(tiempoTranscurrido);

		if(juego->contadorMovimientos < juego->puzzleActual->getMejorMovimiento())
			juego->puzzleActual->setMejorMovimiento(juego->contadorMovimientos);

		// Detenemos el juego durante un tiempo.
		juego->iteracionAnterior = SDL_GetTicks();

		// Detenemos la partida 100 ms.
		while (SDL_GetTicks() - juego->iteracionAnterior < 3000){  }

		// Volvemos al menú.
		juego->setEstado(Juego_EstadoMenu::getInstancia());
	}
}

// Hace un render del juego.
void Juego_EstadoJugando::render(Juego* juego)
{
	// Rectángulo de posición.
	SDL_Rect posicion;

	// Rectángulo de corte.
	SDL_Rect corte;

	// Limpiar pantalla
	SDL_FillRect(juego->getSuperficie("screen"), 0, SDL_MapRGB(juego->getSuperficie("screen")->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(juego->getSuperficie("fondoJuego"), NULL, juego->getSuperficie("screen"), NULL);

	// Activar/Desactivar sonido.
	posicion.x = 0;
	posicion.y = 0;
	if(juego->sonido == true)
		SDL_BlitSurface(juego->getSuperficie("mute"), NULL, juego->getSuperficie("screen"), &posicion);
	else
		SDL_BlitSurface(juego->getSuperficie("unmute"), NULL, juego->getSuperficie("screen"), &posicion);

	// Botón de abandonar.
	posicion.x = 70;
	posicion.y = 10;
	SDL_BlitSurface(juego->getSuperficie("abandonar"), NULL, juego->getSuperficie("screen"), &posicion);

	// Logotipo.
	posicion.x = 0;
	posicion.y = 580;
	SDL_BlitSurface(juego->getSuperficie("logotipo"), NULL, juego->getSuperficie("screen"), &posicion);

	// Comprobamos si está solucionado.
	bool solucionado = juego->puzzleActual->solucionado();

	///////////////////////////
	// PANEL DE ESTADÍSTICAS //
	///////////////////////////

	// Dibujamos el reloj.
	corte.w = 50;
	corte.h = 50;
	corte.x = 50*juego->frameAnimacionReloj;
	corte.y = 0;
	posicion.x = 18;
	posicion.y = 45;
	SDL_BlitSurface(juego->getSuperficie("reloj"), &corte, juego->getSuperficie("screen"), &posicion);

	// Color del texto
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	// Superficie del texto.
	SDL_Surface* texto;

	// Dibujamos el tiempo transcurrido.
	posicion.x = 80;
	posicion.y = 50;
	Uint32 tiempoTranscurrido = SDL_GetTicks() - juego->contadorTiempo;
	texto = TTF_RenderText_Blended(juego->getFuente(), "Actual:", color);
	SDL_BlitSurface(texto, NULL,juego-> getSuperficie("screen"), &posicion);
	posicion.x = 150;
	posicion.y = 50;
	texto = TTF_RenderText_Blended(juego->getFuente(), juego->formatoTiempo(tiempoTranscurrido).c_str(), color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);

	// Dibujamos el mejor tiempo del puzzle.
	posicion.x = 80;
	posicion.y = 80;
	texto = TTF_RenderText_Blended(juego->getFuente(), "Mejor:", color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);
	posicion.x = 150;
	posicion.y = 80;
	texto = TTF_RenderText_Blended(juego->getFuente(), juego->formatoTiempo(juego->puzzleActual->getMejorTiempo()).c_str(), color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);
	
	// Dibujamos los movimientos realizados.
	char msg[30] = "0";
	posicion.x = 18;
	posicion.y = 130;
	sprintf(msg,"Movimientos actuales: %d",juego->contadorMovimientos);
	texto = TTF_RenderText_Blended(juego->getFuente(), msg, color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);

	// Dibujamos los mejores movimientos.
	posicion.x = 18;
	posicion.y = 160;
	sprintf(msg,"Minimo movimientos: %d",juego->puzzleActual->getMejorMovimiento());
	texto = TTF_RenderText_Blended(juego->getFuente(), msg, color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);

	// Texto "miniatura".
	posicion.x = 80;
	posicion.y = 330;
	sprintf(msg,"MINIATURA");
	texto = TTF_RenderText_Blended(juego->getFuente(), msg, color);
	SDL_BlitSurface(texto, NULL, juego->getSuperficie("screen"), &posicion);

	// Dibujamos la miniatura del puzzle en juego.
	posicion.x = 18;
	posicion.y = 350;

	// Dibujamos la miniatura.
	SDL_BlitSurface(juego->puzzleActual->getMedio(), NULL, juego->getSuperficie("screen"), &posicion);

	////////////////////
	// PANEL DE PUZZLE //
	////////////////////

	// Dibujamos el puzzle actual.
	for(int i=0; i<juego->puzzleActual->getTamano(); i++)
	{
		for(int j=0; j<juego->puzzleActual->getTamano(); j++)
		{
			if( (solucionado == true) || ( (i != juego->puzzleActual->huecoX ) || ( j != juego->puzzleActual->huecoY) ) )
			{
				// Calculamos la superficie de corte.
				corte.w = 500 / juego->puzzleActual->getTamano();
				corte.h = 500 / juego->puzzleActual->getTamano();
				corte.x = (500 / juego->puzzleActual->getTamano())*juego->puzzleActual->matriz->getElemento(i,j).getX();
				corte.y = (500 / juego->puzzleActual->getTamano())*juego->puzzleActual->matriz->getElemento(i,j).getY();

				// Calculamos la posición de la pieza.
				posicion.x = 250 + corte.w*i;
				posicion.y = 50 + corte.h*j ;

				// Dibujamos la pieza.
				SDL_BlitSurface(juego->puzzleActual->getGrande(), &corte, juego->getSuperficie("screen"), &posicion);
			}
		}
	}
	
	// Dibujamos el progreso de salir.
	juego->dibujarProgresoSalir();

	// Visualizamos que el puzzle está solucionado.
	if(solucionado)
	{
		// Mostramos el texto "Completado".
		SDL_Rect rectangulo;
		rectangulo.x = 300;
		rectangulo.y = 280;
		SDL_BlitSurface(juego->getSuperficie("completado"), NULL, juego->getSuperficie("screen"), &rectangulo);
	}

	// Refrescamos la pantalla.
	SDL_Flip (juego->getSuperficie("screen"));
}

// Comprueba si una coordenada se encuentra en un zona.
bool Juego_EstadoJugando::zona(int posicion_x, int posicion_y, int origen_x, int origen_y, int destino_x, int destino_y)
{
	return (posicion_x >= origen_x && posicion_x <= destino_x) && (posicion_y >= origen_y && posicion_y <= destino_y);
}
