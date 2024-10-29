#include "Server.h"
#include "Scheduler.h"

int main() {

    Scheduler scheduler;

    Server server("test_server", 1);

    // Utilisation des sous-classes spécifiques
    HumiditySensor sensor1(1, &server);
    TemperatureSensor sensor2(2, &server);
    AirQualitySensor sensor3(3, &server);
    LightSensor sensor4(4, &server);
    NoiseLevelSensor sensor5(5, &server);

    // Ajouter les capteurs au scheduler avec des intervalles différents
    scheduler.addSensor(&sensor1, 1);
    scheduler.addSensor(&sensor2, 1);
    scheduler.addSensor(&sensor3, 1);
    scheduler.addSensor(&sensor4, 1);
    scheduler.addSensor(&sensor5, 1);

    // Démarrer le scheduler pendant 10 secondes
    scheduler.simulation(40);

    // Afficher les données
    std::cout << server;

    return 0;
}
