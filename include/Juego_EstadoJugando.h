#ifndef _JUEGO_ESTADOJUGANDO_H
#define	_JUEGO_ESTADOJUGANDO_H

#include <iostream>

#include "Estado.h"
#include "Juego.h"
using namespace std;

/* Clase Juego_EstadoJugando.
 * La clase Juego_EstadoJugando está implementado siguiendo el patrón de diseño singleton.
 * Representa las funciones del juego cuando se encuentra en el estado jugando.
 */
class Juego_EstadoJugando : public Estado<Juego>
{
public:
	
	/// Devuelve la instancia de la clase.
	static Juego_EstadoJugando* getInstancia();

	// Destructor
	~Juego_EstadoJugando();
	
	// Captura los eventos del juego.
	void eventos(Juego* juego);

	// Actualiza el juego.
	void actualizar(Juego* juego);

	// Hace un render del juego.
	void render(Juego* juego);

private:
	
	// Instancia de la clase.
	static Juego_EstadoJugando* instancia;

	// Constructor por defecto.
	Juego_EstadoJugando();
};


#endif	/* _JUEGO_ESTADOJUGANDO_H */
