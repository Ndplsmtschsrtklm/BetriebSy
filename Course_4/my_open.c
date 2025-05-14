#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if (argc != 2){
        printf("Usage: %s [filename.txt]\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    FILE *file;
    char tempText[255];
    file = fopen(filename, "r");
    if (file == NULL){
        perror("[-] Error: Open file");
        exit(EXIT_FAILURE);
    }
    fgets(tempText, 255, (FILE*)file);

    printf("%s\n", tempText);
    fclose(file);

    return 0;
}
// Öffnet eine Datei zum Lesen, liest die erste Zeile und gibt sie auf der Konsole aus
