#define _CRT_SECURE_NO_WARNINGS
#include "Project.h"
#include <stdexcept>


Document::Document(string a) : author(a) {
    cout << "[C] Створено Document (автор: " << author << ")\n";
}
Document::~Document() {
    cout << "[~] Знищено базову частину Document\n";
}

TechDoc::TechDoc(string a, int pages) : Document(a), pageCount(pages) {
    cout << "[C] Створено TechDoc на " << pageCount << " сторінок\n";
}
TechDoc::~TechDoc() { cout << "[~] Знищено TechDoc\n"; }
void TechDoc::showDocType() { cout << "Це технічна документація (Автор: " << author << ")\n"; }
void TechDoc::Write(ofstream& os) { os << "TechDoc " << author << " " << pageCount << "\n"; }
void TechDoc::Read(ifstream& is) { is >> author >> pageCount; }

FinDoc::FinDoc(string a, double amount) : Document(a), totalAmount(amount) {
    cout << "[C] Створено FinDoc на суму " << totalAmount << "$\n";
}
FinDoc::~FinDoc() { cout << "[~] Знищено FinDoc\n"; }
void FinDoc::showDocType() { cout << "Це фінансовий звіт (Автор: " << author << ")\n"; }
void FinDoc::Write(ofstream& os) { os << "FinDoc " << author << " " << totalAmount << "\n"; }
void FinDoc::Read(ifstream& is) { is >> author >> totalAmount; }

ComplexDoc::ComplexDoc(string a, int pages, double amount, string ministry)
    : Document(a), TechDoc(a, pages), FinDoc(a, amount), targetMinistry(ministry) {
    cout << "[C] Створено ComplexDoc для " << targetMinistry << "\n";
}
ComplexDoc::~ComplexDoc() { cout << "[~] Знищено ComplexDoc\n"; }
void ComplexDoc::showDocType() { cout << "Це комплексний документ (Технічний + Фінансовий) для " << targetMinistry << "\n"; }
void ComplexDoc::Write(ofstream& os) { os << "ComplexDoc " << author << " " << pageCount << " " << totalAmount << " " << targetMinistry << "\n"; }
void ComplexDoc::Read(ifstream& is) { is >> author >> pageCount >> totalAmount >> targetMinistry; }



Supplier::Supplier() {
    companyName = "Немає"; material = "Немає"; price = 0.0; deliveryDays = 0; quantity = 0;
    contactPhone = "-"; isReliable = false; rating = 0;
}
Supplier::Supplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat) {
    companyName = name; material = mat; price = pr; deliveryDays = days; quantity = qty;
    contactPhone = phone; isReliable = rel; rating = rat;
}
Supplier::Supplier(const Supplier& other) {
    companyName = other.companyName + " (Копія)"; material = other.material; price = other.price;
    deliveryDays = other.deliveryDays; quantity = other.quantity; contactPhone = other.contactPhone;
    isReliable = other.isReliable; rating = other.rating;
}
Supplier::~Supplier() { cout << "[~] Знищено постачальника: " << companyName << "\n"; }

string Supplier::getCompanyName() { return companyName; }
void Supplier::setInfo(string name, string mat, double pr, int days) { companyName = name; material = mat; price = pr; deliveryDays = days; }
void Supplier::applyDiscount(int percent) { price -= (price * percent / 100.0); }
void Supplier::applyDiscount(double amount) { price -= amount; }
Supplier Supplier::getCheaper(Supplier other) { return (this->price < other.price) ? *this : other; }
double Supplier::getPrice() { return price; }
void Supplier::printInfo() { cout << "Постачальник: " << companyName << " | Ціна: " << price << "$\n"; }
void Supplier::saveToFile(string filename) {}
void Supplier::loadFromFile(string filename) {}

LocalSupplier::LocalSupplier(string name, string mat, double pr, int days, int qty, string phone, bool rel, int rat, string reg)
    : Supplier(name, mat, pr, days, qty, phone, rel, rat), region(reg) {
}
LocalSupplier::~LocalSupplier() { cout << "[~] Знищено локального постачальника\n"; }
void LocalSupplier::showLocalInfo() { cout << "Регіон: " << region << " | "; Supplier::printInfo(); }



//перевантаження операторів
int Project::totalProjects = 0;

Project::Project() : id(0) {
    projectName = "Пустий проект"; customer = "-"; floors = 0; budget = 0; status = "Новий";
    for (int i = 0; i < 5; i++) expenses[i] = 0;
    totalProjects++;
}
Project::Project(int pId, string pName, string cust, int fl, double budg, Supplier mSup)
    : id(pId), mainSupplier(mSup) {
    projectName = pName; customer = cust; floors = fl; budget = budg; status = "В роботі";
    for (int i = 0; i < 5; i++) expenses[i] = 0;
    totalProjects++;
}
Project::Project(const Project& other)
    : id(other.id + 100), mainSupplier(other.mainSupplier) {
    projectName = other.projectName; customer = other.customer; floors = other.floors;
    budget = other.budget;
    for (int i = 0; i < 5; i++) expenses[i] = other.expenses[i];
    totalProjects++;
}
Project::~Project() { cout << "[~] Знищено проект: " << projectName << "\n"; }



 //перевантаженя унарних операторів(++ та --)
Project& Project::operator++() {
    ++floors;
    return *this; 
}

// Постфіксний інкремент (obj++)
Project Project::operator++(int) {
    Project temp = *this; 
    floors++;             
    return temp;          
}

// Префіксний декремент (--obj)
Project& Project::operator--() {
    if (floors > 0) --floors; 
    return *this;
}

// Постфіксний декремент (obj--)
Project Project::operator--(int) {
    Project temp = *this;
    if (floors > 0) floors--;
    return temp;
}



//перевантаження бінарних операторів (+, -, *) (бюджет)
Project Project::operator+(double extraBudget) const {
    Project temp(*this);          
    temp.budget += extraBudget;   
    return temp;                 
}

Project Project::operator-(double reduceBudget) const {
    Project temp(*this);
    temp.budget -= reduceBudget;
    if (temp.budget < 0) temp.budget = 0; 
    return temp;
}

Project Project::operator*(double multiplier) const {
    Project temp(*this);
    temp.budget *= multiplier;
    return temp;
}


Project& Project::operator=(const Project& other) {
    if (this != &other) {
        projectName = other.projectName;
        customer = other.customer;
        floors = other.floors;
        budget = other.budget;
        mainSupplier = other.mainSupplier;
        status = other.status;
        isApproved = other.isApproved;
        designersCount = other.designersCount;
        altSupplier = other.altSupplier;

        for (int i = 0; i < 5; i++) {
            expenses[i] = other.expenses[i];
        }
    }
    return *this;
}

Project& Project::operator+=(double amount) {
    budget += amount;
    return *this;
}

Project& Project::operator-=(double amount) {
    budget -= amount;
    if (budget < 0) budget = 0;
    return *this;
}

Project& Project::operator*=(double multiplier) {
    budget *= multiplier;
    return *this;
}


//перевантаження індексатора []
double& Project::operator[](int index) {
    if (index < 0 || index >= 5) {
        throw out_of_range("Помилка, Індекс масиву витрат expenses вийшов за межі (0-4)");
    }
    return expenses[index];
}

void Project::printTotal() { cout << "\nЗагалом проектів: " << totalProjects << "\n"; }
string Project::getProjectName() { return projectName; }
void Project::setBaseInfo(string pName, string cust, int fl, double budg) { projectName = pName; customer = cust; floors = fl; budget = budg; }
void Project::updateBudget(double newBudget) { budget = newBudget; }
void Project::updateBudget(double extraFunds, string reason) { budget += extraFunds; }
void Project::assignSupplier(Supplier s) { mainSupplier = s; budget -= s.getPrice(); }
Supplier Project::getSupplier() { return mainSupplier; }
double Project::getBudget() const { return budget; }
void Project::generateAndSortFloors() {}
void Project::saveToFile(string filename) {}
void Project::loadFromFile(string filename) {}

void Project::printInfo() {
    cout << "Проект: " << projectName << " | Поверхів: " << floors << " | Бюджет: " << budget << "$\n";
}


Standard::Standard(string sName) : standardName(sName) {}
Standard::~Standard() {}
void Standard::printStandard() { cout << "Стандарт: " << standardName << "\n"; }

Funding::Funding(double grant) : grantAmount(grant) {}
Funding::~Funding() {}
void Funding::printFunding() { cout << "Грант: " << grantAmount << "$\n"; }

StateProject::StateProject(int pId, string pName, string cust, int fl, double budg, Supplier mSup, string sName, double grant, string ministry)
    : Project(pId, pName, cust, fl, budg, mSup), Standard(sName), Funding(grant), ministryName(ministry) {
}
StateProject::~StateProject() { cout << "[~] Знищено державний проект\n"; }

void StateProject::printInfo() {
    cout << "ДЕРЖ ПРОЕКТ (" << ministryName << ") | Назва: " << projectName << " | Бюджет: " << budget << "$\n";
}

void StateProject::showStateProjectDetails() {
    printInfo();
    Standard::printStandard();
    Funding::printFunding();
}

Contract::Contract(Project* pr, Supplier* su, string d) : p(pr), s(su), date(d) {}
Contract::~Contract() {}


void Service_Static(Project arr[], int& currentSize, double minBudget) {
    try {
        if (currentSize <= 0) throw invalid_argument("Помилка: Розмір масиву <= 0.");
        if (minBudget < 0) throw invalid_argument("Помилка: Бюджет не може бути від'ємним.");

        bool found = false;
        for (int i = 0; i < currentSize; ) {
            if (arr[i].getBudget() < minBudget) {
                found = true;
                for (int j = i; j < currentSize - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                currentSize--;
            }
            else {
                i++;
            }
        }
        if (!found) throw runtime_error("Проектів з таким бюджетом не знайдено.");
    }
    catch (const exception& e) {
        cout << "[ПОМИЛКА]: " << e.what() << endl;
    }
}

void Service_Dinamic(Project* arr[], int& currentSize, double minBudget) {
    try {
        if (arr == nullptr) throw invalid_argument("Помилка: Передано nullptr.");
        if (currentSize <= 0) throw out_of_range("Помилка: Розмір масиву поза межами.");

        for (int i = 0; i < currentSize; ) {
            if (arr[i] == nullptr) throw runtime_error("Помилка: Порожній вказівник.");
            if (arr[i]->getBudget() < minBudget) {
                delete arr[i];
                for (int j = i; j < currentSize - 1; j++) {
                    arr[j] = arr[j + 1];
                }
                currentSize--;
            }
            else {
                i++;
            }
        }
    }
    catch (const exception& e) {
        cout << "[ПОМИЛКА]: " << e.what() << endl;
    }
}

void Service(Document* doc, const string& filename, bool isWriteMode) {
    try {
        if (doc == nullptr) throw invalid_argument("Вказівник на документ порожній.");
        if (filename.empty()) throw invalid_argument("Ім'я файлу не задано.");

        if (isWriteMode) {
            ofstream ofs(filename, ios::app);
            if (!ofs.is_open()) throw ios_base::failure("Неможливо відкрити файл для запису.");
            doc->Write(ofs);
            cout << "Дані записано у файл " << filename << endl;
            ofs.close();
        }
        else {
            ifstream ifs(filename);
            if (!ifs.is_open()) throw ios_base::failure("Неможливо відкрити файл для читання.");
            doc->Read(ifs);
            cout << "Дані зчитано з файлу " << filename << endl;
            ifs.close();
        }
    }
    catch (const exception& e) {
        cout << "[ПОМИЛКА ФАЙЛУ]: " << e.what() << endl;
    }
}