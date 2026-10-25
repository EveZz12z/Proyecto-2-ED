/*
 * Archivo: objeto.c
 * Autor: Pablo Serón
 * Descripción: Implementación de las funciones del módulo Objeto.
 */

#include <stdio.h>
#include "objeto.h"

/**
 * @brief Rellena un objeto con los datos entregados.
 * 
 * @param objeto Objeto destino (no debe ser NULL).
 * @param id Identificador único (> 0).
 * @param nombre Nombre no vacío; si es muy largo se trunca.
 * @param tipo Categoría del objeto.
 * @param valor Efecto numérico del objeto.
 * @return 0 si todo fue correcto, -1 si algún parámetro es inválido.
 */
int objeto_inicializar(Objeto *objeto, int id, const char *nombre, TipoObjeto tipo, int valor)
{
    if (objeto == NULL || nombre == NULL || nombre[0] == '\0' || id <= 0) {
        return -1;
    }

    objeto->id = id;
    snprintf(objeto->nombre, LARGO_NOMBRE_OBJETO, "%s", nombre);
    objeto->tipo = tipo;
    objeto->valor = valor;
    return 0;
}