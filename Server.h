#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

class Server {
    std::string m_name;
    int m_version;
    std::map<std::string, std::vector<std::string>> m_sensorData;

public:
    Server(std::string name, int version);

    Server(const Server& other);

    Server& operator=(const Server& other);

    ~Server();

    void receiveData(const std::string& sensorType, const std::string& data);

    void consoleWrite() const;

    void fileWrite() const;

    friend std::ostream& operator<<(std::ostream& os, const Server& server);
};

#endif // SERVER_H
