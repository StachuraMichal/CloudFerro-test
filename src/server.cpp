#include <iostream>

#include <string>
#include <vector>
#include <chrono>
#include "server.h"
#include <exception>

ConnectionData::ConnectionData(
    std::string pg_port,
    std::string dbname,
    std::string user,
    std::string password,
    std::string redis_port) : pg_port{pg_port}, dbname{dbname}, user{user},
                              password{password}, redis_port{redis_port}
{

    this->host = "localhost";
}

MyServer::MyServer(ConnectionData &con)
{
    std::string redis_connenction = con.host == "localhost" ? "tcp://127.0.0.1:" + con.redis_port : throw "only localhost is accepted";

    std::string pg_connection_string = "host=" + con.host +
                                       " port=" + con.pg_port +
                                       " dbname=" + con.dbname +
                                       " user=" + con.user +
                                       " password=" + con.password;

    this->redis = std::unique_ptr<sw::redis::Redis>(new sw::redis::Redis(redis_connenction.c_str()));

    this->pg_connection = std::unique_ptr<pqxx::connection>(new pqxx::connection(pg_connection_string.c_str()));
    pqxx::work wrk(*pg_connection);

    pqxx::result res = wrk.exec("select to_regclass('pracownicy')");
    for (auto record : res)
    {
        if (record[0].is_null())
        {
            wrk.exec(
                "CREATE TABLE pracownicy ("
                "imie VARCHAR ( 50 )  NOT NULL, "
                "nazwisko VARCHAR ( 50 ) NOT NULL, "
                "data_urodzenia DATE  NOT NULL, "
                "stanowisko VARCHAR ( 50 ) )");
            wrk.commit();
        }
    }
}

MyServer::~MyServer()
{
}

std::unordered_map<std::string, std::string> MyServer::query_employee(std::string surname)
{
    std::unordered_map<std::string, std::string> response;
    this->redis->hgetall(surname, std::inserter(response, response.begin()));

    if (!response.empty())
    {
        response.insert({"from", "cache"});
        response.insert({"status", "ok"});
        return response;
    }

    pqxx::work wrk(*this->pg_connection);
    pqxx::result res = wrk.exec("select * from pracownicy where nazwisko =" + wrk.quote(surname) + "limit 1");
    if (res.empty())
    {
        response.insert({"status", "not found"});
        return response;
    }
    for (auto row : res)
    {
        for (auto pos : row)
        {
            response.insert({pos.name(), pos.c_str()});
        }
    }
    this->redis->hmset(response.at("nazwisko"), response.begin(), response.end());
    this->redis->expire(response.at("nazwisko"), std::chrono::seconds(120));

    response.insert({"from", "postgres"});
    response.insert({"status", "ok"});

    return response;
}

bool MyServer::insert_data(std::unordered_map<std::string, std::string>& data){
    pqxx::work wrk(*this->pg_connection);
    std::string string_values = "";
    std::string string_columns = "";

    try{
        for (auto it: data) {
            string_columns += wrk.quote_name(it.first)+",";
            string_values += wrk.quote(it.second)+",";
        }
        string_values.erase(string_values.end()-1);
        string_columns.erase(string_columns.end()-1);
        wrk.exec0("insert into pracownicy ("+string_columns+") values ("+string_values+")");
        wrk.commit();
    }
    catch(std::exception& e) {
        std::cout<<e.what()<<std::endl;
        return false;
    }
    return true;
}


void MyServer::ping()
{
    std::cout << "Pong" << std::endl;
}

std::string MyServer::status()
{
    if (this->redis->ping() == "PONG" && this->pg_connection->is_open() == true)
        return "ok";
    if (this->redis->ping() == "PONG")
        return "something wrong with postgres!";
    if (this->pg_connection->is_open() == true)
        return "something wrong with redis!";
    return "something wrong with redis and postgres!";
}