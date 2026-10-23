#pragma once
#include <string>
#include <iostream>
#include <fstream> 

using namespace std;

class Document {
protected:
    string author;
public:
    Document(string a);

    virtual ~Document();
    virtual void showDocType() = 0;

    // віртуальні методи 
    virtual void Write(ofstream& os) = 0;
    virtual void Read(ifstream& is) = 0;
};


 // П.2: віртуальне наслідування
 // нащадок 1 технічний документ
class TechDoc : virtual public Document {
protected:
    int pageCount;
public:
    TechDoc(string a, int pages);
    virtual ~TechDoc(); 

    void showDocType() override;
    void Write(ofstream& os) override;
    void Read(ifstream& is) override;
};


 //Нащадок 2 фінансовий документ
class FinDoc : virtual public Document {
protected:
    double totalAmount;
public:
    FinDoc(string a, double amount);
    virtual ~FinDoc();

    void showDocType() override;
    void Write(ofstream& os) override;
    void Read(ifstream& is) override;
};


   //Нащадок 3: Комплексний документ 
class ComplexDoc : public TechDoc, public FinDoc {
private:
    string targetMinistry;
public:
    ComplexDoc(string a, int pages, double amount, string ministry);
    virtual ~ComplexDoc();

    void showDocType() override;
    void Write(ofstream& os) override;
    void Read(ifstream& is) override;
};


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
    virtual ~Supplier();

    string getCompanyName();
    void setInfo(string name, string mat, double pr, int days);
    void applyDiscount(int percent);
    void applyDiscount(double amount);
    Supplier getCheaper(Supplier other);
    double getPrice();

    virtual void printInfo();

    void saveToFile(string filename);
    void loadFromFile(string filename);
};

class LocalSupplier : private Supplier {
private:
    string region;
public:
    LocalSupplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat, string reg);
    virtual ~LocalSupplier();
    void showLocalInfo();
};

class Project {
protected:
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

    Project& operator=(const Project& other);

    virtual ~Project();

    static void printTotal();
    string getProjectName();
    void setBaseInfo(string pName, string cust, int fl, double budg);
    void updateBudget(double newBudget);
    void updateBudget(double extraFunds, string reason);
    void assignSupplier(Supplier s);
    Supplier getSupplier();
    double getBudget() const;

    void generateAndSortFloors();
    void saveToFile(string filename);
    void loadFromFile(string filename);

    virtual void printInfo();
};

class Standard {
protected:
    string standardName;
public:
    Standard(string sName);
    virtual ~Standard();
    virtual void printStandard();
};

class Funding {
protected:
    double grantAmount;
public:
    Funding(double grant);
    virtual ~Funding();
    virtual void printFunding();
};

class StateProject : public Project, public Standard, public Funding {
private:
    string ministryName;
public:
    StateProject(int pId, string pName, string cust, int fl, double budg, Supplier mSup, string sName, double grant, string ministry);
    virtual ~StateProject();

    using Project::printInfo;

    void printInfo() override;
    void showStateProjectDetails();
};

class Contract {
public:
    Project* p;
    Supplier* s;
    string date;
    Contract(Project* pr, Supplier* su, string d);
    ~Contract(); 
};

//глоб функції

 // обробка статичного масиву
void Service_Static(Project arr[], int& currentSize, double minBudget);

// бробка масиву динамічних вказівників
void Service_Dinamic(Project* arr[], int& currentSize, double minBudget);

// універсальна функція роботи з файлами
void Service(Document* doc, const string& filename, bool isWriteMode);