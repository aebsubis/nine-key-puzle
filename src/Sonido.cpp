/// Fichero de definición de la clase Sonido.
/** \file sonido.cpp
 */

#include "Sonido.h"

// Inicializamos el número de sonidos.
int Sonido::numSonidos = 0;

// Constructor por defecto.
Sonido::Sonido ()
{
	sonido = NULL;
	nomSonido = "";
	cargado = false;
	channel = -1;
	numSonidos ++;

	// Es el primer sonido; ajustamos los valores del audio.
	if (numSonidos==1)
	{
		if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
		{
			cerr << "ERROR: No se ha podido inicializar el audio: " << Mix_GetError() << endl;
			exit(1);
		}
	}
}

// Constructor sobrecargado.
Sonido::Sonido (string nomSonido)
{
	channel = -1;
	numSonidos ++;
	cargado = true;
	this->nomSonido = nomSonido;

	// Es el primer sonido; ajustamos los valores del audio.
	if (numSonidos==1)
	{
		if (Mix_OpenAudio(audioRate, audioFormat, audioChannels, audioBuffers) != 0)
		{
			cerr << "ERROR: No se ha podido inicializar el audio: " << Mix_GetError() << endl;
			exit(1);
		}
	}

	sonido = Mix_LoadWAV(this->nomSonido.c_str());
	if(sonido == NULL)
	{
		cargado = false;
		cerr << "ERROR: No se pudo cargar el fichero WAV: " << Mix_GetError() << endl;
	}
}

// Destructor.
Sonido::~Sonido ()
{
	liberar();
	cargado = false;
	nomSonido = "";
	numSonidos--;

	// Era el último sonido; cerramos el mezclador de audio.
	if (numSonidos==0)
	{
		Mix_CloseAudio();
	}
}

// Reproduce el sonido.
bool Sonido::reproducir ()
{
	channel = Mix_PlayChannel(-1, sonido, 0);
	if(channel == -1)
	{
		cerr << "ERROR: No se puede reproducir el fichero WAV: " << Mix_GetError() << endl;
		return false;
	}
	return true;
}

// Detiene el sonido.
bool Sonido::detener ()
{
	// pause all sample playback
	Mix_Pause(channel);
	return true;
}

bool Sonido::reproduciendose ()
{
	return Mix_Playing(channel) != 0;
}

// Carga el sonido el memoria.
bool Sonido::cargar (string nomSonido)
{
	liberar();
	cargado = true;

	if (nomSonido!="")
	{
		this->nomSonido = nomSonido;
	}

	sonido = Mix_LoadWAV(this->nomSonido.c_str());
	if(sonido == NULL)
	{
		cargado = false;
		cerr << "ERROR: No se pudo cargar el fichero WAV: " << Mix_GetError() << endl;
	}

	return cargado;
}

// Libera la memoria reservada por el sonido.
bool Sonido::liberar ()
{
	cargado = false;
	if (sonido != NULL)
	{
		Mix_FreeChunk(sonido);
		return true;
	}
	else
	{
		return false;
	}
}

