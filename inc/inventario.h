/*
 * Archivo: inventario.h
 * Autor: Pablo Serón
 * Descripción: Inventario del personaje implementado como lista enlazada
 *              simple. Cada nodo guarda una copia del Objeto.
 */

#ifndef INVENTARIO_H
#define INVENTARIO_H

#include "objeto.h"

/**
 * @brief Nodo de la lista enlazada del inventario.
 * 
 * objeto: copia del objeto almacenado.
 * siguiente: puntero al siguiente nodo (NULL si es el último).
 */
typedef struct _NodoInventario
{
    Objeto objeto;
    struct _NodoInventario *siguiente;

} NodoInventario;

/**
 * @brief Inventario: lista enlazada de objetos.
 * 
 * cabeza: primer nodo (NULL si el inventario está vacío) (centinela).
 * cantidad: número de objetos almacenados.
 */
typedef struct _Inventario
{
    NodoInventario *cabeza;
    int cantidad;

} Inventario;

/**
 * @brief Códigos de resultado de las operaciones que pueden fallar.
 */
typedef enum 
{
    INVENTARIO_OK = 0,
    INVENTARIO_ERROR_PARAMETRO,     /* puntero NULL o dato inválido   */
    INVENTARIO_ERROR_MEMORIA,       /* malloc devolvió NULL           */
    INVENTARIO_ERROR_ID_DUPLICADO,  /* ya existe un objeto con ese ID */
    INVENTARIO_ERROR_NO_ENCONTRADO  /* el objeto buscado no existe    */

} ResultadoInventario;

/**
 * @brief 
 * 
 * @param inventario 
 */
void inventario_inicializar(Inventario *inventario);


#endif /* INVENTARIO_H */