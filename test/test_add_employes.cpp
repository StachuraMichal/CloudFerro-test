#include <iostream>
#include <string>
#include "server.h"
#include "utilities.h"
#include <unordered_map>
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
    new_employee.insert({"nazwisko", ""});
    new_employee.insert({"data_urodzenia", "1.08.1905"});
    new_employee.insert({"stanowisko", "brak"});
    vector<string> surnames{
        "Anowski", "Bowski", "Cowski", "Dowski", "Eowski",
        "Fowski", "Gowski", "Howski", "Iowski", "Jowski"};
    for (int i = 0; i < 10; i++)
    {
        new_employee["nazwisko"] = surnames[i];
        server->insert_data(new_employee);
    }
    for (int i = 0; i < 10; i++)
    {
        auto respone = server->query_employee(surnames[i]);
        if (respone["nazwisko"] != surnames[i])
            throw;
    }
}