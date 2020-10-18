#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <sw/redis++/redis++.h>
#include <pqxx/pqxx>


struct ConnectionData 
{
    std::string host, pg_port, dbname, user, password, redis_port;

    ConnectionData(std::string pg_port, std::string dbname, std::string user, std::string password, std::string redis_port);
};

class MyServer 
{
private:
    std::unique_ptr<sw::redis::Redis> redis = NULL;
    std::unique_ptr<pqxx::connection> pg_connection = NULL;

public:
    MyServer(ConnectionData &con);
    ~MyServer();
    std::string connect(ConnectionData &con);
    bool insert_data(std::unordered_map<std::string, std::string>& data);
    std::unordered_map<std::string, std::string> query_employee(std::string surname);
    std::string status();
};
