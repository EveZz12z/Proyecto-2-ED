/*
 * Archivo: objeto.h
 * Autor: Pablo Serón
 * Descripción: Definición del tipo Objeto (armas, armaduras, pociones, etc.).
 */

#ifndef OBJETO_H
#define OBJETO_H

#define LARGO_NOMBRE_OBJETO 50

/**
 * @brief 
 * Categorias para objetos
 */
typedef enum {
    TIPO_ARMA,
    TIPO_ARMADURA,
    TIPO_POCION,
    TIPO_OTRO
} TipoObjeto;

/**
 * @brief 
 * id: identificador (> 0)
 * nombre: nombre del objeto
 * tipo: categoría del objeto
 * valor: efecto numérico (+ataque, +defensa, +vida... etc)
 */
typedef struct _Objeto {
    int id;
    char nombre[LARGO_NOMBRE_OBJETO];
    TipoObjeto tipo;
    int valor;
} Objeto;

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
int objeto_inicializar(Objeto *objeto, int id, const char *nombre,TipoObjeto tipo, int valor);

#endif /* OBJETO_H */