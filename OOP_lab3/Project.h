#pragma once
#include <string>
#include <iostream>

using namespace std;

// ПОСТАЧАЛЬНИК 
class Supplier {
private:
    
    string companyName;
    string material;
    int deliveryDays;
    double price;
    int quantity;

public:
    string getCompanyName() { return companyName; }
    string contactPhone;
    bool isReliable;
    int rating;

    // Конструктори і Деструктор
    Supplier();
    Supplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat);
    Supplier(const Supplier& other);
    ~Supplier();

    // Методи з Лаби 2
    void setInfo(string name, string mat, double pr, int days);
    void applyDiscount(int percent);
    void applyDiscount(double amount);
    Supplier getCheaper(Supplier other);
    double getPrice();
    void printInfo();
    void saveToFile(string filename);
    void loadFromFile(string filename);
};


// ПРОЕКТ
class Project {
private:
    string projectName;
    string customer;
    int floors;
    double budget;

    // Лаб 3 (Композиція)
    Supplier mainSupplier;

public:
    // Константа та статичне поле
    string getProjectName() { return projectName; }
    const int id;
    static int totalProjects;

    string status;
    bool isApproved;
    int designersCount;

    // Лаб 3 (Агрегація)
    Supplier* altSupplier;

    // Конструктори та Деструктор
    Project();
    Project(int pId, string pName, string cust, int fl, double budg, Supplier mSup);
    Project(const Project& other);
    ~Project();

    static void printTotal();

    // Методи з Лаби 2
    void setBaseInfo(string pName, string cust, int fl, double budg);
    void updateBudget(double newBudget);
    void updateBudget(double extraFunds, string reason);
    void assignSupplier(Supplier s);
    Supplier getSupplier();
    void generateAndSortFloors(); // Сортування динамічного масиву
    void saveToFile(string filename);
    void loadFromFile(string filename);
    void printInfo();
};

// КОНТРАКТ (Для демонстрації Асоціації)
class Contract {
public:
    Project* p;
    Supplier* s;
    string date;
    Contract(Project* pr, Supplier* su, string d);
    ~Contract();
};