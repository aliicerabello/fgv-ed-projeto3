#include "Matchmaking.hpp"
#include "Player.hpp"
#include <iostream>
#include <chrono>
#include <string> 

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
    int n1;
    Player* waiting = matchmaking.getWaitingPlayers(&n1);

    cout << "n = " << n1 << endl;
    for (int i = 0; i < n1; i++) {
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
    Player* group = matchmaking.formGroup(3, 30, &n1);

    matchmaking.printGroup(group, n1);
    cout << "n = " << n1 << endl;

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

    group = matchmaking.formGroup(3, 50, &n1);

    matchmaking.printGroup(group, n1);
    cout << "n = " << n1 << endl;

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

    Matchmaking* matchmakingMerge1 = new Matchmaking();

    matchmakingMerge1->insert(Player(1, "Ana", 1000, 8));
    matchmakingMerge1->insert(Player(2, "Bruno", 900, 2));
    matchmakingMerge1->insert(Player(3, "Carla", 1000, 1));
    matchmakingMerge1->insert(Player(4, "Diego", 900, 4));
    matchmakingMerge1->insert(Player(5, "Eduarda", 1100, 3));

    cout << "Antes da ordenacao:" << endl;
    matchmakingMerge1->printWaitingPlayers();

    matchmakingMerge1->sortByScoreMerge();

    cout << endl;
    cout << "Depois da ordenacao por merge sort:" << endl;
    matchmakingMerge1->printWaitingPlayers();

    delete matchmakingMerge1;

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

    cout << endl;
    cout << "=== Testes de desempenho ===" << endl;

    int sizes[] = {100, 500, 1000, 2000, 5000};
    int numTests = 5;

    for (int t = 0; t < numTests; t++) {
        int n2 = sizes[t];

        Player* basePlayers = new Player[n2];

        // Geracao deterministica dos dados
        // Assim, insertion sort e merge sort recebem exatamente os mesmos jogadores
        for (int i = 0; i < n2; i++) {
            int id = i + 1;
            string name = "Player" + to_string(id);

            // Score pseudoaleatorio, mas deterministico
            int score = (i * 37 + 13) % 100000;

            // Timestamp crescente
            int timestamp = i + 1;

            basePlayers[i] = Player(id, name, score, timestamp);
        }

        Matchmaking* matchmakingInsertion = new Matchmaking();
        Matchmaking* matchmakingMerge2 = new Matchmaking();

        for (int i = 0; i < n2; i++) {
            matchmakingInsertion->insert(basePlayers[i]);
            matchmakingMerge2->insert(basePlayers[i]);
        }

        auto startInsertion = chrono::high_resolution_clock::now();

        matchmakingInsertion->sortByScoreInsertion();

        auto endInsertion = chrono::high_resolution_clock::now();

        auto durationInsertion =
            chrono::duration_cast<chrono::microseconds>(endInsertion - startInsertion).count();

        auto startMerge = chrono::high_resolution_clock::now();

        matchmakingMerge2->sortByScoreMerge();

        auto endMerge = chrono::high_resolution_clock::now();

        auto durationMerge =
            chrono::duration_cast<chrono::microseconds>(endMerge - startMerge).count();

        cout << "n = " << n2 << endl;
        cout << "Insertion sort: " << durationInsertion << " microseconds" << endl;
        cout << "Merge sort:     " << durationMerge << " microseconds" << endl;
        cout << endl;

        delete matchmakingInsertion;
        delete matchmakingMerge2;
        delete[] basePlayers;
    }

    cout << endl;
    cout << "=== Stress test: insertion sort vs merge sort ===" << endl;

    int testSizes3[] = {1000, 5000, 10000, 20000, 50000};
    int numTests3 = 5;

    for (int testIndex3 = 0; testIndex3 < numTests3; testIndex3++) {
        int n3 = testSizes3[testIndex3];

        cout << endl;
        cout << "----------------------------------------" << endl;
        cout << "Teste com n = " << n3 << " jogadores" << endl;

        Player* basePlayers3 = new Player[n3];

        // Geracao deterministica dos dados.
        // Os dois algoritmos recebem exatamente os mesmos jogadores.
        for (int playerIndex3 = 0; playerIndex3 < n3; playerIndex3++) {
            int id3 = playerIndex3 + 1;
            string name3 = "Player" + to_string(id3);

            int score3 = (playerIndex3 * 7919 + 12345) % 100000;
            int timestamp3 = (playerIndex3 * 3571 + 999) % 100000;

            basePlayers3[playerIndex3] = Player(id3, name3, score3, timestamp3);
        }

        Matchmaking* matchmakingInsertion2 = new Matchmaking();
        Matchmaking* matchmakingMerge3 = new Matchmaking();

        for (int insertIndex3 = 0; insertIndex3 < n3; insertIndex3++) {
            matchmakingInsertion2->insert(basePlayers3[insertIndex3]);
            matchmakingMerge3->insert(basePlayers3[insertIndex3]);
        }

        auto startInsertion3 = chrono::high_resolution_clock::now();

        matchmakingInsertion2->sortByScoreInsertion();

        auto endInsertion3 = chrono::high_resolution_clock::now();

        auto insertionTime3 =
            chrono::duration_cast<chrono::milliseconds>(
                endInsertion3 - startInsertion3
            ).count();

        auto startMerge3 = chrono::high_resolution_clock::now();

        matchmakingMerge3->sortByScoreMerge();

        auto endMerge3 = chrono::high_resolution_clock::now();

        auto mergeTime3 =
            chrono::duration_cast<chrono::milliseconds>(
                endMerge3 - startMerge3
            ).count();

        cout << "Insertion sort: " << insertionTime3 << " ms" << endl;
        cout << "Merge sort:     " << mergeTime3 << " ms" << endl;

        delete matchmakingInsertion2;
        delete matchmakingMerge3;
        delete[] basePlayers3;
    }
    return 0;
}