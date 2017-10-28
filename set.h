#ifndef __SET_H__
#define __SET_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "block.h"

#define block_count 2 // 2WSA

//extern memory_t memory;

typedef struct {
	int index;
	block_t* blocks[block_count];
	int last_recent_used;
} set_t;

// inicializa la estructura para ser utilziada
// Pre: self apunta a un sector valido de memoria
int set_create(set_t* self, int index);

// destruye la estructura liberando sus recursos
// Pre: self inicializada con set_create
int set_destroy(set_t* self);

// devuelve el block correspondiente al tag
// NULL si no contiene un bloque con el tag especificado
// Pre: self inicializada con set_create
block_t* set_get_block(set_t* self, int tag);

int set_insert_block(set_t* self, block_t* block);

#endif /* __SET_H__ */