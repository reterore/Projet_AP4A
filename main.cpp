#include "Server.h"

int main() {
    Server server("test_server", 1);

    // Simuler la réception de données de capteurs
    server.receiveData("temperature", "25.3");
    server.receiveData("humidity", "60%");
    server.receiveData("temperature", "26.1");
    server.receiveData("pressure", "1013 hPa");

    // Afficher les données dans la console
    server.consoleWrite();

    // Écrire les données dans les fichiers de logs
    server.fileWrite();

    // Utiliser l'opérateur << pour afficher les données
    std::cout << server;



    return 0;
}
