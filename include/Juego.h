#ifndef _JUEGO_H
#define	_JUEGO_H

#include <iostream>
#include <list>
#include <map>


#include <SDL/SDL_video.h>
#include <SDL/SDL_events.h>
#include "SDL.h"
#include "SDL/SDL_ttf.h"
#include "SDL/SDL_image.h"


#include "Puzzle.h"
#include "Sonido.h"
#include "Directorio.h"

class Juego;
#include "Estado.h"
#include "Juego_EstadoJugando.h"
#include "Juego_EstadoMenu.h"

using namespace std;

/* Clase juego.
 * La clase juego está diseñada con el patrón sigletón.
 */
class Juego
{
	// El estado puede acceder a los miembros privados del juego. (Intentar evitar).
	friend class Juego_EstadoMenu;
	friend class Juego_EstadoJugando;
public:

	/// Devuelve la instancia de la clase.
	static Juego* getInstancia();
	
	// Destructor.
	~Juego();

	// Inicializa el juego.
	void inicializar();

	// Inicia el juego.
	void iniciar();

	// Procesa los eventos.
	void eventos();

	// Actualiza.
	void actualizar();

	// Hace un render.
	void render();

	// Modifica el estado del juego.
	void setEstado(Estado<Juego>* estado);

	// Finaliza el juego.
	void finalizar();

	// Establece como puzzle actual el puzzle anterior.
	void puzzleAnterior();

	// Establece como puzzle actual el puzzle siguiente.
	void puzzleSiguiente();

	// Indica si se debe salir.
	bool getSalir() const;

	// Establece si se debe salir.
	void setSalir(bool salir);

	// Devuelve la superficie.
	SDL_Surface* getSuperficie(string nombre);

	// Establece la superficie.
	void setSuperficie(string nombre, SDL_Surface* superficie);

	// Devuelve la fuente.
	TTF_Font* getFuente() const;

	// Establece la fuente.
	void setFuente(TTF_Font* fuente);

private:

	// Constructor privado.
	Juego();

	// Reproduce el sonido que recibe por parámetro.
	void reproducirSonido(string sonido);

	// Carga el puzzle actual con el tamaño indicado.
	void cargarPuzzle(int tamano);

	// Inicializa SDL.
	void inicializaSDL();

	// Inicializa el sonido.
	void inicializaSonido();
	
	// Inicializa los puzzles.
	void inicializaPuzzles();
	
	// Finaliza SDL.
	void finalizaSDL();

	// Finaliza el sonido.
	void finalizaSonido();

	// Finaliza los puzzles.
	void finalizaPuzzles();

	// Devuelve el tiempo en formato (dd:)(hh:)mm:ss
	string formatoTiempo(Uint32 tiempo);

	// Dibuja la barra de progreso para salir
	void dibujarProgresoSalir();

	/// Instancia de la clase
	static Juego* instancia;

	// Indica el estado actual del juego.
	Estado<Juego>* estado;

	// Listado de puzzles disponibles.
	list<Puzzle*> puzzles;

	// Puzzle que se está jugando.
	Puzzle* puzzleActual;

	// Número de puzzle que se va a jugar o se está jugando.
	int numPuzzleActual;

	// Mapa de superficies.
	map<string, SDL_Surface*> superficies;
	
	// Mapa de sonidos.
	map<string, Sonido*> sonidos;

	// Indica si se debe salir.
	bool salir;

	// Fuente del texto.
	TTF_Font* FONTfuente;
	
	// Contadores.
	Uint32 temporizadorEscape;
	Uint32 iteracionAnterior;
	Uint32 temporizadorReloj;
	
	// Contador del tiempo transcurrido.
	Uint32 contadorTiempo;
	
	// Contabiliza los movimientos realizados.
	int contadorMovimientos;

	// Frame de la animación del reloj.
	int frameAnimacionReloj;

	// Tiempo de escape.
	int tiempoEscape;

	// Tiempo de delay en desplazamiento.
	int delay;
};

#endif	/* _JUEGO_H */
