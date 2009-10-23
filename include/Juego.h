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


#include "Puzle.h"
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

	// Establece como puzle actual el puzle anterior.
	void puzzleAnterior();

	// Establece como puzle actual el puzzle siguiente.
	void puzzleSiguiente();

	// Indica si se debe salir.
	bool getSalir();

	// Establece si se debe salir.
	void setSalir(bool salir);

private:

	// Constructor privado.
	Juego();

	// Reproduce el sonido que recibe por parámetro.
	void reproducirSonido(string sonido);

	// Inicializa SDL.
	void inicializaSDL();

	// Inicializa el sonido.
	void inicializaSonido();
	
	// Inicializa los puzles.
	void inicializaPuzzles();
	
	// Finaliza SDL.
	void finalizaSDL();

	// Finaliza el sonido.
	void finalizaSonido();

	// Finaliza los puzles.
	void finalizaPuzzles();

	// Devuelve el tiempo en formato (dd:)(hh:)mm:ss
	string formatoTiempo(Uint32 tiempo);



	/// Instancia de la clase
	static Juego* instancia;

	// Indica el estado actual del juego.
	Estado<Juego>* estado;

	// Listado de puzles disponibles.
	list<Puzle*> puzles;

	// Puzle que se está jugando.
	Puzle* puzleActual;

	// Número de puzle que se va a jugar o se está jugando.
	int numPuzleActual;

	// Mapa de sonidos.
	map<string, Sonido*> sonidos;

	// Indica si se debe salir.
	bool salir;













	// Dibuja la barra de progreso para salir
	void dibujarProgresoSalir();	

	// Devuelve el mejor tiempo del puzle.
	Uint32 getMejorTiempo(string rutaPuzle);

	// Devuelve los mejores movimientos del puzle.
	int getMejorMovimiento(string rutaPuzle);

	// Establece el valor del mejor tiempo.
	void setMejorTiempo(string ruta, Uint32 mejorTiempo);

	// Establece el valor del mejor movimiento.
	void setMejorMovimiento(string ruta, int mejorMovimiento);

	// Carga el puzle actual con el tamaño indicado.
	void cargarPuzle(int tamano);

	





	// Pantalla sobre la que se dibuja.
	SDL_Surface *SURFscreen;

	// Imagen de fondo.
	SDL_Surface *SURFfondo;

	// Imagen de fondo2.
	SDL_Surface *SURFfondo2;

	// Superficie de juego.
	SDL_Surface *SURFjuego;

	// Texto saliendo.
	SDL_Surface *SURFsaliendo;

	// Texto completado.
	SDL_Surface *SURFcompletado;

	// Animación del reloj.
	SDL_Surface *SURFreloj;

	// Superficie de tiempo.
	SDL_Surface *SURFtexto;

	// Fuente utilizada.
	TTF_Font* FONTfuente;
	
	

	// Contadores.
	Uint32 temporizadorEscape;
	Uint32 iteracionAnterior;
	Uint32 temporizadorReloj;
	Uint32 temporizadorJuego;

	// Contabiliza los movimientos realizados.
	int contadorMovimientos;

	// Mejor número de movimientos del puzle.
	int mejorMovimiento;

	// Mejor tiempo del puzle.
	Uint32 mejorTiempo;

	// Frame de la animación del reloj.
	int frameAnimacionReloj;

	// Tiempo de escape.
	int tiempoEscape;

	// Tiempo de delay en desplazamiento.
	int delay;
};

#endif	/* _JUEGO_H */
