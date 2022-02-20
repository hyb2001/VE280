#include <iostream>
#include "fstream"
#include "sstream"
#include "iomanip"
#include "string"
#include "cstdlib"
#include "cassert"
#include "simulation.h"
#include "world_type.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 4) {
        cout << "Error: Missing arguments!" << endl;
        cout << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        return 0;
    }
    bool verbose = false;
    if (argc > 4 && (argv[4] == (string) "verbose" || argv[4] == (string) "v")) {
        verbose = true;
    }
    world_t world;
    int round = atoi(argv[3]);
    int simuRound = 0;
    if (round < 0) {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        return 0;
    } else {
        if (initWorld(world, argv[1], argv[2])) {
            //if the world is valid start simulation
            cout<<"Initial state"<<endl;
            printGrid(world.grid);
            while (simuRound < round) {
                simuRound++;
                cout << "Round " << simuRound << endl;
                for (int i = 1; i <= (int) world.numCreatures; ++i) {
                    simulateCreature(world.creatures[i], world.grid, verbose);
                }
                if (!verbose) {
                    printGrid(world.grid);
                }
            }
        }
    }
    return 0;
}