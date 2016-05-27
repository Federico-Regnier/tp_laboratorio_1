#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct{
    char titulo[20];
    char genero[20];
    unsigned int duracion;
    char descripcion[500];
    int puntaje;
    char linkImagen[200];
}EMovie;

/**
* Crea asignandole memoria un o varios elementos de la estructura pelicula
* \param movie puntero al puntero donde sera guardada la/s peliculas a agregar
* \return -1 si no logro crear la o las peliculas o 1 si termino con exito
*
*/
int crearPelicula(EMovie **movie);

/**
* Imprime por pantalla los elementos de movie
* \param movie estructura a ser impresa
* \return no devuelve ningun valor
*
*/
void mostrar(EMovie movie);

/**
* Busca la pelicula pasada en el archivo movies.bin y la carga en memoria en caso de encontrarla
* \param movie puntero a la direccion de memoria donde se cargara la pelicula en caso de ser encontrada
* \param searchMovie titulo de la pelicula que va a ser buscada en el archivo
* \return retorna el indice en el que se encuentra la pelicula dentro del archivo o -1 si no logro encontrarla
*
*/
int buscarPelicula(EMovie *movie, char searchMovie[]);

/**
* Carga las estructuras que contenga el archivo fileName
* \param movie puntero al puntero que apuntara a las estructuras cargadas
* \param fileName nombre del archivo de donde se cargaran las estructuras
* \return Si logro cargar al menos una devuelve la cantidad cargada, si no retorna -1
*
*/
int loadMovies(EMovie **movie, char *fileName);

/**
* Obtiene una lista (titulo) de las peliculas a ser cargadas, las imprime y espera el input del usuario
* \param movie puntero al array de estructuras a cargar
* \param tam tamaño del array de estructuras
* \return tamaño del array si se quiere generar la pagina, si no retorna -1
*
*/
int getLista(EMovie *movie, int tam);


/**
 *  Agrega una pelicula al archivo binario
 *  @param movie puntero a las estructuras a ser agregadas al archivo
 *  @param tam tamaño del array de estructuras a cargar
 *  @return retorna -1 si no se pudo agregar la pelicula y 0 si pudo agregarla
 */
int agregarPelicula(EMovie *movie, int tam);

/**
 *  Borra una pelicula del archivo binario
 *  @param movie la estructura a ser eliminada al archivo
 *  @return retorna 0 si se pudo eliminar la película y -1 si no.
 */
int borrarPelicula(EMovie movie);

/**
 *  Genera un archivo html a partir de las peliculas cargadas en el archivo binario.
 *  @param lista la lista de peliculas a ser agregadas en el archivo.
 *  @param listSize tamaño de la lista a ser agregada en el archivo
 *  @param nombre el nombre para el archivo.
 */
int generarPagina(EMovie lista[], int listSize, char nombre[]);

#endif // FUNCIONES_H_INCLUDED
