#include "block.h"

int block_create(block_t* self) {
	self->data = malloc(block_size);
	if (!self->data) {
		fprintf(stderr, "%s\n", "Error al alocar memoria para el bloque");
		return ERROR;
	}
	memset(self->data, 0, block_size);
	self->tag = -1;
	self->dirty = false;
	self->valid = false;
	return SUCESS;
}

int block_destroy(block_t* self) {
	free(self->data);
	self->tag = 0;
	self->dirty = false;
	self->valid = false;
	return SUCESS;
}

int block_get_tag(block_t* self) {
	return self->tag;
}

bool block_get_dirty(block_t* self) {
	return self->dirty;
}

bool block_get_valid(block_t* self) {
	return self->valid;
}

int block_set_data(block_t* self, int tag, void* data) {
	memcpy(self->data, data, block_size);
	self->tag = tag;
	return SUCESS;
}

void* block_get_data(block_t* self) {
	return self->data;
}
