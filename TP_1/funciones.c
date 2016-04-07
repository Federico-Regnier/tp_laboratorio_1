#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>

/**
*\brief Pide un numero al usuario y devulve como output de la funcion
*\param mensaje Es el mensaje a ser mostrado al usuario
*\return Valor ingresado por el usuario
*
*/
float getFloat(char mensaje[])
{
    float numero;
    printf("%s", mensaje);
    scanf("%f", &numero);
    return numero;
}


/**
*\brief Valida que el entero ingresado este en el intervalo, sino pide que se reingrese
*\param num Es el numero a validar
*\param inf Numero menor que puede tomar el numero a validar
*\param sup Numero mayor que puede tomar el numero a validar
*\return Numero validado
*
*/
int valida(int num, int inf, int sup)
{
    while(num < inf || num > sup)
    {
        printf("\nError. La opcion no es valida. Intentelo denuevo.\n");
        scanf("%d", &num);
    }
    return num;
}


/**
*\brief Suma los dos numeros pasados a la funcion e imprime el resultado
*\param num1 Numero a sumar
*\param num2 Numero a sumar
*\return no devulve valor, imprime por pantalla la suma
*
*/
void sumar(float num1, float num2)
{
    float suma;

    suma = num1 + num2;
    printf("La suma es: %f\n", suma);

}


/**
*\brief Resta dos numeros pasados a la funcion e imprime el resultado por pantalla
*\param num1 Numero a restar
*\param num2 Numero a restar
*\return Void, no devulve valor, imprime por pantalla la resta
*
*/
void restar(float num1, float num2)
{
    float resta;
    resta = num1 - num2;
    printf("La resta es: %f\n", resta);

}



/**
*\brief Divide numerador por el denominador e imprime el resultado
*\param numerador Es el numero a divir
*\param denominador Es el numero por el que se va a dividir
*\return Void, imprime por pantalla el resultado
*
*/
void dividir(float numerador, float denominador)
{
    float division;
    if(denominador == 0)//Checkeo que el denominador no sea cero
    {
        printf("Error. No existe la division por cero. Ingrese otro denominador.\n");
    }
    else
    {
        division = numerador / denominador;
        printf("La division es: %f\n", division);

    }
}

/**
*\brief Multiplica dos numeros pasados a la funcion e imprime el resultado por pantalla
*\param num1 Numero a multiplicar
*\param num2 Numero a multiplicar
*\return Void, imprime por pantalla el resultado
*
*/
void multiplicar(float num1, float num2)
{
    float mult;
    mult = num1 * num2;
    printf("El resultado de la multiplicacion es: %f", mult);


}


/**
*\brief Calcula el factorial de un numero y devulve por return
*\param numero Es el numero a calcular el factorial
*\return Devulve el factorial del numero ingresado
*
*/
double factorial(float numero)
{
    double auxiliar;
    if(numero == 1)
        return 1;
    auxiliar = (double) numero * factorial(numero - 1);
    return auxiliar;
}


/**
*\brief Valida el numero a calcular el factorial, lo calcula e imprime el resultado
*\param numero Es el numero a calcular el factorial
*\return Void, imprime el factorial por pantalla
*
*/
void validaFactorial(float numero)
{
    double fact;
    if(numero < 0)
    {
        printf("Error. No existe el factorial de un numero negativo\n");
    }
    else if(numero == 0)
    {
        printf("Error. No existe el factorial de cero. Ingrese otro numero.\n");
    }
    else if(floor(numero) != numero)
    {
        printf("Error. Debe ingresar un numero natural para poder calcular el factorial.\n");
    }
    else
    {
        fact = factorial(numero);
        printf("El factorial de %.0f es %.0lf\n", numero, fact);
    }


}


/**
*\brief Valida la opcion entre S/N
*\param opcion Es la opcion que ingresó el usuario
*\return Devuelve la opcion validada s o n según que se ingresó
*
*/
char validaSN(char opcion)
{
    while(opcion != 's' && opcion != 'n')
    {
        system("cls");
        printf("Error. Desea salir? s/n \n");
        opcion = tolower(getche());
    }
    return opcion;
}
