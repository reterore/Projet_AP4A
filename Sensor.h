#include <string>
#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <map>
#include <typeinfo>
#include <type_traits>
#include "Server.h"

// Interface Sensor with template
template <typename T>
class Sensor {
protected:
    int m_id;                     // Sensor identifier
    std::string m_type;          // Sensor type
    Server* m_server;            // Associated server
    T m_data;                    // Sensor data
    T m_lowerBound;              // Lower limit
    T m_upperBound;              // Upper limit

public:
    Sensor(int id, const std::string& type, Server* server, T lowerBound, T upperBound)
            : m_id(id), m_type(type), m_server(server), m_data(T{}),
              m_lowerBound(lowerBound), m_upperBound(upperBound) {}

    virtual ~Sensor() = default;

    // Pure virtual method to update sensor data
    virtual void update() = 0;

    // Method to get data
    virtual T getData() const { return m_data; }

    // Accessors for sensor information
    int getId() const { return m_id; }
    std::string getType() const { return m_type; }
};

// Air Quality Sensor with double as data type
class AirQualitySensor : public Sensor<double> {
public:
    AirQualitySensor(int id, Server* server)
            : Sensor<double>(id, "Air_quality", server, 0.0, 500.0) {}

    void update() override {
        std::random_device rd;
        std::mt19937 gen(rd());

        // Ensure m_data doesn't start at zero or 50
        if (m_data <= 0 || m_data == 50) {
            std::uniform_real_distribution<> initial_dis(m_lowerBound + 1, m_upperBound - 1);
            m_data = initial_dis(gen);
        }

        // Reduced variation to a maximum of 3%
        std::uniform_real_distribution<> dis(0.97, 1.03);
        m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data * dis(gen)));

        // Random pollution spike
        if (std::uniform_real_distribution<>(0.0, 1.0)(gen) > 0.98) {
            m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data + 20.0));
        }

        if (m_server) {
            m_server->mesure(this);
        }
    }
};

// Light Sensor with bool as data type
// Light Sensor with bool as data type
class LightSensor : public Sensor<bool> {
public:
    LightSensor(int id, Server* server)
            : Sensor<bool>(id, "Light", server, false, true) {}

    void update() override {
        std::random_device rd;
        std::mt19937 gen(rd());

        std::uniform_real_distribution<> dayNightCycle(0.0, 1.0);

        // Generate a random number to determine if we switch the state
        std::uniform_int_distribution<> chanceDistribution(1, 500);
        int chance = chanceDistribution(gen);

        // Change state if the random number is 1 (1/500 chance)
        if (chance == 1) {
            m_data = !m_data;  // Invert the current state
        } else {
            m_data = dayNightCycle(gen) > 0.15;  // Maintain the previous logic
        }

        if (m_server) {
            m_server->mesure(this);
        }
    }
};


// Noise Level Sensor with int as data type
class NoiseLevelSensor : public Sensor<int> {
public:
    NoiseLevelSensor(int id, Server* server)
            : Sensor<int>(id, "Noise_level", server, 30, 120) {
        // Initialiser m_data avec une valeur aléatoire dans les limites
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> initial_dis(m_lowerBound, m_upperBound);
        m_data = initial_dis(gen);
    }

    void update() override {
        std::random_device rd;
        std::mt19937 gen(rd());

        // Reduced variation to a maximum of 3%
        std::uniform_real_distribution<> dis(0.97, 1.03);
        m_data = std::max(m_lowerBound, std::min(m_upperBound, static_cast<int>(m_data * dis(gen))));

        // Random noise spike
        if (std::uniform_real_distribution<>(0.0, 1.0)(gen) > 0.98) {
            m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data + 20));
        }

        if (m_server) {
            m_server->mesure(this);
        }
    }
};

// Temperature Sensor with double as data type
class TemperatureSensor : public Sensor<double> {
public:
    TemperatureSensor(int id, Server* server)
            : Sensor<double>(id, "Temperature", server, -40.0, 85.0) {}

    void update() override {
        std::random_device rd;
        std::mt19937 gen(rd());

        // Reduced variation to a maximum of 3%
        std::uniform_real_distribution<> dis(0.97, 1.03);
        m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data * dis(gen)));

        if (m_server) {
            m_server->mesure(this);
        }
    }
};

// Humidity Sensor with int as data type
class HumiditySensor : public Sensor<int> {
public:
    HumiditySensor(int id, Server* server)
            : Sensor<int>(id, "Humidity", server, 10, 90) {
        // Initialiser m_data avec une valeur aléatoire dans les limites
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> initial_dis(m_lowerBound, m_upperBound);
        m_data = initial_dis(gen);
    }

    void update() override {
        std::random_device rd;
        std::mt19937 gen(rd());

        // Generate a change percentage between -2% and +1%
        std::uniform_real_distribution<> dis(-0.02, 0.01);
        double changePercentage = dis(gen); // Get a random change percentage

        // Apply the change percentage to the current humidity value
        m_data = static_cast<int>(m_data * (1 + changePercentage));

        // Ensure the new humidity value is within the defined bounds
        m_data = std::max(m_lowerBound, std::min(m_upperBound, m_data));

        if (m_server) {
            m_server->mesure(this);
        }
    }
};
