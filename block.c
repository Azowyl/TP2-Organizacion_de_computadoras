#include "block.h"

int block_create(block_t* self, int tag) {
	self->data = (char*) malloc(block_size);
	if (!self->data) {
		fprintf(stderr, "%s\n", "Error al alocar memoria para el bloque");
		return ERROR;
	}
	memset(self->data, 0, block_size);
	self->tag = tag;
	self->dirty = false;
	self->valid = false;
	return SUCESS;
}

int block_destroy(block_t* self) {
	if (self->data) { free(self->data); }
	self->tag = 0;
	self->dirty = false;
	self->valid = false;
	return SUCESS;
}

int block_get_tag(block_t* self) {
	return self->tag;
}

bool block_get_dirty_bit(block_t* self) {
	return self->dirty;
}

bool block_get_valid_bit(block_t* self) {
	return self->valid;
}

int block_set_data(block_t* self, char* data) {
	self->valid = true;
	memcpy(self->data, data, block_size);
	return SUCESS;
}

int block_get_data(block_t* self, int offset, char* data) {
	if (offset < 0 || offset > 4) { return ERROR; }
	memcpy(data, &self->data[offset], 1);
	return SUCESS;
}

void block_set_dirty(block_t* self, bool is_dirty) {
	self->dirty = is_dirty;
}
