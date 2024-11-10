#include "Scheduler.h"

// Ajoute un capteur de température
void Scheduler::addSensor(TemperatureSensor* sensor, int interval) {
    m_temperatureSensors.emplace_back(sensor, interval);
    m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
}

// Ajoute un capteur d'humidité
void Scheduler::addSensor(HumiditySensor* sensor, int interval) {
    m_humiditySensors.emplace_back(sensor, interval);
    m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
}

// Ajoute un capteur de qualité de l'air
void Scheduler::addSensor(AirQualitySensor* sensor, int interval) {
    m_airQualitySensors.emplace_back(sensor, interval);
    m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
}

// Ajoute un capteur de lumière
void Scheduler::addSensor(LightSensor* sensor, int interval) {
    m_lightSensors.emplace_back(sensor, interval);
    m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
}

// Ajoute un capteur de niveau sonore
void Scheduler::addSensor(NoiseLevelSensor* sensor, int interval) {
    m_noiseLevelSensors.emplace_back(sensor, interval);
    m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
}

// Fonction de simulation infinie du Scheduler
void Scheduler::simulation() {
    while (true) {
        updateSensors();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Fonction de simulation avec durée limitée
void Scheduler::simulation(int duration) {
    using clock = std::chrono::steady_clock;
    auto startTime = clock::now();

    while (true) {
        auto currentTime = clock::now();
        auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

        if (elapsedSeconds >= duration) {
            break;
        }

        updateSensors();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

// Met à jour chaque capteur en fonction de son intervalle
void Scheduler::updateSensors() {
    auto currentTime = std::chrono::steady_clock::now();

    // Met à jour les capteurs de température
    for (size_t i = 0; i < m_temperatureSensors.size(); ++i) {
        auto& sensor_tuple = m_temperatureSensors[i];
        TemperatureSensor* sensor = std::get<0>(sensor_tuple);
        int interval = std::get<1>(sensor_tuple);
        auto& lastUpdateTime = m_lastUpdateTimes[i];

        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
            sensor->update();
            lastUpdateTime = currentTime;
        }
    }

    // Met à jour les capteurs d'humidité
    for (size_t i = 0; i < m_humiditySensors.size(); ++i) {
        auto& sensor_tuple = m_humiditySensors[i];
        HumiditySensor* sensor = std::get<0>(sensor_tuple);
        int interval = std::get<1>(sensor_tuple);
        auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + i];

        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
            sensor->update();
            lastUpdateTime = currentTime;
        }
    }

    // Met à jour les capteurs de qualité de l'air
    for (size_t i = 0; i < m_airQualitySensors.size(); ++i) {
        auto& sensor_tuple = m_airQualitySensors[i];
        AirQualitySensor* sensor = std::get<0>(sensor_tuple);
        int interval = std::get<1>(sensor_tuple);
        auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + i];

        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
            sensor->update();
            lastUpdateTime = currentTime;
        }
    }

    // Met à jour les capteurs de lumière
    for (size_t i = 0; i < m_lightSensors.size(); ++i) {
        auto& sensor_tuple = m_lightSensors[i];
        LightSensor* sensor = std::get<0>(sensor_tuple);
        int interval = std::get<1>(sensor_tuple);
        auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + m_airQualitySensors.size() + i];

        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
            sensor->update();
            lastUpdateTime = currentTime;
        }
    }

    // Met à jour les capteurs de niveau sonore
    for (size_t i = 0; i < m_noiseLevelSensors.size(); ++i) {
        auto& sensor_tuple = m_noiseLevelSensors[i];
        NoiseLevelSensor* sensor = std::get<0>(sensor_tuple);
        int interval = std::get<1>(sensor_tuple);
        auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + m_airQualitySensors.size() + m_lightSensors.size() + i];

        if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
            sensor->update();
            lastUpdateTime = currentTime;
        }
    }
}
