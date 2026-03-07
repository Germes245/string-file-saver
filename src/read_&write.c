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

uint32_t count_chars(char *array, char number, uint32_t length){
    uint32_t numbers = 0;
    for(uint32_t i = 0; i < length; i++) numbers += array[i] == number;
    return numbers;
}

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

typedef struct{
    char **text;
    uint32_t text_length;
    uint32_t not_full_string_length;
} readBlockResult;

readBlockResult read_block(char block[], uint32_t length_of_block){
    readBlockResult result;
    result.text_length = count_chars(block, 0, length_of_block);
    uint32_t *position = find_chars(result.text_length, block);
    int32_t index = 0;
    result.text = malloc(result.text_length);
    uint32_t i = 0;
    for(; i < result.text_length; i++){
        uint32_t length_ = position[i] - index + 1;
        result.text[i] = malloc(length_);
        memcpy(result.text[i], block + index, length_);
        index += length_;
    }
    free(position);
    return result;
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
    uint32_t score_of_strings = count_chars(block, 0, length_of_block);
    uint32_t *position = find_chars(score_of_strings, block);
    int32_t index = 0;
    char **text = malloc(score_of_strings);
    uint32_t i = 0;
    for(; i < score_of_strings; i++){
        uint32_t length_ = position[i] - index + 1;
        text[i] = malloc(length_);
        memcpy(text[i], block + index, length_);
        index += length_;
    }
    uint32_t not_full_string_length = 0;
    if(block[length_of_block - 1]){
        not_full_string_length = length_of_block - index;
        text = realloc(text, (++score_of_strings));
        //char not_full_string[not_full_string_length];
        text[score_of_strings-1] = malloc(not_full_string_length);
        memcpy(text[score_of_strings-1], block + index, not_full_string_length);
        //printf(text[score_of_strings-1]);
        //write(1, text[score_of_strings-1], not_full_string_length+2);
        i++;
    }
    printf("%d\n", not_full_string_length);
    //exit(1);
    free(position);
    length_of_block = fread(block, sizeof(char), sizeof(block), file); //bytes
    uint32_t score2 = count_chars(block, 0, length_of_block);
    score_of_strings += score2;
    position = find_chars(score2, block);
    printf("%s\n", text[score_of_strings-1]);
    if(not_full_string_length){
        text[score_of_strings-1] = realloc(text[score_of_strings-1], strlen(block) + 1 + not_full_string_length);
        memcpy(text[score_of_strings-1] + not_full_string_length, block, strlen(block));
        printf("strlen: %d\n", strlen(block));
    }
    printf("%s\n", text[score_of_strings-1]);
    //printf("i = %d\nscore: %d\n", i, score_of_strings);
    text = realloc(text, score_of_strings);
    index = 0;
    for(uint32_t i2 = 0; i < score_of_strings; i2++){
        uint32_t length_ = position[i2] - index + 1;
        //printf("shya %d\n", text[i]);
        text[i] = malloc(length_);
        memcpy(text[i], block + index, length_);
        index += length_;
        i++;
    }
    //printf("вывод строк:\n");
    //for(uint32_t i = 0; i < score_of_strings; i++) printf("%s\n", text[i]);

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
