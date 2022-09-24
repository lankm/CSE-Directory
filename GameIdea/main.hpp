#include <cstdio>
#include <vector>

using namespace std;

class AstroObject {
    public:
        char c;
        vector<AstroObject*> satalites;

        virtual void map()=0;
};

class AstroBody: public AstroObject {
    public:
        
        string name;
        float mass;
        float radius;

        AstroBody(float mass, float radius, vector<AstroObject*> satalites, string name) {
            this->mass=mass;
            this->radius=radius;
            this->satalites=satalites;
            this->name=name;
        }
        void map() {
            printf("%c\t\t\"%s\"\n", c, name.c_str());
            for(int i=0; i<satalites.size(); i++) {
                printf("  %c\n", satalites[i]->c);
            }
        }
        
};
class Star: public AstroBody {
    public:
        Star(float mass, float radius, vector<AstroObject*> satalites, string name) : AstroBody(mass, radius, satalites, name) {
            c='O';
        }
};
class Planet: public AstroBody  {
    public:
};
class Moon: public AstroBody  {
    public:
};

class BaryPair: public AstroObject {
    
};