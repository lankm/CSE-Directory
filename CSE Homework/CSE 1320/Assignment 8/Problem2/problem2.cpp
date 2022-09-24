#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Vehicle.hpp"

using namespace std;

void addVehicle(vector<Vehicle>& vec) {
    Vehicle v;
    string buff;

    cout << "Enter a year: ";
    cin >> buff;
    v.setYear(stoi(buff));

    cout << "Enter a make: ";
    cin >> buff;
    v.setMake(buff);

    cout << "Enter a model: ";
    cin >> buff;
    v.setModel(buff);

    cout << "Enter a color: ";
    cin >> buff;
    v.setColor(buff);

    cout << "Enter a license plate #: ";
    cin >> buff;
    v.setLIC(buff);

    vec.push_back(v);
}
void loadVehicles(vector<Vehicle>& vec) {
    string buff;

    cout << "Enter a CSV filename: ";
    cin >> buff;

    ifstream file(buff);
    while(getline(file, buff)) {
        vec.push_back(Vehicle(buff));
    }
}
void printVehicles(vector<Vehicle>& vec) {
    for(int i=0; i<(int)vec.size(); i++) {
        cout << vec[i] << endl;
    }
}
void printVehiclesCSV(vector<Vehicle>& vec) {
    for(int i=0; i<(int)vec.size(); i++) {
        cout << vec[i].toCsv() << endl;
    }
}

int main() {
    vector<Vehicle> vec;

    vector<string> commands;
    commands.push_back("Add a vehicle");
    commands.push_back("Load vehicles");
    commands.push_back("Print vehicles");
    commands.push_back("Print vehicles CSV");
    commands.push_back("Quit");

    bool loop = true;
    while(loop) {
        string buff;

        for(int i=0; i<(int)commands.size(); i++) {
            cout << i+1 << ". " << commands[i] << endl;
        }
        cout << "> ";
        cin >> buff;

        switch(stoi(buff)) {
            case 1: addVehicle(vec); break;
            case 2: loadVehicles(vec); break;
            case 3: printVehicles(vec); break;
            case 4: printVehiclesCSV(vec); break;
            case 5: loop=false; break;
            default: cout << "Invalid input" << endl;
        }
    }
}
