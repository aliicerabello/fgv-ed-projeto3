#include "Matchmaking.hpp"
#include "Player.hpp"

#include <chrono>
#include <iostream>
#include <string>

void printTitle(const std::string& title) {
    std::cout << std::endl;
    std::cout << "=== " << title << " ===" << std::endl;
}

void printSeparator() {
    std::cout << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}

void printPlayersArray(Player* players, int playerCount) {
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++) {
        std::cout << "["
                  << players[playerIndex].getId() << " | "
                  << players[playerIndex].getName() << " | "
                  << players[playerIndex].getScore() << " | "
                  << players[playerIndex].getTimestamp()
                  << "]" << std::endl;
    }
}

void insertBasicPlayers(Matchmaking& matchmaking) {
    matchmaking.insert(Player(1, "Ana", 1000, 1));
    matchmaking.insert(Player(2, "Bruno", 1010, 2));
    matchmaking.insert(Player(3, "Carla", 1020, 3));
    matchmaking.insert(Player(4, "Diego", 1100, 4));
}

void insertSortSamplePlayers(Matchmaking& matchmaking) {
    matchmaking.insert(Player(1, "Ana", 1000, 8));
    matchmaking.insert(Player(2, "Bruno", 900, 2));
    matchmaking.insert(Player(3, "Carla", 1000, 1));
    matchmaking.insert(Player(4, "Diego", 900, 4));
    matchmaking.insert(Player(5, "Eduarda", 1100, 3));
}

void runBasicTests() {
    Matchmaking matchmaking;

    printTitle("Teste 1: insercao");
    insertBasicPlayers(matchmaking);
    matchmaking.printWaitingPlayers();

    printTitle("Teste 2: getWaitingPlayers");
    int waitingCount = 0;
    Player* waitingPlayers = matchmaking.getWaitingPlayers(&waitingCount);

    std::cout << "n = " << waitingCount << std::endl;
    printPlayersArray(waitingPlayers, waitingCount);

    delete[] waitingPlayers;

    printTitle("Teste 3: formGroup com sucesso");
    int groupCount = 0;
    Player* group = matchmaking.formGroup(3, 30, &groupCount);

    matchmaking.printGroup(group, groupCount);
    std::cout << "n = " << groupCount << std::endl;

    delete[] group;

    std::cout << std::endl;
    std::cout << "Estado apos formar grupo:" << std::endl;
    matchmaking.printWaitingPlayers();

    printTitle("Teste 4: removePlayer");
    bool removed = matchmaking.removePlayer(4);
    std::cout << "removePlayer(4): " << removed << std::endl;
    matchmaking.printWaitingPlayers();

    printTitle("Teste 5: tentativa de remover ID inexistente");
    removed = matchmaking.removePlayer(99);
    std::cout << "removePlayer(99): " << removed << std::endl;
    matchmaking.printWaitingPlayers();

    printTitle("Teste 6: formGroup sem sucesso");
    matchmaking.insert(Player(5, "Eduarda", 1000, 5));
    matchmaking.insert(Player(6, "Felipe", 1200, 6));
    matchmaking.insert(Player(7, "Giulia", 1400, 7));

    matchmaking.printWaitingPlayers();

    group = matchmaking.formGroup(3, 50, &groupCount);

    matchmaking.printGroup(group, groupCount);
    std::cout << "n = " << groupCount << std::endl;

    delete[] group;

    std::cout << std::endl;
    std::cout << "Estado final:" << std::endl;
    matchmaking.printWaitingPlayers();
}

void runInsertionSortTest() {
    printTitle("Teste 7: insertion sort");

    Matchmaking matchmakingInsertion;
    insertSortSamplePlayers(matchmakingInsertion);

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingInsertion.printWaitingPlayers();

    matchmakingInsertion.sortByScoreInsertion();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por insertion sort:" << std::endl;
    matchmakingInsertion.printWaitingPlayers();
}

void runMergeSortDefaultTest() {
    printTitle("Teste 8: merge sort");

    Matchmaking matchmakingMerge;
    insertSortSamplePlayers(matchmakingMerge);

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingMerge.printWaitingPlayers();

    matchmakingMerge.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingMerge.printWaitingPlayers();
}

void runMergeSortEqualScoresTest() {
    printTitle("Teste 9: merge sort com scores iguais");

    Matchmaking matchmakingEqualScores;

    matchmakingEqualScores.insert(Player(10, "Lucas", 1000, 5));
    matchmakingEqualScores.insert(Player(11, "Marina", 1000, 2));
    matchmakingEqualScores.insert(Player(12, "Nina", 1000, 8));
    matchmakingEqualScores.insert(Player(13, "Otavio", 1000, 1));

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingEqualScores.printWaitingPlayers();

    matchmakingEqualScores.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingEqualScores.printWaitingPlayers();
}

void runMergeSortAlreadySortedTest() {
    printTitle("Teste 10: merge sort ja ordenado");

    Matchmaking matchmakingAlreadySorted;

    matchmakingAlreadySorted.insert(Player(20, "A", 800, 1));
    matchmakingAlreadySorted.insert(Player(21, "B", 900, 2));
    matchmakingAlreadySorted.insert(Player(22, "C", 1000, 3));
    matchmakingAlreadySorted.insert(Player(23, "D", 1100, 4));

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingAlreadySorted.printWaitingPlayers();

    matchmakingAlreadySorted.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingAlreadySorted.printWaitingPlayers();
}

void runMergeSortReverseTest() {
    printTitle("Teste 11: merge sort em ordem inversa");

    Matchmaking matchmakingReverse;

    matchmakingReverse.insert(Player(30, "A", 1200, 1));
    matchmakingReverse.insert(Player(31, "B", 1100, 2));
    matchmakingReverse.insert(Player(32, "C", 1000, 3));
    matchmakingReverse.insert(Player(33, "D", 900, 4));
    matchmakingReverse.insert(Player(34, "E", 800, 5));

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingReverse.printWaitingPlayers();

    matchmakingReverse.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingReverse.printWaitingPlayers();
}

void runMergeSortTimestampTest() {
    printTitle("Teste 12: score igual com timestamps fora de ordem");

    Matchmaking matchmakingTimestamp;

    matchmakingTimestamp.insert(Player(1, "Ana", 900, 5));
    matchmakingTimestamp.insert(Player(2, "Bruno", 900, 2));
    matchmakingTimestamp.insert(Player(3, "Carla", 1000, 4));
    matchmakingTimestamp.insert(Player(4, "Diego", 1000, 1));

    std::cout << "Antes:" << std::endl;
    matchmakingTimestamp.printWaitingPlayers();

    matchmakingTimestamp.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois:" << std::endl;
    matchmakingTimestamp.printWaitingPlayers();
}

void runMergeSortReverseTieTest() {
    printTitle("Teste 13: ordem inversa com empates");

    Matchmaking matchmakingReverseTie;

    matchmakingReverseTie.insert(Player(1, "Ana", 1100, 3));
    matchmakingReverseTie.insert(Player(2, "Bruno", 1000, 5));
    matchmakingReverseTie.insert(Player(3, "Carla", 1000, 2));
    matchmakingReverseTie.insert(Player(4, "Diego", 900, 4));
    matchmakingReverseTie.insert(Player(5, "Eduarda", 900, 1));

    std::cout << "Antes:" << std::endl;
    matchmakingReverseTie.printWaitingPlayers();

    matchmakingReverseTie.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois:" << std::endl;
    matchmakingReverseTie.printWaitingPlayers();
}

void runMergeSortSinglePlayerTest() {
    printTitle("Teste 14: merge sort com apenas um jogador");

    Matchmaking matchmakingOne;

    matchmakingOne.insert(Player(40, "Unico", 1000, 1));

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingOne.printWaitingPlayers();

    matchmakingOne.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingOne.printWaitingPlayers();
}

void runMergeSortTwoPlayersTest() {
    printTitle("Teste 15: merge sort com dois jogadores");

    Matchmaking matchmakingTwo;

    matchmakingTwo.insert(Player(1, "Ana", 1000, 2));
    matchmakingTwo.insert(Player(2, "Bruno", 900, 1));

    std::cout << "Antes:" << std::endl;
    matchmakingTwo.printWaitingPlayers();

    matchmakingTwo.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois:" << std::endl;
    matchmakingTwo.printWaitingPlayers();
}

void runMergeSortEmptyTest() {
    printTitle("Teste 16: merge sort sem jogadores");

    Matchmaking matchmakingEmpty;

    std::cout << "Antes da ordenacao:" << std::endl;
    matchmakingEmpty.printWaitingPlayers();

    matchmakingEmpty.sortByScoreMerge();

    std::cout << std::endl;
    std::cout << "Depois da ordenacao por merge sort:" << std::endl;
    matchmakingEmpty.printWaitingPlayers();
}

void runMergeSortTests() {
    runMergeSortDefaultTest();
    runMergeSortEqualScoresTest();
    runMergeSortAlreadySortedTest();
    runMergeSortReverseTest();
    runMergeSortTimestampTest();
    runMergeSortReverseTieTest();
    runMergeSortSinglePlayerTest();
    runMergeSortTwoPlayersTest();
    runMergeSortEmptyTest();
}

void generateRandomPlayers(Player* players, int playerCount) {
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++) {
        const int id = playerIndex + 1;
        const std::string name = "Player" + std::to_string(id);
        const int score = (playerIndex * 7919 + 12345) % 100000;
        const int timestamp = (playerIndex * 3571 + 999) % 100000;

        players[playerIndex] = Player(id, name, score, timestamp);
    }
}

void fillMatchmaking(Matchmaking& matchmaking, const Player* players, int playerCount) {
    for (int playerIndex = 0; playerIndex < playerCount; playerIndex++) {
        matchmaking.insert(players[playerIndex]);
    }
}

void runPerformanceTests() {
    printTitle("Testes de desempenho");

    const int testSizes[] = {100, 500, 1000, 2000, 5000};
    const int testCount = 5;
    const int repetitions = 30;

    for (int testIndex = 0; testIndex < testCount; testIndex++) {
        const int playerCount = testSizes[testIndex];

        long long totalInsertionTime = 0;
        long long totalMergeTime = 0;

        for (int repetition = 0; repetition < repetitions; repetition++) {
            Player* basePlayers = new Player[playerCount];

            generateRandomPlayers(basePlayers, playerCount);

            Matchmaking* matchmakingInsertion = new Matchmaking();
            Matchmaking* matchmakingMerge = new Matchmaking();

            fillMatchmaking(*matchmakingInsertion, basePlayers, playerCount);
            fillMatchmaking(*matchmakingMerge, basePlayers, playerCount);

            const auto startInsertion = std::chrono::high_resolution_clock::now();
            matchmakingInsertion->sortByScoreInsertion();
            const auto endInsertion = std::chrono::high_resolution_clock::now();

            const auto insertionTime =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    endInsertion - startInsertion
                ).count();

            const auto startMerge = std::chrono::high_resolution_clock::now();
            matchmakingMerge->sortByScoreMerge();
            const auto endMerge = std::chrono::high_resolution_clock::now();

            const auto mergeTime =
                std::chrono::duration_cast<std::chrono::microseconds>(
                    endMerge - startMerge
                ).count();

            totalInsertionTime += insertionTime;
            totalMergeTime += mergeTime;

            delete matchmakingInsertion;
            delete matchmakingMerge;
            delete[] basePlayers;
        }

        const double averageInsertionTime =
            static_cast<double>(totalInsertionTime) / repetitions;

        const double averageMergeTime =
            static_cast<double>(totalMergeTime) / repetitions;

        std::cout << "n = " << playerCount << std::endl;
        std::cout << "Insertion sort medio: " << averageInsertionTime
                  << " microseconds" << std::endl;
        std::cout << "Merge sort medio:     " << averageMergeTime
                  << " microseconds" << std::endl;
        std::cout << "Repeticoes: " << repetitions << std::endl;
        std::cout << std::endl;
    }
}

void runStressTests() {
    printTitle("Stress test: insertion sort vs merge sort");

    const int testSizes[] = {1000, 5000, 10000, 20000, 50000};
    const int testCount = 5;

    for (int testIndex = 0; testIndex < testCount; testIndex++) {
        const int playerCount = testSizes[testIndex];

        printSeparator();
        std::cout << "Teste com n = " << playerCount << " jogadores" << std::endl;

        Player* basePlayers = new Player[playerCount];
        generateRandomPlayers(basePlayers, playerCount);

        Matchmaking* matchmakingInsertion = new Matchmaking();
        Matchmaking* matchmakingMerge = new Matchmaking();

        fillMatchmaking(*matchmakingInsertion, basePlayers, playerCount);
        fillMatchmaking(*matchmakingMerge, basePlayers, playerCount);

        const auto startInsertion = std::chrono::high_resolution_clock::now();
        matchmakingInsertion->sortByScoreInsertion();
        const auto endInsertion = std::chrono::high_resolution_clock::now();

        const auto insertionTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                endInsertion - startInsertion
            ).count();

        const auto startMerge = std::chrono::high_resolution_clock::now();
        matchmakingMerge->sortByScoreMerge();
        const auto endMerge = std::chrono::high_resolution_clock::now();

        const auto mergeTime =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                endMerge - startMerge
            ).count();

        std::cout << "Insertion sort: " << insertionTime << " ms" << std::endl;
        std::cout << "Merge sort:     " << mergeTime << " ms" << std::endl;

        delete matchmakingInsertion;
        delete matchmakingMerge;
        delete[] basePlayers;
    }
}

int main() {
    runBasicTests();
    runInsertionSortTest();
    runMergeSortTests();
    runPerformanceTests();
    runStressTests();
    return 0;
}
