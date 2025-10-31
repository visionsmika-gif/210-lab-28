/*
INSTRUCTIONS:

Lab 24 provided basic functionality to the list of Goat objects: add, delete.

Now we know quite a bit more about STL algorithms and how to implement them on associative containers such as the std::list.

Expand the main menu of this program by adding 8 more options that feature different STL algorithms. Each of the 8 additions
should be its own milestone for a total of 8 milestones. Your code should run at each milestone and clearly demonstrate or
exercise what you just coded in that milestone.
*/

/*

New STL algorithms to implement:

1 - Unique: Remove duplicates (assuming sorted)

2 - Reverse: Reverse the order of all goats.

4 - Find_if: Find a goat according to a condition, like their name.

5 - Transform: Age all goats by 1.

6 - Accumulate: Calculate the total age of every goat.

7 - Any_of: Check if any of the goats have a certain color.

8 - Clear: Empty the goat container.

3 - Shuffle: Shuffle all goats.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
#include <algorithm>
#include <numeric>
#include <random>
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

// std::unique
void unique_letter_names(list<Goat>& trip) {
    trip.sort();
    trip.erase(unique(trip.begin(), trip.end(), [](const Goat& a, const Goat& b) { return a.get_name()[0] == b.get_name()[0]; }), trip.end());

    cout << "New trip:\n";
    display_trip(trip);
}

// std::find_if
void find_goat(const list<Goat>& trip) {
    string name;
    cout << "Enter a name to find --> ";
    cin >> name;

    auto it = find_if(trip.begin(), trip.end(), [name](const Goat& g) { return g.get_name() == name; });

    if (it != trip.end()) {
        cout << "Found " << name << "'s data:\n";
        cout << "\t"
            << name
            << " (" << it->get_age()
            << ", " << it->get_color() << ")\n";
    }
    else {
        cout << name << " not found.\n";
    }
}

// std::reverse
void reverse_trip(list<Goat>& trip) {
    reverse(trip.begin(), trip.end());

    cout << "New trip:\n";
    display_trip(trip);
}

// std::accumulate
void total_age(const list<Goat>& trip) {
    int totalAge = accumulate(trip.begin(), trip.end(), 0, [](int sum, const Goat& g) { return sum + g.get_age(); });
    cout << "Total age of all goats: " << totalAge << "\n";
}

// std:: any_of
void find_color(const list<Goat>& trip) {
    string color;
    cout << "Enter a color (case sensitive) --> ";
    cin >> color;

    bool hasColor = any_of(trip.begin(), trip.end(), [color](const Goat& g) { return g.get_color() == color; });

    if (hasColor) {
        cout << "A goat with the color '" << color << "' exists.\n";
    }
    else {
        cout << "No goats have the color '" << color << ".'\n";
    }
}

// std::clear
void clear_trip(list<Goat>& trip) {
    trip.clear();
}

// std::transform
void age_goats(list<Goat>& trip) {
    transform(trip.begin(), trip.end(), trip.begin(), [](Goat& g) {g.set_age(g.get_age() + 1); return g; });
    
    cout << "New trip:\n";
    display_trip(trip);
}

// std::for_each
void paint_trip(list <Goat>& trip) {
    string color;
    cout << "Enter a color to paint all goats --> ";
    cin >> color;

    for_each(trip.begin(), trip.end(), [color](Goat& g) {g.set_color(color);});

    cout << "New trip:\n";
    display_trip(trip);

}

int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 12) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4: // [4] Remove consecutive goats whose name starts with the same letter
                cout << "Reversing goats.\n";
                reverse_trip(trip);
                break;
            case 5:
                cout << "Finding a goat.\n";
                find_goat(trip);
                break;
            case 6:
                cout << "Removing goats.\n";
                unique_letter_names(trip);
                break;
            case 7:
                cout << "Calculating total age.\n";
                total_age(trip);
                break;
            case 8:
                cout << "Aging all goats by 1.\n";
                age_goats(trip);
                break;
            case 9:
                cout << "Checking for the existence of a color.\n";
                find_color(trip);
                break;
            case 10:
                cout << "Painting goats.\n";
                paint_trip(trip);
                break;
            case 11:
                cout << "Clearing all goats.\n";
                clear_trip(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";

    // Main menu has been expanded to include 8 new options that feature different STL algorithms.
    cout << "[4] Reverse goats\n";
    cout << "[5] Find a goat by name\n";
    cout << "[6] Remove consecutive goats whose name starts with the same letter\n";
    cout << "[7] Calculate the total age of all goats\n";
    cout << "[8] Age up all goats\n";
    cout << "[9] Check if any goats have a certain color\n";
    cout << "[10] Paint all goats a certain color\n";
    cout << "[11] Clear all goats\n";

    cout << "[12] Quit\n";

    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 12) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    if (trip.empty()) {
        cout << "Trip is empty. No goats deleted.\n";
        return;
    }

    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    if (trp.empty()) {
        cout << "Trip is empty.\n";
        return;
    }

    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}