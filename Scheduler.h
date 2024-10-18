#ifndef PROJET_AP4A_SCHEDULER_H
#define PROJET_AP4A_SCHEDULER_H

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <tuple>
#include "Sensor.h"

class Scheduler {

    // Liste de tuples contenant un capteur et son intervalle d'envoi en secondes
    std::vector<std::tuple<Sensor*, int>> m_sensors;

public:
    // Ajoute un capteur à la liste des capteurs avec un intervalle de temps
    void addSensor(Sensor* sensor, int interval) {
        m_sensors.push_back(std::make_tuple(sensor, interval));
    }

    // Fonction qui démarre le Scheduler
    void start() {
        using clock = std::chrono::steady_clock;
        auto startTime = clock::now();  // Capture le temps de démarrage

        while (true) {
            auto currentTime = clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // Temps écoulé en secondes

            for (auto& sensor_tuple : m_sensors) {
                Sensor* sensor = std::get<0>(sensor_tuple);  // Récupère le capteur
                int interval = std::get<1>(sensor_tuple);    // Récupère l'intervalle en secondes

                // Appelle la fonction du capteur si le temps écoulé modulo l'intervalle est 0
                if (elapsedSeconds % interval == 0) {
                    sensor->sendData();
                }
            }

            // Attendre 1 seconde avant de vérifier à nouveau
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    void start(int duration) {
        using clock = std::chrono::steady_clock;
        auto startTime = clock::now();  // Capture le temps de démarrage

        while (true) {
            auto currentTime = clock::now();
            auto elapsedSeconds = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime).count(); // Temps écoulé en secondes

            // Arrêter la boucle lorsque la durée spécifiée est atteinte
            if (elapsedSeconds >= duration) {
                break;
            }

            for (auto& sensor_tuple : m_sensors) {
                Sensor* sensor = std::get<0>(sensor_tuple);  // Récupère le capteur
                int interval = std::get<1>(sensor_tuple);    // Récupère l'intervalle en secondes

                // Appelle la fonction du capteur si le temps écoulé modulo l'intervalle est 0
                if (elapsedSeconds % interval == 0) {
                    sensor->sendData();
                }
            }

            // Attendre 1 seconde avant de vérifier à nouveau
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

};

#endif //PROJET_AP4A_SCHEDULER_H
