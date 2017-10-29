#include "cache.h"

int cache_create(cache_t* self) {
	int index = 0;
	for (int i = 0; i < set_count; i++) {
		self->sets[i] = (set_t*) malloc(sizeof(set_t));
		if (!self->sets[i]) {
			fprintf(stderr, "%s%d\n", "Error al asingar memoria para el set: ", i);
		} else {
			set_create(self->sets[i], index++);		
		}
	}
	return SUCESS;
}

int cache_destroy(cache_t* self) {
	for (int i = 0; i < set_count; i++) {
		if (self->sets[i]) {
			set_destroy(self->sets[i]);	
			free(self->sets[i]);
		}
	}
	return SUCESS;
}	

int cache_read_data(cache_t* self, metadata_t* metadata, char* data) {
	self->access++;

	int index = metadata_get_index(metadata);
	if (index < 0 || index > set_count) {
		return ERROR;
	}

	block_t* block = set_get_block(self->sets[index], metadata_get_tag(metadata));

	if (block) {
		if (block_get_valid_bit(block)) {
			block_get_data(block, metadata_get_offset(metadata), data);
			return HIT;	
		}
	}
	// MISS
	self->misses++;
	
	block = (block_t*) malloc(sizeof(block_t));
	block_create(block, metadata_get_tag(metadata));
	block_set_data(block, &memory[metadata_get_address(metadata)]);
	set_insert_block(self->sets[index], block); // Allocate
	block_get_data(block, metadata_get_offset(metadata), data);
	block_destroy(block);
	free(block);
	return MISS;
}

int cache_write_data(cache_t* self, metadata_t* metadata, char* data) {
	self->access++;

	int index = metadata_get_index(metadata);
	if (index < 0 || index > set_count) {
		return ERROR;
	}

	block_t* block = set_get_block(self->sets[index], metadata_get_tag(metadata));
	if (block) {
		block_set_data(block, data);
		block_set_dirty(block, true);
		return HIT;
	} else {
		self->misses++;

		block = (block_t*) malloc(sizeof(block_t));
		block_create(block, metadata_get_tag(metadata));
		block_set_data(block, &memory[metadata_get_address(metadata)]);
		set_insert_block(self->sets[index], block); // Write Allocate
		block_destroy(block);
		free(block);
		block = set_get_block(self->sets[index], metadata_get_tag(metadata));
		block_set_data(block, data);
		block_set_dirty(block, true);
		return MISS;
	}
}

int cache_get_miss_rate(cache_t* self) {
	return ((float)(self->misses / self->access))* 100;
}