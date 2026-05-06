#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>

using namespace std;

int main() {
    Matchmaking matchmaking;

    cout << "=== Teste 1: insercao ===" << endl;
    matchmaking.insert(Player(1, "Ana", 1000, 1));
    matchmaking.insert(Player(2, "Bruno", 1010, 2));
    matchmaking.insert(Player(3, "Carla", 1020, 3));
    matchmaking.insert(Player(4, "Diego", 1100, 4));
    matchmaking.printWaitingPlayers();

    cout << endl;

    cout << "=== Teste 2: getWaitingPlayers ===" << endl;
    int n;
    Player* waiting = matchmaking.getWaitingPlayers(&n);

    cout << "n = " << n << endl;
    for (int i = 0; i < n; i++) {
        cout << "["
             << waiting[i].getId() << " | "
             << waiting[i].getName() << " | "
             << waiting[i].getScore() << " | "
             << waiting[i].getTimestamp()
             << "]" << endl;
    }

    delete[] waiting;

    cout << endl;

    cout << "=== Teste 3: formGroup com sucesso ===" << endl;
    Player* group = matchmaking.formGroup(3, 30, &n);

    matchmaking.printGroup(group, n);
    cout << "n = " << n << endl;

    delete[] group;

    cout << endl;

    cout << "Estado apos formar grupo:" << endl;
    matchmaking.printWaitingPlayers();

    cout << endl;

    cout << "=== Teste 4: removePlayer ===" << endl;
    bool removed = matchmaking.removePlayer(4);
    cout << "removePlayer(4): " << removed << endl;
    matchmaking.printWaitingPlayers();

    cout << endl;

    cout << "=== Teste 5: tentativa de remover ID inexistente ===" << endl;
    removed = matchmaking.removePlayer(99);
    cout << "removePlayer(99): " << removed << endl;
    matchmaking.printWaitingPlayers();

    cout << endl;

    cout << "=== Teste 6: formGroup sem sucesso ===" << endl;
    matchmaking.insert(Player(5, "Eduarda", 1000, 5));
    matchmaking.insert(Player(6, "Felipe", 1200, 6));
    matchmaking.insert(Player(7, "Giulia", 1400, 7));

    matchmaking.printWaitingPlayers();

    group = matchmaking.formGroup(3, 50, &n);

    matchmaking.printGroup(group, n);
    cout << "n = " << n << endl;

    delete[] group;

    cout << endl;

    cout << "Estado final:" << endl;
    matchmaking.printWaitingPlayers();

    cout << endl;

    cout << "=== Teste 7: insertion sort ===" << endl;


    matchmaking.insert(Player(1, "Ana", 1000, 8));
    matchmaking.insert(Player(2, "Bruno", 900, 2));
    matchmaking.insert(Player(3, "Carla", 1000, 1));
    matchmaking.insert(Player(4, "Diego", 900, 4));
    matchmaking.insert(Player(5, "Eduarda", 1100, 3));

    cout << "Antes da ordenacao:" << endl;
    matchmaking.printWaitingPlayers();

    matchmaking.sortByScoreInsertion();

    cout << endl;
    cout << "Depois da ordenacao por insertion sort:" << endl;
    matchmaking.printWaitingPlayers();

    return 0;
}