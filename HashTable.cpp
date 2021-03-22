//
// Created by BedTed on 3/1/2021.
//

#include "HashTable.h"

HashTable::HashTable(int max_size, unsigned int resize_occupancy) {
    this->max_size = max_size;
    if (max_size < 10) max_size = 10;
    table = new student[max_size];
    this->resize_occupancy = resize_occupancy;
    occupancy = 0;

    is_use = new int[max_size];
    for (int i = 0; i < max_size; i++) {
        is_use[i] = 0;
    }
}

HashTable::~HashTable() {
    delete[] table;
    delete[] is_use;
}

ostream &operator<<(ostream &HashOut, student record) {
    HashOut << record.FIO << " c паспортом " << record.passport << " живёт в общежитие " << record.hostel
            << " в комнате " << record.roomNumber;
}

int HashTable::HashF1(string key) {
   long int h = 0;
    int a = 127;

    for (int i = 0; key[i] != '\0'; i++) {
        h = ( h + key[i]) ;
    }
 //   cout<<h<<endl;
    return h% max_size;
}

int HashTable::HashF2(int h1, int n = 0) {
    int h2 = (h1 + c * n + d * n * n) % max_size;
    return h2;
}

int HashTable::AddHash(student cell) {
    int count = 0;
    int h1 = HashF1(cell.FIO);
    int h2 = HashF2(h1, count);
    bool flag = false;
    int flagH = -1;

    while ((is_use[h2] == 1 || is_use[h2] == 2) && count < max_size) { // посмотрели на наличие этого студента в таблице
        if (is_use[h2] == 2) { // если нашли пустое место, после удаления, то занесём туда
            flag = h2;
            flag = true;
        }
        if (is_use[h2] == 1 && cell.passport == table[h2].passport && cell.FIO == table[h2].FIO ) {
            cout << "данный студент уже добавлен ";
            cout << cell << endl;
            return 0;
        }

        count++;
        h2 = HashF2(h1, count);
    }

    if (count == max_size || ((float)occupancy / (float)max_size) * 100 > (float)resize_occupancy) {
        ReSize(); // увеличиваем на N
        AddHash(cell);
    } else {
        occupancy++; // считаем добавление;
        if (flag) {
            is_use[flagH] = 1;
            table[flagH] = cell;
            return 1;
        } else {
            is_use[h2] = 1;
            table[h2] = cell;
            return 1;
        }
    }
}

int HashTable::DelHash(student cell) {
    int count = 0;
    int h1 = HashF1(cell.FIO);
    int h2 = HashF2(h1, count);

    while (is_use[h2] != 0) {
        if (is_use[h2] == 1
            && cell.FIO == table[h2].FIO
            && cell.passport == table[h2].passport
            && cell.hostel == table[h2].hostel
            && cell.roomNumber == table[h2].roomNumber) {

            occupancy--;
            is_use[h2] = 2;
            if (((float)occupancy / (float)max_size) * 100 < (float)resize_occupancy - 10) { //???
                ReHash();
            }
            return 1; // найдено, удалено (состоние 2)
        }
        count++;
        h2 = HashF2(h1, count);
    }
    return 0; // не найдено
}

bool HashTable::SearchCell(student cell) {
    int count = 0;
    int h1 = HashF1(cell.FIO);
    int h2 = HashF2(h1, count);

    while (is_use[h2] != 0) {

        if (is_use[h2] != 2
            && cell.FIO == table[h2].FIO
            && cell.passport == table[h2].passport
            && cell.hostel == table[h2].hostel
            && cell.roomNumber == table[h2].roomNumber) {

            return true; // найдено
        }
        count++;
        h2 = HashF2(h1, count);
    }
    return false; // не найдено
}



void HashTable::coutHashTable() {
    cout << "---------------------------------Hash Table---------------------------------" << endl;
    for (int i = 0; i < max_size; i++) {
        cout << i + 1 << ". ";
        if (is_use[i] == 1) {
            cout << table[i] << endl;
        } else if (is_use[i] == 0) {
            cout << "-" << endl;
        } else {
            cout << "Del" << endl;
        }
    }
    cout << endl;
}

int HashTable::ReSize() { // расширение
    this->occupancy = 0;

    student *helpTable = table; // запомнили ссылки на наши таблицы
    int *help_is_use = is_use;

    int help_max_size = max_size; // расширенеи размера
    this->max_size *= 2;

    this->is_use = new int[max_size]; // создание новой таблицы
    this->table = new student[max_size];

    for (int i = 0; i < max_size; i++) {
        is_use[i] = 0;
    }

    for (int i = 0; i < help_max_size; i++) {
        if (help_is_use[i]) {
            AddHash(helpTable[i]);
        }
    }

    // удалить прошлую таблицу
    delete[] help_is_use;
    delete[] helpTable;
}

int HashTable::ReHash() { // попытка сужения
    this->occupancy = 0;

    student *helpTable = table; // запомнили ссылки
    int *help_is_use = is_use;

    int help_max_size = max_size;
    this->max_size /= 2;
    if (max_size < 10) max_size = 10;

    this->is_use = new int[max_size];
    this->table = new student[max_size];

    for (int i = 0; i < max_size; i++) {
        is_use[i] = 0;
    }

    for (int i = 0; i < help_max_size; i++) {
        if (help_is_use[i] == 1) {
            AddHash(helpTable[i]);
        }
    }

    // удалить прошлую таблицу
    delete[] help_is_use;
    delete[] helpTable;
}