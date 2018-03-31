// Demonstrate the virtual function
// g++ -std=c++11 -g -o ch14_experiment_virtual.exe ch14_experiment_virtual.C  2>&1 | tee tmp.txt

/* Note:
 * If we do class derivation (inheritance) with a key word class, we need to explicitly call public.
 * Compare the difference with the struct:
 *   class Cat: public Animal
 *   struct Fish: Animal
 *
 *   Note: if public were not used, we would get a compile error:
 *   ch14_experiment_virtual.C:60:11: error: ‘Animal’ is an inaccessible base of ‘Cat’
 *   as the default class inheritance is private
 *
 * Also the use of word virtual demonstrated in the base class
 * if virtual not used,
 *   func(cat); // the output will be from the basic functoin

 * Documentation:
https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
http://stackoverflow.com/questions/2391679/why-do-we-need-virtual-functions-in-c

*/
// #include "std_lib_facilities.h"
#include <iostream>

class Animal
{
public:
  virtual void eat() {std::cout << "I'm eating generic food\n";}
   ~Animal() { }
};

class Cat: public Animal
{
public:
  void eat() {std::cout << "I'm eating a rat\n";}
};

struct Fish: Animal
{
public:
  void eat() {std::cout << "I'm eating a worm\n";}
};

struct SiamCat: Cat
{
public:
  void eat() {std::cout << "SiamCat is eating a mouse\n";}
};

void func(Animal *xyz) { xyz->eat(); }


int main ()
{
  std::cout<< "\n";
  std::cout << "Animal experiment:\n";
  Animal *animal = new Animal;
  Cat *cat = new Cat;
  Fish *fish = new Fish;
  SiamCat *siamCat = new SiamCat;

  std::cout << "Using the direct pointers:\n";
  animal->eat();  // outputs: "I'm eating generic food"
  cat->eat();     // outputs: "I'm eating a rat"
  fish->eat();    // outputs: "I'm eating a worm"
  siamCat->eat(); // output: "SiamCat is eating a mouse"
  std::cout << "\n";


  std::cout << "Using function call:\n";
  func(animal);  // outputs: "I'm eating generic food"
  func(cat);     // the output depends on the use of virtual in the base class
  func(fish);    // the output depends on the use of virtual in the base class
  func(siamCat);
  return 0;
}
