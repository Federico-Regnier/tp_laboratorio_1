#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>
#include "funciones.h"

int main()
{
    float num1=0, num2=0;
    char salir='n';
    int opcion=0;

    while(salir=='n')
    {
        system("cls");
        printf("1- Ingresar 1er operando (A=%f)\n", num1);
        printf("2- Ingresar 2do operando (B=%f)\n", num2);
        printf("3- Calcular la suma (A+B)\n");
        printf("4- Calcular la resta (A-B)\n");
        printf("5- Calcular la division (A/B)\n");
        printf("6- Calcular la multiplicacion (A*B)\n");
        printf("7- Calcular el factorial (A!)\n");
        printf("8- Calcular todas las operaciones\n");
        printf("9- Salir\n");
        printf("Elija una opcion: ");

        scanf("%d",&opcion);
        opcion = valida(opcion, 1, 9);

        switch(opcion)
        {
            case 1:
                system("cls");
                num1 = getFloat("Ingrese el primer operando: ");
                break;
            case 2:
                system("cls");
                num2 = getFloat("Ingrese el segundo operando: ");
                break;
            case 3:
                system("cls");
                sumar(num1, num2);
                system("pause");
                break;
            case 4:
                system("cls");
                restar(num1, num2);
                system("pause");
                break;
            case 5:
                system("cls");
                dividir(num1, num2);
                system("pause");
                break;
            case 6:
                system("cls");
                multiplicar(num1, num2);
                system("pause");
                break;
            case 7:
                system("cls");
                validaFactorial(num1);
                system("pause");
                break;
            case 8:
                system("cls");
                sumar(num1, num2);
                restar(num1, num2);
                dividir(num1, num2);
                multiplicar(num1, num2);
                printf("\n");
                validaFactorial(num1);
                system("pause");
                break;
            case 9:
                system("cls");
                printf("Esta seguro que desea salir?\n");
                salir = tolower(getche());
                salir = validaSN(salir);
                break;
        }//Fin del Switch
    }//Fin del while

    return 0;
}
