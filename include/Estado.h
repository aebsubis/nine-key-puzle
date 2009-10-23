#ifndef _ESTADO_H
#define	_ESTADO_H

#include <iostream>

using namespace std;

template <class tipoEntidad>

/// Clase Estado
/** La clase Estado es una clase virtual pura de la que heredarán los estados del juego
 */
class Estado
{
public:
	/// Destructor
	virtual ~Estado() {}

	/// Eventos
	virtual void eventos(tipoEntidad* entidad) = 0;

	/// Actualizar
	virtual void actualizar(tipoEntidad* entidad) = 0;

	/// Render
	virtual void render(tipoEntidad* entidad) = 0;
};

#endif	/* _ESTADO_H */
