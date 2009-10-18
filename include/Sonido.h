/// Fichero de cabecera de la clase Sonido.
/** \file sonido.h
 */

#ifndef _SONIDO_H
#define _SONIDO_H

#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include <iostream>
using namespace std;

/// Esta clase representa un sonido que puede reproducirse.
/** Debe tener un formato WAV y requiere que SDL esté inicializado con el 'flag' de audio (SDL_INIT_AUDIO).
 */
class Sonido
{
	public:

		/// Constructor por defecto.
		/** Si es el primer sonido, abre el manejador de audio de SDL.
		 */
		Sonido ();

		/// Destructor.
		/** Libera la memoria reservada.
		 * Si es el último sonido, también cierra el manejador de audio de SDL.
		 */
		~Sonido ();

		/// Reproduce el sonido.
		/** Una vez que se invoca al método, el proceso que lo invocó debe seguir vivo el tiempo suficiente para
		 * para completar la reproducción.
		 * \return Devuelve falso si no está cargado y no lo reproduce. Verdadero en caso contrario.
		 */
		bool reproducir ();

		/// Comprueba si el sonido está reproduciéndose actualmente.
		/** \return Devuelve verdadero si está reproduciéndose. Falso en caso contrario.
		 */
		bool reproduciendose ();

		/// Carga el sonido el memoria.
		/** \param nomSonido Nombre (ruta) del fichero que contiene el sonido en formato WAV.
		 * \return Devuelve falso si no ha conseguido cargarlo (por ejemplo: ruta incorrecta, formato incorrecto o no hay memoria).
		 */
		bool cargar (string nomSonido="");

		/// Libera la memoria reservada por el sonido.
		/** \return Devuelve falso si no estaba cargado. Si lo ha liberado correctamente, verdadero.
		 */
		bool liberar ();


	private:

		/// Puntero al sonido cargado en memoria.
		Mix_Chunk *sonido;

		/// Nombre (ruta) del sonido.
		string nomSonido;

		/// Indica si está cargado el sonido.
		bool cargado;

		/// Canal donde se reproduce el sonido.
		/** Cuando se reproduce el sonido, se almacena en esta variable el número de canal por el que se reproduce.
		 * Si no se consigue reproducir, esta variable toma valor -1.
		 */
		int channel;

		/// Número de sonidos creados.
		/** El primero debe inicializar el audio con las opciones de audio. El último debe cerrarlo.
		 */
		static int numSonidos;

		/// Frecuencia.
		static const int audioRate = 22050;

		/// Formato de audio.
		static const Uint16 audioFormat = AUDIO_S16SYS;

		/// Número de canáles (estéreo).
		static const int audioChannels = 2;

		/// Tamaño del buffer de audio en memoria.
		static const int audioBuffers = 1024;
};

#endif /* _SONIDO_H */



