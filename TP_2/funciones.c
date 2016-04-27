#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <windows.h>
#include <conio.h>
#include "input.h"
#include "funciones.h"

/**
 * \brief Obtiene el primer indice libre del array.
 * \param lista el array se pasa como parametro.
 * \param tam el tamaño del array que se paso como parametro
 * \return el primer indice disponible
 */
int obtenerEspacioLibre(EPersona lista[],int tam)
{
    int i;
    for(i=0;i<tam;i++)
    {
        if(lista[i].estado == 0)
            return i;
    }
    return -1;
}


/**
 * \brief Obtiene el indice que coincide con el dni pasado por parametro.
 * \param lista el array se pasa como parametro.
 * \param size tamaño del array pasado anteriormente
 * \param dni el dni a ser buscado en el array.
 * \return el indice en donde se encuentra el elemento que coincide con el parametro dni o [-1] si no lo encuentra
 */
int buscarPorDni(EPersona lista[],int size, int dni)
{
    int i;
    for(i=0;i<size;i++)
    {
        if(lista[i].dni == dni)
        {
            return i;
        }
    }
    printf("\nDNI no encontrado");
    return -1;
}


/**
*\brief Ordena la estructura por el nombre de forma ascendente(de A a Z)
*\param lista Array de la estructura EPersona pasado como parametro
*\param size Tamaño del array lista
*
*\return Void no devuelve valor
*/
void ordenarPorNombre(EPersona lista[],int size)
{
    int i,j, max;
    EPersona aux;
    max = obtenerEspacioLibre(lista,size);
    for(i=0;i<max-1;i++)
    {
        for(j=i+1;j<max;j++)
        {
            if(strcmp(lista[i].nombre,lista[j].nombre) > 0)
            {
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}

/**
*\brief Agrega una persona al array pasado como parametro
*\param lista Array pasado como parametro
*\param size Tamaño del array lista
*
*\return devuelve [1] si logro dar de alta una persona, si no, devuelve [-1]
*/
int altas(EPersona lista[],int size)
{
    int i,resp;

    i = obtenerEspacioLibre(lista,size);
    if(i == -1)
    {
        printf("Error. Lista llena, modifique una persona existente.");
        return -1;
    }

    resp = getString(lista[i].nombre,"Ingrese el nombre: ","\nError. El largo debe estar entre 1 y 50",1,50);
    if(resp == -1)
        return -1;

    resp = getInt(&lista[i].edad,"Ingrese la edad: ","\nError.La edad debe estar entre 0 y 150",0,150);
    if(resp == -1)
        return -1;

    resp = getLongInt(&lista[i].dni,"Ingrese el dni (sin puntos): ","Error. DNI incorrecto",1000000,99999999);
    if(resp == -1)
        return -1;
    lista[i].estado = 1;
    return 0;
}


/**
*\brief Imprime por pantalla la lista de empleados
*\param lista Array de la estructura EPersona pasado como puntero
*\param size Tamaño del array lista
*
*\return No devuelve ningún valor
*/
void mostrarLista(EPersona *lista,int size)
{
    int i;
    printf("%-50s %10s %5s\n","Nombre","DNI","Edad");
    for(i=0;i<size;i++)
    {
        if(lista[i].estado == 1)
            printf("%-50s %10ld %5d\n",lista[i].nombre,lista[i].dni,lista[i].edad);
    }
}

/**
*\brief Busca a la persona por DNI y borra los datos asociados a la estructura
*\param lista Array de la estructura EPersona pasado como puntero
*\param size Tamaño del array lista
*
*\return [0] en caso de borrar exitosamente la persona, si no, devuelve [-1]
*/
int borrarPersona(EPersona *lista,int size)
{
    int i,dni;
    char resp='N';
    printf("Ingrese el dni de la persona a borrar: ");
    scanf("%d",&dni);
    i = buscarPorDni(lista,size,dni);
    if(i == -1)
        return -1;
    else
    {
        system("cls");
        printf("Nombre: %s", lista[i].nombre);
        printf("\nDNI: %ld", lista[i].dni);
        printf("\nEdad: %d", lista[i].edad);
        getSN(&resp,"\nEsta seguro que desea eliminar? S/N","\nError. Opcion no valida");
        if(resp == 'S')
        {
            strcpy(lista[i].nombre,"\0");
            lista[i].edad=0;
            lista[i].dni=0;
            lista[i].estado = 0;
            return 0;
        }
        return 1;
    }

}



/**
*\brief Imprime por pantalla un grafico segun las edades (menor 18, 18 a 35 y mayor 18)
*\param lista Array de estructura EPersona pasado como parametro
*\param size Tamaño del array lista
*\return No devuelve ningún parametro, imprime por pantalla el grafico de edades
*
*/
void graficoEdades(EPersona lista[],int size)
{
    int i,contMenores=0,contHastaTC=0,contMasTC=0,max;
    for(i=0;i<size;i++)
    {
        if(lista[i].estado != 0 && lista[i].edad <= 18)
        {
            contMenores++;
        }
        if(lista[i].estado != 0 && lista[i].edad > 18 && lista[i].edad <= 35)
        {
            contHastaTC++;
        }
        if(lista[i].estado != 0 && lista[i].edad >35)
        {
            contMasTC++;
        }
    }

    //Calculo que cantidad de persona (<18, 18 a 35,>35) es la mayor
    if(contMenores > contHastaTC && contMenores > contMasTC)
    {
        max = contMenores;
    }
    else if(contHastaTC > contMasTC)
        max = contHastaTC;
    else
        max = contMasTC;

    //Imprimo un * o un espacio segun corresponda
    for(i=max;i>0;i--)
    {
       if(i <= contMenores)
       {
           printf("  *");
       }

       if(i <= contHastaTC)
       {
           printf("\t  *");
       }
       else
       {
           printf("\t");
       }

       if(i <= contMasTC)
       {
           printf("\t *");
       }

       printf("\n");
    }
    printf(" <18 \t18-35\t>35\n");

}


