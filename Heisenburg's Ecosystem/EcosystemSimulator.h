#ifndef ECOSYSTEM_SIMULATOR_H
#define ECOSYSTEM_SIMULATOR_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Ecosystem entity structures
struct Organism
{
    string name;
    string type;
    string color;
    int energy;
    int x, y;
};

struct Plant
{
    string name;
    string color;
    int growthRate;
    int energy; // Added missing energy field
    int x, y;
};

struct Animal
{
    string name;
    string color;
    int speed;
    int x, y;
    int energy;
};

struct Environment
{
    string name;
    string description;
    vector<Organism> organisms;
    vector<Plant> plants;
    vector<Animal> animals;
};

// Function declarations
void setColor(int color);
void printColored(const string &text, const string &color);
void clearScreen();
void displayTitle();
void displayEcosystem(const Environment &env);
void animateOrganism(const Organism &org);
void simulateDay(Environment &env);
void displayStory();
void initializeEcosystem(Environment &env);
void runEcosystemSimulation(Environment &env); // Fixed: added Environment& parameter

#endif // ECOSYSTEM_SIMULATOR_H