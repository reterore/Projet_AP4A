#include "Server.h"
#include <iostream>
#include <map>
#include <iomanip>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

// Constructeur et destructeur
Server::Server(std::string name, int version) : m_name(std::move(name)), m_version(version) {
    createCSVFiles();  // Crée les fichiers lors de l'initialisation du serveur
}

Server::Server(Server& other) {
    m_name = other.m_name;
    m_version = other.m_version;
    createCSVFiles();
}

Server::~Server() = default;

// Surcharge de l'opérateur <<
std::ostream& operator<<(std::ostream& os, const Server& server) {
    os << "Server Name: " << server.m_name
       << ", Version: " << server.m_version;
    return os;
}

// Méthode pour créer les fichiers CSV pour chaque type de capteur
void Server::createCSVFiles() {
    std::string dirName = m_name + "_" + std::to_string(m_version);
    fs::create_directories(dirName);

    std::map<std::string, std::string> sensorFiles = {
            {"Temperature", dirName + "/temperature_log.csv"},
            {"Humidity", dirName + "/humidity_log.csv"},
            {"Air_quality", dirName + "/air_quality_log.csv"},
            {"Light", dirName + "/light_log.csv"},
            {"Noise_level", dirName + "/noise_level_log.csv"}
    };

    // Créer les fichiers uniquement si aucun fichier n'existe et écrire les en-têtes
    for (const auto& file : sensorFiles) {
        if (!fs::exists(file.second)) {  // Vérifie si le fichier n'existe pas
            std::ofstream ofs(file.second, std::ios::app);
            if (!ofs) {
                std::cerr << "Failed to create or open file: " << file.second << std::endl;
            } else {
                // Écrire les en-têtes spécifiques pour chaque type de capteur
                if (file.first == "Temperature") {
                    ofs << "Date;Heure;Sensor ID;Data (°C)" << std::endl;  // En-tête pour Temperature
                } else if (file.first == "Humidity") {
                    ofs << "Date;Heure;Sensor ID;Data (%)" << std::endl;   // En-tête pour Humidity
                } else if (file.first == "Air_quality") {
                    ofs << "Date;Heure;Sensor ID;Data (PPM)" << std::endl; // En-tête pour Air Quality
                } else if (file.first == "Light") {
                    ofs << "Date;Heure;Sensor ID;Data (lux)" << std::endl;  // En-tête pour Light
                } else if (file.first == "Noise_level") {
                    ofs << "Date;Heure;Sensor ID;Data (dB)" << std::endl;   // En-tête pour Noise Level
                }
            }
        }
    }
}

// Méthodes pour obtenir la date et l'heure actuelles
std::string Server::getCurrentDate() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%Y-%m-%d");
    return ss.str();
}

std::string Server::getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%H:%M:%S");
    return ss.str();
}

Server& Server::operator=(const Server& other) {
    if (this != &other) { // Vérification pour éviter l'auto-affectation
        m_name = other.m_name;
        m_version = other.m_version;
        // Si nécessaire, du code pour copier d'autres ressources
    }
    return *this;
}
