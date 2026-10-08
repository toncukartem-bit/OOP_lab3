#define _CRT_SECURE_NO_WARNINGS
#include "Project.h"

// КЛАС SUPPLIER (ПОСТАЧАЛЬНИК)

Supplier::Supplier() {
    companyName = "Немає"; material = "Немає"; price = 0.0; deliveryDays = 0; quantity = 0;
    contactPhone = "-"; isReliable = false; rating = 0;
}

Supplier::Supplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat) {
    companyName = name; material = mat; price = pr; deliveryDays = days; quantity = qty;
    contactPhone = phone; isReliable = rel; rating = rat;
}

// П.1: Конструктор копіювання. (точну копію іншого постачальника)
Supplier::Supplier(const Supplier& other) {
    companyName = other.companyName + " (Копія)";
    material = other.material; price = other.price;
    deliveryDays = other.deliveryDays; quantity = other.quantity; contactPhone = other.contactPhone;
    isReliable = other.isReliable; rating = other.rating;
}

Supplier::~Supplier() {
    cout << " ~ Постачальника " << companyName << " видалено.\n";
}
// Методи з Лаби 2
void Supplier::setInfo(string name, string mat, double pr, int days) {
    companyName = name; material = mat; price = pr; deliveryDays = days;
}

void Supplier::applyDiscount(int percent) { price -= (price * percent / 100.0); }
void Supplier::applyDiscount(double amount) { price -= amount; }

Supplier Supplier::getCheaper(Supplier other) { return (this->price < other.price) ? *this : other; }
double Supplier::getPrice() { return price; }
void Supplier::printInfo() { cout << "Постачальник: " << companyName << " | Ціна: " << price << "$\n"; }

// Заглушки для роботи з файлами (Лаб 2)
void Supplier::saveToFile(string filename) {}
void Supplier::loadFromFile(string filename) {}


// КЛАС PROJECT 
int Project::totalProjects = 0;

Project::Project() : id(0) {
    projectName = "Пустий проект"; customer = "-"; floors = 0; budget = 0; status = "Новий";
    isApproved = false; designersCount = 0;
    altSupplier = nullptr; 
    totalProjects++;      
}
Project::Project(int pId, string pName, string cust, int fl, double budg, Supplier mSup)
    : id(pId), mainSupplier(mSup) {
    projectName = pName; customer = cust; floors = fl; budget = budg;
    status = "В роботі"; isApproved = true; designersCount = 5;
    altSupplier = nullptr;
    totalProjects++;
}

// П.1 П.2  Конструктор копіювання
Project::Project(const Project& other)
    : id(other.id + 100), mainSupplier(other.mainSupplier) { // Зсуваємо ID, щоб він залишався унікальним
    projectName = other.projectName; customer = other.customer; floors = other.floors;
    budget = other.budget; status = other.status; isApproved = other.isApproved;
    designersCount = other.designersCount; altSupplier = other.altSupplier;
    totalProjects++;
}

Project::~Project() {
    cout << " ~ Проект " << projectName << " видаляється з пам'яті.\n";
}

// П.4: Реалізація статичного методу
void Project::printTotal() {
    cout << "\n--- Загалом проектів у системі: " << totalProjects << " ---\n";
}


// Методи з Лаби 2
void Project::setBaseInfo(string pName, string cust, int fl, double budg) {
    projectName = pName; customer = cust; floors = fl; budget = budg;
}
void Project::updateBudget(double newBudget) { budget = newBudget; }
void Project::updateBudget(double extraFunds, string reason) { budget += extraFunds; }

void Project::assignSupplier(Supplier s) {
    mainSupplier = s; 
    budget -= s.getPrice(); 
}
Supplier Project::getSupplier() { return mainSupplier; }

void Project::generateAndSortFloors() {
    int size = rand() % 5 + 5;
    int* dynArray = new int[size];

    cout << "Варіанти поверхів: ";
    for (int i = 0; i < size; i++) {
        dynArray[i] = floors + (rand() % 10 - 5);
        cout << dynArray[i] << " ";
    }

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (dynArray[j] > dynArray[j + 1]) swap(dynArray[j], dynArray[j + 1]);
        }
    }

    cout << " | Відсортовані: ";
    for (int i = 0; i < size; i++) cout << dynArray[i] << " ";
    cout << "\n";

    delete[] dynArray; 
}

void Project::saveToFile(string filename) {}
void Project::loadFromFile(string filename) {}
void Project::printInfo() {
    cout << "Проект: " << projectName << " (Замовник: " << customer << ") | Бюджет: " << budget << "$\n";
}


// КЛАС CONTRACT

// П.11: Клас асоціації. 
Contract::Contract(Project* pr, Supplier* su, string d) : p(pr), s(su), date(d) {
    cout << ">>> Укладено контракт між " << p->getProjectName() << " та " << s->getCompanyName() << " на " << date << "\n";
}

Contract::~Contract() {
    cout << " ~ Контракт розірвано.\n";
}