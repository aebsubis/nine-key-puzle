#ifndef _JUEGO_ESTADOMENU_H
#define	_JUEGO_ESTADOMENU_H

#include <iostream>

#include "Estado.h"
#include "Juego.h"
using namespace std;

/* Clase Juego_EstadoMenu.
 * La clase Juego_EstadoMenu está implementado siguiendo el patrón de diseño singleton.
 * Representa las funciones del juego cuando se encuentra en el estado del menú.
 */
class Juego_EstadoMenu : public Estado<Juego>
{
public:
	
	/// Devuelve la instancia de la clase.
	static Juego_EstadoMenu* getInstancia();

	// Destructor
	~Juego_EstadoMenu();

	// Captura los eventos del menú.
	void eventos(Juego* juego);

	// Actualiza el menú.
	void actualizar(Juego* juego);

	// Hace un render del menú.
	void render(Juego* juego);

private:
	
	// Instancia de la clase.
	static Juego_EstadoMenu* instancia;
	
	// Constructor por defecto.
	Juego_EstadoMenu();

	// Comprueba si una coordenada se encuentra en un zona.
	bool zona(int posicion_x, int posicion_y, int origen_x, int origen_y, int destino_x, int destino_y);
};


#endif	/* _JUEGO_ESTADOMENU_H */
