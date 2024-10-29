#ifndef PROJET_AP4A_SCHEDULER_H
#define PROJET_AP4A_SCHEDULER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <tuple>
#include "Sensor.h"  // Assurez-vous d'avoir inclus le bon fichier d'en-tête

class Scheduler {
    // Chaque type de capteur a un tuple : (capteur, intervalle)
    std::vector<std::tuple<TemperatureSensor*, int>> m_temperatureSensors;
    std::vector<std::tuple<HumiditySensor*, int>> m_humiditySensors;
    std::vector<std::tuple<AirQualitySensor*, int>> m_airQualitySensors;
    std::vector<std::tuple<LightSensor*, int>> m_lightSensors;
    std::vector<std::tuple<NoiseLevelSensor*, int>> m_noiseLevelSensors;

    // Suivi du temps écoulé pour chaque capteur
    std::vector<std::chrono::steady_clock::time_point> m_lastUpdateTimes;

public:
    // Ajoute un capteur de température avec l'intervalle
    void addSensor(TemperatureSensor* sensor, int interval) {
        m_temperatureSensors.emplace_back(sensor, interval);
        m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
    }

    void addSensor(HumiditySensor* sensor, int interval) {
        m_humiditySensors.emplace_back(sensor, interval);
        m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
    }

    void addSensor(AirQualitySensor* sensor, int interval) {
        m_airQualitySensors.emplace_back(sensor, interval);
        m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
    }

    void addSensor(LightSensor* sensor, int interval) {
        m_lightSensors.emplace_back(sensor, interval);
        m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
    }

    void addSensor(NoiseLevelSensor* sensor, int interval) {
        m_noiseLevelSensors.emplace_back(sensor, interval);
        m_lastUpdateTimes.push_back(std::chrono::steady_clock::now());
    }

    // Fonction qui démarre le Scheduler avec une boucle infinie
    void simulation() {
        while (true) {
            // Met à jour chaque type de capteur indépendamment
            updateSensors();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Petite pause pour éviter une boucle trop rapide
        }
    }

    // Simulation avec durée limite
    void simulation(int duration) {
        using clock = std::chrono::steady_clock;
        auto startTime = clock::now();

        while (true) {
            auto currentTime = clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count();

            // Arrêter la boucle lorsque la durée spécifiée est atteinte
            if (elapsedSeconds >= duration) {
                break;
            }

            // Met à jour chaque type de capteur indépendamment
            updateSensors();
            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Petite pause pour éviter une boucle trop rapide
        }
    }

private:
    // Fonction pour mettre à jour chaque capteur en fonction de son intervalle
    void updateSensors() {
        auto currentTime = std::chrono::steady_clock::now();

        // Met à jour les capteurs de température
        for (size_t i = 0; i < m_temperatureSensors.size(); ++i) {
            auto& sensor_tuple = m_temperatureSensors[i];
            TemperatureSensor* sensor = std::get<0>(sensor_tuple);
            int interval = std::get<1>(sensor_tuple);
            auto& lastUpdateTime = m_lastUpdateTimes[i];

            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
                sensor->update();
                lastUpdateTime = currentTime; // Met à jour le temps de la dernière mise à jour
            }
        }

        // Met à jour les capteurs d'humidité
        for (size_t i = 0; i < m_humiditySensors.size(); ++i) {
            auto& sensor_tuple = m_humiditySensors[i];
            HumiditySensor* sensor = std::get<0>(sensor_tuple);
            int interval = std::get<1>(sensor_tuple);
            auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + i]; // Index ajusté

            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
                sensor->update();
                lastUpdateTime = currentTime;
            }
        }

        // Répétez pour les autres types de capteurs...
        for (size_t i = 0; i < m_airQualitySensors.size(); ++i) {
            auto& sensor_tuple = m_airQualitySensors[i];
            AirQualitySensor* sensor = std::get<0>(sensor_tuple);
            int interval = std::get<1>(sensor_tuple);
            auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + i]; // Index ajusté

            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
                sensor->update();
                lastUpdateTime = currentTime;
            }
        }

        for (size_t i = 0; i < m_lightSensors.size(); ++i) {
            auto& sensor_tuple = m_lightSensors[i];
            LightSensor* sensor = std::get<0>(sensor_tuple);
            int interval = std::get<1>(sensor_tuple);
            auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + m_airQualitySensors.size() + i]; // Index ajusté

            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
                sensor->update();
                lastUpdateTime = currentTime;
            }
        }

        for (size_t i = 0; i < m_noiseLevelSensors.size(); ++i) {
            auto& sensor_tuple = m_noiseLevelSensors[i];
            NoiseLevelSensor* sensor = std::get<0>(sensor_tuple);
            int interval = std::get<1>(sensor_tuple);
            auto& lastUpdateTime = m_lastUpdateTimes[m_temperatureSensors.size() + m_humiditySensors.size() + m_airQualitySensors.size() + m_lightSensors.size() + i]; // Index ajusté

            if (std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastUpdateTime).count() >= interval) {
                sensor->update();
                lastUpdateTime = currentTime;
            }
        }
    }
};

#endif // PROJET_AP4A_SCHEDULER_H
