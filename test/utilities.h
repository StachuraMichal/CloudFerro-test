#pragma once

#include "server.h"
#include <string>
#define TEST_DECORATOR(x) drop_table_pracownicy();\
    clearRedis();\
    x;\
    drop_table_pracownicy();\
    clearRedis()

using namespace std;

ConnectionData getConnectionData();

bool drop_table_pracownicy();
bool clearRedis();

unique_ptr<Server> getServer();

unique_ptr<pqxx::connection> get_connection();

struct Myexception : exception
{
    string msg;
    Myexception(string message);

    const char *what() const throw();
};
