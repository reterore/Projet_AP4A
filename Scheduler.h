#ifndef PROJET_AP4A_SCHEDULER_H
#define PROJET_AP4A_SCHEDULER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <tuple>
#include "Sensor.h"  // Inclut les capteurs nécessaires

class Scheduler {
    // Chaque type de capteur est stocké dans un vecteur de tuples : (capteur, intervalle)
    std::vector<std::tuple<TemperatureSensor*, int>> m_temperatureSensors;
    std::vector<std::tuple<HumiditySensor*, int>> m_humiditySensors;
    std::vector<std::tuple<AirQualitySensor*, int>> m_airQualitySensors;
    std::vector<std::tuple<LightSensor*, int>> m_lightSensors;
    std::vector<std::tuple<NoiseLevelSensor*, int>> m_noiseLevelSensors;

    // Suivi du temps écoulé pour chaque capteur
    std::vector<std::chrono::steady_clock::time_point> m_lastUpdateTimes;

public:
    // Méthodes pour ajouter un capteur avec son intervalle
    void addSensor(TemperatureSensor* sensor, int interval);
    void addSensor(HumiditySensor* sensor, int interval);
    void addSensor(AirQualitySensor* sensor, int interval);
    void addSensor(LightSensor* sensor, int interval);
    void addSensor(NoiseLevelSensor* sensor, int interval);

    // Démarre le Scheduler avec une boucle infinie
    void simulation();

    // Démarre le Scheduler pour une durée limitée (en secondes)
    void simulation(int duration);

private:
    // Met à jour chaque capteur en fonction de son intervalle
    void updateSensors();
};

#endif // PROJET_AP4A_SCHEDULER_H
