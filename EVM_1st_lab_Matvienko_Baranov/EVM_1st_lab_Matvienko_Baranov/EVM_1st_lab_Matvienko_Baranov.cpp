#include <iostream>

using namespace std;

union LongDouble {
    long double value;
    unsigned char bytes[sizeof(long double)];
};

union Int {
    int value;
    unsigned char bytes[sizeof(int)];
};

void printBinaryLongDouble(LongDouble LD) {
    
    int bits = sizeof(long double) * 8;     // Размер long double в битах

    // Печать двоичного представления
    cout << "Двоичное представление long double: ";
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((LD.bytes[i / 8] & (1 << (i % 8))) ? '1' : '0');
        if (i % 8 == 0 && i != 0) {
            cout << ' ';
        }
    }
    cout << endl;
}

void printBinaryInt(Int I) {
    int bits = sizeof(int) * 8;     // Размер int в битах

    // Печать двоичного представления
    cout << "Двоичное представление int: ";
    for (int i = bits - 1; i >= 0; i--) {
        cout << ((I.bytes[i / 8] & (1 << (i % 8))) ? '1' : '0');
        if (i % 8 == 0 && i != 0) {
            cout << ' ';
        }
    }
    cout << endl;
}

void swapBitGroupsLongDouble(LongDouble& LD, int start1, int start2, int groupSize) {
    for (int i = 0; i < groupSize; i++) {
        // Извлекаем биты из первой группы
        bool bit1 = (LD.bytes[(start1 + i) / 8] & (1 << ((start1 + i) % 8))) != 0;
        // Извлекаем биты из второй группы
        bool bit2 = (LD.bytes[(start2 + i) / 8] & (1 << ((start2 + i) % 8))) != 0;

        // Меняем местами биты
        if (bit1 != bit2) { // Если биты разные, меняем их
            LD.bytes[(start1 + i) / 8] ^= (1 << ((start1 + i) % 8)); // Меняем бит в первой группе
            LD.bytes[(start2 + i) / 8] ^= (1 << ((start2 + i) % 8)); // Меняем бит во второй группе
        }
    }
}

void swapBitGroupsInt(Int& I, int start1, int start2, int groupSize) {
    for (int i = 0; i < groupSize; i++) {
        // Извлекаем биты из первой группы
        bool bit1 = (I.bytes[(start1 + i) / 8] & (1 << ((start1 + i) % 8))) != 0;
        // Извлекаем биты из второй группы
        bool bit2 = (I.bytes[(start2 + i) / 8] & (1 << ((start2 + i) % 8))) != 0;

        // Меняем местами биты
        if (bit1 != bit2) { // Если биты разные, меняем их
            I.bytes[(start1 + i) / 8] ^= (1 << ((start1 + i) % 8)); // Меняем бит в первой группе
            I.bytes[(start2 + i) / 8] ^= (1 << ((start2 + i) % 8)); // Меняем бит во второй группе
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    cout << "Выберите тип данных для работы:" << endl;
    cout << "1. long double" << endl;
    cout << "2. int" << endl;
    cin >> choice;

    if (choice == 1) {
        LongDouble LD;

        cout << "Введите число типа long double: ";
        cin >> LD.value;

        printBinaryLongDouble(LD);

        int startBitGroup1, startBitGroup2, groupSize;

        cout << "Введите номер старшего бита первой группы: ";
        cin >> startBitGroup1;

        cout << "Введите номер старшего бита второй группы: ";
        cin >> startBitGroup2;

        cout << "Введите количество бит в группе: ";
        cin >> groupSize;

        // Проверка на корректность ввода
        int totalBits = sizeof(long double) * 8;

        if (startBitGroup1 < 0 || startBitGroup2 < 0 ||
            startBitGroup1 >= totalBits || startBitGroup2 >= totalBits ||
            startBitGroup1 + groupSize > totalBits ||
            startBitGroup2 + groupSize > totalBits) {
            cout << "Ошибка: неверный ввод. Убедитесь, что номера битов и размер группы корректны." << endl;
            return -1;
        }

        // Замена битовых групп
        swapBitGroupsLongDouble(LD, startBitGroup1, startBitGroup2, groupSize);

        // Печать результата после замены
        printBinaryLongDouble(LD);

    }
    else if (choice == 2) {
        Int I;

        cout << "Введите число типа int: ";
        cin >> I.value;

        printBinaryInt(I);

        int startBitGroup1, startBitGroup2, groupSize;

        cout << "Введите номер старшего бита первой группы: ";
        cin >> startBitGroup1;

        cout << "Введите номер старшего бита второй группы: ";
        cin >> startBitGroup2;

        cout << "Введите количество бит в группе: ";
        cin >> groupSize;

        // Проверка на корректность ввода
        int totalBits = sizeof(int) * 8;

        if (startBitGroup1 < 0 || startBitGroup2 < 0 ||
            startBitGroup1 >= totalBits || startBitGroup2 >= totalBits ||
            startBitGroup1 + groupSize > totalBits ||
            startBitGroup2 + groupSize > totalBits) {
            cout << "Ошибка: неверный ввод. Убедитесь, что номера битов и размер группы корректны." << endl;
            return -1;
        }

        // Замена битовых групп
        swapBitGroupsInt(I, startBitGroup1, startBitGroup2, groupSize);

        // Печать результата после замены
        printBinaryInt(I);

    }
    else {
        cout << "Неверный выбор типа данных." << endl;
        return -1;
    }

    return 0;
}