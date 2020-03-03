#include <iostream>

using namespace std;

class Animal{
    private:
        string _name;
        string _noise;
    public:
        Animal(const Animal& other); // copy constructor
        Animal(string animalName, string animalNoise);
        ~Animal();
        void makeNoise();
        string getNoise();
        string getName();
};

Animal::Animal(const Animal& other){
    _noise = other._noise;
    _name = other._name;
    cout << _name << " is being copied" << endl;
}

Animal::Animal(string animalName, string animalNoise){
    cout << "Creating " << animalName << endl;
    _name = animalName;
    _noise = animalNoise;
}

// tilda means class destructor
Animal::~Animal(){
    cout << _name << " is gone!!1!" << endl;
}

string Animal::getNoise(){
    return _noise;
}

string Animal::getName(){
    return _name;
}

void Animal::makeNoise(){
    cout << _noise << endl;
}

void sayMyName(Animal someAnimal){
    cout << someAnimal.getName() << endl;
}

int main(){
    Animal frog{"Frog", "Croak"};
    Animal cow{"Cow", "Moo"};
    Animal otherCow = cow;
    cout << "Animal Name: " << frog.getName() << endl;
    cout << "Animal Noise: " << frog.getNoise() << endl;
    frog.makeNoise();
    return 0;
}
