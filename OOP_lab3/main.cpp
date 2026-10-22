#include <iostream>
#include <windows.h>
#include "Project.h"

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Supplier baseSup("СтандартБуд", "Бетон", 5000, 2, 100, "099-000-00", true, 5);

    cout << "\n=== П.7: ДЕМОНСТРАЦІЯ ПРОСТОГО НАСЛІДУВАННЯ (LocalSupplier) ===\n";
    {
        LocalSupplier locSup("УкрЦегла", "Цегла", 3000, 1, 500, "044-111", true, 4, "Київська область");
        locSup.showLocalInfo();
    } 

    cout << "\n=== П.7: ДЕМОНСТРАЦІЯ МНОЖИННОГО НАСЛІДУВАННЯ (StateProject) ===\n";
    {
        // Виклики конструкторів  Project Standard Funding StateProject
        StateProject govProj(777, "Школа", "Міносвіти", 3, 500000, baseSup, "ДСТУ-2026", 150000, "Міністерство Освіти");

        govProj.showStateProjectDetails();

        // П.6: Демонстрація оператора using.
        cout << "\nДемонстрація оператора using:\n";
        govProj.printInfo();
    } 

    cout << "\n=== ЛАБОРАТОРНА 2 ТА 3 (Збережений функціонал) ===\n";
    Project p2(2, "ЖК Мрія", "ТОВ Буд", 15, 200000, baseSup);
    p2.generateAndSortFloors();
    Contract myContract(&p2, &baseSup, "10.10.2026");

    return 0;
}