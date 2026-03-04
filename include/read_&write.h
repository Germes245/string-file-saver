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

typedef struct{
    uint32_t *array;
    uint32_t length;
} array_2;

array_2 find_elements_in_array(const char array[], const char element, uint32_t length);
array_2 calculate_lengths(array_2 indexes);
array_ length_of_strings(char array[], uint32_t length);

void write_strings_into_file(char* name_of_file, char *text[], uint32_t number_of_strings_in_text);
char_pointer_array read_strings_from_file(char* name_of_file);