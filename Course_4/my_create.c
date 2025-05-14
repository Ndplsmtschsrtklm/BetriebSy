#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    //Überprüfen ob die Argumente ['filename'.txt] [text] übergeben wurden
    if (argc != 3){
        printf("Usage: %s [filename.txt] [\"text\"]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    char *text = argv[2];

    FILE *file;

    //Öffnen der Datei zum Schreiben (w), Wenn Datei nicht exestiert wird sie erstellt.
    file = fopen(filename, "w");

    // Wenn das Öffnen der Datei fehlschlägt, gib eine Fehlermeldung aus und beende das Programm.
    if (file == NULL){
        perror("[-] Error: Open file");
        exit(EXIT_FAILURE);
    }

    //String in die Datei schreiben
    fprintf(file, "%s",text);

    //File schließen
    fclose(file);

    printf("[+] Datei %s wurde erfolgreich erstellt.\n", filename);
    return 0;
}
// schreibt den übergebenen Text in eine angegebene Datei (erstellt sie neu oder überschreibt sie)
