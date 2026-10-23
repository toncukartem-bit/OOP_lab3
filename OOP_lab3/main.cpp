#include <windows.h>
#include <iostream>
#include <string>
#include <new> // Для bad_alloc 
#include "Project.h"


using namespace std;


void PolymorphicFunction(Document* doc) {
    cout << "   [Спосіб 3: Через параметр функції] -> ";
    doc->showDocType();
}

int main(int argc, char* argv[]) {

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    string filename = "default_data.txt";
    if (argc > 1) {
        filename = argv[1];
        cout << ">>> Знайдено параметр командного рядка. Робота з файлом: " << filename << "\n\n";
    }
    else {
        cout << ">>> Параметр файлу не передано. Використовується стандартний: " << filename << "\n\n";
    }

    // Створення 2 типів масивів по 5 об'єктів
    const int MAX_SIZE = 5;
    Project staticArr[MAX_SIZE]; // Статичний масив 
    int staticCount = 0;

    Project* dynamicArr[MAX_SIZE]; // Масив динамічних вказівників 
    int dynamicCount = 0;

    Supplier defSupplier("БудОпт", "Цегла", 5000, 2, 100, "044", true, 5);

    int choice;
    do {
        cout << "1. Створити об'єкти (заповнити масиви)\n";
        cout << "2. П.6: Очистити СТАТИЧНИЙ масив (видалити проекти з бюджетом < 500 000)\n";
        cout << "3. П.6: Очистити ДИНАМІЧНИЙ масив (видалити проекти з бюджетом < 500 000)\n";
        cout << "4. П.7: Робота з файлами (Запис та Читання Document)\n";
        cout << "5. П.9-11: Демонстрація ПОЛІМОРФІЗМУ та раннього/пізнього зв'язування\n";
        cout << "0. Вийти з програми\n";
        cout << "Ваш вибір: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
        case 1: {
            try {
                staticCount = 0;
                dynamicCount = 0;

                cout << "Заповнення СТАТИЧНОГО масиву\n";
                for (int i = 0; i < MAX_SIZE; i++) {
                    double budg = (i % 2 == 0) ? 300000.0 : 600000.0;
                    staticArr[i] = Project(i + 1, "Стат_Проект_" + to_string(i + 1), "Клієнт", 5, budg, defSupplier);
                    staticCount++;
                }
                cout << "Статичний масив заповнено (" << staticCount << " об'єктів).\n\n";

                cout << "Заповнення ДИНАМІЧНОГО масиву\n";
                for (int i = 0; i < MAX_SIZE; i++) {
                    double budg = (i % 2 != 0) ? 200000.0 : 800000.0;

                    dynamicArr[i] = new StateProject(i + 10, "Держ_Проект_" + to_string(i + 1), "Держава", 3, budg, defSupplier, "ДСТУ", 100000, "МОН");
                    dynamicCount++;
                }
                cout << "Динамічний масив заповнено (" << dynamicCount << " об'єктів).\n";

            }
            catch (const bad_alloc& e) { 
                cout << "[ПОМИЛКА ПАМ'ЯТІ]: Не вдалося виділити пам'ять! " << e.what() << endl;
            }
            catch (const exception& e) {
                cout << "[НЕВІДОМА ПОМИЛКА]: " << e.what() << endl;
            }
            break;
        }
        case 2: {
            cout << "Статичний масив до чистки (Кількість: " << staticCount << ")\n";
            for (int i = 0; i < staticCount; i++) {
                staticArr[i].printInfo(); 
            }

            cout << "\nВикликаємо Service_Static (видалення бюджету < 500000)...\n";
            Service_Static(staticArr, staticCount, 500000.0);

            cout << "\nСтатичний масив ПІСЛЯ чистки (Кількість: " << staticCount << ")\n";
            for (int i = 0; i < staticCount; i++) {
                staticArr[i].printInfo();
            }
            break;
        }
        case 3: {
            cout << "Динамічний масив до чистки (Кількість: " << dynamicCount << ")\n";
            for (int i = 0; i < dynamicCount; i++) {
                dynamicArr[i]->printInfo(); // Пізнє зв'язування викличеця printInfo() від StateProject
            }

            cout << "\nВикликаємо Service_Dinamic (видалення бюджету < 500000)...\n";
            Service_Dinamic(dynamicArr, dynamicCount, 500000.0);

            cout << "\nДинамічний масив ПІСЛЯ чистки (Кількість: " << dynamicCount << ")\n";
            for (int i = 0; i < dynamicCount; i++) {
                dynamicArr[i]->printInfo();
            }
            break;
        }
        case 4: {
   
            TechDoc tDoc("Іванов І.І.", 120);
            ComplexDoc cDoc("Міністерство", 50, 15000.50, "Оборони");

            // Запис у файл через поліморфну функцію Service
            cout << "\nЗапис у файл\n";
            Service(&tDoc, filename, true); // Запис технічний документ
            Service(&cDoc, filename, true); // Запис комплексний документ

            cout << "\nЧитання з файлу\n";
            TechDoc newDoc("Невідомо", 0);
            Service(&newDoc, filename, false);
            break;
        }
        case 5: {
            cout << "П.9: ПОЛІМОРФІЗМ 3-МА СПОСОБАМИ\n";
            TechDoc techDoc("Шевченко Т.Г.", 45);

            // через вказівник на базовий клас
            Document* ptr = &techDoc;
            cout << "   [Спосіб 1: Через вказівник] -> ";
            ptr->showDocType();

            // через посилання на базовий клас
            Document& ref = techDoc;
            cout << "   [Спосіб 2: Через посилання] -> ";
            ref.showDocType();

            PolymorphicFunction(&techDoc);


            cout << "\nП.10: РАННЄ ТА ПІЗНЄ ЗВ'ЯЗУВАННЯ\n";
            StateProject sp(99, "Нова Школа", "Міська Рада", 2, 1200000, defSupplier, "ДСТУ", 300000, "МОН");

            Project* basePtr = &sp;
            cout << "Пізнє зв'язування (basePtr->printInfo): ";
            basePtr->printInfo();

            Project baseObj = sp;
            cout << "Раннє зв'язування (baseObj.printInfo):  ";
            baseObj.printInfo(); 


            cout << "\nП.11: ОБХІД ВІРТУАЛЬНОЇ ФУНКЦІЇ\n";
            cout << "Обхід віртуальності (basePtr->Project::printInfo): ";
            basePtr->Project::printInfo();

            break;
        }
        case 0:
            cout << "Завершення роботи...\n";
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз.\n";
            break;
        }

    } while (choice != 0);

    for (int i = 0; i < dynamicCount; i++) {
        delete dynamicArr[i];
    }

 
}