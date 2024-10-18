#include <random>   // Pour std::random_device, std::mt19937, std::uniform_real_distribution
#include "Server.h"

using namespace std;

// Classe de base
class Sensor {
protected:
    int m_id;
    string m_type;
    double m_data;
    Server *m_server;
    double m_lowerBound; // Borne inférieure pour la valeur initiale
    double m_upperBound; // Borne supérieure pour la valeur initiale

public:
    Sensor(int id, const string& type, Server *server, double lowerBound, double upperBound)
            : m_id(id), m_type(type), m_server(server),
              m_lowerBound(lowerBound), m_upperBound(upperBound) {}

    virtual ~Sensor() {
        m_server = nullptr;
    }

    // Méthode pour générer et retourner les données du capteur
    virtual double fetchData() {
        static bool firstCall = true;
        std::random_device rd;
        std::mt19937 gen(rd());  // Générateur Mersenne Twister

        if (firstCall) {
            std::uniform_real_distribution<> dis(m_lowerBound, m_upperBound);
            m_data = dis(gen);
            firstCall = false;
        } else {
            std::uniform_real_distribution<> dis(0.9, 1.1);  // Variation entre 90% et 110%
            double variation = dis(gen);
            m_data *= variation;
        }
        return m_data;
    }

    void sendData() {
        m_server->receiveData(fetchData(), m_id, m_type);
    }
};

// Sous-classe HumiditySensor
class HumiditySensor : public Sensor {
public:
    HumiditySensor(int id, Server *server)
            : Sensor(id, "Humidity", server, 10.0, 90.0) { // Borne d'humidité : [10, 90] %
    }
};

// Sous-classe TemperatureSensor
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(int id, Server *server)
            : Sensor(id, "Temperature", server, -40.0, 85.0) { // Borne de température : [-40, 85] °C
    }
};

// Sous-classe AirQualitySensor
class AirQualitySensor : public Sensor {
public:
    AirQualitySensor(int id, Server *server)
            : Sensor(id, "Air_quality", server, 0.0, 500.0) { // Borne qualité de l'air : [0, 500] AQI
    }
};

// Sous-classe LightSensor
class LightSensor : public Sensor {
public:
    LightSensor(int id, Server *server)
            : Sensor(id, "Light", server, 0.0, 100000.0) { // Borne de luminosité : [0, 100000] lux
    }
};

// Sous-classe NoiseLevelSensor
class NoiseLevelSensor : public Sensor {
public:
    NoiseLevelSensor(int id, Server *server)
            : Sensor(id, "Noise_level", server, 30.0, 120.0) { // Borne de bruit : [30, 120] dB
    }
};
