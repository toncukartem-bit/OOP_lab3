#include <iostream>
#include <windows.h>
#include "Project.h"

using namespace std;

// Зовнішня функція 
void analyzeBudget(Project p) {
    cout << "Аналіз: бюджет проекту " << p.id << " складає " << p.getSupplier().getPrice() << "$\n";
}
// Перевантажена функція
void analyzeBudget(Project* p) {
    cout << "Аналіз за адресою: постачальник " << p->getSupplier().contactPhone << "\n";
}

Project createStandardProject() {
    Supplier baseSup("СтандартБуд", "Бетон", 5000, 2, 100, "099-000-00", true, 5);
    return Project(999, "Типове ТЗ", "Міськрада", 5, 50000, baseSup);
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Project::printTotal();
    cout << "\nВІДСЛІДКОВУВАННЯ ДЕСТРУКТОРА\n";
    {
        Supplier tempSup;
        Project tempProj(1, "Тимчасовий ТЗ", "ТОВ", 3, 1000, tempSup);
    }

    cout << "\nСТВОРЕННЯ І КОПІЮВАННЯ ОБ'ЄКТІВ\n";
    Supplier mainSup("ЕкоБуд", "Цегла", 75000, 5, 1000, "067-111", true, 5);
    Project p1;                                                       
    Project p2(2, "ЖК Мрія", "ТОВ Буд", 15, 200000, mainSup);          
    Project p3 = p2;                                                  

    p2.printInfo();

    cout << "\nДИНАМІЧНА ПАМ'ЯТЬ ТА МЕТОДИ ЛАБ 2\n";
    Project* dynProj = new Project(3, "ТРЦ", "Інвестор", 4, 100000, mainSup);
    dynProj->generateAndSortFloors(); // Виклик методу з другої лаби

    cout << "\nЗОВНІШНІ ФУНКЦІЇ\n";
    analyzeBudget(p2);   
    analyzeBudget(&p2);  

    cout << "\n ВЗАЄМОДІЯ КЛАСІВ (Лаб 3)\n";
    Supplier altSup("КиївБетон", "Бетон", 80000, 3, 500, "044-222", true, 4);

    // Композиція (П.13): mainSup вже "вбудований" в p2 і змінить його бюджет
    p2.assignSupplier(mainSup);

    // Агрегація (П.12): Просто тримаємо запасного постачальника на випадок проблеми
    p2.altSupplier = &altSup;

    // Асоціація (П.11): Незалежний контракт
    Contract myContract(&p2, &altSup, "10.10.2026");

    Project::printTotal(); 

    cout << "\n=== ОЧИЩЕННЯ ПАМ'ЯТІ ===\n";
    delete dynProj;

    return 0;
}