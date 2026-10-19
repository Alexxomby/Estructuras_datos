/* Lista estatica de enteros. */

#include "listae.h"

#include <stdio.h>

void init(Lista *lista)
{
	if (lista != NULL) {
		lista->cantidad = 0;
	}
}

int isempty(const Lista *lista)
{
	return lista == NULL || lista->cantidad == 0;
}

int isfull(const Lista *lista)
{
	return lista != NULL && lista->cantidad == CAPACIDAD_LISTA;
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

int insert(Lista *lista, size_t posicion, int valor)
{
	size_t indice;

	if (lista == NULL || isfull(lista) || posicion > lista->cantidad) {
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
