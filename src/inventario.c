/*
 * Archivo: inventario.c
 * Autor: Pablo Serón
 * Descripción: Implementación de las funciones del módulo inventario.
 */

#include <stdio.h>
#include "objeto.h"
#include "inventario.h"

/**
 * @brief 
 * 
 * @param inventario 
 */
void inventario_inicializar(Inventario *inventario)
{
    if (inventario == NULL)
    {
        return;
    }

    inventario->cabeza = NULL;
    inventario->cantidad = 0;
    
}