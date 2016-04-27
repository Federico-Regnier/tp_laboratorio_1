#ifndef FUNCIONES_H_INCLUDED
#define FUNCIONES_H_INCLUDED

typedef struct {

    char nombre[50];
    int edad;
    int estado;
    long int dni;

}EPersona;


int obtenerEspacioLibre(EPersona lista[],int tam);
int buscarPorDni(EPersona lista[],int size, int dni);
void ordenarPorNombre(EPersona lista[],int size);
int altas(EPersona *lista,int size);
void mostrarLista(EPersona *lista,int size);
int borrarPersona(EPersona *lista,int size);
void graficoEdades(EPersona lista[],int size);
#endif // FUNCIONES_H_INCLUDED
