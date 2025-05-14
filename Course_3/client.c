#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    // Überprüfen, ob die IP_Adresse und er Port als Argumente übergeben wurden
    if(argc != 3){
        printf("Usage: %s <IP> <port>\n", argv[0]);
        return 1;
    }
    char *server_ip = argv[1];
    int port = atoi(argv[2]);

    // 1. Ein Socket erstellen
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket == -1){
        perror("[-] Cannot create socket.\n");
        return 1;
    }
    printf("[+] Created socket.\n");

    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address)); // Den Speicher mit 0 initialisieren: sonst Müll
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = inet_addr(server_ip);  // IP-Adresse in binäre Form umwandeln
    
    // 3. Zum Server verbinden
    if(connect(client_socket, (struct sockaddr *) &server_address, sizeof(server_address)) == -1){
        perror("[-] Connection faild.\n");
        close(client_socket);
        return 1;
    }
    printf("[+] Connected to server.\n");

    while (1) {
        printf("\nGeben eine Nachricht ein (oder 'exit' zum Beenden): ");
        char client_message[256];
        fgets(client_message, sizeof(client_message), stdin);
        client_message[strcspn(client_message, "\n")] = '\0';

        // Wenn der Benutzer "exit" eingibt, beenden Sie die Schleife.
        if (strcmp(client_message, "exit") == 0) {
            break;
        }

        // Deine Nachricht wird an den Server gesendet
        ssize_t bytes_sent = send(client_socket, client_message, strlen(client_message), 0);
        if (bytes_sent == -1) {
            perror("[-] Error sending client message.\n");
            break;
        }

        // Du erhälst eine Antwort vom Server
        char buffer[256];
        ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received == -1) {
            perror("[-] Error receiving message.\n");
            break;
        } else if (bytes_received == 0) {
            printf("[-] Server closed the connection.\n");
            break;
        }
        buffer[bytes_received] = '\0';  // Null-Terminator hinzufügen
        printf("[Server]: %s\n", buffer);

        //close(client_socket);
        printf("\n[+] Disconnectet from Server\n");
        return 0;
    }

    
    close(client_socket);

    return 0;
}
// einfacher TCP-Client, der sich mit einem Server verbindet, Nachrichten schickt und Antworten empfängt (bis "exit" eingegeben wird)
