#include "Directorio.h"

// Constructor por defecto.
Directorio::Directorio(string nombreDirectorio)
{
	this->nombreDirectorio = nombreDirectorio;
	directorioLeido = false;

	#ifdef WIN32

	WIN32_FIND_DATA findFileData;
	HANDLE hFind;

	string nombreDirectorioAux = nombreDirectorio + "/*";
	hFind = FindFirstFile(nombreDirectorioAux.c_str(), &findFileData);

	if (hFind != INVALID_HANDLE_VALUE)
	{
		int contador = 0;
		do
		{
			string nombre = string(findFileData.cFileName);
			string ruta = nombreDirectorio + "/" + nombre;
			ifstream fichero;
			fichero.open(ruta.c_str(), ios::in);
			if (fichero.is_open())
			{
				try
				{
					string leoAlgo;
					fichero >> leoAlgo;
					nombreFicheros.push_back(nombre);
					rutaFicheros.push_back(ruta);
				}
				catch(...)
				{
					nombreDirectorios.push_back(nombre);
					rutaDirectorios.push_back(ruta);
				}
				fichero.close();
			}
			else
			{
				nombreDirectorios.push_back(nombre);
				rutaDirectorios.push_back(ruta);
			}
		}
		while (FindNextFile(hFind, &findFileData) != 0);
		directorioLeido = true;
	}

	#else

	DIR* dp = NULL;
	struct dirent* dirp = NULL;
	// Abrimos el directorio.
    if ((dp  = opendir(nombreDirectorio.c_str())) != NULL)
    {
		// Leemos todas las entradas.
		while ((dirp = readdir(dp)) != NULL)
		{
			string nombre = string(dirp->d_name);
			string ruta = nombreDirectorio + "/" + nombre;
			ifstream fichero;
			fichero.open(ruta.c_str(), ios::in);

			if (fichero.is_open())
			{
				// Si podemos leer, es un fichero. Si no, es un directorio.
		    	try
		    	{
		    		string leoAlgo;
					fichero >> leoAlgo;
					nombreFicheros.push_back(nombre);
					rutaFicheros.push_back(ruta);
				}
				catch(...)
				{
			    	nombreDirectorios.push_back(nombre);
					rutaDirectorios.push_back(ruta);
				}
				fichero.close();
			}
		}

		// Cerramos el directorio.
		closedir(dp);

		directorioLeido = true;
	}

	#endif
}

// Constructor de copia.
Directorio::Directorio(const Directorio& directorio)
{
	*this = directorio;
}

// Destructor.
Directorio::~Directorio()
{
	nombreDirectorio = "";
	directorioLeido = false;
	nombreFicheros.clear();
	nombreDirectorios.clear();
	rutaFicheros.clear();
	rutaDirectorios.clear();
}

// Operador de asignación.
Directorio& Directorio::operator=(const Directorio& directorio)
{
	if (this != &directorio)
	{
		nombreDirectorio = directorio.nombreDirectorio;
		directorioLeido = directorio.directorioLeido;
		nombreFicheros = directorio.nombreFicheros;
		nombreDirectorios = directorio.nombreDirectorios;
		rutaFicheros = directorio.rutaFicheros;
		rutaDirectorios = directorio.rutaDirectorios;
	}
	return *this;
}

// Obtiene los nombres de los ficheros que hay dentro del directorio.
list<string> Directorio::getNombreFicheros() const
{
	return nombreFicheros;
}

// Obtiene los nombres de los directorios que hay dentro del directorio.
list<string> Directorio::getNombreDirectorios() const
{
	return nombreDirectorios;
}

// Obtiene las rutas de los ficheros que hay dentro del directorio.
list<string> Directorio::getRutaFicheros() const
{
	return rutaFicheros;
}

// Obtiene las rutas de los directorios que hay dentro del directorio.
list<string> Directorio::getRutaDirectorios() const
{
	return rutaDirectorios;
}

// Obtiene el nombre del directorio creado.
string Directorio::getNombreDirectorio() const
{
	return nombreDirectorio;
}

// Comprueba si el directorio se ha leido correctamente.
bool Directorio::isLeido() const
{
	return directorioLeido;
}


