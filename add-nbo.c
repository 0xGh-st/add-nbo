#include <stdio.h>
#include <stdint.h>

// endian change(big to little)
uint32_t bigEndianToLittleEndian(uint32_t value) {
    uint32_t result = ((value & 0xFF) << 24) |
                      ((value & 0xFF00) << 8) |
                      ((value & 0xFF0000) >> 8) |
                      ((value & 0xFF000000) >> 24);
    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("파일 경로를 제대로 입력해주세요.\n");
        return 1;
    }

    FILE *file_a, *file_b;
    uint32_t value_a, value_b, sum;

    
    file_a = fopen(argv[1], "rb");
    file_b = fopen(argv[2], "rb");

    if (file_a == NULL || file_b == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    // read binary
    fread(&value_a, sizeof(uint32_t), 1, file_a);
    fread(&value_b, sizeof(uint32_t), 1, file_b);

    // change endian 
    value_a = bigEndianToLittleEndian(value_a);
    value_b = bigEndianToLittleEndian(value_b);

   
    sum = value_a + value_b;

    // result
    printf("%u(0x%x) + %u(0x%x) = %u(0x%x)\n", value_a, value_a, value_b, value_b, sum, sum);

    
    fclose(file_a);
    fclose(file_b);

    return 0;
}

