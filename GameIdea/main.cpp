#include <iostream>
#include "main.hpp"
#include <vector>

using namespace std;

int main (int argc, char *argv[]) {
    vector<AstroObject*> satalites;
    Star o(10.0f,10.0f,satalites,"sol");
    satalites.push_back(&o);
    satalites.push_back(&o);
    satalites.push_back(&o);
    satalites.push_back(&o);

    Star s(10.0f,10.0f,satalites,"sol");

    s.map();
}
