#include <iostream>
#include <sw/redis++/redis++.h>
#include <pqxx/pqxx>
#include <string>
#include <vector>
#include "server.h"

using namespace sw::redis;

int main(int, char**) {
    ServerTools d;
    std::cout<<d.sanatize("dasd");
    ConnectionData initial_connection(
            "5431", "my_company", "postgres", "admin1", "6379"
    );

    MyServer server(initial_connection);
    //MyServer s1;
    //s1.ping();
    //MyServer s1;
    //s1.ping();
    std::cout << "Hello, world!\n";
   // auto redis = Redis("tcp://127.0.0.1:6379");
    //std::cout<<redis.ping()<<std::endl;
    // std::string con_s = ("host=localhost port=5431 dbname=my_company user=postgres password=admin1");
    // pqxx::connection con(con_s.c_str());
    // pqxx::work wrk(con);
    // pqxx::result res = wrk.exec("select * from employee");
    // if(res.size()<1){
    //     std::cout<<"łupsssss"<<std::endl;
    //     return -1;
    // }
    // for (auto record : res) {
    //     std::cout<<record[0]<<std::endl;
    // }

}
