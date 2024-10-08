#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <vector>

using namespace std;

class FishCaught : public exception {
public:
    const char* what() const noexcept override {
        return "You caught a fish! Congratulations!";
    }
};

class BootCaught : public exception {
public:
    const char* what() const noexcept override {
        return "Oh no, you caught a boot! Game over.";
    }
};

struct Sector {
    bool hasFish = false;
    bool hasBoot = false;
};

class FishingGame {
private:
    vector<Sector> pond;
    int attempts;

public:
    FishingGame() : pond(9), attempts(0) {
        srand(static_cast<unsigned>(time(0)));
        int fishSector = rand() % 9;
        pond[fishSector].hasFish = true;

        int bootCount = 0;
        while (bootCount < 3) {
            int bootSector = rand() % 9;
            if (!pond[bootSector].hasFish && !pond[bootSector].hasBoot) {
                pond[bootSector].hasBoot = true;
                bootCount++;
            }
        }
    }

    void castRod(int sector) {
        if (sector < 0 || sector >= 9) {
            throw invalid_argument("Invalid sector. Choose a number between 0 and 8.");
        }

        attempts++;

        if (pond[sector].hasFish) {
            throw FishCaught();
        }
        else if (pond[sector].hasBoot) {
            throw BootCaught();
        }
        else {
            cout << "No fish here! Try again." << endl;
        }
    }

    int getAttempts() const {
        return attempts;
    }
};

int main() {
    FishingGame game;
    int sector;

    cout << "Welcome to the Fishing Game!" << endl;
    cout << "There are 9 sectors in the pond. Try to catch the fish!" << endl;

    while (true) {
        cout << "Enter sector number (0-8): ";
        cin >> sector;

        try {
            game.castRod(sector);
        }
        catch (const FishCaught& fish) {
            cout << fish.what() << endl;
            cout << "Attempts: " << game.getAttempts() << endl;
            break;
        }
        catch (const BootCaught& boot) {
            cout << boot.what() << endl;
            cout << "Attempts: " << game.getAttempts() << endl;
            break;
        }
        catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
