#include "Sensor.h"
#include <algorithm>
#include <random>

// Implémentation du constructeur de Sensor
template <typename T>
Sensor<T>::Sensor(int id, const std::string& type, Server* server, T lowerBound, T upperBound)
        : m_id(id), m_type(type), m_server(server), m_data(T{}),
          m_lowerBound(lowerBound), m_upperBound(upperBound) {}

// Implémentation de la méthode getData
template <typename T>
T Sensor<T>::getData() const {
    return m_data;
}

// Implémentation de AirQualitySensor
AirQualitySensor::AirQualitySensor(int id, Server* server)
        : Sensor<double>(id, "Air_quality", server, 0.0, 500.0) {}

void AirQualitySensor::update() {
    std::random_device rd;
    std::mt19937 gen(rd());

    // Initialise m_data si nécessaire
    if (m_data <= 0 || m_data == 50) {
        std::uniform_real_distribution<> initial_dis(m_lowerBound + 1, m_upperBound - 1);
        m_data = initial_dis(gen);
    }

    std::uniform_real_distribution<> dis(0.97, 1.03);
    m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data * dis(gen)));

    if (std::uniform_real_distribution<>(0.0, 1.0)(gen) > 0.98) {
        m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data + 20.0));
    }

    if (m_server) {
        m_server->mesure(this);
        m_server->checkThreshold(this, 100.0);
    }
}

// Implémentation de LightSensor
LightSensor::LightSensor(int id, Server* server)
        : Sensor<bool>(id, "Light", server, false, true) {}

void LightSensor::update() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dayNightCycle(0.0, 1.0);
    std::uniform_int_distribution<> chanceDistribution(1, 500);
    int chance = chanceDistribution(gen);

    if (chance == 1) {
        m_data = !m_data;
    } else {
        m_data = dayNightCycle(gen) > 0.15;
    }

    if (m_server) {
        m_server->mesure(this);
    }
}

// Implémentation de NoiseLevelSensor
NoiseLevelSensor::NoiseLevelSensor(int id, Server* server)
        : Sensor<int>(id, "Noise_level", server, 30, 120) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> initial_dis(m_lowerBound, m_upperBound);
    m_data = initial_dis(gen);
}

void NoiseLevelSensor::update() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.97, 1.03);
    m_data = std::max(m_lowerBound, std::min(m_upperBound, static_cast<int>(m_data * dis(gen))));

    if (std::uniform_real_distribution<>(0.0, 1.0)(gen) > 0.98) {
        m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data + 20));
    }

    if (m_server) {
        m_server->mesure(this);
        m_server->checkThreshold(this, 85);
    }
}

// Implémentation de TemperatureSensor
// TemperatureSensor mise à jour avec une plage initiale entre 10 et 30°C
TemperatureSensor::TemperatureSensor(int id, Server* server)
        : Sensor<double>(id, "Temperature", server, 10.0, 30.0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> initial_dis(m_lowerBound, m_upperBound);
    m_data = initial_dis(gen);  // Initialise m_data dans la plage [10, 30]
}

void TemperatureSensor::update() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0.97, 1.03);  // Variation de ±3 %
    m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data * dis(gen)));

    if (m_server) {
        m_server->mesure(this);
        m_server->checkThreshold(this, 30.0);  // Vérifie si la température dépasse 30°C
    }
}

// HumiditySensor avec une tendance vers des valeurs autour de 20%
HumiditySensor::HumiditySensor(int id, Server* server)
        : Sensor<int>(id, "Humidity", server, 10, 90) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> initial_dis(25, 35);  // Initialise m_data autour de 30%
    m_data = initial_dis(gen);
}

void HumiditySensor::update() {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(-0.01, 0.02);  // Variation de -1 % à +2 %
    double changePercentage = dis(gen);

    m_data = static_cast<int>(m_data * (1 + changePercentage));
    m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data));

    if (m_server) {
        m_server->mesure(this);
        m_server->checkThreshold(this, 80);  // Vérifie si l'humidité dépasse 80%
    }
}

