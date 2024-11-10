#ifndef SERVER_H
#define SERVER_H

#include <string>
#include <map>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <chrono>

template<typename T>
class Sensor;

namespace fs = std::filesystem;

class Server {
private:
    std::string m_name;
    int m_version;

    // Méthode pour créer des fichiers CSV pour chaque type de capteur
    void createCSVFiles();

    // Méthodes pour obtenir la date et l'heure actuelles
    std::string getCurrentDate();
    std::string getCurrentTime();

public:
    // Constructeur et destructeur
    Server(std::string name, int version);
    Server(Server& other);
    ~Server();

    // Opérateur d'affectation par copie
    Server& operator=(const Server& other);

    // Méthode mesure pour enregistrer les données du capteur
    template <typename T>
    void mesure(Sensor<T>* sensor);

    // Méthodes pour afficher et enregistrer les données du capteur
    template <typename T>
    void consoleWrite(const Sensor<T>* sensor) const;

    template <typename T>
    void fileWrite(const Sensor<T>* sensor);

    template <typename T>
    void checkThreshold(const Sensor<T>* sensor, double threshold);

    // Surcharge de l'opérateur << pour l'affichage
    friend std::ostream& operator<<(std::ostream& os, const Server& server);
};

// Définition des méthodes template directement dans le fichier d’en-tête

template <typename T>
void Server::mesure(Sensor<T>* sensor) {
    consoleWrite(sensor);
    fileWrite(sensor);
}

template <typename T>
void Server::consoleWrite(const Sensor<T>* sensor) const {
    std::cout << "Sensor ID: " << sensor->getId()
              << ", Type: " << sensor->getType()
              << ", Data: " << std::fixed << std::setprecision(2) << sensor->getData()
              << std::endl;
}

template <typename T>
void Server::fileWrite(const Sensor<T>* sensor) {
    std::string dirName = m_name + "_" + std::to_string(m_version);
    std::map<std::string, std::string> sensorFiles = {
            {"Temperature", dirName + "/temperature_log.csv"},
            {"Humidity", dirName + "/humidity_log.csv"},
            {"Air_quality", dirName + "/air_quality_log.csv"},
            {"Light", dirName + "/light_log.csv"},
            {"Noise_level", dirName + "/noise_level_log.csv"}
    };

    auto it = sensorFiles.find(sensor->getType());
    if (it == sensorFiles.end()) {
        std::cerr << "Unknown sensor type: " << sensor->getType() << std::endl;
        return;
    }

    std::ofstream logFile(it->second, std::ios::app);
    if (!logFile) {
        std::cerr << "Error opening file: " << it->second << std::endl;
        return;
    }

    logFile << getCurrentDate() << ";" << getCurrentTime() << ";" << sensor->getId() << ";"
            << std::fixed << std::setprecision(2) << sensor->getData() << "\n";
    logFile.close();

    std::cout << "Sensor's data for " << sensor->getType()
              << " has been written to the file " << it->second << std::endl;
}

template <typename T>
void Server::checkThreshold(const Sensor<T>* sensor, double threshold) {
    double data = sensor->getData();
    if (data > threshold) {
        std::cout << "Alert! Sensor ID: " << sensor->getId()
                  << " of type " << sensor->getType()
                  << " has exceeded the threshold with a value of " << data
                  << std::endl;
    }
}


#endif // SERVER_H
