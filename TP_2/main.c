#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "funciones.h"
#include "input.h"
#define TAM 20 //tamaño del array de personas
int main()
{
    char salir='n';
    int opcion=0,resp,i;
    EPersona pers[TAM];

    for(i=0;i<TAM;i++)
    {
        pers[i].estado=0;
    }

    while(salir !='S')
    {
        system("cls");
        printf("Menu de Opciones\n");
        printf("1- Agregar persona\n");
        printf("2- Borrar persona\n");
        printf("3- Imprimir lista ordenada por  nombre\n");
        printf("4- Imprimir grafico de edades\n\n");
        printf("5- Salir\n");
        printf("Elija una opcion: ");
        scanf("%d",&opcion);

        switch(opcion)
        {
            case 1:
                system("cls");
                resp = altas(pers,TAM);
                if(resp == 0)
                {
                    printf("\nPersona agregada con exito\n");
                    system("pause");
                }
                else
                {
                    printf("\nPersona no agregada. Intentelo nuevamente.\n");
                    system("pause");
                }
                break;

            case 2:
                system("cls");
                resp = borrarPersona(pers,TAM);
                if(resp == 0)
                {
                    printf("\nPersona borrada con exito\n");
                    system("pause");
                }
                else
                {
                    printf("\nLa persona no fue borrada\n");
                    system("pause");
                }
                break;

            case 3:
                system("cls");
                ordenarPorNombre(pers,TAM);
                mostrarLista(pers,TAM);
                system("pause");
                break;

            case 4:
                system("cls");
                graficoEdades(pers,TAM);
                system("pause");
                break;

            case 5:
                resp = getSN(&salir,"Esta seguro que desea salir? S/N","\nError. Debe ingresar S/N\n");
                if(resp == -1)
                {
                    system("pause");
                }
                break;

            default:
                system("cls");
                printf("Error. Opcion no valida.");
                printf("\nIngrese una opcion entre 1 y 5.\n");
                system("pause");
                break;
        }
    }

    return 0;
}
