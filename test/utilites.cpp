#include "utilities.h"
#include <exception>

ConnectionData getConnectionData()
{
    return ConnectionData(
        "5431", "my_company", "postgres", "admin1", "6379");
}

Myexception::Myexception(string message) : msg{message} {}

const char *Myexception::what() const throw()
{
    return msg.c_str();
}

bool drop_table_pracownicy()
{
    try
    {
        auto con = getConnectionData();
        std::string pg_connection_string = "host=" + con.host +
                                           " port=" + con.pg_port +
                                           " dbname=" + con.dbname +
                                           " user=" + con.user +
                                           " password=" + con.password;
        pqxx::connection c(pg_connection_string.c_str());

        pqxx::work wrk(c);
        wrk.exec("DROP TABLE pracownicy");
        wrk.commit();
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool clearRedis()
{
    try
    {
        auto con = getConnectionData();
        std::string redis_connenction = con.host == "localhost" ? "tcp://127.0.0.1:" + con.redis_port : throw "only localhost is accepted";

        sw::redis::Redis redis(redis_connenction.c_str());
        redis.flushall();
        return true;
    }
    catch (...)
    {
        return false;
    }
}

unique_ptr<Server> getServer()
{
    auto con = getConnectionData();
    return unique_ptr<Server>(new Server(con));
}
