#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Color codes for console output
#define RESET "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"
#define BOLD "\x1b[1m"

// Ecosystem entities
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
    int energy;
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

// Function prototypes
void setColor(int color);
void printColored(const string &text, const string &color);
void clearScreen();
void displayTitle();
void displayEcosystem(const Environment &env);
void animateOrganism(const Organism &org);
void simulateDay(Environment &env);
void displayStory();
void initializeEcosystem(Environment &env);
void runEcosystemSimulation(Environment &env);

int main()
{
    // Initialize random seed
    srand(time(0));

    displayStory();

    Environment ecosystem;
    initializeEcosystem(ecosystem);

    cout << "\n"
         << CYAN << "Press ENTER to begin the ecosystem simulation..." << RESET;
    cin.get();

    runEcosystemSimulation(ecosystem);

    return 0;
}

void setColor(int color)
{
    // Simplified color function - using ANSI escape codes
}

void printColored(const string &text, const string &color)
{
    cout << color << text << RESET;
}

void clearScreen()
{
    system("cls");
}

void displayEcosystem(const Environment &env)
{
    clearScreen();
    cout << BOLD << MAGENTA << "🌍 " << env.name << RESET << endl;
    cout << BLUE << env.description << RESET << endl
         << endl;

    cout << "\n"
         << GREEN << "🌱 Plants (" << env.plants.size() << "):" << RESET << endl;
    for (const auto &plant : env.plants)
    {
        cout << "  " << plant.color << "🌿 " << plant.name;
        cout << " [" << plant.growthRate << " growth/day]" << RESET << endl;
    }

    cout << "\n"
         << YELLOW << "🦊 Animals (" << env.animals.size() << "):" << RESET << endl;
    for (const auto &animal : env.animals)
    {
        cout << "  " << animal.color << "🐾 " << animal.name;
        cout << " [" << animal.speed << " speed, " << animal.energy << " energy]" << RESET << endl;
    }

    cout << "\n"
         << CYAN << "🦠 Microorganisms (" << env.organisms.size() << "):" << RESET << endl;
    for (const auto &org : env.organisms)
    {
        cout << "  " << org.color << "🔬 " << org.name;
        cout << " [" << org.energy << " energy]" << RESET << endl;
    }
}

void animateOrganism(const Organism &org)
{
    // Simple animation effect
    for (int i = 0; i < 3; i++)
    {
        clearScreen();
        cout << org.color << "🔬 " << org.name << " is moving..." << RESET;

        // Simulate delay
        for (int j = 0; j < 30000000; j++)
            ;

        clearScreen();
        cout << org.color << "🔬 " << org.name << " is at (" << org.x << "," << org.y << ")" << RESET;

        // Simulate delay
        for (int j = 0; j < 50000000; j++)
            ;
    }
}

void simulateDay(Environment &env)
{
    displayEcosystem(env);

    cout << "\n"
         << BOLD << WHITE << "🌅 Day Simulation - Watch the ecosystem come alive!" << RESET << endl;
    cout << CYAN << "Press any key to continue to next day..." << RESET;
    cin.get();

    // Simulate organism movements
    for (auto &org : env.organisms)
    {
        // Random movement
        org.x += (rand() % 3) - 1;
        org.y += (rand() % 3) - 1;
        org.energy -= 5; // Energy consumption

        // Keep within bounds
        if (org.x < 0)
            org.x = 0;
        if (org.y < 0)
            org.y = 0;
        if (org.x > 20)
            org.x = 20;
        if (org.y > 10)
            org.y = 10;

        if (org.energy <= 0)
        {
            org.energy = 0;
            cout << RED << "💀 " << org.name << " has run out of energy!" << RESET << endl;
        }
    }

    // Simulate plant growth
    for (auto &plant : env.plants)
    {
        plant.growthRate += (rand() % 3);
        if (plant.growthRate > 10)
            plant.growthRate = 10;
    }

    // Simulate animal behavior
    for (auto &animal : env.animals)
    {
        animal.x += (rand() % 5) - 2;
        animal.y += (rand() % 3) - 1;
        animal.energy -= 3;

        // Keep within bounds
        if (animal.x < 0)
            animal.x = 0;
        if (animal.y < 0)
            animal.y = 0;
        if (animal.x > 20)
            animal.x = 20;
        if (animal.y > 10)
            animal.y = 10;

        if (animal.energy <= 0)
        {
            animal.energy = 0;
            cout << RED << "🦴 " << animal.name << " is exhausted!" << RESET << endl;
        }
    }

    // Show final state
    displayEcosystem(env);
}

void displayStory()
{
    clearScreen();

    cout << BOLD << CYAN << R"(
    ╔════════════════════════════════════════════════════════════════════════════╗
    ║                                                                            ║
    ║  THE TALE OF HEISENBURG'S ECOSYSTEM                                        ║
    ║                                                                            ║
    ║  In the year 2045, in the digital realm of Heisenburg, a brilliant         ║
    ║  computer scientist named Dr. Elena Heisenberg discovered something         ║
    ║  remarkable. She had created not just programs, but living ecosystems -     ║
    ║  digital worlds where data structures and algorithms danced together        ║
    ║  in perfect harmony.                                                        ║
    ║                                                                            ║
    ║  Her greatest creation was the 'Ecosystem Simulator' - a program that      ║
    ║  could take simple menu systems, shopping carts, thesaurus tools, and      ║
    ║  inventory management, and weave them into a single, living digital         ║
    ║  environment.                                                               ║
    ║                                                                            ║
    ║  One fateful day, Dr. Heisenberg decided to connect all her systems         ║
    ║  using a revolutionary 'Data Harmony Protocol'. As she activated the        ║
    ║  system, something magical happened...                                      ║
    ║                                                                            ║
    ╚════════════════════════════════════════════════════════════════════════════╝
    )" << RESET;

    // Simulate delay
    for (int i = 0; i < 100000000; i++)
        ;

    cout << BOLD << CYAN << "\n📖 CHAPTER 1: THE AWAKENING" << RESET << endl;
    cout << GREEN << "The systems came online one by one:\n";
    cout << GREEN << "  🍽 Menu Management System" << RESET << " - Restaurant menus began organizing themselves\n";
    cout << YELLOW << "  🛒 Shopping Cart System" << RESET << " - Inventory started tracking items\n";
    cout << CYAN << "  📚 Thesaurus System" << RESET << " - Words began finding their meanings\n";
    cout << MAGENTA << "  📦 Inventory Cleanup" << RESET << " - Sparse matrices optimized themselves\n";
    cout << BLUE << "  🔬 Word Replacement" << RESET << " - Language evolved dynamically\n";

    // Simulate delay
    for (int i = 0; i < 50000000; i++)
        ;

    cout << BOLD << CYAN << "\n📖 CHAPTER 2: THE CONVERGENCE" << RESET << endl;
    cout << GREEN << "The Data Harmony Protocol activated!\n";
    cout << "Suddenly, the systems weren't just programs anymore...\n";
    cout << GREEN << "🌱 Plants began growing in digital soil\n";
    cout << YELLOW << "🦊 Animals started roaming with purpose\n";
    cout << CYAN << "🔬 Microorganisms began processing information\n";
    cout << MAGENTA << "💾 Data structures formed the foundation of all life\n";

    // Simulate delay
    for (int i = 0; i < 50000000; i++)
        ;

    cout << BOLD << CYAN << "\n📖 CHAPTER 3: THE ECOSYSTEM" << RESET << endl;
    cout << GREEN << "Welcome to " << BOLD << WHITE << "Heisenburg's Living Digital World" << RESET << "!\n\n";
    cout << "Where every algorithm, every data structure, and every line of code\n";
    cout << "contributes to a thriving, balanced ecosystem.\n\n";
    cout << CYAN << "Press ENTER to witness the birth of a new digital dawn..." << RESET;
}

void initializeEcosystem(Environment &env)
{
    env.name = "Heisenburg's Digital Garden";
    env.description = "A harmonious blend of menu systems, shopping carts, thesauruses, and inventory management - all working together in perfect data-driven harmony.";

    // Add plants (name, color, growthRate, energy, x, y)
    Plant plant1{"Oak Tree", GREEN, 2, 100, 5, 5};
    env.plants.push_back(plant1);
    Plant plant2{"Rose Bush", RED, 3, 100, 8, 7};
    env.plants.push_back(plant2);
    Plant plant3{"Fern", GREEN, 1, 100, 12, 3};
    env.plants.push_back(plant3);
    Plant plant4{"Cactus", YELLOW, 1, 100, 15, 9};
    env.plants.push_back(plant4);
    Plant plant5{"Blue Flower", BLUE, 2, 100, 10, 12};
    env.plants.push_back(plant5);

    // Add animals (name, color, speed, x, y, energy)
    Animal animal1{"Digital Fox", YELLOW, 3, 10, 5, 100};
    env.animals.push_back(animal1);
    Animal animal2{"Cyber Rabbit", WHITE, 2, 15, 8, 100};
    env.animals.push_back(animal2);
    Animal animal3{"Data Bird", CYAN, 4, 3, 10, 100};
    env.animals.push_back(animal3);
    Animal animal4{"Algorithm Wolf", RED, 2, 18, 15, 100};
    env.animals.push_back(animal4);

    // Add microorganisms (name, type, color, energy, x, y)
    Organism org1{"Binary Tree", "Microorganism", MAGENTA, 100, 10, 10};
    env.organisms.push_back(org1);
    Organism org2{"Linked List", "Microorganism", CYAN, 80, 15, 5};
    env.organisms.push_back(org2);
    Organism org3{"Hash Table", "Microorganism", GREEN, 90, 8, 12};
    env.organisms.push_back(org3);
    Organism org4{"Dynamic Array", "Microorganism", YELLOW, 85, 20, 8};
    env.organisms.push_back(org4);
    Organism org5{"Stack Memory", "Microorganism", BLUE, 95, 18, 3};
    env.organisms.push_back(org5);
}

void runEcosystemSimulation(Environment &env)
{
    int day = 1;

    while (true)
    {
        clearScreen();
        cout << BOLD << YELLOW << "🌅 Day " << day << RESET << endl;

        simulateDay(env);

        cout << "\n"
             << CYAN << "Options:" << RESET << endl;
        cout << GREEN << "1. Continue to next day" << RESET << endl;
        cout << YELLOW << "2. Watch specific organism" << RESET << endl;
        cout << RED << "3. Exit ecosystem" << RESET << endl;
        cout << "\n"
             << WHITE << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            day++;
        }
        else if (choice == 2)
        {
            cout << "\n"
                 << CYAN << "Select organism to watch:" << RESET << endl;
            cout << GREEN << "Plants:" << RESET << endl;
            for (int i = 0; i < (int)env.plants.size(); i++)
            {
                cout << (i + 1) << ". " << env.plants[i].name << endl;
            }
            cout << YELLOW << "Animals:" << RESET << endl;
            for (int i = 0; i < (int)env.animals.size(); i++)
            {
                cout << (i + 1) << ". " << env.animals[i].name << endl;
            }
            cout << MAGENTA << "Microorganisms:" << RESET << endl;
            for (int i = 0; i < (int)env.organisms.size(); i++)
            {
                cout << (i + 1) << ". " << env.organisms[i].name << endl;
            }
            cout << "\n"
                 << WHITE << "Enter organism number: ";

            int orgChoice;
            cin >> orgChoice;
            cin.ignore();

            if (orgChoice > 0 && orgChoice <= (int)env.plants.size())
            {
                int idx = orgChoice - 1;
                animateOrganism({env.plants[idx].name, "Plant", GREEN,
                                 env.plants[idx].energy, env.plants[idx].x, env.plants[idx].y});
            }
            else if (orgChoice > (int)env.plants.size() &&
                     orgChoice <= (int)(env.plants.size() + env.animals.size()))
            {
                int animalIndex = orgChoice - (int)env.plants.size() - 1;
                animateOrganism({env.animals[animalIndex].name, "Animal",
                                 env.animals[animalIndex].color,
                                 env.animals[animalIndex].energy,
                                 env.animals[animalIndex].x, env.animals[animalIndex].y});
            }
            else if (orgChoice > (int)(env.plants.size() + env.animals.size()) &&
                     orgChoice <= (int)(env.organisms.size() + env.plants.size() + env.animals.size()))
            {
                int orgIndex = orgChoice - (int)env.plants.size() - (int)env.animals.size() - 1;
                animateOrganism({env.organisms[orgIndex].name, "Microorganism",
                                 env.organisms[orgIndex].color,
                                 env.organisms[orgIndex].energy,
                                 env.organisms[orgIndex].x, env.organisms[orgIndex].y});
            }
        }
        else if (choice == 3)
        {
            clearScreen();
            cout << BOLD << RED << "Thank you for visiting Heisenburg's Digital Ecosystem!" << RESET << endl;
            cout << GREEN << "The systems will continue their dance in the digital realm..." << RESET << endl;
            break;
        }
        else
        {
            cout << RED << "Invalid choice. Please try again." << RESET;
            // Simulate delay
            for (int i = 0; i < 100000000; i++)
                ;
        }
    }
}