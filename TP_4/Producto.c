#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "input.h"
#include "ArrayList.h"
#include "Producto.h"


/**
* Carga una lista de productos en lista
*\param lista Arraylist donde se cargaran los productos
*\param archivo Nombre del archivo
*\return [-1] En caso de error al abrir el archivo
*        [0] Si cargó los productos
*/
int CsvAProducto(ArrayList *lista, char *archivo)
{
    int r, contError = 0, contAgregados = 0;
    FILE *fp;
    char aux[500];

    if(lista == NULL)
        return -1;

    fp = fopen(archivo, "r");
    if(fp == NULL)
    {
        printf("\nError al abrir el archivo.\n");
        return -1;
    }



    while(fgets(aux, 500, fp) != NULL && aux[0] != '\n')
    {
        eProducto *prod;
        prod = malloc(sizeof(eProducto));

        if(prod != NULL)
        {
            r = validacionProducto(prod, aux);
            if(r == 0)
            {
                r = lista->add(lista, prod);
                if(r == -1)
                {
                    printf("\nMemoria insuficiente para seguir agregando productos.\n");
                    break;
                }
                contAgregados++;

            }
            else
            {
                contError++;
                free(prod);
            }
        }
    }

    fclose(fp);

    printf("\n%d productos agregados.", contAgregados);
    printf("\n%d productos no agregados.\n", contError);

    return 0;
}

/**
* Valida que el string input contenga los elementos de la estructura
* eProducto separados por comas y los carga en prod
*\param prod Puntero a la estructura donde se cargaran los valores validados
*\param input Cadena de caracteres a validar
*\return [-1] Si hay valores invalidos
*        [0] Si cargo los valores en prod
*
*/
int validacionProducto(eProducto *prod, char *input)
{
    int i;
    eProducto aux;
    char *temp;

    temp = strtok(input, ",");
    if(strlen(temp) > 20)
        return -1;

    for(i=0; i < strlen(temp); i++)
    {
        if(!isdigit(temp[i]))
        {
            return -1;
        }

    }

    strcpy(aux.codBarra, temp);

    temp = strtok(NULL, ",");
    if(strlen(temp) > 60)
        return -1;
    strcpy(aux.nombre, temp);

    temp = strtok(NULL, ",");
    for(i = 0; i < strlen(temp); i++)
    {
        if(!isdigit(temp[i]))
        {
            return -1;
        }

    }

    aux.cantidad = atoi(temp);
    if(aux.cantidad < 0)
        return -1;


    temp = strtok(NULL, "\n");
    for(i = 0; i < strlen(temp); i++)
    {
        if(!isdigit(temp[i]) && temp[i] != '.')
        {
            return -1;
        }
    }
    aux.precio = atof(temp);
    if(aux.precio <  0)
        return -1;


    strcpy(prod->codBarra, aux.codBarra);
    strcpy(prod->nombre, aux.nombre);
    prod->cantidad = aux.cantidad;
    prod->precio = aux.precio;
    return 0;
}

/**
* Establece la cantidad de un producto
*\param prod Puntero al producto a editar
*\param newValue Cantidad a establecer
*\return [-1] En caso de error
*        [0] Si tuvo exito
*
*/
int set_cantidad(eProducto *prod, int newValue)
{
    if(prod != NULL && newValue >= 0)
    {
        prod->cantidad = newValue;
        return 0;
    }
    return -1;
}

/**
* Obtiene el precio de un producto
* \param prod Puntero void al producto
* \return [-1] Si prod es nulo
*         Precio del producto Si prod no es nulo
*
*/
float get_precio(void *prod)
{
    float aux;

    if(prod != NULL)
    {
        aux = ((eProducto *)prod)->precio;
        return aux;
    }

    return -1;
}

/**
* Obtiene la cantidad de un producto
* \param producto Producto a obtener la cantidad
* \return [-1]    Si producto es nulo
*         Entero  Cantidad del producto
*
*/
int get_cant(void *producto)
{
    int aux = -1;
    if(producto != NULL)
    {
        aux = ((eProducto*)producto)->cantidad;
    }
    return aux;
}

/**
* Compara las cantidades de dos productos
* \param prod1 Producto a comparar
* \param prod2 Producto a comparar
* \return [-1] Si la cantidad del primer producto es menor
*         [0]  Si tienen igual cantidad
*         [1]  Si la cantidad del primer producto es mayor a la del segundo
*
*/
int comparar_producto(void *prod1, void *prod2)
{
    if(get_cant(prod1) > get_cant(prod2))
        return 1;


    if(get_cant(prod1) < get_cant(prod2))
        return -1;

    return 0;
}

/**
* Compara el nombre del producto con el nombre pasado
*\param producto Puntero void al producto a comparar
*\param nombre Nombre del producto a comparar
*\return [-1] Si producto o nombre son nulos
*        [0] Si el nombre del producto no es nombre
*        [1] Si el nombre del producto es igual a nombre
*
*/
int contains_name(void *prod, void *name)
{
    int aux = -1;
    if(prod != NULL && name != NULL && strlen(name) != 0)
    {
        aux = 0;
        if(strcmp(((eProducto *)prod)->nombre, ((char *)name)) == 0)
            aux = 1;
    }

    return aux;
}

/**
* Imprime el producto por pantalla
*\param producto Puntero void al producto a imprimir
*\return Void - Imprime el producto por pantalla
*
*/
void imprimir_producto(void *producto)
{
    printf("%-13s %-50s %6d %5.2f\n", ((eProducto*)producto)->codBarra, ((eProducto*)producto)->nombre, ((eProducto*)producto)->cantidad, ((eProducto*)producto)->precio);

}

/**
* Imprime la lista de productos de a 20 productos por vez
* \param listaProductos ArrayList con la lista de productos a imprimir
* \return Void - Imprime por pantalla
*
*/
void imprimir_pagina(ArrayList *listaProductos)
{
    ArrayList *printAux;
    int from = 0, to = 0, i;

    printf("Listado de Productos\n");
    while(to < listaProductos->size)
    {
        to = from + 20;
        if(to > listaProductos->size)
            to = listaProductos->size;
        printAux = listaProductos->subList(listaProductos, from, to);
        printf("%-13s %-50s %6s %6s\n", "Cod Barra", "Nombre", "Cant", "Precio");
        for(i = 0; i < printAux->size; i++)
        {
            imprimir_producto(printAux->get(printAux,i));
        }
        system("pause");
        system("cls");
        from += 20;
        printAux->clear(printAux);
    }

    printAux->remove(printAux);

}

/**
* Imprime una lista de productos con precio mayor a 100 ordenada por cantidad
* \param listaProductos ArrayList con la lista de productos a imprimir
* \return Void - Imprime por pantalla
*
*/
void imprimir_mayores(ArrayList *listaProductos)
{
    ArrayList *printAux = NULL;
    int i;

    if(listaProductos != NULL)
        printAux = listaProductos->clone(listaProductos);

    if(printAux != NULL)
    {

        for(i = 0; i < printAux->size; i++)
        {
            if(get_precio(printAux->get(printAux,i)) < 100)
            {
                printAux->remove(printAux, i);
                i--;
            }
        }
        printAux->sort(printAux, comparar_producto, 0);
        system("cls");
        printf("Productos con precio mayor a 100\n");
        printf("%-13s %-50s %6s %6s\n", "Cod Barra", "Nombre", "Cant", "Precio");
        for(i = 0; i < printAux->size; i++)
        {
            imprimir_producto(printAux->get(printAux, i));
        }
        system("pause");
        printAux->deleteArrayList(printAux);
    }
    else
    {
        printf("\nError al imprimir los productos.\n");
        system("pause");
    }

}

/**
* Genera un archivo de texto separado por comas con los productos de la lista
* \param productos ArrayList de productos
* \param archivo Nombre del archivo a generar
* \return [-1] Si el archivo ya existe
*         [0] Si crea el archivo
*
*/
int archivo_productos(ArrayList *productos, char *archivo)
{
    FILE *fp = NULL;
    eProducto *aux;
    int i;
    fp = fopen(archivo,"r");
    if(fp == NULL && productos != NULL)
    {
        fp = fopen(archivo,"w");
        for(i=0; i < productos->size; i++)
        {
            aux = (eProducto *) productos->get(productos, i);
            fprintf(fp,"%s,%s,%d,%.2f\n", aux->codBarra, aux->nombre, aux->cantidad, aux->precio);
        }
        fclose(fp);
        return 0;
    }
    fclose(fp);
    return -1;
}
