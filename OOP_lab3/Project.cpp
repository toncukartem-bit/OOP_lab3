#define _CRT_SECURE_NO_WARNINGS
#include "Project.h"

// SUPPLIER 
Supplier::Supplier() {
    companyName = "Немає"; material = "Немає"; price = 0.0; deliveryDays = 0; quantity = 0;
    contactPhone = "-"; isReliable = false; rating = 0;
    cout << "[C] Викликано базовий конструктор Supplier (за замовчуванням)\n";
}
Supplier::Supplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat) {
    companyName = name; material = mat; price = pr; deliveryDays = days; quantity = qty;
    contactPhone = phone; isReliable = rel; rating = rat;
    cout << "[C] Викликано базовий конструктор Supplier з параметрами\n";
}
Supplier::Supplier(const Supplier& other) {
    companyName = other.companyName + " (Копія)"; material = other.material; price = other.price;
    deliveryDays = other.deliveryDays; quantity = other.quantity; contactPhone = other.contactPhone;
    isReliable = other.isReliable; rating = other.rating;
}
Supplier::~Supplier() { cout << "[~] Базовий деструктор: Постачальника " << companyName << " видалено.\n"; }

string Supplier::getCompanyName() { return companyName; }
void Supplier::setInfo(string name, string mat, double pr, int days) { companyName = name; material = mat; price = pr; deliveryDays = days; }
void Supplier::applyDiscount(int percent) { price -= (price * percent / 100.0); }
void Supplier::applyDiscount(double amount) { price -= amount; }
Supplier Supplier::getCheaper(Supplier other) { return (this->price < other.price) ? *this : other; }
double Supplier::getPrice() { return price; }
void Supplier::printInfo() { cout << "Постачальник: " << companyName << " | Ціна: " << price << "$\n"; }
void Supplier::saveToFile(string filename) {}
void Supplier::loadFromFile(string filename) {}

// LOCAL SUPPLIER (П.3) 
// П.5 Передача параметрів базовому конструктору всередині похідного
LocalSupplier::LocalSupplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat, string reg)
    : Supplier(name, mat, pr, days, qty, phone, rel, rat), region(reg) {
    cout << "[C] Викликано похідний конструктор LocalSupplier\n";
}
LocalSupplier::~LocalSupplier() { cout << "[~] Похідний деструктор LocalSupplier видаляється\n"; }

void LocalSupplier::showLocalInfo() {
    // П.6: Доступ через оператор глобального доступу ::
    cout << "Регіональний постачальник з " << region << ": ";
    Supplier::printInfo();
}

// PROJECT
int Project::totalProjects = 0;

Project::Project() : id(0) {
    projectName = "Пустий проект"; customer = "-"; floors = 0; budget = 0; status = "Новий";
    isApproved = false; designersCount = 0; altSupplier = nullptr;
    totalProjects++;
    cout << "[C] Викликано базовий конструктор Project (за замовчуванням)\n";
}
Project::Project(int pId, string pName, string cust, int fl, double budg, Supplier mSup)
    : id(pId), mainSupplier(mSup) {
    projectName = pName; customer = cust; floors = fl; budget = budg;
    status = "В роботі"; isApproved = true; designersCount = 5; altSupplier = nullptr;
    totalProjects++;
    cout << "[C] Викликано базовий конструктор Project з параметрами\n";
}
Project::Project(const Project& other)
    : id(other.id + 100), mainSupplier(other.mainSupplier) {
    projectName = other.projectName; customer = other.customer; floors = other.floors;
    budget = other.budget; status = other.status; isApproved = other.isApproved;
    designersCount = other.designersCount; altSupplier = other.altSupplier;
    totalProjects++;
}
Project::~Project() { cout << "[~] Базовий деструктор: Проект " << projectName << " видаляється з пам'яті.\n"; }

void Project::printTotal() { cout << "\n--- Загалом проектів у системі: " << totalProjects << " ---\n"; }
string Project::getProjectName() { return projectName; }
void Project::setBaseInfo(string pName, string cust, int fl, double budg) { projectName = pName; customer = cust; floors = fl; budget = budg; }
void Project::updateBudget(double newBudget) { budget = newBudget; }
void Project::updateBudget(double extraFunds, string reason) { budget += extraFunds; }
void Project::assignSupplier(Supplier s) { mainSupplier = s; budget -= s.getPrice(); }
Supplier Project::getSupplier() { return mainSupplier; }

void Project::generateAndSortFloors() {
    int size = rand() % 5 + 5;
    int* dynArray = new int[size];
    for (int i = 0; i < size; i++) dynArray[i] = floors + (rand() % 10 - 5);
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (dynArray[j] > dynArray[j + 1]) swap(dynArray[j], dynArray[j + 1]);
        }
    }
    delete[] dynArray;
}
void Project::saveToFile(string filename) {}
void Project::loadFromFile(string filename) {}
void Project::printInfo() { cout << "Проект: " << projectName << " (Замовник: " << customer << ") | Бюджет: " << budget << "$\n"; }

//ДОДАТКОВІ КЛАСИ МНОЖИННОГО НАСЛІДУВАННЯ (П.4) 
Standard::Standard(string sName) : standardName(sName) { cout << "[C] Викликано конструктор Standard\n"; }
Standard::~Standard() { cout << "[~] Деструктор Standard\n"; }
void Standard::printStandard() { cout << "Стандарт якості: " << standardName << "\n"; }

Funding::Funding(double grant) : grantAmount(grant) { cout << "[C] Викликано конструктор Funding\n"; }
Funding::~Funding() { cout << "[~] Деструктор Funding\n"; }
void Funding::printFunding() { cout << "Сума державного гранту: " << grantAmount << "$\n"; }

//STATE PROJECT (Множинне наслідування) 
// П.5, П.7: Порядок виклику конструкторів при множинному наслідуванні
StateProject::StateProject(int pId, string pName, string cust, int fl, double budg, Supplier mSup, string sName, double grant, string ministry)
    : Project(pId, pName, cust, fl, budg, mSup), Standard(sName), Funding(grant), ministryName(ministry) {
    cout << "[C] Викликано конструктор множинного наслідування StateProject\n";
}
StateProject::~StateProject() { cout << "[~] Деструктор StateProject\n"; }

void StateProject::showStateProjectDetails() {
    cout << "\nДЕРЖАВНИЙ ПРОЕКТ\nМіністерство: " << ministryName << "\n";
    Project::printInfo(); 
    Standard::printStandard();
    Funding::printFunding();
}

// CONTRACT
Contract::Contract(Project* pr, Supplier* su, string d) : p(pr), s(su), date(d) {
    cout << ">>> Укладено контракт між " << p->getProjectName() << " та " << s->getCompanyName() << " на " << date << "\n";
}
Contract::~Contract() { cout << "[~] Контракт розірвано.\n"; }