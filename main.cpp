// Автор коду: Зюзін Євген, К16

#include "DS.h"
#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "--- Start testing DS (Variant 105) ---\n\n";

    DS list = {
        {1.5, 2.0},
        {3.1, 4.2},
        {5.0, 6.0}
    };

    cout << "Initial elements: ";
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        cout << "(" << it->x << ", " << it->y << ") ";
    }

    cout << "\nSize: " << list.size();
    cout << ", Capacity: " << list.capacity() << "\n\n";

    list.push_front({ 0.0, 0.0 });
    list.push_back({ 7.7, 8.8 });

    cout << "After push_front and push_back: ";
    for (const auto& elem : list)
    {
        cout << "(" << elem.x << ", " << elem.y << ") ";
    }
    cout << "\nSize: " << list.size() << "\n\n";

    list.pop_front();
    list.pop_back();

    cout << "After pop_front() and pop_back(): ";
    for (const auto& elem : list)
    {
        cout << "(" << elem.x << ", " << elem.y << ") ";
    }
    cout << "\n\n";

    list.clear();
    cout << "After clear():\nSize: " << list.size();
    cout << ", Capacity: " << list.capacity() << "\n";

    cout << "\n--- Testing successfully completed! ---\n";

    return 0;
}