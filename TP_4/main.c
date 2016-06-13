#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "input.h"
#include "ArrayList.h"
#include "Producto.h"

int main()
{
    char salir = 'N', aux[60];
    int r, cantAux;
    ArrayList *inventario;
    eProducto *producto = NULL;

    inventario = al_newArrayList();

    while(salir != 'S')
    {
        system("cls");
        switch(menu())
        {
        case 1:
            system("cls");
            if(!inventario->isEmpty(inventario))
            {
                printf("Los productos ya fueron agregados.\n");
                system("pause");
                break;
            }
            if(inventario != NULL)
            {
                getString(aux, "Ingrese el nombre del archivo csv: ", "\nError. Archivo invalido.\n", 1, 30);
                r = CsvAProducto(inventario, aux);
                if(r != 0)
                {
                    printf("\nProductos no agregados.\n");
                    system("pause");
                    break;
                }
                system("pause");
                break;
            }
            printf("\nError.Memoria insuficiente.\n");
            system("pause");
            break;

        case 2:
            system("cls");
            if(inventario->isEmpty(inventario))
            {
                printf("Debe cargar los productos primero.\n");
                system("pause");
                break;
            }
            getString(aux, "Ingrese el nombre del producto: ", "\nError. Nombre invalido.\n", 1, 60);
            r = inventario->containsElement(inventario, aux, contains_name);
            if(r != -1)
            {
                producto = (eProducto*)inventario->get(inventario, r);
                imprimir_producto(producto);
                if(getSN("Desea modificar el producto (S/N)?","\nError.Ingrese S o N: ") == 'S')
                {
                    system("cls");
                    getInt(&cantAux, "Ingrese la nueva cantidad: ", "\nError. Cantidad invalida.\n", 0, 32767);
                    r = set_cantidad(producto, cantAux);
                    if(r != -1)
                    {
                        printf("\nProducto modificado con exito.\n");
                        system("pause");
                        break;
                    }
                }
                printf("\nEl producto no fue modificado.\n");
                system("pause");
            }

            break;
        case 3:
            system("cls");
            if(inventario->isEmpty(inventario))
            {
                printf("Debe cargar los productos primero.\n");
                system("pause");
                break;
            }

            getString(aux, "Ingrese el nombre del producto: ", "\nError. Nombre invalido.\n", 1, 60);
            r = inventario->containsElement(inventario, aux, contains_name);
            if(r != -1)
            {
                producto = (eProducto*)inventario->pop(inventario, r);
                imprimir_producto(producto);
                if(getSN("Desea eliminar (S/N)? ","\nError. Ingrese S o N: ") == 'S')
                {
                    free(producto);
                    printf("\nProducto eliminado con exito.\n");
                }
                else
                {
                    inventario->push(inventario, r, producto);
                    printf("\nEl producto no fue eliminado.\n");
                }
                system("pause");
                break;
            }

            printf("\nProducto no encontrado.\n");
            system("pause");
            break;

        case 4:
            system("cls");
            if(inventario->isEmpty(inventario))
            {
                printf("Debe cargar los productos primero.\n");
                system("pause");
                break;
            }
            imprimir_pagina(inventario);
            imprimir_mayores(inventario);
            break;

        case 5:
            system("cls");
            if(inventario->isEmpty(inventario))
            {
                printf("Debe cargar los productos primero.\n");
                system("pause");
                break;
            }
            getString(aux, "Ingrese el nombre del archivo: ","Error. Nombre invalido", 1, 60);
            r = archivo_productos(inventario, aux);
            if(r == -1)
                printf("\nEl archivo ya existe.\n");
            else
                printf("\nArchivo generado con exito.\n");

            system("pause");
            break;

        case 6:
            salir = 'S';
            destructor(inventario);
            inventario->deleteArrayList(inventario);
            break;

        default:
            system("cls");
            printf("\nOpcion invalida. Reingrese.\n");
            system("pause");
            break;
        }
    }

    return 0;
}
