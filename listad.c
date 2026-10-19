/* Lista dinamica de enteros. */

#include "listad.h"

#include <stdio.h>
#include <stdlib.h>

void init(Lista *lista)
{
	if (lista != NULL) {
		lista->elementos = NULL;
		lista->cantidad = 0;
		lista->capacidad = 0;
	}
}

void destroy(Lista *lista)
{
	if (lista != NULL) {
		free(lista->elementos);
		lista->elementos = NULL;
		lista->cantidad = 0;
		lista->capacidad = 0;
	}
}

int isempty(const Lista *lista)
{
	return lista == NULL || lista->cantidad == 0;
}

int isfull(const Lista *lista)
{
	return lista != NULL && lista->cantidad == lista->capacidad;
}

size_t size(const Lista *lista)
{
	return lista == NULL ? 0 : lista->cantidad;
}

int get(const Lista *lista, size_t posicion, int *valor)
{
	if (lista == NULL || valor == NULL || posicion >= lista->cantidad) {
		return 0;
	}

	*valor = lista->elementos[posicion];
	return 1;
}

static int grow(Lista *lista)
{
	size_t nueva_capacidad;
	int *nuevos_elementos;

	if (lista->capacidad == 0) {
		nueva_capacidad = 1;
	} else {
		nueva_capacidad = lista->capacidad * 2;
		if (nueva_capacidad < lista->capacidad) {
			return 0;
		}
	}

	nuevos_elementos = realloc(lista->elementos,
			nueva_capacidad * sizeof(*nuevos_elementos));
	if (nuevos_elementos == NULL) {
		return 0;
	}

	lista->elementos = nuevos_elementos;
	lista->capacidad = nueva_capacidad;
	return 1;
}

int insert(Lista *lista, size_t posicion, int valor)
{
	size_t indice;

	if (lista == NULL || posicion > lista->cantidad) {
		return 0;
	}

	if (isfull(lista) && !grow(lista)) {
		return 0;
	}

	for (indice = lista->cantidad; indice > posicion; --indice) {
		lista->elementos[indice] = lista->elementos[indice - 1];
	}

	lista->elementos[posicion] = valor;
	++lista->cantidad;
	return 1;
}

int push_front(Lista *lista, int valor)
{
	return insert(lista, 0, valor);
}

int push(Lista *lista, int valor)
{
	if (lista == NULL) {
		return 0;
	}

	return insert(lista, lista->cantidad, valor);
}

int remove_at(Lista *lista, size_t posicion, int *valor)
{
	size_t indice;

	if (lista == NULL || posicion >= lista->cantidad) {
		return 0;
	}

	if (valor != NULL) {
		*valor = lista->elementos[posicion];
	}

	for (indice = posicion; indice + 1 < lista->cantidad; ++indice) {
		lista->elementos[indice] = lista->elementos[indice + 1];
	}

	--lista->cantidad;
	return 1;
}

int pop_front(Lista *lista, int *valor)
{
	return remove_at(lista, 0, valor);
}

int pop(Lista *lista, int *valor)
{
	if (lista == NULL || lista->cantidad == 0) {
		return 0;
	}

	return remove_at(lista, lista->cantidad - 1, valor);
}

int peek(const Lista *lista, int *valor)
{
	if (lista == NULL || valor == NULL || lista->cantidad == 0) {
		return 0;
	}

	*valor = lista->elementos[lista->cantidad - 1];
	return 1;
}

int find(const Lista *lista, int valor, size_t *posicion)
{
	size_t indice;

	if (lista == NULL) {
		return 0;
	}

	for (indice = 0; indice < lista->cantidad; ++indice) {
		if (lista->elementos[indice] == valor) {
			if (posicion != NULL) {
				*posicion = indice;
			}
			return 1;
		}
	}

	return 0;
}

void print(const Lista *lista)
{
	size_t indice;

	if (lista == NULL) {
		return;
	}

	printf("[");
	for (indice = 0; indice < lista->cantidad; ++indice) {
		if (indice > 0) {
			printf(", ");
		}
		printf("%d", lista->elementos[indice]);
	}
	printf("]\n");
}
