#include "utils.hpp"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    system("chcp 65001 > nul");
    srand(time(0)); // seed random

    vector<string> players = {"Ben","Chou","Dara","Ean","Faye","Gita","Hout","Anna"};

    Tournament t;
    t.create(players);
    
    cout << "\n🎮 First Round Matches:\n";
    t.printFirstRound(t.getRoot());

    t.startTournament(); // plays all rounds and shows champion
    cout << "\n🛣️ Path to Final for Anna:\n";
    vector<string> path = t.pathToFinal("Anna");

    if (path.empty())
        cout << "Player not found!\n";
    else {
        for (size_t i = 0; i < path.size(); i++)
            cout << path[i] << " ";
        cout << endl;
    }
    t.wouldMeet("Chou", "Hout");
    t.wouldMeet("Anna", "Ben");
    t.wouldMeet("Faye", "Hout");
    t.wouldMeet("Anna","Hout");
}
