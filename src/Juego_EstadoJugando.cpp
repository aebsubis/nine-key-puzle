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
			if (event.key.keysym.sym == SDLK_KP9 || event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Al pulsar la tecla 9 se activa un temporizador para forzar la salida.
				if(juego->temporizadorEscape == 0)
					juego->temporizadorEscape = SDL_GetTicks();
			}
			else if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				// Al pulsar el escape se sale directamente sin esperar.
				juego->setSalir(true);
			}
		}
		else if (event.type == SDL_KEYUP)
		{
			if (event.key.keysym.sym == SDLK_KP2 || event.key.keysym.sym == SDLK_DOWN)
			{
				// Movemos la pieza de abajo al hueco.
				if(juego->puzleActual->mover("abajo"))
				{
					// Reproducimos el sonido.
					juego->reproducirSonido("intercambiar");

					// Incrementamos los movimientos.
					juego->contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP4 || event.key.keysym.sym == SDLK_LEFT)
			{
				// Movemos la pieza de la izquierda al hueco.
				if (juego->puzleActual->mover("izquierda"))
				{
					// Reproducimos el sonido.
					juego->reproducirSonido("intercambiar");

					// Incrementamos los movimientos.
					juego->contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP6 || event.key.keysym.sym == SDLK_RIGHT)
			{
				// Movemos la pieza de la derecha al hueco.
				if (juego->puzleActual->mover("derecha"))
				{
					// Reproducimos el sonido.
					juego->reproducirSonido("intercambiar");

					// Incrementamos los movimientos.
					juego->contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP8 || event.key.keysym.sym == SDLK_UP)
			{
				// Movemos la pieza de arriba al hueco.
				if (juego->puzleActual->mover("arriba"))
				{
					// Reproducimos el sonido.
					juego->reproducirSonido("intercambiar");

					// Incrementamos los movimientos.
					juego->contadorMovimientos++;
				}
			}
			else if (event.key.keysym.sym == SDLK_KP9)
			{
				// Al soltar la tecla 9 se reinicia el temporizador para forzar la salida.
				juego->temporizadorEscape = 0;
			}
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

	// Comprobamos si el puzle está solucionado.
	if(juego->puzleActual->solucionado() == true)
	{
		// Reproducimos el sonido de victoria.
		juego->reproducirSonido("victoria");

		// Hacemos un render con el texto de la victoria.
		juego->render();

		// Guardamos las estadísticas (si son mejores).
		Uint32 tiempoTranscurrido = SDL_GetTicks() - juego->temporizadorJuego;
		if(tiempoTranscurrido < juego->mejorTiempo)
			juego->setMejorTiempo("puzles/"+juego->puzleActual->getRuta(), tiempoTranscurrido);

		if(juego->contadorMovimientos < juego->mejorMovimiento)
			juego->setMejorMovimiento("puzles/"+juego->puzleActual->getRuta(), juego->contadorMovimientos);

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
	SDL_FillRect(juego->SURFscreen, 0, SDL_MapRGB(juego->SURFscreen->format, 0, 0, 0));

	// Fondo.
	SDL_BlitSurface(juego->SURFfondo2, NULL, juego->SURFscreen, NULL);

	// Comprobamos si está solucionado.
	bool solucionado = juego->puzleActual->solucionado();


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
	SDL_BlitSurface(juego->SURFreloj, &corte, juego->SURFscreen, &posicion);

	// Color del texto
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;

	// Dibujamos el tiempo transcurrido.
	posicion.x = 80;
	posicion.y = 50;
	Uint32 tiempoTranscurrido = SDL_GetTicks() - juego->temporizadorJuego;
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, "Actual:", color);
	SDL_BlitSurface(juego->SURFtexto, NULL,juego-> SURFscreen, &posicion);
	posicion.x = 150;
	posicion.y = 50;
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, juego->formatoTiempo(tiempoTranscurrido).c_str(), color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);

	// Dibujamos el mejor tiempo del puzle.
	posicion.x = 80;
	posicion.y = 80;
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, "Mejor:", color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);
	posicion.x = 150;
	posicion.y = 80;
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, juego->formatoTiempo(juego->mejorTiempo).c_str(), color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);

	// Dibujamos los movimientos realizados.
	char msg[30] = "0";
	posicion.x = 18;
	posicion.y = 130;
	sprintf(msg,"Movimientos actuales: %d",juego->contadorMovimientos);
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, msg, color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);

	// Dibujamos los mejores movimientos.
	posicion.x = 18;
	posicion.y = 160;
	sprintf(msg,"Minimo movimientos: %d",juego->mejorMovimiento);
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, msg, color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);

	// Texto "miniatura".
	posicion.x = 80;
	posicion.y = 330;
	sprintf(msg,"MINIATURA");
	juego->SURFtexto = TTF_RenderText_Blended(juego->FONTfuente, msg, color);
	SDL_BlitSurface(juego->SURFtexto, NULL, juego->SURFscreen, &posicion);

	// Dibujamos la miniatura del puzle en juego.
	posicion.x = 18;
	posicion.y = 350;

	// Dibujamos la miniatura.
	SDL_BlitSurface(juego->puzleActual->getMedio(), NULL, juego->SURFscreen, &posicion);



	////////////////////
	// PANEL DE PUZLE //
	////////////////////

	// Dibujamos el puzle actual.
	for(int i=0; i<juego->puzleActual->getTamano(); i++)
	{
		for(int j=0; j<juego->puzleActual->getTamano(); j++)
		{
			if( (solucionado == true) || ( (i != juego->puzleActual->huecoX ) || ( j != juego->puzleActual->huecoY) ) )
			{
				// Calculamos la superficie de corte.
				corte.w = 500 / juego->puzleActual->getTamano();
				corte.h = 500 / juego->puzleActual->getTamano();
				corte.x = (500 / juego->puzleActual->getTamano())*juego->puzleActual->matriz->getElemento(i,j).getX();
				corte.y = (500 / juego->puzleActual->getTamano())*juego->puzleActual->matriz->getElemento(i,j).getY();

				// Calculamos la posición de la pieza.
				posicion.x = 250 + corte.w*i;
				posicion.y = 50 + corte.h*j ;

				// Dibujamos la pieza.
				SDL_BlitSurface(juego->puzleActual->getGrande(), &corte, juego->SURFscreen, &posicion);
			}
		}
	}




	// Dibujamos el progreso de salir.
	juego->dibujarProgresoSalir();

	// Visualizamos que el puzle está solucionado.
	if(solucionado)
	{
		// Mostramos el texto "Completado".
		SDL_Rect rectangulo;
		rectangulo.x = 300;
		rectangulo.y = 280;
		SDL_BlitSurface(juego->SURFcompletado, NULL, juego->SURFscreen, &rectangulo);
	}

	// Refrescamos la pantalla.
	SDL_Flip (juego->SURFscreen);
}
