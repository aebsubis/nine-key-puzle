#ifndef _JUEGO_H
#define	_JUEGO_H

#include <iostream>
#include <list>
#include <SDL/SDL_video.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "Puzle.h"
#include "Sonido.h"

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
	
	// Listado de puzles disponibles.
	list<Puzle> puzles;

	// Número de puzle que se va a jugar o se está jugando.
	int puzleActual;

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

	// Texto, color, fuente y superficie de texto.
	SDL_Surface *SURFtexto;
	SDL_Rect RECTtexto;
	SDL_Color bgcolor,fgcolor;
	TTF_Font *FONTfuente;

	// Sonidos
	Sonido intercambiar;
	Sonido seleccionar;
	Sonido menu;

	// Contadores.
	Uint32 temporizador;
};

#endif	/* _JUEGO_H */

