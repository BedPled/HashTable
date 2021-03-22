#include <iostream>
#include "HashTable.cpp"

//string FIO;
//string passport;
//string hostel;
//unsigned int roomNumber;

using namespace std;
int main() {
    HashTable h(10, 80);
    student a,a1;
    string p="A0000";
    a = {"Zarozov", p, "123", 1};
    a1 = {"Azrozov", p, "123", 1};
    for (int i = 0; i < 10; ++i) {


        h.AddHash(a);
        a.passport[0]+=1;
        a.FIO[0]-=1;
        h.AddHash(a1);
        a1.passport[0]+=1;
        a1.FIO[0]+=1;
       a.FIO[1]+=1;

    }

    h.coutHashTable();

    for (int i = 0; i < 5; ++i) {
        a.FIO[0]+=2;
        a.FIO[1]-=2;
        a.passport[0]-=2;
        h.DelHash(a);
    }

    h.coutHashTable();
    for (int i = 0; i < 10; ++i) {


        h.AddHash(a);
        a.passport[0]+=1;
        a.FIO[0]-=1;
        a.FIO[1]+=1;

    }

    h.coutHashTable();



    return 0;
}

