#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funciones.h"
#include "input.h"



int main()
{
    char seguir='s', auxMovie[20], auxNombre[50];
    int opcion=0, aux;
    EMovie *movie;

    while(seguir=='s')
    {
        system("cls");
        printf("1- Agregar pelicula\n");
        printf("2- Borrar pelicula\n");
        printf("3- Generar pagina web\n");
        printf("4- Salir\n");
        printf("Opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                system("cls");

                if((aux = crearPelicula(&movie)) == -1)
                {
                    printf("\nLa pelicula no pudo ser creada\n");
                    system("pause");
                    break;
                }

                if(agregarPelicula(movie, aux) == -1)
                {
                    printf("\nLa pelicula no fue agregada\n");
                    free(movie);
                    system("pause");
                    break;
                }

                printf("\nPeliculas agregadas con exito.\n");
                system("pause");
                break;

            case 2:
                system("cls");

                if(getString(auxMovie, "Ingrese la pelicula que desea eliminar: ", "\nError. Titulo invalido (max 20 caracteres).\n", 1, 20) == -1)
                {
                    printf("\nLa pelicula no fue eliminada.\n");
                    system("pause");
                    break;
                }

                movie = (EMovie *)malloc(sizeof(EMovie));
                if(movie == NULL)
                {
                    printf("\nMemoria insuficiente.\n");
                    system("pause");
                    break;
                }

                if(buscarPelicula(movie, auxMovie) == -1)
                {
                    printf("\nNo se encontro la pelicula.\n");
                    system("pause");
                    free(movie);
                    break;
                }


                if(borrarPelicula(*movie) == -1)
                {
                    printf("\nLa pelicula no fue eliminada.\n");
                    free(movie);
                    system("pause");
                    break;
                }



                printf("\nPelicula eliminada con exito.\n");
                free(movie);
                system("pause");
                break;

            case 3:
                if(getString(auxNombre, "Ingrese el nombre del archivo (Ej: index.html): ","\nError. Nombre invalido.\n", 1, 40) == -1)
                {
                    system("pause");
                    break;
                }

                if((aux = loadMovies(&movie, "movies.bin")) == -1)
                {
                    printf("\nError. No se pudo cargar el archivo.\n");
                    system("pause");
                    break;
                }

                if( getLista(movie, aux) == -1)
                {
                    printf("\nLa pagina no fue generada.\n");
                    system("pause");
                    free(movie);
                    break;
                }


                if((generarPagina(movie, aux, auxNombre)) == -1)
                {
                    printf("\nError.No se pudo generar el archivo.\n");
                    free(movie);
                    system("pause");
                    break;
                }

                printf("\nArchivo generado con exito.\n");
                free(movie);
                system("pause");
                break;

            case 4:
                seguir = 'n';
                break;

            default:
                printf("\nOpcion invalida. Reingrese.\n");
                system("pause");
                break;
        }
    }

    return 0;
}
