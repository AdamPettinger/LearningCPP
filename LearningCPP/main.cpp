//
//  main.cpp
//  LearningCPP
//
//  Created by Adam on 6/21/17.
//  Copyright © 2017 Adam. All rights reserved.
//

#include <iostream>
#include <string>
#include "Poker.hpp"

using std::cout;

void DemonstrationFunction(){
    std::cout << "I am in the Demo Function!\n";
    
}

double Addf(double x, double y){
    
    return(x+y);
}

void swap(int *x, int *y);

enum BREED {Yorkie, Cairn, Dandie, Shetland, Doberman, Lab};

class Mammal
{
public:
    Mammal(): itsAge(2), itsWeight(5){};
    Mammal(int age);
    ~Mammal(){};
    
    int GetAge() const {return itsAge;};
    void SetAge(int age) {itsAge = age;};
    int GetWeight() const {return itsWeight;};
    void SetWeight(int w) {itsWeight = w;};
    
    void Speak() const {std::cout << "My mammal speaks\n";};
    void Sleep()const {std::cout << "My mammal is sleeping\n";};
    
protected:
    int itsAge;
    int itsWeight;
};

Mammal::Mammal(int age)
{
    itsAge = age;
    itsWeight = 5;
}

class Dog: public Mammal
{
public:
    Dog():itsBreed(Yorkie){};
    Dog(int age);
    Dog (int age, BREED b);
    ~Dog(){};
    
    BREED GetBreed() const {return itsBreed;};
    void SetBreed(BREED b) {itsBreed = b;};
    
    void WagTail() {std::cout << "Wagging meh tail\n";};
    void BegForFood() {std::cout << "Gimme food\n";};
    void Speak() {std::cout << "Woof woof!\n";};
    
protected:
    BREED itsBreed;
};

Dog::Dog(int age):
Mammal(age)
{
    std::cout << "Setting Dog's (and Mammal's) age...\n";
}

Dog::Dog(int age, BREED b):
Mammal(age),
itsBreed(b)
{
    std::cout << "Setting Dog's (and Mammal's) age, and Dog's breed...\n";
}


class Cat: public Mammal
{
public:
    // public accessors
    Cat(int initAge);
    ~Cat();
    int getAge() const;
    void setAge(int Age);
    
    int getWeight() const;
    void setWeight(int Weight);
    
    void Meow() const;
    
private:
    int itsAge;
    int itsWeight;
};

// Define some Cat methods
Cat::Cat(int initAge)
{
    itsAge = initAge;
}

Cat::~Cat()
{
}

int Cat::getAge() const
{
    return itsAge;
}

void Cat::setAge(int Age)
{
    itsAge = Age;
}

void Cat::Meow() const
{
    std::cout << "Meow\n";
}


class CatDog: public Dog, public Cat
{
public:
    CatDog();
    ~CatDog();
};


int main() {
    //std::cout << "Hello, World!\n";
    

    //std::cout << "Testing Manipulator" << std::endl;
    //std::cout << "\tTest";
    //std::cout << "Divide 8 by 5: " << (double) 8/5 << "\n";
    
    /*
    std::cout << "In Main\n";
    DemonstrationFunction();
    std::cout << "In Main again\n";
    */
    
    /*
    //      Day 2
    double a,b;
    std::cout << "Enter Two Numbers to add: ";
    std::cin >> a;
    std::cin >> b;
    
    std::cout << "Sum is: " << Addf(a,b) << "\n";
    */
    
    
    /*
    //      Day 3
    unsigned short int x = 4;
    std::cout << x << "\n";
    
    typedef unsigned int UINT;
    
    UINT y;
    std::cin >> y;
    std::cout << "\nY is: " << y << "\n";
    
    const short z = 42;
    std::cout << z << "\n";
    
    enum Days {Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday};
    Days Dayoff = Sunday;
    Days Dayoff2 = Monday;
    
    std::cout << Dayoff << " " << Dayoff2;
    */
    
    /*
    //      Day 4
    std::cout << "Input Number please: ";
    int test;
    std::cin >> test;
    std::cout << "\n";
    
    if (test == 0)
    {
        std::cout << "Number is 0\n";
    }
    else if (test % 2 == 1)
    {
        std::cout << "Number is Odd\n";
    }
    else
    {
        std::cout << "Number is Even\n";
    }
    
    std::cout << "\nInput 2 Numbers please: ";
    int x, y, z;
    std::cin >> x >> y;
    
    z = (x > y) ? x : y;
    std::cout << "z is: " << z << "\n";
    */
    
    /*
    //      Day 5
    // Prototype the function before main()
    // Define the function after main()
    // Variables defined before main are global
    // The return types can be the same or different on overloaded functions
    */
    
    /*
    //      Day 6
    Cat Frisky(7);
    std::cout << "Frisky's Age is: " << Frisky.getAge() << "\n";
    int age;
    std::cin >> age;
    Frisky.setAge(age);
    
    // Generally try to keep the member data private and use public functions to access and set it.
    
    std::cout << "Frisky's Age is: " << Frisky.getAge() << "\n";
    Frisky.Meow();
    
    // To do this in multiple files, do the class declaration (just the info) in a header (.hpp) file
    // Then right the methods and stuff if a class file (.cpp) and put #NAME.hpp at the top
    */
    
    
    //      Day 7
    /*
    int i, j;
    for (i = 0, j = 1; i<10; i++, j++)
    {
        std::cout << "i is: " << i << ", j is " << j << "\n";
    }
    
    while (i>1)
    {
        std::cout << i << " ";
        i --;
    }
    
    std::cout << "Enter number between 1 and 4: ";
    int s;
    std::cin >> s;
    std::cout << "\n";
    
    switch (s)
    {
        case 1: std::cout << "You chose 1?!?\n";
                break;
            
        case 2:
        {
            std::cout << "Nice one!\n";
            break;
        }
            
        case 3:
        {
            std::cout << "You dingus! Gonna fall through...\n";
        }
            
        case 4:
        {
            std::cout << "Bold choice!\n";
            break;
        }
        default:
        {
            std::cout << "Were my instructions not clear?\n";
            break;
        }
            
    }
    */
    
    /*
    //      Day 8
    short ShortVar = 5;
    std:cout << "Short Variable: " << ShortVar << "\tAddress is: " << &ShortVar << "\n";
    
    int howOld = 22;
    int *pAge = &howOld;
    
    int yourAge = *pAge;
    
    int localVariable = 5;
    int *pLocal = &localVariable;
    int *pHeap = new int;
    
    *pHeap = 7;
    std::cout << "Local: " << localVariable << "\t *pLocal: " <<  *pLocal << "\n";
    std::cout << "pHeap: " << *pHeap;
    
    delete pHeap;
    *pHeap = 0;
    */
    
    
    /*
    //      Day 9
    int intOne;
    int &rIntOne = intOne;
    intOne = 5;
    
    std::cout << "intOne: " << intOne << "\n";
    std::cout << "rIntOne: " << rIntOne << "\n";
    
    rIntOne = 7;

    std::cout << "intOne: " << intOne << "\n";
    std::cout << "rIntOne: " << rIntOne << "\n";
    
    int x = 5, y = 10;
    
    swap(&x, &y);
    std::cout << "x is: " << x << ". y is : " << y << "\n";
     */
    
    
    /*
    //      Day 11 - Arrays
    int LongArray[25];
    LongArray[5] = 2;
    
    int shortArray[3] = {1, 5, 10};
    int length = sizeof(shortArray)/sizeof(shortArray[0]);
    std::cout << length;
    
    int chessBoard[8][8];
    
    char testString[] = "Test!";
    std::cout << strlen(testString);
    
    std::string testing = "Testing Again!";
    std::cout << "\n" << testing << "\n";
    
    std::string oneMore = testing + " " + "Whooo!";
    std::cout << "\n" << oneMore << "\n";
    */
    
    
    /*
    //      Day 12 - Inheritance
    // "protected" allows derived classes to access, but nothing else. Its between public and private
    Dog fido;
    fido.Speak();
    fido.WagTail();
    
    std::cout << "Fido is " << fido.GetAge() << " years old \n";
    
    Dog rover(5);
    Dog buster(3, Yorkie);
    buster.Speak();
    
    std::cout << "Rover's age: " << rover.GetAge() << "\n";
    std::cout << "Buster's age: " << buster.GetAge() << "\n";
    */
    
    
    //      Day 13 - Polymorphism
    
    
    return 0;
    
   
    
}


void swap(int *px, int *py){
    int temp;
    temp = *px;
    *px = *py;
    *py = temp;
    
    
}


