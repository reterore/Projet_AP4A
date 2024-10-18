#include "Server.h"
#include <chrono>  // Pour obtenir le timestamp
#include <iomanip> // Pour formater le timestamp
#include <sstream> // Pour convertir le timestamp en chaîne de caractères
#include <fstream> // Pour manipuler les fichiers
#include <iostream>
#include <map>
#include <iomanip> // Pour std::setprecision
#include <filesystem> // Pour gérer les fichiers et répertoires

namespace fs = std::filesystem;

// Constructeur par défaut
Server::Server(std::string name, int version) {
    m_name = std::move(name);
    m_version = version;
    std::cout << "Server initialized." << std::endl;

    // Créer les fichiers CSV pour chaque type de capteur
    createCSVFiles();
}

// Autres constructeurs et opérateurs ...

Server::~Server() {
    std::cout << "Server destroyed." << std::endl;
}

bool fileExists(const std::string& fileName) {
    std::ifstream infile(fileName);
    return infile.good();
}

void Server::createCSVFiles() {
    // Créer un dossier avec le nom du serveur et sa version
    std::string dirName = m_name + "_" + std::to_string(m_version);
    fs::create_directory(dirName);  // Créer le dossier s'il n'existe pas

    std::map<std::string, std::string> sensorFiles = {
            {"Temperature", dirName + "/temperature_log.csv"},
            {"Humidity", dirName + "/humidity_log.csv"},
            {"Air_quality", dirName + "/air_quality_log.csv"},
            {"Light", dirName + "/light_log.csv"},
            {"Noise_level", dirName + "/noise_level_log.csv"}
    };

    for (const auto& entry : sensorFiles) {
        const std::string& fileName = entry.second;

        if (!fileExists(fileName)) {
            std::ofstream logFile(fileName);
            if (logFile.is_open()) {
                // En-tête avec unités spécifiques pour chaque capteur
                if (entry.first == "Temperature") {
                    logFile << "Date;Time;Sensor ID;Value (°C)\n";  // Séparation de la date et de l'heure
                } else if (entry.first == "Humidity") {
                    logFile << "Date;Time;Sensor ID;Value (%)\n";   // Humidité en %
                } else if (entry.first == "Air_quality") {
                    logFile << "Date;Time;Sensor ID;Value (ppm)\n"; // Qualité de l'air en ppm
                } else if (entry.first == "Light") {
                    logFile << "Date;Time;Sensor ID;Value (lux)\n";  // Lumière en lux
                } else if (entry.first == "Noise_level") {
                    logFile << "Date;Time;Sensor ID;Value (dB)\n";   // Niveau de bruit en dB
                }

                logFile.close();
                std::cout << "Created empty file: " << fileName << " with header." << std::endl;
            } else {
                std::cerr << "Error creating file: " << fileName << std::endl;
            }
        }
    }
}


void Server::receiveData(double data, int sensorId, const std::string& sensorType) {
    // Map associant les types de capteurs aux noms de fichiers CSV
    std::string dirName = m_name + "_" + std::to_string(m_version);
    std::map<std::string, std::string> sensorFiles = {
            {"Temperature", dirName + "/temperature_log.csv"},
            {"Humidity", dirName + "/humidity_log.csv"},
            {"Air_quality", dirName + "/air_quality_log.csv"},
            {"Light", dirName + "/light_log.csv"},
            {"Noise_level", dirName + "/noise_level_log.csv"}
    };

    // Rechercher le fichier correspondant au type de capteur
    auto it = sensorFiles.find(sensorType);
    if (it == sensorFiles.end()) {
        std::cerr << "Unknown sensor type: " << sensorType << std::endl;
        return;  // Sortir si le type de capteur est inconnu
    }

    std::string fileName = it->second;

    // Ouvrir le fichier en mode append (ajout)
    std::ofstream logFile(fileName, std::ios::app);
    if (!logFile) {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return;
    }

    std::string currentDate = getCurrentDate(); // Récupérer la date
    std::string currentTime = getCurrentTime(); // Récupérer l'heure
    // Écrire les données du capteur dans le fichier avec une précision fixée
    logFile << currentDate << ";" << currentTime << ";" << sensorId << ";" << std::fixed << std::setprecision(2) << data << "\n";
    logFile.close();

    std::cout << "Sensor's data for " << sensorType << " has been written to the file " << fileName << std::endl;
}

std::string Server::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d"); // Format de la date
    return ss.str();
}

std::string Server::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%H:%M:%S"); // Format de l'heure
    return ss.str();
}


void Server::consoleWrite() const {
    std::cout << "Server Name: " << m_name << ", Version: " << m_version << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "Server Name: " << server.m_name << ", Version: " << server.m_version << std::endl;
    return os;
}
