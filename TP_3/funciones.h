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

int crearPelicula(EMovie **movie);
void mostrar(EMovie movie);
int buscarPelicula(EMovie *movie, char searchMovie[]);
int loadMovies(EMovie **movie, char *fileName);
int getLista(EMovie *movie, int tam);
/**
 *  Agrega una pelicula al archivo binario
 *  @param movie puntero a las estructuras a ser agregadas al archivo
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
 *  @param nombre el nombre para el archivo.
 */
int generarPagina(EMovie lista[], int listSize, char nombre[]);

#endif // FUNCIONES_H_INCLUDED
