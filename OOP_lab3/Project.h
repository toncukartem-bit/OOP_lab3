#pragma once
#include <string>
#include <iostream>

using namespace std;

// БАЗОВИЙ КЛАС 1 (з Лаби 2 і 3)
class Supplier {
protected: 
    string companyName;
    string material;
    int deliveryDays;
    double price;
    int quantity;

public:
    string contactPhone;
    bool isReliable;
    int rating;

    Supplier();
    Supplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat);
    Supplier(const Supplier& other);
    ~Supplier();

    string getCompanyName();
    void setInfo(string name, string mat, double pr, int days);
    void applyDiscount(int percent);
    void applyDiscount(double amount);
    Supplier getCheaper(Supplier other);
    double getPrice();
    void printInfo();
    void saveToFile(string filename);
    void loadFromFile(string filename);
};

// ПОХІДНИЙ КЛАС (П.3 Закрите наслідування) 
class LocalSupplier : private Supplier {
private:
    string region;
public:
    LocalSupplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat, string reg);
    ~LocalSupplier();
    void showLocalInfo();
};

// БАЗОВИЙ КЛАС 2 (з Лаб 2 і 3)
class Project {
protected: // П.2: protected для спадкоємців
    string projectName;
    string customer;
    int floors;
    double budget;
    Supplier mainSupplier;

public:
    const int id;
    static int totalProjects;
    string status;
    bool isApproved;
    int designersCount;
    Supplier* altSupplier;

    Project();
    Project(int pId, string pName, string cust, int fl, double budg, Supplier mSup);
    Project(const Project& other);
    ~Project();

    static void printTotal();
    string getProjectName();
    void setBaseInfo(string pName, string cust, int fl, double budg);
    void updateBudget(double newBudget);
    void updateBudget(double extraFunds, string reason);
    void assignSupplier(Supplier s);
    Supplier getSupplier();
    void generateAndSortFloors();
    void saveToFile(string filename);
    void loadFromFile(string filename);
    void printInfo();
};

// ДОДАТКОВІ КЛАСИ ДЛЯ МНОЖИННОГО НАСЛІДУВАННЯ (П.4) 
class Standard {
protected:
    string standardName;
public:
    Standard(string sName);
    ~Standard();
    void printStandard();
};

class Funding {
protected:
    double grantAmount;
public:
    Funding(double grant);
    ~Funding();
    void printFunding();
};

// КЛАС МНОЖИННОГО НАСЛІДУВАННЯ (П.4) 
class StateProject : public Project, public Standard, public Funding {
private:
    string ministryName;
public:
    // П.5: Передача параметрів всім базовим конструкторам
    StateProject(int pId, string pName, string cust, int fl, double budg, Supplier mSup, string sName, double grant, string ministry);
    ~StateProject();

    using Project::printInfo; // П.6: Використання оператора using
    void showStateProjectDetails();
};

//КЛАС АСОЦІАЦІЇ (з Лаб 3) 
class Contract {
public:
    Project* p;
    Supplier* s;
    string date;
    Contract(Project* pr, Supplier* su, string d);
    ~Contract();
};