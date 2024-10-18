#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>

class Server {
    std::string m_name;
    int m_version;

public:
    Server(std::string name, int version);

    Server(const Server& other);

    Server& operator=(const Server& other);

    ~Server();

    void receiveData(double data, int sensorId, const std::string& sensorType);

    void consoleWrite() const;

    friend std::ostream& operator<<(std::ostream& os, const Server& server);

    void createCSVFiles();

    std::string getCurrentDate();

    std::string getCurrentTime();

};

#endif // SERVER_H