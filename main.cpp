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
    scheduler.addSensor(&sensor2, 2);
    scheduler.addSensor(&sensor3, 3);
    scheduler.addSensor(&sensor4, 4);
    scheduler.addSensor(&sensor5, 5);

    // Démarrer le scheduler pendant 5 secondes
    scheduler.start(5);

    // Afficher les données
    std::cout << server;

    return 0;
}
