#include "metadata.h"

int main(int argc, char* argv[]) { 
	metadata_t metadata;
	metadata_create(&metadata, 51199);
	printf("%d\n", metadata_get_index(&metadata));
	return 0;
}
