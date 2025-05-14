#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    // Überprüfe, ob der Port als Argument übergeben wurde
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        return 1;
    }
    int port = atoi(argv[1]);

    // 1. Ein Socket erstellen: 
    // AF_INET = IPv4 Internet protocols, 
    // SOCK_STREAM = Provides sequenced, reliable, two-way, connection-based byte streams.  An out-of-band data transmission mechanism may be supported.
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Überprüfe, ob das Socket erfolgreich erstellt wurde
    if (server_socket == -1) {
        perror("[-] Cannot create socket.\n");
        return 1;
    }
    printf("[+] Create socket.\n");

    // 2. Den Socket an einen Port binden
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address)); // Den Speicher mit 0 initialisieren: Sonst könnte Müll in der Struktur vorkommen
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);  // Wandelt den Port in Network Byte Order um
    server_address.sin_addr.s_addr = INADDR_ANY; // Akzeptiere Verbindungen von jeder IP
    
    if(bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1){
        perror("[-] Cannot bind.\n");
        return 1;
    }
    printf("[+] Soket binded.\n");

    // 4. Eine Endlosschleife starten
    while (1){

        // 3. Den Socket als passiv markieren (listen)
        if(listen(server_socket, 5) == -1){
            perror("[-] Cannot listen.\n");
            return 1;
        }
        printf("[+] listen for new client...\n");

        // 5. Eine Verbindung akzeptieren
        int client_socket = accept(server_socket, NULL, NULL);
        if(client_socket == -1){
            perror("[-] Error accepting connection.\n");
            continue;
        }

        // 6. Nachricht vom Client verarbeiten
        // Puffer für die empfangene Nachricht
        char buffer[256];
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        buffer[bytes_received] = '\0';
        if(bytes_received <= 0){
            perror("[-] Connection closed or error receiving message from client.\n");
            close(client_socket);
            continue;
        }
        printf("[Client]: %s\n", buffer);

        // 7. Eine Antwort senden
        char server_message[] = "HALLO ICH BIN SERVER";
        ssize_t bytes_send =  send(client_socket, server_message, sizeof(server_message), 0);
        if(bytes_send == -1){
            perror("[-] Error sending server message.\n");
            continue;
        }
        close(client_socket);
        printf("\n[+] Client disconnected.\n");

    }
    close(server_socket);

    return 0;
}
// einfacher TCP-Server, der auf Verbindungen wartet, Nachrichten vom Client empfängt und mit einer festen Antwort reagiert
