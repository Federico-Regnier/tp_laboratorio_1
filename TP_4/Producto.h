#ifndef PRODUCTO_H_INCLUDED
#define PRODUCTO_H_INCLUDED

typedef struct
{
    char codBarra[20];
    char nombre[60];
    int cantidad;
    float precio;
}eProducto;

int CsvAProducto(ArrayList *lista, char *archivo);
int validacionProducto(eProducto *prod, char *input);
int set_cantidad(eProducto *prod, int newValue);
float get_precio(void *prod);
int get_cant(void *producto);
int comparar_producto(void *prod1, void *prod2);
int contains_name(void *prod, void *name);
void imprimir_producto(void *producto);
void imprimir_pagina(ArrayList *listaProductos);
void imprimir_mayores(ArrayList *listaProductos);
int archivo_productos(ArrayList *productos, char *archivo);
#endif // PRODUCTO_H_INCLUDED
