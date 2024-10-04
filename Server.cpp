#include "Server.h"

// Constructeur par défaut
Server::Server(std::string name, int version) {
    m_name = name;
    m_version = version;
    std::cout << "Server initialized." << std::endl;
}

Server::Server(const Server& other) {
    m_sensorData = other.m_sensorData;
    std::cout << "Server copied." << std::endl;
}

Server& Server::operator=(const Server& other) {
    if (this != &other) {
        m_sensorData = other.m_sensorData;
    }
    return *this;
}

Server::~Server() {
    std::cout << "Server destroyed." << std::endl;
}

void Server::receiveData(const std::string& sensorType, const std::string& data) {
    m_sensorData[sensorType].push_back(data);
}

void Server::consoleWrite() const {
    std::cout << "my name is " << m_name << "and my version is " << m_version << std::endl;
    for (const auto& pair : m_sensorData) {
        std::cout << "Sensor type: " << pair.first << std::endl;
        for (const std::string& data : pair.second) {
            std::cout << "  data: " << data << std::endl;
        }
    }
}

void Server::fileWrite() const {
    for (const auto& pair : m_sensorData) {
        std::string fileName = pair.first + "_log.csv";
        std::ofstream logFile(fileName, std::ios::app);

        if (logFile.is_open()) {
            for (const std::string& data : pair.second) {
                logFile << data << std::endl; // Écrire chaque donnée dans le fichier
            }
            logFile.close();
            std::cout << "Sensor's data " << pair.first << " wrote into the file" << fileName << std::endl;
        } else {
            std::cerr << "Error during the opening of the file " << fileName << std::endl;
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Server& server) {
    for (const auto& pair : server.m_sensorData) {
        os << "Sensor type: " << pair.first << std::endl;
        for (const std::string& data : pair.second) {
            os << "  Data: " << data << std::endl;
        }
    }
    return os;
}
