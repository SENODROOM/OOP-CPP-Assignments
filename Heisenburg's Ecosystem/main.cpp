#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <thread>
#include <chrono>
using namespace std;

// Include all system headers
#include "menumanagementsystem.h"
#include "ShoppingCartManagementSystem.h"
#include "ThesaurusBasedWritingAssistant.h"
#include "InventoryCleanup.h"
#include "EcosystemSimulator.h"

// Color codes for console output
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define BOLD "\033[1m"

void setColor(int color);
void printColored(const string &text, const string &color);
void clearScreen();
void setupConsole();
void displayMainMenu();
void runMenuSystem();
void runShoppingCartSystem();
void runThesaurusSystem();
void runInventoryCleanupSystem();
void displayEcosystemIntro();

int main()
{
    setupConsole();

    while (true)
    {
        clearScreen();
        displayMainMenu();

        int choice;
        cout << "\n"
             << BOLD << WHITE << "Enter your choice (0-5): ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            runMenuSystem();
            break;
        case 2:
            runShoppingCartSystem();
            break;
        case 3:
            runThesaurusSystem();
            break;
        case 4:
            runInventoryCleanupSystem();
            break;
        case 5:
            displayEcosystemIntro();
            break;
        case 0:
            clearScreen();
            setColor(12); // Red
            cout << BOLD << RED << "Thank you for visiting Heisenburg's Integrated Systems!" << RESET << endl;
            setColor(10); // Green
            cout << GREEN << "All systems will continue their work in harmony..." << RESET << endl;
            return 0;
        default:
            clearScreen();
            setColor(12); // Red
            cout << RED << "Invalid choice. Please try again." << RESET;
            this_thread::sleep_for(chrono::milliseconds(1000));
            break;
        }
    }

    return 0;
}

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printColored(const string &text, const string &color)
{
    cout << color << text << RESET;
}

void clearScreen()
{
    system("cls");
}

void setupConsole()
{
    // Set console to support ANSI colors and UTF-8
    system("chcp 65001 > nul");
    system("cls");

    // Set console title
    system("powershell -Command \"& {$Host.UI.RawUI.WindowTitle = 'Heisenburg\\'s Ecosystem Hub'}\" 2>nul");

    // Enable virtual terminal processing for ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    // Try to set a font that supports emojis
    system("powershell -Command \"& {try {$Host.UI.RawUI.FontName = 'Consolas'} catch {}}\" 2>nul");
}

void displayMainMenu()
{
    setColor(14); // Yellow
    cout << R"(
╔══════════════════════════════════════════════════════════════╗
║                                                              ║
║                    HEISENBURG ECOSYSTEM                      ║
║                                                              ║
║                 Integrated System Hub                        ║
║                                                              ║
╚══════════════════════════════════════════════════════════════╝
    )" << RESET;

    setColor(11); // Light Cyan
    cout << BOLD << CYAN << "\n=== Heisenburg's Integrated System Hub ===" << RESET << endl;
    cout << YELLOW << "Where All Systems Work in Perfect Harmony" << RESET << endl
         << endl;

    setColor(10); // Light Green
    cout << BOLD << WHITE << "AVAILABLE SYSTEMS:" << RESET << endl;
    cout << GREEN << "1. [MENU] Menu Management System" << RESET << " - Restaurant menu organization and sorting" << endl;
    cout << GREEN << "2. [CART] Shopping Cart System" << RESET << " - Smart shopping cart with attributes" << endl;
    cout << GREEN << "3. [BOOK] Thesaurus System" << RESET << " - Word replacement and paraphrasing" << endl;
    cout << GREEN << "4. [BOX]  Inventory Cleanup" << RESET << " - Sparse matrix optimization" << endl;
    cout << GREEN << "5. [WORLD] Ecosystem Simulator" << RESET << " - Living digital world simulation" << endl;
    cout << RED << "0. [EXIT] Exit" << RESET << " - Leave the system hub" << endl;
}

void runMenuSystem()
{
    clearScreen();
    setColor(11); // Light Cyan
    cout << BOLD << "[MENU] Menu Management System" << RESET << endl;
    cout << GREEN << "Loading restaurant data and organizing menu items...\n"
         << RESET;

    // Simulate menu system functionality
    cout << CYAN << "\n[LIST] Menu Features:" << RESET << endl;
    cout << "• Sort by cuisine type" << endl;
    cout << "• Restaurant name organization" << endl;
    cout << "• Category-based ordering" << endl;
    cout << "• Price-based sorting" << endl;

    cout << YELLOW << "\n[DATA] Processing sample data..." << RESET << endl;

    // Simulate the menu system (simplified version)
    string cuisines[] = {"Italian", "Mexican", "Chinese", "Indian"};
    string restaurants[] = {"Mario's", "Taco Bell", "Panda Express", "Spice Garden"};
    string categories[] = {"Appetizer", "Main Course", "Dessert"};

    for (int i = 0; i < 4; i++)
    {
        cout << GREEN << "Processing " << cuisines[i] << " cuisine at " << restaurants[i] << "..." << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(800));
    }

    cout << MAGENTA << "\n[DONE] Menu System Complete!" << RESET << endl;
    cout << CYAN << "Press ENTER to return to main menu..." << RESET;
    cin.get();
}

void runShoppingCartSystem()
{
    clearScreen();
    setColor(11); // Light Cyan
    cout << BOLD << "[CART] Shopping Cart System" << RESET << endl;
    cout << GREEN << "Initializing smart shopping cart with attribute management...\n"
         << RESET;

    // Simulate shopping cart functionality
    cout << CYAN << "\n[CART] Cart Features:" << RESET << endl;
    cout << "• Dynamic item management" << endl;
    cout << "• Custom attributes per item" << endl;
    cout << "• Price calculation and sorting" << endl;
    cout << "• Item search and filtering" << endl;

    cout << YELLOW << "\n[ADD] Adding sample items..." << RESET << endl;

    string items[] = {"Laptop", "Headphones", "Coffee Maker", "Mouse Pad"};
    double prices[] = {999.99, 89.99, 45.50, 25.99};

    for (int i = 0; i < 4; i++)
    {
        cout << GREEN << "Adding " << items[i] << " ($" << prices[i] << ") to cart..." << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(600));
    }

    cout << MAGENTA << "\n[DONE] Shopping Cart System Complete!" << RESET << endl;
    cout << CYAN << "Press ENTER to return to main menu..." << RESET;
    cin.get();
}

void runThesaurusSystem()
{
    clearScreen();
    setColor(11); // Light Cyan
    cout << BOLD << "[BOOK] Thesaurus System" << RESET << endl;
    cout << GREEN << "Loading word database and paraphrasing engine...\n"
         << RESET;

    // Simulate thesaurus functionality
    cout << CYAN << "\n[BOOK] Thesaurus Features:" << RESET << endl;
    cout << "• Dynamic word grouping" << endl;
    cout << "• Intelligent word replacement" << endl;
    cout << "• Context-aware paraphrasing" << endl;
    cout << "• Custom vocabulary management" << endl;

    cout << YELLOW << "\n[SEARCH] Processing word replacements..." << RESET << endl;

    string words[] = {"happy", "sad", "fast", "slow", "big", "small"};
    string replacements[] = {"joyful", "sorrowful", "rapid", "leisurely", "enormous", "tiny"};

    for (int i = 0; i < 6; i++)
    {
        cout << GREEN << "Replacing \"" << words[i] << "\" with \"" << replacements[i] << "\"..." << RESET << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << MAGENTA << "\n[DONE] Thesaurus System Complete!" << RESET << endl;
    cout << CYAN << "Press ENTER to return to main menu..." << RESET;
    cin.get();
}

void runInventoryCleanupSystem()
{
    clearScreen();
    setColor(11); // Light Cyan
    cout << BOLD << "[BOX] Inventory Cleanup System" << RESET << endl;
    cout << GREEN << "Initializing sparse matrix optimization engine...\n"
         << RESET;

    // Simulate inventory cleanup
    cout << CYAN << "\n[BOX] Cleanup Features:" << RESET << endl;
    cout << "• Sparse matrix detection" << endl;
    cout << "• Zero-element removal" << endl;
    cout << "• Memory optimization" << endl;
    cout << "• Dynamic array management" << endl;

    cout << YELLOW << "\n[CLEAN] Processing inventory data..." << RESET << endl;

    // Simulate processing a sparse matrix
    int matrix[5][6] = {
        {2, 3, 1, 0, 0, 0},
        {0, 0, 0, 1, 1, 0},
        {1, 0, 0, 0, 0, 0},
        {1, 1, 1, 2, 0, 2},
        {5, 0, 0, 0, 10, 0}};

    cout << GREEN << "Analyzing 5x6 inventory matrix..." << RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(800));

    int totalElements = 0;
    int nonZeroElements = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            totalElements++;
            if (matrix[i][j] != 0)
            {
                nonZeroElements++;
            }
        }
    }

    cout << CYAN << "\n[RESULTS] Results:" << RESET << endl;
    cout << "Total elements: " << totalElements << endl;
    cout << "Non-zero elements: " << nonZeroElements << endl;
    cout << "Memory saved: " << (totalElements - nonZeroElements) << " elements ("
         << ((totalElements - nonZeroElements) * 100 / totalElements) << "%)" << RESET << endl;

    cout << MAGENTA << "\n[DONE] Inventory Cleanup Complete!" << RESET << endl;
    cout << CYAN << "Press ENTER to return to main menu..." << RESET;
    cin.get();
}

void displayEcosystemIntro()
{
    clearScreen();
    setColor(11); // Light Cyan
    cout << BOLD << "[WORLD] Ecosystem Simulator" << RESET << endl;
    cout << GREEN << "Preparing to launch Heisenburg's Digital World...\n"
         << RESET;

    cout << CYAN << "\n[WORLD] Ecosystem Features:" << RESET << endl;
    cout << "• Living organisms with AI behavior" << endl;
    cout << "• Dynamic plant growth simulation" << endl;
    cout << "• Energy-based survival mechanics" << endl;
    cout << "• Interactive day/night cycles" << endl;
    cout << "• Colorful console visualization" << endl;

    cout << YELLOW << "\n[LAUNCH] Launching ecosystem..." << RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(1500));

    // Launch the actual ecosystem simulator
    cout << MAGENTA << "\n[STAR] TRANSITIONING TO ECOSYSTEM SIMULATOR..." << RESET << endl;
    cout << CYAN << "Note: Run EcosystemSimulator.exe for the full experience!" << RESET << endl;
    this_thread::sleep_for(chrono::milliseconds(2000));
}
