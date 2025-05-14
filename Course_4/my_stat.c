#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s [filename]\n", argv[0]);
        return 1;
    }
    char *filename = argv[1];

    struct stat fstat;
    if (stat(filename, &fstat) == -1) {
        perror("[-] Error getting file attributes");
        return 1;
    }

    printf("File Attributes for %s:\n", filename); // Dateiname
    printf("Size: %ld bytes\n", fstat.st_size); // Größe in Bytes
    printf("Filesystem Block Size: %ld\n", fstat.st_blksize); // Dateisystem-Blockgröße
    printf("Number of Blocks: %ld\n", fstat.st_blocks); // Anzahl der Blocks
    printf("Mode: %o\n", fstat.st_mode); // Zugrifsrechte
    printf("Owner User ID: %d\n", fstat.st_uid); // Eigentümer Benutzer ID
    printf("Owner Group ID: %d\n", fstat.st_gid); // Eigentümer Gruppen ID
    printf("Last Access Time: %s", ctime(&fstat.st_atime)); // Letzter Zugriffszeitpunkt
    printf("Last Modification Time: %s", ctime(&fstat.st_mtime)); // Letzter Änderungszeitpunkt
    printf("Last Status Change Time: %s", ctime(&fstat.st_ctime)); // Letzter Statusänderungszeitpunkt
    printf("Inode Number: %ld\n", fstat.st_ino); // Inode-Nummer
    printf("Number of Hard Links: %ld\n", fstat.st_nlink); // Anzahl der harten Links
    printf("Device File: %ld\n", fstat.st_dev); // Gerätedatei

    return 0;
}
// Gibt verschiedene Dateiattribute wie Größe, Zugriffsrechte, Änderungszeiten und Inode-Nummer für eine angegebene Datei aus

