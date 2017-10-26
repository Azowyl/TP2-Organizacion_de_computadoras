#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "metadata.h"
#include "set.h"

#define set_count 512 // cache 2WSA de 4KB con bloques de 4B

typedef struct {
	int access;
	int misses;
	set_t* sets[set_count];
} cache_t;

// inicializa la cache
// Pre: self apunta a un sector valido de memoria
int cache_create(cache_t* self);

// destruye la cache liberando sus recursos
// Pre: self inicializada con cache_create
int cache_destroy(cache_t* self);

// retorna true si contiene el bloque con el tag, false en caso contrario
// Pre: self inicializada con cache_create
bool cache_contains_block(cache_t* self, metadata_t* metadata);

// carda en data, la informacion del bloque direcciondo por info.
// retorna true si data fue cargada, false en caso contrario
// Pre: self inicializada con cache_create,
// info contiene tag, index, y block offset
bool cache_read_block(cache_t* self, metadata_t* info, void* data);

// guarda en el bloque identificado por info, los bytes de data.
// retorna true si data fue guardada, false en caso contrario
// Pre: self inicializada con cache_create,
// info contiene tag, index, y block offset
int cache_write_block(cache_t* self, metadata_t* info, void* data);

#endif /* __CACHE_H__ */