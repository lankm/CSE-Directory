#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Vehicle {
    int year_;
    string make_;
    string model_;
    string color_;
    string lic_;

    public:
        Vehicle() {
            year_=2021;
            make_="None";
            model_="None";
            color_="None";
            lic_="None";
        }

        Vehicle(string make, string model) {    // why would you ever need to only set the make and model.
            year_=-1;
            make_=make;
            model_=model;
            color_="None";
            lic_="None";
        }

        Vehicle(string csv) {
            vector<string> tokens;

            stringstream check(csv);
            string temp;

            while(getline(check, temp, ',')) {
                tokens.push_back(temp);
            }

            year_=stoi(tokens[0]);
            make_=tokens[1];
            model_=tokens[2];
            color_=tokens[3];
            lic_=tokens[4];
        }

        Vehicle(int year, string make, string model, string color, string lic) {
            year_=year;
            make_=make;
            model_=model;
            color_=color;
            lic_=lic;
        }

        string toCsv() {
            return to_string(year_)+","+make_+","+model_+","+color_+","+lic_;
        }

        auto& getYear() const { return year_; }
        void setYear(int y) { year_=y; }

        auto& getMake() const { return make_; }
        void setMake(string s) { make_=s; }

        auto& getModel() const { return model_; }
        void setModel(string s) { model_=s; }

        auto& getColor() const { return color_; }
        void setColor(string s) { color_=s; }

        auto& getLIC() const { return lic_; }
        void setLIC(string s) { lic_=s; }

        friend ostream& operator<<(ostream& os, Vehicle const& v) {    //tostring equivilant
            return os << v.getYear()
                << " " << v.getMake()
                << " " << v.getModel() 
                << " (" << v.getColor() 
                << ") LIC#" << v.getLIC();
        }
        bool operator==(const Vehicle& b) {
            return year_==b.getYear() && make_==b.getMake() && model_==b.getModel() && color_==b.getColor() && lic_==b.getLIC();
        } 
};
