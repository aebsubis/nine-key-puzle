#ifndef _JUEGO_H
#define	_JUEGO_H

#include <iostream>
#include <list>
#include <SDL/SDL_video.h>
#include <SDL/SDL_events.h>
#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"
#include "Puzle.h"
#include "Sonido.h"
#include "Directorio.h"

using namespace std;

/* Clase juego.
 *
 */
class Juego
{
public:

	// Constructor por defecto.
	Juego();

	// Destructor.
	~Juego();

	// Inicia el juego.
	void iniciar();

	// Intercambia la posición de dos piezas.
	void intercambiar(int posicionInicio, int posicionDestino);

private:

	// Inicializa SDL.
	void inicializaSDL();

	// Procesa los eventos del menú.
	void eventosMenu();

	// Actualiza el menu.
	void actualizarMenu();

	// Hace un render del menú.
	void renderMenu();

	// Procesa los eventos del juego.
	void eventosJuego();

	// Actualiza el juego.
	void actualizarJuego();

	// Hace un render del juego.
	void renderJuego();

	// Carga todos los puzles.
	void cargarPuzles();

	// Dibuja la barra de progreso para salir
	void dibujarProgresoSalir();
	
	// Listado de puzles disponibles.
	list<Puzle*> puzles;

	// Puzle que se está jugando.
	Puzle* puzleActual;

	// Número de puzle que se va a jugar o se está jugando.
	int numPuzleActual;

	// Indica si se debe salir.
	bool salir;

	// Indica el estado del juego.
	// 0 = menú principal.
	// 1 = jugando
	int estado;


	// Pantalla sobre la que se dibuja.
	SDL_Surface *SURFscreen;

	// Imagen de fondo.
	SDL_Surface *SURFfondo;

	// Superficie de juego.
	SDL_Surface *SURFjuego;

	// Texto saliendo.
	SDL_Surface *SURFsaliendo;

	// Texto completado.
	SDL_Surface *SURFcompletado;

	// Superficie translucida.
	SDL_Surface *SURFtranslucida;
	
	// Sonidos
	Sonido sIntercambiar;
	Sonido sSeleccionar;
	Sonido sMenu;
	Sonido sRemover;
	Sonido sVictoria;
        Sonido sFondo;

	// Contadores.
	Uint32 temporizadorEscape;
	Uint32 iteracionAnterior;

	// Tiempo de escape.
	int tiempoEscape;

	// Tiempo de delay en desplazamiento.
	int delay;

	// Ficha seleccionada 1.
	int fichaSeleccionada1;

	// Ficha seleccionada 2.
	int fichaSeleccionada2;
};

#endif	/* _JUEGO_H */
