#include <iostream>
#include <string>
#include <vector>
#include "server.h"


int main(int, char**) {

    ConnectionData initial_connection(
            "5431", "my_company", "postgres", "admin1", "6379"
    );

    MyServer server(initial_connection);
    auto res = server.query_employee("Stachura'; DROP TABLE users; --");
    for (auto& it: res) {
        std::cout<<it.first<<"\t"<<it.second<<std::endl;
    }
    std::cout<<server.status()<<std::endl;

    std::unordered_map<std::string, std::string> new_employee;
    new_employee.insert({"imide", "Kuba"});
    new_employee.insert({"nazwisko", "a"});
    new_employee.insert({"data_urodzenia", "1.08.1905"});
    new_employee.insert({"stanowisko", "brak"});

    server.insert_data(new_employee);
}
