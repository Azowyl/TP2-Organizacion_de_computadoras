#include "metadata.h"

int metadata_create(metadata_t* self, unsigned short int address) {
	self->metadata = address;
	return SUCESS;
}

int metadata_destroy(metadata_t* self) { return SUCESS; }

int metadata_get_tag(metadata_t* self) {
	return self->metadata >> (index_size + offset_size);
}

int metadata_get_index(metadata_t* self) {
	unsigned short int index = self->metadata << tag_size;
	index = index >> (tag_size + offset_size);

	return index;
}

int metadata_get_offset(metadata_t* self) {
	unsigned short int offset = self->metadata << (index_size + tag_size);

	return (offset >> (index_size + tag_size));
}