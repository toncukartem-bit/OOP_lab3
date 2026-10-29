#include <windows.h>
#include <iostream>
#include <string>
#include "Project.h"

using namespace std;

int main() {
    
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    Supplier defSupplier("БудОпт", "Цегла", 5000, 2, 100, "044", true, 5);

    int choice;
    do {
        cout << "1. Унарні оператори (++, -- префіксні та постфіксні)\n";
        cout << "2. Бінарні оператори (+, -)\n";
        cout << "3. Складені оператори (*, =, +=, -=, *=) та індексатор []\n";
        cout << "4. Шаблонна функція в класі Project\n";
        cout << "5. Шаблонний клас TemplateContainer з типом Supplier\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1: {
            cout << "Демонстрація УНАРНИХ операторів (зміна поверхів)\n";
            Project p1(1, "ЖК 'Світанок'", "Клієнт А", 10, 100000, defSupplier);

            cout << "Початковий стан:\n";
            p1.printInfo();

            cout << "\n1. Префіксний інкремент (++p1):\n";
            Project p2 = ++p1;
            p1.printInfo();

            cout << "\n2. Постфіксний інкремент (p1++):\n";
            Project p3 = p1++;
            cout << "Результат (повернута стара копія): "; p3.printInfo(); 
            cout << "Оригінал після збільшення:         "; p1.printInfo(); 

            cout << "\n3. Префіксний декремент (--p1):\n";
            --p1; 
            p1.printInfo();

            cout << "\n4. Постфіксний декремент (p1--):\n";
            p1--; 
            p1.printInfo();
            break;
        }
        case 2: {
            cout << "Демонстрація БІНАРНИХ операторів (зміна бюджету)\n";
            Project p1(2, "Офіс-Центр", "Бізнес ТОВ", 5, 200000.0, defSupplier);

            cout << "Оригінальний проект:\n";
            p1.printInfo();

            cout << "\nСтворюємо новий проект додаванням бюджету (+ 50000):\n";
            Project p2 = p1 + 50000.0;
            p2.printInfo(); 

            cout << "\nСтворюємо новий проект відніманням бюджету (- 30000):\n";
            Project p3 = p1 - 30000.0;
            p3.printInfo(); 

            cout << "\n(Оригінальний проект p1 при цьому не змінився):\n";
            p1.printInfo();
            break;
        }
        case 3: {
            cout << "Демонстрація СКЛАДЕНИХ операторів та []\n";
            Project p1(3, "ТРЦ 'Галактика'", "Клієнт Б", 3, 100000.0, defSupplier);
            p1.printInfo();

            cout << "\n1. Оператор *= 2 (подвоєння бюджету):\n";
            p1 *= 2.0;
            p1.printInfo();

            cout << "\n2. Оператор += 50000:\n";
            p1 += 50000.0;
            p1.printInfo(); 

            cout << "\n3. Оператор -= 100000:\n";
            p1 -= 100000.0;
            p1.printInfo();

            cout << "\n4. Оператор присвоювання = (копіювання p1 в p2):\n";
            Project p2;
            p2 = p1;
            cout << "Скопійований проект (p2): ";
            p2.printInfo();

            cout << "\n5. Оператор [] (доступ до масиву витрат expenses):\n";
            p1[0] = 1500.50; 
            p1[1] = 300.00;
            cout << "Витрати [0]: " << p1[0] << "$\n";
            cout << "Витрати [1]: " << p1[1] << "$\n";

            cout << "Спроба вийти за межі масиву (p1[10]):\n";
            try {
                p1[10] = 50;
            }
            catch (const exception& e) {
                cout << "[ПОМИЛКА]: " << e.what() << "\n";
            }
            break;
        }
        case 4: {
            cout << "Демонстрація ШАБЛОННОЇ ФУНКЦІЇ\n";
            Project p(4, "Школа", "Місто", 3, 500000.0, defSupplier);

            p.logExtraInfo(404);                              
            p.logExtraInfo(99.99);                             
            p.logExtraInfo(string("Перевірка систем безпеки"));
            break;
        }
        case 5: {
            cout << "--- Демонстрація ШАБЛОННОГО КЛАСУ TemplateContainer ---\n";

            TemplateContainer<Supplier> suppliersContainer(3);

            Supplier s1("БетонСервіс", "Бетон", 3000, 1, 50, "067", true, 8);
            Supplier s2("МеталПроф", "Арматура", 8000, 3, 200, "050", true, 9);
            Supplier s3("СклоЛюкс", "Скло", 1500, 2, 30, "093", false, 6);

            cout << "Додаємо постачальників у контейнер...\n";
            suppliersContainer.addElement(s1);
            suppliersContainer.addElement(s2);
            suppliersContainer.addElement(s3);

            cout << "Спроба додати 4-го (контейнер на 3 елементи):\n";
            Supplier s4("Екстра", "Пісок", 500, 1, 10, "000", false, 5);
            suppliersContainer.addElement(s4);

            cout << "\nОтримуємо дані з контейнера за індексом:\n";
            for (int i = 0; i < suppliersContainer.getSize(); i++) {
                cout << "[" << i << "] ";
                suppliersContainer.getElement(i).printInfo(); 
            }
            break;
        }
        case 0:
            cout << "Завершення роботи програми...\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
            break;
        }
    } while (choice != 0);

    return 0;
}