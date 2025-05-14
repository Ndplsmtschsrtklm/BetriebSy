#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [filename.txt]\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];


    //Verschiedene Berechtigung für Dateien 
	//IRUSR: Leserecht für Eigentümer
	//IWUSR: Schreibrecht für Eigentümer
	//RDWR: Öffnen der Datei zum Lesen und Schreiben
    //CREAT: Erstellen der Datei, falls sie nicht existiert
    int file = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (file == -1) {
        perror("[-] Error open file");
        exit(EXIT_FAILURE);
    }

    // Den Dateizeiger an das Ende der Datei bewegen und 20 Leerzeichen schreiben
    lseek(file, 0, SEEK_END);
    char spaces[20] = "                    ";  // 20 Leerzeichen
    write(file, spaces, 20);

    // Text in die Datei schreiben
    char text[] = "mein beispiel Text";
    write(file, text, strlen(text));

    lseek(file, 0, SEEK_SET);

    char tempText[255 + 20];
    ssize_t bytesRead = read(file, tempText, sizeof(tempText) - 1);
    if (bytesRead == -1) {
        perror("[-] Error reading file");
        close(file);
        exit(EXIT_FAILURE);
    }
    tempText[bytesRead] = '\0';  // Null-Terminator hinzufügen
    printf("%s\n", tempText);

    close(file);

    return 0;
}
// Öffnet eine Datei zum Lesen und Schreiben, fügt 20 Leerzeichen ans Ende der Datei an 
// und schreibt dann einen Beispieltext. Anschließend wird der Inhalt der Datei ausgelesen und ausgegeben.
