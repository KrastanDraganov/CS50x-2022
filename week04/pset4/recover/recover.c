#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

const int BLOCK_SIZE = 512;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *forensic_image = fopen(argv[1], "r");
    if (forensic_image == NULL)
    {
        printf("Couldn't open the image.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];

    int jpeg_counter = 0;
    FILE *current_jpeg = NULL;
    char current_filename[8];

    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, forensic_image) == BLOCK_SIZE)
    {
        bool is_jpeg_start = (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0);

        if (is_jpeg_start)
        {
            if (current_jpeg != NULL)
            {
                fclose(current_jpeg);
            }

            sprintf(current_filename, "%03i.jpg", jpeg_counter);
            ++jpeg_counter;

            current_jpeg = fopen(current_filename, "w");
        }

        if (current_jpeg != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, current_jpeg);
        }
    }

    if (current_jpeg != NULL)
    {
        fclose(current_jpeg);
    }
    fclose(forensic_image);

    return 0;
}