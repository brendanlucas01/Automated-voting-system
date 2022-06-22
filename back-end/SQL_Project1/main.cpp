#include "crow.h"
#include <stdlib.h>
#include <iostream>
#include <ctime>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
//#include "crow_all.h"

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "";

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api/admin/login")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        int admin_id = stoi(req.url_params.get("admin_id"));

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM admin WHERE admin_id = (?)");
        pstmt->setInt(1, admin_id);
        res = pstmt->executeQuery();
        crow::json::wvalue x;
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /*cout << "name = " << res->getString("name") << endl;
                cout << "admin_id = " << res->getInt("admin_id") << endl;
                cout << "constituency = " << res->getString("constituency") << endl;
                cout << "password = " << res->getString("password_hash") << endl;
                cout << "event_id = " << res->getInt("event_id") << endl;*/
                x["name"] = res->getString("name");
                x["admin_id"] = res->getInt("admin_id");
                x["constituency"] = res->getString("constituency");
                x["password_hash"] = res->getString("password_hash");
                x["event_id"] = res->getInt("event_id");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    CROW_ROUTE(app, "/api/localadmin/dashboard")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        int admin_id = stoi(req.url_params.get("admin_id"));

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM voting_event WHERE event_id = (SELECT event_id FROM admin WHERE admin_id = (?))");
        pstmt->setInt(1, admin_id);
        res = pstmt->executeQuery();
        crow::json::wvalue x;
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /*cout << "event_id = " << res->getInt("event_id") << endl;
                cout << "status = " << res->getString("status") << endl;
                cout << "no_of_voters = " << res->getInt("no_of_voters") << endl;
                cout << "no_of_candidates = " << res->getInt("no_of_candidates") << endl;
                cout << "constituency = " << res->getString("constituency") << endl;*/
                x["event_id"] = res->getInt("event_id");
                x["status"] = res->getString("status");
                x["no_of_voters"] = res->getInt("no_of_voters");
                x["start_date"] = res->getString("start_date");
                x["end_date"] = res->getString("end_date");
                x["no_of_candidates"] = res->getInt("no_of_candidates");
                x["constituency"] = res->getString("constituency");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    CROW_ROUTE(app, "/api/dashboard")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        string constituency = req.url_params.get("constituency");

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM voting_event WHERE constituency = (?)");
        pstmt->setString(1, constituency);
        crow::json::wvalue x;
        res = pstmt->executeQuery();
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /* cout << "event_id = " << res->getInt("event_id") << endl;
                 cout << "status = " << res->getString("status") << endl;
                 cout << "no_of_voters = " << res->getInt("no_of_voters") << endl;
                 cout << "no_of_candidates = " << res->getInt("no_of_candidates") << endl;
                 cout << "constituency = " << res->getString("constituency") << endl;*/
                x["event_id"] = res->getInt("event_id");
                x["status"] = res->getString("status");
                x["no_of_voters"] = res->getInt("no_of_voters");
                x["start_date"] = res->getString("start_date");
                x["end_date"] = res->getString("end_date");
                x["no_of_candidates"] = res->getInt("no_of_candidates");
                x["constituency"] = res->getString("constituency");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    CROW_ROUTE(app, "/api/dashboard/vote")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        string vote = req.url_params.get("vote");
        long long int voter_id = stoll(req.url_params.get("voter_id"));
        int event_id = stoi(req.url_params.get("event_id"));

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("INSERT INTO voting (event_id, voter_id, vote) VALUES(?, ?, ?)");
        pstmt->setInt(1, event_id);
        pstmt->setInt(2, voter_id);
        pstmt->setString(3, vote);
        bool voted = pstmt->execute();
        if (voted)
            cout << "voted: " << voted << endl;

        delete pstmt;
        delete con;
        return voted;
        });

    CROW_ROUTE(app, "/api/localadmin/dashboard/result")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        int event_id = stoi(req.url_params.get("event_id"));

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM voting_event WHERE event_id = (?)");
        pstmt->setInt(1, event_id);
        res = pstmt->executeQuery();
        crow::json::wvalue x;
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /*cout << "event_id = " << res->getInt("event_id") << endl;
                cout << "status = " << res->getString("status") << endl;
                cout << "no_of_voters = " << res->getInt("no_of_voters") << endl;
                cout << "no_of_candidates = " << res->getInt("no_of_candidates") << endl;
                cout << "constituency = " << res->getString("constituency") << endl;*/
                x["event_id"] = res->getInt("event_id");
                x["status"] = res->getString("status");
                x["no_of_voters"] = res->getInt("no_of_voters");
                x["start_date"] = res->getString("start_date");
                x["end_date"] = res->getString("end_date");
                x["no_of_candidates"] = res->getInt("no_of_candidates");
                x["constituency"] = res->getString("constituency");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    CROW_ROUTE(app, "/api/admin/dashboard/result")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        int event_id = stoi(req.url_params.get("event_id"));

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM result WHERE event_id = (?)");
        pstmt->setInt(1, event_id);
        res = pstmt->executeQuery();
        crow::json::wvalue x;
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /*cout << "event_id = " << res->getInt("event_id") << endl;
                cout << "candidate_id = " << res->getInt("candidate_id") << endl;
                cout << "no_of_votes = " << res->getInt("no_of_votes") << endl;
                cout << "result = " << res->getString("result") << endl;*/
                x["event_id"] = res->getInt("event_id");
                x["candidate_id"] = res->getInt("candidate_id");
                x["no_of_votes"] = res->getInt("no_of_votes");
                x["result"] = res->getString("result");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    CROW_ROUTE(app, "/api/admin/dashboard")([](const crow::request& req) { // 
        sql::Driver* driver;
        sql::Connection* con;
        sql::Statement* stmt;
        sql::PreparedStatement* pstmt;
        sql::ResultSet* res;

        try
        {
            driver = get_driver_instance();
            con = driver->connect(server, username, password);
        }
        catch (sql::SQLException e)
        {
            cout << "Could not connect to server. Error message: " << e.what() << endl;
            system("pause");
            exit(1);
        }

        con->setSchema("voting_system");

        pstmt = con->prepareStatement("SELECT * FROM voting_event");
        res = pstmt->executeQuery();
        crow::json::wvalue x;
        if (res) {
            //cout << "printing" << endl;
            while (res->next()) {
                /*cout << "event_id = " << res->getInt("event_id") << endl;
                cout << "status = " << res->getString("status") << endl;
                cout << "no_of_voters = " << res->getInt("no_of_voters") << endl;
                cout << "no_of_candidates = " << res->getInt("no_of_candidates") << endl;
                cout << "constituency = " << res->getString("constituency") << endl;*/
                x["event_id"] = res->getInt("event_id");
                x["status"] = res->getString("status");
                x["no_of_voters"] = res->getInt("no_of_voters");
                x["start_date"] = res->getString("start_date");
                x["end_date"] = res->getString("end_date");
                x["no_of_candidates"] = res->getInt("no_of_candidates");
                x["constituency"] = res->getString("constituency");
            }
        }
        else
            cout << "Happy ending" << endl;

        delete pstmt;
        delete con;
        return x;
        });

    app.port(18080).multithreaded().run();

}