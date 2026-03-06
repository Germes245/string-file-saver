#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

uint32_t find_letter(const char *string, char element, uint32_t length){
    uint32_t i = 0;
    /*do {
        i++;
    } while (string[i] != element);*/
    
    while(string[i] != element && i < length){
        i++;
        length--;
    }
    //for(; string[i] != element; i++);
    return i;
}

// (не)чистая функция
array_ find_elements_in_array(const char array[], const char element, uint32_t length){
    array_ result;
    result.length = 0;
    printf("length: %d\n", length);
    for(uint32_t i = 0; i < length; i++){
        if(array[i] == element){
            result.length++;
        }
    }
    result.array_of_lengths = malloc(result.length * sizeof(uint32_t));
    for(uint32_t index = 0, j = 0; j < result.length; index++){
        if(array[index] == element){
            result.array_of_lengths[j] = index;
            j++;
            //printf("length: %d\n", length);
            //length = 0;
        }
        //length++;
    }
    /*for(uint32_t index = 0, length2 = 0; index < length; index++){
        if(array[index] == element){
            printf("length: %d\n", length2);
            length2 = 0;
        }
        //printf("length2: %d\n", length2);
        length2++;
    }*/
    printf("shya\n");
    return result;
}

array_2 calculate_lengths(array_2 indexes){
    array_2 result;
    result.array = malloc(indexes.length);
    result.array[0] = indexes.array[0];
    for(uint32_t i = 1; i < result.length; i++){
        //printf("length: %d\n", indexes.array[i] - indexes.array[i-1]);
        result.array[i] = indexes.array[i] - indexes.array[i-1];
    }
    return result;
}

/*uint32_t count_chars(char *array, char number, uint32_t length){
    uint32_t numbers = 0;
    for(uint32_t i = 0; i < length; i++) numbers += array[i] == number;
    return numbers;
}*/

uint32_t count_chars_until_there_are_no_repeat_chars(char *array, char number, uint32_t length){
    uint32_t numbers = 0;
    for(uint32_t i = 0; i < length - 1; i++){
        uint8_t bool_ = array[i] == number;
        numbers += bool_;
        if(bool_ && array[i + 1] == number) break;
    }
    return numbers;
}

uint32_t length_of_strings(char *result[], const char array[], uint32_t length){
    const char* index = array;
    uint32_t length2 = 0;
    uint32_t i = 0;
    /*for(; length2 < length; i++){
        uint32_t length_of_string = find_letter(index, 0, length);
        if(!length_of_string) break;
        //printf("length_of_string: %d\n", length_of_string);
        result[i] = malloc(length_of_string);
        //printf("%s\n", index);
        memcpy(result[i], index, length_of_string);
        length2 += length_of_string;
        index = length2 + 1;
        //printf("index: %d\n", index);
        
        //printf("%d\n", length2);
        //printf("shya\n");

        //if(array[length2] == array[length2+1]) break; //*index *(index + 1)
    }*/
    uint32_t length3 = length;
    uint32_t length_of_string = find_letter(index, 0, length3);
    result[0] = malloc(length_of_string);
    memcpy(result[0], index, length_of_string);
    write(1, result[0], length_of_string);
    length2 += length_of_string;
    index = length2 + 1;

    /*length3 -= length_of_string;
    length_of_string = find_letter(index, 0, length3);
    result[1] = malloc(length_of_string);
    memcpy(result[1], index, length_of_string);
    write(1, result[1], length_of_string);
    length2 += length_of_string;
    index = length2 + 1;*/

    exit(1);
    //return i;
}

// чистая функция
/*array_ length_of_strings(char array[], uint32_t length){ // 1. блок 2. размер блока 3. количество строк
    array_ result;
    result.length = 0;
    for(uint32_t i = 0; i < length; i++){
        if(array[i] == 0){
            result.length++;
            if((i + 1 == length) || (array[i + 1] == 0)){
                break;
            }
        }
    }
    result.array_of_indexes = malloc(result.length * sizeof(uint32_t));
    result.array_of_lengths = malloc(result.length * sizeof(uint32_t));
    for(uint32_t index = 0, j = 0, length = 0; j < result.length; index++){
        if(array[index] == 0){
            result.array_of_indexes[j] = index;
            j++;
            result.array_of_indexes[j] = length;
            length = 0;
        }
        if(index + 1 == length && array[index + 1] == 0){
            break;
        }
        length++;
    }
    return result;
}*/

// нечистая функция
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
    //printf("size_of_block = %d, strings.length = %d\n", size_of_block, strings.length);
    //exit(1);
    strings.text = malloc(strings.length*sizeof(char*));
    char block[size_of_block];
    //register size_t i = 0;
    uint32_t score = 0;
    fread(block, sizeof(char), size_of_block, file);
    write(1, block, size_of_block);

    score += length_of_strings(strings.text + score, block, size_of_block);

    //printf("score: %d\n", score);
    /*fread(block, sizeof(char), size_of_block, file);
    score += length_of_strings(strings.text + score, block, size_of_block);
    printf("score: %d\n", score);
    //for(int i = 0; i < result.length; i++) printf("%d ",result.array_of_indexes[i]);
    //putchar('\n');*/
    //printf("%s\n%s\n", strings.text[0], strings.text[1]);
    exit(1);
    fclose(file);
    return strings;
}

void write_strings_into_file(char* name_of_file, char *text[], uint32_t number_of_strings_in_text){
    uint32_t size_of_block = 0;
    for(uint32_t i = 0; i < number_of_strings_in_text; i++){
        uint32_t len = strlen(text[i]);
        if(len > size_of_block) size_of_block = len + 1;
    }
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
        free(array);
        //write(1, array, size_for_array);
    }
    char block[size_of_block];
    for(uint32_t i = 0; i < size_of_block; i++) block[i] = 0;
    uint8_t current_size_of_strings = 0;
    for(size_t i = 0; i < number_of_strings_in_text; i++){
        size_t size = strlen(text[i])+1;
        if(size <= size_of_block - current_size_of_strings){
            memcpy(block+current_size_of_strings, text[i], size);
        }
        else{
            //write(1, block, size_of_block);
            fwrite(block, sizeof(char), size_of_block, file);
            for(size_t i = 0; i < size_of_block; i++)
                block[i] = 0;
        }
            memcpy(block, text[i], size); // возможно переполнение...
        current_size_of_strings += size;
    }
    //write(1, block, size_of_block);
    fwrite(block, sizeof(char), size_of_block, file);
    fclose(file);
}