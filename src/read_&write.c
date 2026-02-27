#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    size_t* array_of_lengths;// длина включая нулевой терминатор
    size_t* array_of_indexes;
    size_t length;
} array_;

typedef struct{
    char **text;
    size_t length;
} char_pointer_array;

array_ length_of_strings(char array[], size_t length, size_t score){ // 1. блок 2. размер блока 3. количество строк
    array_ result;
    result.array_of_lengths = malloc(score*sizeof(size_t));
    result.array_of_indexes = malloc(score*sizeof(size_t));
    result.length = score;
    for(size_t i = 0, j = 0; i < length; j++){
        size_t length = strlen(array+i)+1;
        if(array[i] == 0) break;
        result.array_of_lengths[j] = length;
        result.array_of_indexes[j] = i;
        i += length;
    }
    return result;
}

void write_strings_into_file(char* name_of_file, char *text[], uint32_t number_of_strings_in_text){
    uint32_t size_of_block = 0;
    for(uint32_t i = 0; i < number_of_strings_in_text; i++){
        uint32_t len = strlen(text[i]);
        printf("len %d\n", len);
        if(len > size_of_block) size_of_block = len + 1;
    }
    printf("size_of_block %d\n", size_of_block);
    FILE *file = fopen(name_of_file, "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    {
        uint8_t size_for_array = sizeof(uint32_t)*2;
        uint32_t *array = malloc(size_for_array);
        array[0] = size_of_block; //в первые байты записываем размер блока
        array[1] = number_of_strings_in_text;
        fwrite(array, size_for_array, 1, file);
        //write(1, array, size_for_array);
    }
    char block[size_of_block];
    for(uint32_t i = 0; i < size_of_block; i++) block[i] = 0;
    uint8_t current_size_of_strings = 0;
    for(size_t i = 0; i < number_of_strings_in_text; i++){
        size_t size = strlen(text[i])+1;
        printf("shya\n");
        if(size <= size_of_block - current_size_of_strings){
            printf("shya1\n");
            memcpy(block+current_size_of_strings, text[i], size);
        }
        else{
            printf("shya2\n");
            fwrite(block, sizeof(char), size_of_block*sizeof(char), file);
            for(size_t i = 0; i < size_of_block; i++)
                block[i] = 0;
        }
            memcpy(block, text[i], size); // возможно переполнение...
        current_size_of_strings += size;
    }
    fwrite(block, sizeof(char), size_of_block, file);
    fclose(file);
}

char_pointer_array read_strings_from_file(char* name_of_file){
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char_pointer_array strings;
    uint32_t size_of_block;
    {
        uint32_t array[2];
        fread(array, sizeof(uint32_t), 2, file);
        size_of_block = array[0];
        strings.length = array[1];
    }
    strings.text = malloc(strings.length*sizeof(char*));
    char block[size_of_block];
    register size_t i = 0;
    while(fread(block, sizeof(char), size_of_block, file) != 0){
        array_ result = length_of_strings(block, size_of_block, strings.length);
        for(size_t i = 0; i < result.length; i++){
            strings.text[i] = malloc(result.array_of_lengths[i]);
            memcpy(strings.text[i], block + result.array_of_indexes[i], result.array_of_lengths[i]);
        }
    }
    fclose(file);
    return strings;
}