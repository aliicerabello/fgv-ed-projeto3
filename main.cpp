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

    cout << "=== Teste 8: merge sort ===" << endl;

    Matchmaking* matchmakingMerge = new Matchmaking();

    matchmakingMerge->insert(Player(1, "Ana", 1000, 8));
    matchmakingMerge->insert(Player(2, "Bruno", 900, 2));
    matchmakingMerge->insert(Player(3, "Carla", 1000, 1));
    matchmakingMerge->insert(Player(4, "Diego", 900, 4));
    matchmakingMerge->insert(Player(5, "Eduarda", 1100, 3));

    cout << "Antes da ordenacao:" << endl;
    matchmakingMerge->printWaitingPlayers();

    matchmakingMerge->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingMerge->printWaitingPlayers();

    delete matchmakingMerge;

    cout << endl;

    cout << "=== Teste 9: merge sort com scores iguais ===" << endl;

    Matchmaking* matchmakingEqualScores = new Matchmaking();

    matchmakingEqualScores->insert(Player(10, "Lucas", 1000, 5));
    matchmakingEqualScores->insert(Player(11, "Marina", 1000, 2));
    matchmakingEqualScores->insert(Player(12, "Nina", 1000, 8));
    matchmakingEqualScores->insert(Player(13, "Otavio", 1000, 1));

    cout << "Antes da ordenacao:" << endl;
    matchmakingEqualScores->printWaitingPlayers();

    matchmakingEqualScores->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingEqualScores->printWaitingPlayers();

    delete matchmakingEqualScores;

    cout << endl;

    cout << "=== Teste 10: merge sort ja ordenado ===" << endl;

    Matchmaking* matchmakingAlreadySorted = new Matchmaking();

    matchmakingAlreadySorted->insert(Player(20, "A", 800, 1));
    matchmakingAlreadySorted->insert(Player(21, "B", 900, 2));
    matchmakingAlreadySorted->insert(Player(22, "C", 1000, 3));
    matchmakingAlreadySorted->insert(Player(23, "D", 1100, 4));

    cout << "Antes da ordenacao:" << endl;
    matchmakingAlreadySorted->printWaitingPlayers();

    matchmakingAlreadySorted->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingAlreadySorted->printWaitingPlayers();

    delete matchmakingAlreadySorted;

    cout << endl;

    cout << "=== Teste 11: merge sort em ordem inversa ===" << endl;

    Matchmaking* matchmakingReverse = new Matchmaking();

    matchmakingReverse->insert(Player(30, "A", 1200, 1));
    matchmakingReverse->insert(Player(31, "B", 1100, 2));
    matchmakingReverse->insert(Player(32, "C", 1000, 3));
    matchmakingReverse->insert(Player(33, "D", 900, 4));
    matchmakingReverse->insert(Player(34, "E", 800, 5));

    cout << "Antes da ordenacao:" << endl;
    matchmakingReverse->printWaitingPlayers();

    matchmakingReverse->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingReverse->printWaitingPlayers();

    delete matchmakingReverse;

    cout << endl;

    cout << "=== Teste 12: merge sort com apenas um jogador ===" << endl;

    Matchmaking* matchmakingOne = new Matchmaking();

    matchmakingOne->insert(Player(40, "Unico", 1000, 1));

    cout << "Antes da ordenacao:" << endl;
    matchmakingOne->printWaitingPlayers();

    matchmakingOne->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingOne->printWaitingPlayers();

    delete matchmakingOne;

    cout << endl;

    cout << "=== Teste 13: merge sort sem jogadores ===" << endl;

    Matchmaking* matchmakingEmpty = new Matchmaking();

    cout << "Antes da ordenacao:" << endl;
    matchmakingEmpty->printWaitingPlayers();

    matchmakingEmpty->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingEmpty->printWaitingPlayers();

    delete matchmakingEmpty;

    return 0;
}