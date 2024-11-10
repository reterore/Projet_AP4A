#ifndef SENSOR_H
#define SENSOR_H

#include <string>
#include <random>
#include "Server.h"

// Déclaration de la classe template Sensor
template <typename T>
class Sensor {
protected:
    int m_id;                     // Identifiant du capteur
    std::string m_type;          // Type du capteur
    Server* m_server;            // Serveur associé
    T m_data;                    // Donnée du capteur
    T m_lowerBound;              // Limite inférieure
    T m_upperBound;              // Limite supérieure

public:
    Sensor(int id, const std::string& type, Server* server, T lowerBound, T upperBound);

    virtual ~Sensor() = default;

    // Méthode pure virtuelle pour mettre à jour les données du capteur
    virtual void update() = 0;

    // Méthode pour obtenir les données du capteur
    virtual T getData() const;

    // Accesseurs pour les informations du capteur
    int getId() const{
        return m_id;
    }

    std::string getType() const{
        return m_type;
    }
};

// Déclaration de la classe AirQualitySensor
class AirQualitySensor : public Sensor<double> {
public:
    AirQualitySensor(int id, Server* server);
    void update() override;
};

// Déclaration de la classe LightSensor
class LightSensor : public Sensor<bool> {
public:
    LightSensor(int id, Server* server);
    void update() override;
};

// Déclaration de la classe NoiseLevelSensor
class NoiseLevelSensor : public Sensor<int> {
public:
    NoiseLevelSensor(int id, Server* server);
    void update() override;
};

// Déclaration de la classe TemperatureSensor
class TemperatureSensor : public Sensor<double> {
public:
    TemperatureSensor(int id, Server* server);
    void update() override;
};

// Déclaration de la classe HumiditySensor
class HumiditySensor : public Sensor<int> {
public:
    HumiditySensor(int id, Server* server);
    void update() override;
};

#endif // SENSOR_H
