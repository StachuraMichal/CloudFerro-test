#include <iostream>
#include <string>
#include "server.h"
#include "utilities.h"
#include <chrono>
#include <thread>

using namespace std;

void test();

int main(int argc, char const *argv[])
{
    TEST_DECORATOR(test());
    return 0;
}


void test(){
    auto server = getServer();
    std::unordered_map<std::string, std::string> new_employee;
    new_employee.insert({"imie", "Kuba"});
    new_employee.insert({"nazwisko", "Aowski"});
    new_employee.insert({"data_urodzenia", "1.08.1905"});
    new_employee.insert({"stanowisko", "brak"});

    server->insert_data(new_employee);

    auto response = server->query_employee(new_employee["nazwisko"]);

    if (response["from"] != "postgres")
        throw Myexception(response["from"]);
    response.clear();
    response = server->query_employee(new_employee["nazwisko"]);
    if (response["from"] != "cache")
        throw Myexception(response["from"]);

    response.clear();
    this_thread::sleep_for(chrono::seconds(121));
    response = server->query_employee(new_employee["nazwisko"]);
    if (response["from"] != "postgres")
        throw Myexception(response["from"]);
}