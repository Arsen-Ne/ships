#include <iostream>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <deque> 

using namespace std;

vector<string> pirs(10);
deque<string> shipQueue;

ofstream out("ships.out");

void assignPirs(int n, string name) {
    pirs[n] = name;
    out << "Корабль " << name << " направляется к причалу №" << n + 1 << endl;
}

boolean findPirs(string name) {
    for (int i = 0; i < pirs.size(); i++) {
        if (pirs[i].empty()) {
            assignPirs(i, name);
            return true;
        }
    }
    return false;
}

void arrivedNewShip(string name) {   
    out << "Корабль " << name << " прибыл в порт" << endl; 
    if (shipQueue.empty() && findPirs(name)) {
        return;       
    }
    else {
        shipQueue.push_back(name);
            out << "Корабль " << name << " встал в очередь" << endl;
    }
}

void releasePirs(int number) {       
    pirs[number] = "";
    out << "Причал №" << number + 1 << " освободился" << endl;

    if (!shipQueue.empty()) {
        string name = shipQueue.front();
        shipQueue.pop_front();
        assignPirs(number, name);
    }
}

void printQueue() {
    out << "---" << endl << "Очередь кораблей на рейде (" << shipQueue.size() << ")";
    if (shipQueue.size() > 0) {
        out << ": " << endl;
        for (int i = 0; i < shipQueue.size(); i++) {
            out << shipQueue[i] << endl;
        }
    }
    else {
        out << endl;
    }
     out << "---" << endl;
}

void printPirsState() {
    out << "---" << endl << "Статус причалов:" << endl;
    for (int i = 0; i < pirs.size(); i++) {
        out << i + 1 << ": " << pirs[i] << endl;
    }
    out << "---" << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
        
    ifstream in("ships.in");

    
    if (!in.is_open()) {
        out << "Ошибка открытия файла ships.in";
        exit(0);
    }
    else if (in.peek() == EOF) {
        out << "Файл ships.in пустой";
        exit(0);
    }
       
    int n;
    in >> n;
    pirs.resize(n);
 
    string line, name;
    int key, number;

    while (getline(in, line))
    {        
        stringstream ss(line);       
        ss >> key;              
        switch (key) {
        case 1:
            getline(ss, name, ' '); 
            getline(ss, name);
            arrivedNewShip(name);            
            break;
        case 2:
            ss >> number;            
            releasePirs(number - 1);                        
            break;
        case 3:
            printQueue();
            break;
        case 4:
            printPirsState();
            break;
        }                
        key = 0; 
    }
 }