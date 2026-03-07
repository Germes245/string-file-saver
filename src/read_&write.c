#include <stddef.h>
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

uint32_t count_chars(char *array, char number, uint32_t length){
    uint32_t numbers = 0;
    for(uint32_t i = 0; i < length; i++) numbers += array[i] == number;
    return numbers;
}

/*uint32_t count_chars_until_there_are_no_repeat_chars(char *array, char number, uint32_t length){
    uint32_t numbers = 0;
    for(uint32_t i = 0; i < length - 1; i++){
        uint8_t bool_ = array[i] == number;
        numbers += bool_;
        if(bool_ && array[i + 1] == number) break;
    }
    return numbers;
}*/

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

uint32_t *find_chars(uint32_t score_of_chars, char array[]){
    uint32_t *position = malloc(score_of_chars*sizeof(uint32_t));
    for(uint32_t i = 0, j = 0; j < score_of_chars; i++){
        if(array[i] == 0){
            //printf("%d\n", i);
            position[j] = i;
            j++;
        }
    }
    return position;
}

// нечистая функция
char_pointer_array read_strings_from_file(char* name_of_file){
    FILE *file = fopen(name_of_file, "rb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    char block[60];
    uint32_t length_of_block = fread(block, sizeof(char), sizeof(block), file); //bytes
    uint32_t score = count_chars(block, 0, length_of_block);
    uint32_t *position = find_chars(score, block);
    int32_t index = 0;
    char **text = malloc(score);
    uint32_t i = 0;
    for(; i < score; i++){
        uint32_t length_ = position[i] - index + 1;
        text[i] = malloc(length_);
        memcpy(text[i], block + index, length_);
        index += length_;
    }
    char *not_full_string, not_full_string_length = 0;
    if(block[length_of_block - 1]){
        not_full_string_length = length_of_block - index;
        not_full_string = malloc(not_full_string_length);
        memcpy(not_full_string, block + index, not_full_string_length);
        
    }
    free(position);
    length_of_block = fread(block, sizeof(char), sizeof(block), file); //bytes 
    uint32_t score2 = count_chars(block, 0, length_of_block);
    position = find_chars(score2, block);
    printf("i = %d\nscore: %d\n", i, score);
    text = realloc(text, score);
    for(; i < score; i++){
        uint32_t length_ = position[i] - index + 1;
        text[i] = malloc(length_);
        memcpy(text[i], block + index, length_);
        index += length_;
    }
    printf("вывод строк:\n");
    for(uint32_t i = 0; i < score; i++) printf("%s\n", text[i]);

    free(position);
    fclose(file);
    exit(1);
}

void write_strings_into_file(char* name_of_file, char *text[], uint32_t number_of_strings_in_text){
    FILE *file = fopen(name_of_file, "wb");
    if (file == NULL) {
        perror("Ошибка открытия");
        exit(1);
    }
    for(uint32_t i = 0; i < number_of_strings_in_text; i++){
        fwrite(text[i], sizeof(char), strlen(text[i])+1, file);
    }
    fclose(file);
}
