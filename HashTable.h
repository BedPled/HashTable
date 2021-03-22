//
// Created by BedTed on 3/1/2021.
//
#pragma once
#include "lib.h"


#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

/*
1) Конструктор (N, % заполнияемости)
2) Деструктор
3) Hash_f1 (key) -> addz
4) Hash_f2 (addz, n попытки) -> add
5) Add (record) -> int  (не добовлять одинаковые, не добовлять с одинаковым ключём)
6) Del (record) -> (если все поля совпали)
7) Search (record) -> (true/false)
8) Печать (перегрузка вывоа в поток <<)
 */
using namespace std;

class HashTable {
private:
    student* table;
    int* is_use; // вектор состояний 0 - пустая, 1 - заполнена, 2 - удалена
    int max_size;
    unsigned int resize_occupancy; // в процентах от 0 до 100
    unsigned int occupancy; // процент заполненности от 0 до 100

// 3) Hash_f1 (key) -> addz
    int HashF1(string key);

// 4) Hash_f2 (hash, n попытки) -> add
    int HashF2(int h1, int n);

    int ReSize();

    int ReHash();

public:

//    1) Конструктор (N, % заполнияемости)
    HashTable(int max_size, unsigned int resize_occupancy);

//    2) Деструктор
    ~HashTable();

//    5) Add (record) -> int (1 ок, 0 плохо) (не добовлять одинаковые, не добовлять с одинаковым ключём)
    int AddHash(student cell);

//    6) Del (record) ->
    int DelHash(student cell);

//    7) Search (record) -> (true/false)
    bool SearchCell(student cell);

//    8) Печать (перегрузка вывоа в поток <<)
    void coutHashTable();
};


#endif //HASHTABLE_HASHTABLE_H
