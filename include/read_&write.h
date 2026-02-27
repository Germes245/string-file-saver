#include <stdint.h>
#include <stddef.h>

typedef struct{
    size_t* array_of_lengths;// длина включая нулевой терминатор
    size_t* array_of_indexes;
    size_t length;
} array_;

typedef struct{
    char **text;
    size_t length;
} char_pointer_array;

void write_strings_into_file(char* name_of_file, char *text[], uint32_t number_of_strings_in_text);
char_pointer_array read_strings_from_file(char* name_of_file);