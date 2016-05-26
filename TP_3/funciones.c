#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "funciones.h"

/*typedef struct{
    char titulo[20];
    char genero[20];
    int duracion;
    char descripcion[50];
    int puntaje;
    char linkImagen[50];
}EMovie;*/


int crearPelicula(EMovie **movie)
{
    char auxTitulo[20], auxGenero[20], auxDescripcion[500], auxLink[200], seguir = 'S';
    int auxDuracion, auxPuntaje, i = 0, tam = 1, flagAdd = 0;
    EMovie *temp, auxMovie;

    if(movie == NULL)
    {
        printf("Error. Puntero invalido.");
        return -1;
    }

    temp = (EMovie *)malloc(sizeof(EMovie) * tam);

    while(seguir == 'S')
    {

        system("cls");
        if(getString(auxTitulo, "Ingrese el titulo: ", "\nError. Titulo invalido.\n", 1, 20) == -1)
            goto END;

        if(buscarPelicula(&auxMovie, auxTitulo) != -1)
        {
            printf("\nLa pelicula ya existe.\n");
            goto END;
        }

        if(getString(auxGenero, "Ingrese el genero: ", "\nError. Genero invalido (max 20 caracteres).\n", 1, 20) == -1)
            goto END;

        if(getInt(&auxDuracion, "Ingrese la duracion: ", "\nError. Duracion invalida.\n", 1, 32000) == -1)
            goto END;

        if(getString(auxDescripcion, "Ingrese la descripcion: ", "\nError. Descripcion Invalida (max 500 caracteres).\n", 1, 500) == -1)
            goto END;

        if(getInt(&auxPuntaje, "Ingrese el puntaje (0 a 100): ", "\nError.Puntaje invalido (0 a 100).\n", 0, 100) == -1)
            goto END;

        if(getString(auxLink, "Ingrese el link de la imagen: ", "\nError. Link incorrecto.\n", 0, 200) == -1)
            goto END;


        if(i >= tam)
        {
            tam++;
            temp = (EMovie *)realloc(temp, sizeof(EMovie)* tam);
            if(temp == NULL)
            {
                printf("\nMemoria insuficiente.\n");
                return -1;
            }
        }

        strcpy((temp+i)->titulo, auxTitulo);
        strcpy((temp+i)->genero, auxGenero);
        (temp+i)->duracion = auxDuracion;
        strcpy((temp+i)->descripcion, auxDescripcion);
        (temp+i)->puntaje = auxPuntaje;
        strcpy((temp+i)->linkImagen, auxLink);
        flagAdd = 1;
        i++;

        END:
            seguir = getSN("Desea agregar otra pelicula? ", "\nError. Ingrese S o N. ");
    }

    if(flagAdd == 1)
    {
        *movie = temp;
        return tam;
    }
    else
    {
        free(temp);
        return -1;
    }


}

int agregarPelicula(EMovie *movie, int tam)
{
    FILE *fp;
    int i;

    if((fp = fopen("movies.bin", "ab+")) == NULL)
    {
        printf("\nError. No se puede abrir el archivo.\n");
        return -1;
    }

    for(i = 0; i < tam; i++)
    {
        if(fwrite((movie + i), sizeof(EMovie), 1, fp) != 1)
        {
            printf("\nError al escribir el archivo\n");
            return -1;
        }
    }
    fclose(fp);
    return 0;
}



void mostrar(EMovie movie)
{
    printf("Titulo: %s", movie.titulo);
    printf("\nGenero: %s", movie.genero);
    printf("\nDuracion: %d", movie.duracion);
    printf("\nDescripcion: %s", movie.descripcion);
    printf("\nPuntaje: %d", movie.puntaje);
    printf("\nLink Imagen: %s\n", movie.linkImagen);
}

int buscarPelicula(EMovie *movie, char searchMovie[])
{
    FILE *fp;
    int index = 0, flagFound = 0;

    if((fp = fopen("movies.bin", "rb")) == NULL)
    {
        return -1;
    }

    while(fread(movie, sizeof(EMovie), 1, fp) != 0)
    {
        if(strcmp(movie->titulo, searchMovie) == 0)
        {
            flagFound = 1;
            break;
        }
        index++;
    }

    if(flagFound == 0)
    {
        fclose(fp);
        return -1;
    }
    else
    {
        fclose(fp);
        return index;
    }

}

int borrarPelicula(EMovie movie)
{
    FILE *pRet, *pSave;
    EMovie *temp;
    char resp;
    int tam = 1, i=0, j;

    mostrar(movie);
    resp = getSN("Esta seguro que desea eliminar (S/N)? ","\nError. Debe ingresar S o N: ");
    if(resp == 'N')
    {
        return -1;
    }

    if((pRet = fopen("movies.bin", "rb")) == NULL)
    {
        printf("\nNo se pudo abrir el archivo\n");
        return -1;
    }

    if((temp = (EMovie *)malloc(sizeof(EMovie) * tam)) == NULL)
    {
        printf("\nError. Memoria insuficiente.\n");
        fclose(pRet);
        return -1;
    }

    while(fread(temp+i, sizeof(EMovie), 1, pRet) != 0)
    {
        i++;
        if(i >= tam)
        {
            tam++;
            if((temp = (EMovie *)realloc(temp, sizeof(EMovie) * tam)) == NULL)
            {
                printf("\nError. Memoria insuficiente.\n");
                free(temp);
                fclose(pRet);
                return -1;
            }
        }
    }
    fclose(pRet);

    if((pSave = fopen("temp.bin", "wb")) == NULL)
    {
        printf("\nError al crear el archivo.\n");
        free(temp);
        return -1;
    }

    for(j = 0; j < i; j++)
    {
        if(strcmp((temp + j)->titulo, movie.titulo) != 0)
        {
            fwrite((temp + j), sizeof(EMovie), 1, pSave);
        }
    }

    fclose(pSave);
    free(temp);
    remove("movies.bin");
    rename("temp.bin", "movies.bin");

    return 0;
}


int loadMovies(EMovie **movie, char *fileName)
{
    FILE *fp;
    EMovie *temp;
    int tam = 1, i = 0;

    if((fp = fopen(fileName, "rb")) == NULL)
    {
        printf("\nNo se pudo abrir el archivo\n");
        return -1;
    }

    if((temp = (EMovie *)malloc(sizeof(EMovie) * tam)) == NULL)
    {
        printf("\nError. Memoria insuficiente.\n");
        fclose(fp);
        return -1;
    }

    while(fread(temp+i, sizeof(EMovie), 1, fp) != 0)
    {
        i++;
        if(i >= tam)
        {
            tam++;
            if((temp = (EMovie *)realloc(temp, sizeof(EMovie) * tam)) == NULL)
            {
                printf("\nError. Memoria insuficiente.\n");
                free(temp);
                fclose(fp);
                return -1;
            }
        }
    }
    tam--;
    temp = (EMovie *)realloc(temp, sizeof(EMovie) * tam);
    fclose(fp);
    *movie = temp;
    return tam;
}

int getLista(EMovie *movie, int tam)
{
    int i;
    char opcion = 'N';

    system("cls");
    printf("Se generara el archivo con las siguientes peliculas: \n");
    for(i=0; i < tam; i++)
    {
        printf("%d.%s\n", i+1, movie[i].titulo);
    }
    opcion = getSN("\nDesea continuar (S/N)? ","Error. Ingrese S o N: ");
    if(opcion == 'N')
        return -1;
    else
        return tam;

}


int generarPagina(EMovie lista[], int listSize, char nombre[])
{
    FILE *fp;
    int i;

    if((fp = fopen("temp.txt","w")) == NULL)
    {
        printf("Error al generar el archivo\n");
        return -1;
    }

    fprintf(fp,"<!DOCTYPE html>\n"
    "<!-- Template by Quackit.com -->\n"
    "<html lang='en'>\n"
    "<head>\n"
    "    <meta charset='utf-8'>\n"
    "    <meta http-equiv='X-UA-Compatible' content='IE=edge'>\n"
    "    <meta name='viewport' content='width=device-width, initial-scale=1'>\n"
    "    <!-- The above 3 meta tags *must* come first in the head; any other head content must come *after* these tags -->\n"
    "    <title>Lista peliculas</title>\n"
    "    <!-- Bootstrap Core CSS -->\n"
    "    <link href='css/bootstrap.min.css' rel='stylesheet'>\n"
    "    <!-- Custom CSS: You can use this stylesheet to override any Bootstrap styles and/or apply your own styles -->\n"
    "    <link href='css/custom.css' rel='stylesheet'>\n"
    "    <!-- HTML5 Shim and Respond.js IE8 support of HTML5 elements and media queries -->\n"
    "    <!-- WARNING: Respond.js doesn't work if you view the page via file:// -->\n"
    "    <!--[if lt IE 9]>\n"
    "        <script src='https://oss.maxcdn.com/libs/html5shiv/3.7.0/html5shiv.js'></script>\n"
    "        <script src='https://oss.maxcdn.com/libs/respond.js/1.4.2/respond.min.js'></script>\n"
    "    <![endif]-->\n"
    "</head>\n"
    "<body>\n"
    "    <div class='container'>\n"
    "        <div class='row'>\n");

    for(i=0; i < listSize; i++)
    {
        fprintf(fp, "<article class='col-md-4 article-intro'>\n"
        "                <a href='#'>\n"
        "                    <img class='img-responsive img-rounded' src='%s' alt=''>\n"
        "                </a>\n"
        "                <h3>\n"
        "                    <a href='#'>%s</a>\n"
        "                </h3>\n"
        "				<ul>\n"
        "					<li>G&eacutenero:%s</li>\n"
        "					<li>Puntaje:%d</li>\n"
        "					<li>Duraci&oacuten:%d</li>\n"
        "				</ul>\n"
        "                <p>%s</p>\n"
        "            </article>\n\n", lista[i].linkImagen, lista[i].titulo, lista[i].genero, lista[i].puntaje, lista[i].duracion, lista[i].descripcion);
    }

    fprintf(fp,"       </div>\n"
    "        <!-- /.row -->\n"
    "    </div>\n"
    "    <!-- /.container -->\n"
    "    <!-- jQuery -->\n"
    "    <script src='js/jquery-1.11.3.min.js'></script>\n"
    "    <!-- Bootstrap Core JavaScript -->\n"
    "    <script src='js/bootstrap.min.js'></script>\n"
    "	<!-- IE10 viewport bug workaround -->\n"
    "	<script src='js/ie10-viewport-bug-workaround.js'></script>\n"
    "	<!-- Placeholder Images -->\n"
    "	<script src='js/holder.min.js'></script>\n"
    "</body>\n"
    "</html>\n");

    fclose(fp);
    rename("temp.txt", nombre);
    return 0;
}
