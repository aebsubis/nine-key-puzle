#include <iostream>
#include <list>
#include <string>
#include <fstream>
#ifdef WIN32
#include <windows.h>
#else
#include <dirent.h>
#endif
using namespace std;

/// Clase que representa un directorio.
/** Permite obtener los elementos contenidos en dicho directorio (que pueden ser ficheros o más directorios).
 * Al crearse el objeto debe indicarse la ruta del directorio e internamente obtendrá todas las entradas que contiene.
 * Si todo ha ido bien, isLeido() devolverá verdadero y podrán obtener los ficheros con getNombreFicheros() o getNombreDirectorios().
 *
 * Ejemplo de uso:
 * @verbatim
 *        Directorio directorio("/home");
 *        if (directorio.isLeido())
 *        {
 *             list<string> nombreFicheros = directorio.getNombreFicheros();
 *             list<string>::iterator pos = nombreFicheros.begin();
 *             while (pos != nombreFicheros.end())
 *             {
 *                  cout << (*pos) << endl;
 *        	        pos++;
 *             }
 *        }
 * @endverbatim
 */
class Directorio
{
	public:

		/// Constructor por defecto.
		/** Recibe el nombre del directorio que se intentará leer.
		 * @param nombreDirectorio Cadena de caracteres que indica el nombre del directorio que va a ser procesador.
		 */
		Directorio(string nombreDirectorio);

		/// Constructor de copia.
		/** Dado un objeto de la misma clase ya instanciado, crea otro con los mismos atributos.
		 * @param directorio Directorio original que va a ser copiado.
		 */
		Directorio(const Directorio& directorio);

		/// Destructor.
		~Directorio();

		/// Operador de asignación.
		/** Asigna un objeto a otro objeto ya creado, quedando una copia idéntica.
		 * @param directorio Directorio original que va a ser asignado.
		 * @return Devuelve una copia por referencia del objeto que invocó el método para concatenar asignaciones.
		 */
		Directorio& operator=(const Directorio& directorio);

		/// Obtiene los nombres de los ficheros que hay dentro del directorio.
		/** @return Devuelve una lista de cadenas de caracteres con los nombres de los ficheros. */
		list<string> getNombreFicheros() const;

		/// Obtiene los nombres de los directorios que hay dentro del directorio.
		/** @return Devuelve una lista de cadenas de caracteres con los nombres de los directorios. */
		list<string> getNombreDirectorios() const;

		/// Obtiene las rutas de los ficheros que hay dentro del directorio.
		/** @return Devuelve una lista de cadenas de caracteres con las rutas de los ficheros. */
		list<string> getRutaFicheros() const;

		/// Obtiene las rutas de los directorios que hay dentro del directorio.
		/** @return Devuelve una lista de cadenas de caracteres con las rutas de los directorios. */
		list<string> getRutaDirectorios() const;

		/// Obtiene el nombre del directorio creado.
		/** Éste es el nombre del directorio que se indicó en el constructor.
		 * @return Devuelve una cadena de caracteres con el nombre del directorio.
		 */
		string getNombreDirectorio() const;

		/// Comprueba si el directorio se ha leido correctamente.
		/** Al crear el objeto, se lee el directorio extrayendo cada una de sus entradas y se compara
		 * si esa entrada es un fichero o un directorio (que posteriormente pueden obtenerse con getNombreFicheros()
		 * o getNombreDirectorios(). Si falla la lectura del directorio, este método devolverá falso.
		 * @return Devuelve verdadero si se ha creado y leído el directorio correctamente.
		 */
		bool isLeido() const;


	private:

		/// Nombre (y ruta) del directorio
		string nombreDirectorio;

		/// Contiene el estado del directorio: verdadero si fue leido correctamente; falso si no se puedo abrir y leer.
		bool directorioLeido;

		/// Lista de cadenas de caracteres con los nombres de los ficheros que hay dentro del directorio.
		list<string> nombreFicheros;

		/// Lista de cadenas de caracteres con los nombres de los directorios que hay dentro del directorio.
		list<string> nombreDirectorios;
		
		/// Lista de cadenas de caracteres con las rutas de los ficheros que hay dentro del directorio.
		list<string> rutaFicheros;

		/// Lista de cadenas de caracteres con las rutas de los directorios que hay dentro del directorio.
		list<string> rutaDirectorios;

};

