#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <string>
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <iomanip>


using namespace std;
int total = 0;



struct Time
{
    int day1;
    int month2;
    int year3;
};

struct Clients {
    string fullName;
    long long phoneNumber;
};

struct Service {
    string serviceName;
    int serviceCode;
    float tariff;
    int time;
};

struct InfService {
    long long phoneNumber;
    int serviceCode;
    int day;
    int month;
    int year;
    string Time;
    int work;
};

struct Param {
    int total;
    long long phoneNumber;
};

int main() {

    setlocale(LC_ALL, "Russian");

#pragma warning(disable : 4996)
    ofstream starttime("datetime.txt", std::ios::app);
    auto now = chrono::system_clock::now();
    time_t now_c = chrono::system_clock::to_time_t(now);
    tm* tm = localtime(&now_c);
    starttime << put_time(tm, "%d.%m.%Y") << endl;
    starttime.close();

    ifstream start("datetime.txt");
    Time newtime;
    start >> newtime.day1;
    start.ignore(1, ',');
    start >> newtime.month2;
    start.ignore(1, ',');
    start >> newtime.year3;
    start.close();


    ifstream file("клиенты.txt");
    vector<Clients> client;
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        Clients newclient;
        getline(iss, newclient.fullName, ',');
        iss >> newclient.phoneNumber;
        iss.ignore(1, ',');
        client.push_back(newclient);//Добавление элементов в вектор
    }
    file.close();
    ifstream file2("услуги.txt");
    vector<Service> services;
    while (getline(file2, line)) {
        istringstream iss(line);
        Service newservice;
        getline(iss, newservice.serviceName, ',');
        iss >> newservice.serviceCode;
        iss.ignore(1, ' ');
        iss >> newservice.tariff;
        iss.ignore(1, ' ');
        iss >> newservice.time;
        services.push_back(newservice);//Добавление элементов в вектор
    }
    file2.close();
    ifstream file3("инф об услугах.txt");
    vector<InfService> inf;
    while (getline(file3, line)) {
        istringstream iss(line);
        InfService newinf;
        iss >> newinf.phoneNumber;
        iss.ignore(1, ',');
        iss >> newinf.serviceCode;
        iss.ignore(1, ' ');
        iss >> newinf.day;
        iss.ignore(1, '.');
        iss >> newinf.month;
        iss.ignore(1, '.');
        iss >> newinf.year;
        iss.ignore(1, ' ');
        getline(iss, newinf.Time, ',');
        iss >> newinf.work;
        inf.push_back(newinf);//Добавление элементов в вектор
    }
    file3.close();
    ifstream par("Param.txt");
    ofstream rep("Report.txt");

    Param newparam;
    par >> newparam.phoneNumber;
    par >> newparam.total;
    par.close();


    for (const auto& newservice : services) {
        for (const auto& newinf : inf) {
            if (newinf.phoneNumber == newparam.phoneNumber && newinf.serviceCode == newservice.serviceCode && (newinf.year == newtime.year3) && (newinf.month == newtime.month2) && (newtime.day1 - newinf.day) <= 3) {
                total += newservice.tariff * newinf.work;
                if (total > newparam.total) {
                    rep << total << " " << newinf.phoneNumber << endl;
                    break;
                }
            }


        }
    }
    return 0;
}



/* Param newparam;
par >> newparam.total;
par >> newparam.phoneNumber;
par.close();
*/
