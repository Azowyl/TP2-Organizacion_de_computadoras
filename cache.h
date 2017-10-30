#ifndef __CACHE_H__
#define __CACHE_H__

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "metadata.h"
#include "set.h"

#define set_count 512 // cache 2WSA de 4KB con bloques de 4B
#define memory_size 65536 // 64K

#define HIT 0
#define MISS -2

extern char memory[memory_size];

typedef struct {
	float access;
	float misses;
	set_t* sets[set_count];
} cache_t;

// inicializa la cache
// Pre: self apunta a un sector valido de memoria
int cache_create(cache_t* self);

// destruye la cache liberando sus recursos
// Pre: self inicializada con cache_create
int cache_destroy(cache_t* self);

// carda en data, la informacion del bloque direcciondo por info.
// retorna HIT o MISS dependiendo si estaba o no el bloque en cache
// Pre: self inicializada con cache_create,
// info contiene tag, index, y block offset
// data apunta a un sector valido de memoria
int cache_read_data(cache_t* self, metadata_t* info, char* data);

// guarda en el bloque identificado por info, 4 bytes comenzando desde data.
// retorna HIT o MISS dependiendo si estaba o no el bloque en cache
// Pre: self inicializada con cache_create,
// info contiene tag, index, y block offset
int cache_write_data(cache_t* self, metadata_t* info, char* data);

// retorna el miss rate como el cociente entre misses y access
// Pre: self inicializada con cache_create
float cache_get_miss_rate(cache_t* self);

#endif /* __CACHE_H__ */