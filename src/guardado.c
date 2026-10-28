/*
 * Archivo: guardado.c
 * Autor: Pablo Serón
 * Descripción: Implementacion de guardar y cargar partida.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "guardado.h"

#define MARCA_ARCHIVO "RPG_PARTIDA_V1"
#define MARCA_PERSONAJE "PERSONAJE"
#define MARCA_INVENTARIO "INVENTARIO"
#define MARCA_FIN "FIN"
#define LARGO_MARCA 32
#define LARGO_RUTA 256


/**
 * @brief Escribe la seccion del personaje.
 * 
 * @return 0 si se escribio bien, -1 si fprintf fallo.
 */
static int escribir_personaje(FILE *archivo, const Personaje *p)
{
    if (fprintf(archivo, "%s\n%s\n", MARCA_PERSONAJE, p->nombre) < 0)
    {
        return -1;
    }
    if (fprintf(archivo, "%d %d %d %d %d %d\n", p->puntos_vida, p->vida_maxima,
                p->ataque, p->bono_ataque, p->defensa, p->bono_defensa) < 0)
    {
        return -1;
    }
    return 0;
}

/**
 * @brief Escribe la seccion del inventario recorriendo la lista.
 * 
 * @return 0 si se escribio bien, -1 si fprintf fallo.
 */
static int escribir_inventario(FILE *archivo, const Inventario *inventario)
{
    NodoInventario *actual;

    if (fprintf(archivo, "%s\n%d\n", MARCA_INVENTARIO, inventario->cantidad) < 0)
    {
        return -1;
    }

    // Saltamos el centinela
    actual = inventario->cabeza->siguiente;
    while (actual != NULL)
    {
        // Datos numericos en una linea y el nombre en otra (puede tener espacios gracias a "fgetc")
        if (fprintf(archivo, "%d %d %d\n%s\n", actual->objeto.id,
                    (int)actual->objeto.tipo, actual->objeto.valor,
                    actual->objeto.nombre) < 0)
        {
            return -1;
        }
        actual = actual->siguiente;
    }
    return 0;
}

ResultadoGuardado guardar_partida(const char *ruta, const Personaje *personaje,
                                  const Inventario *inventario)
{
    char ruta_temporal[LARGO_RUTA];
    FILE *archivo;
    int error = 0;

    if (ruta == NULL || personaje == NULL || inventario == NULL ||
        inventario->cabeza == NULL)
    {
        return GUARDADO_ERROR_PARAMETRO;
    }

    // Escribimos en "ruta.tmp" y recien al final lo renombramos
    if (snprintf(ruta_temporal, LARGO_RUTA, "%s.tmp", ruta) >= LARGO_RUTA)
    {
        return GUARDADO_ERROR_PARAMETRO;
    }

    archivo = fopen(ruta_temporal, "w");
    if (archivo == NULL)
    {
        return GUARDADO_ERROR_ARCHIVO;
    }

    if (fprintf(archivo, "%s\n", MARCA_ARCHIVO) < 0 ||
        escribir_personaje(archivo, personaje) != 0 ||
        escribir_inventario(archivo, inventario) != 0 ||
        fprintf(archivo, "%s\n", MARCA_FIN) < 0)
    {
        error = 1;
    }

    // fclose también puede fallar (ej: disco lleno al vaciar el buffer)
    if (fclose(archivo) != 0)
    {
        error = 1;
    }

    if (error || rename(ruta_temporal, ruta) != 0)
    {
        remove(ruta_temporal);
        return GUARDADO_ERROR_ARCHIVO;
    }
    return GUARDADO_OK;
}


/**
 * @brief Lee una palabra del archivo y verifica que sea la marca esperada.
 *        fscanf con %s salta los espacios y saltos de linea previos.
 * 
 * @return 1 si coincide, 0 si no.
 */
static int leer_marca(FILE *archivo, const char *marca)
{
    char palabra[LARGO_MARCA];

    // %31s: maximo 31 caracteres
    if (fscanf(archivo, "%31s", palabra) != 1)
    {
        return 0;
    }
    return strcmp(palabra, marca) == 0;
}

/**
 * @brief Lee una linea de texto completa (puede tener espacios) con fgetc.
 *
 * @param archivo Archivo abierto para lectura.
 * @param destino Arreglo donde se guarda el texto.
 * @param largo Tamaño de destino.
 *
 * @return 1 si leyo un texto no vacio que cabe en destino, 0 si no.
 */
static int leer_texto(FILE *archivo, char *destino, int largo)
{
    int caracter;
    int i;

    // Descartamos el resto de la linea anterior
    caracter = fgetc(archivo);
    while (caracter != '\n' && caracter != EOF)
    {
        caracter = fgetc(archivo);
    }
    if (caracter == EOF)
    {
        return 0;
    }

    // Leemos la linea del texto hasta el salto de linea
    i = 0;
    caracter = fgetc(archivo);
    while (caracter != '\n' && caracter != EOF)
    {
        if (i >= largo - 1)
        {
            return 0; // no cabe en destino
        }
        destino[i] = (char)caracter;
        i++;
        caracter = fgetc(archivo);
    }
    destino[i] = '\0';

    return caracter == '\n' && i > 0;
}

/**
 * @brief Lee la seccion del personaje a una variable temporal.
 * @return GUARDADO_OK o GUARDADO_ERROR_FORMATO.
 */
static ResultadoGuardado leer_personaje(FILE *archivo, Personaje *destino)
{
    Personaje temporal;

    if (!leer_marca(archivo, MARCA_PERSONAJE))
    {
        return GUARDADO_ERROR_FORMATO;
    }

    if (!leer_texto(archivo, temporal.nombre, LARGO_NOMBRE_PERSONAJE))
    {
        return GUARDADO_ERROR_FORMATO;
    }

    // fscanf devuelve cuantos valores logro leer: deben ser los 6
    if (fscanf(archivo, "%d %d %d %d %d %d", &temporal.puntos_vida,
               &temporal.vida_maxima, &temporal.ataque, &temporal.bono_ataque,
               &temporal.defensa, &temporal.bono_defensa) != 6)
    {
        return GUARDADO_ERROR_FORMATO;
    }

    // Validaciones
    if (temporal.vida_maxima <= 0 || temporal.puntos_vida < 0 ||
        temporal.puntos_vida > temporal.vida_maxima)
    {
        return GUARDADO_ERROR_FORMATO;
    }

    *destino = temporal;
    return GUARDADO_OK;
}

/**
 * @brief Lee la seccion del inventario y la reconstruye en "destino"
 *        (un inventario ya inicializado y vacio).
 * @return GUARDADO_OK, GUARDADO_ERROR_FORMATO o GUARDADO_ERROR_MEMORIA.
 */
static ResultadoGuardado leer_inventario(FILE *archivo, Inventario *destino)
{
    char nombre[LARGO_NOMBRE_OBJETO];
    Objeto objeto;
    ResultadoInventario resultado;
    int cantidad;
    int id, tipo, valor;
    int i;

    if (!leer_marca(archivo, MARCA_INVENTARIO))
    {
        return GUARDADO_ERROR_FORMATO;
    }

    if (fscanf(archivo, "%d", &cantidad) != 1 || cantidad < 0)
    {
        return GUARDADO_ERROR_FORMATO;
    }

    // Si cantidad es 0 el for no entra: inventario vacio valido
    for (i = 0; i < cantidad; i++)
    {
        if (fscanf(archivo, "%d %d %d", &id, &tipo, &valor) != 3)
        {
            return GUARDADO_ERROR_FORMATO;
        }
        if (tipo < TIPO_ARMA || tipo > TIPO_OTRO)
        {
            return GUARDADO_ERROR_FORMATO;
        }
        if (!leer_texto(archivo, nombre, LARGO_NOMBRE_OBJETO))
        {
            return GUARDADO_ERROR_FORMATO;
        }
        // Reutilizamos la validacion de objeto.c (id > 0, nombre no vacio)
        if (objeto_inicializar(&objeto, id, nombre, (TipoObjeto)tipo, valor) != 0)
        {
            return GUARDADO_ERROR_FORMATO;
        }

        // inventario_agregar detecta ID duplicados y falta de memoria
        resultado = inventario_agregar(destino, &objeto);
        if (resultado == INVENTARIO_ERROR_MEMORIA)
        {
            return GUARDADO_ERROR_MEMORIA;
        }
        if (resultado != INVENTARIO_OK)
        {
            return GUARDADO_ERROR_FORMATO;
        }
    }
    return GUARDADO_OK;
}

/**
 * @brief Carga una partida desde un archivo de texto.
 *
 * @param ruta Ruta del archivo de guardado.
 * @param personaje Personaje donde se carga (se sobrescribe).
 * @param inventario Inventario donde se carga. (Este debe estar inicializado)
 *
 * @return GUARDADO_OK, GUARDADO_ERROR_PARAMETRO, GUARDADO_ERROR_ARCHIVO si no
 *         se puede abrir/leer, GUARDADO_ERROR_FORMATO si los datos son
 *         invalidos, o GUARDADO_ERROR_MEMORIA si malloc falla.
 */
ResultadoGuardado cargar_partida(const char *ruta, Personaje *personaje,
                                 Inventario *inventario)
{
    FILE *archivo;
    Personaje personaje_temporal;
    Inventario inventario_temporal;
    ResultadoGuardado resultado;

    if (ruta == NULL || personaje == NULL || inventario == NULL)
    {
        return GUARDADO_ERROR_PARAMETRO;
    }

    archivo = fopen(ruta, "r");
    if (archivo == NULL)
    {
        return GUARDADO_ERROR_ARCHIVO;
    }

    // Todo se lee a temporales: si algo falla, lo original no se toca
    if (inventario_inicializar(&inventario_temporal) != INVENTARIO_OK)
    {
        fclose(archivo);
        return GUARDADO_ERROR_MEMORIA;
    }

    resultado = GUARDADO_OK;
    if (!leer_marca(archivo, MARCA_ARCHIVO))
    {
        resultado = GUARDADO_ERROR_FORMATO;
    }
    if (resultado == GUARDADO_OK)
    {
        resultado = leer_personaje(archivo, &personaje_temporal);
    }
    if (resultado == GUARDADO_OK)
    {
        resultado = leer_inventario(archivo, &inventario_temporal);
    }
    if (resultado == GUARDADO_OK && !leer_marca(archivo, MARCA_FIN))
    {
        resultado = GUARDADO_ERROR_FORMATO;
    }
    fclose(archivo);

    if (resultado != GUARDADO_OK)
    {
        inventario_liberar(&inventario_temporal);
        return resultado;
    }

    // Si todo salio bien entonces: liberamos el inventario anterior y nos quedamos con el nuevo inventario
    inventario_liberar(inventario);
    *inventario = inventario_temporal;
    *personaje = personaje_temporal;
    return GUARDADO_OK;
}