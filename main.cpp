#include <iostream>
#include "Matchmaking.hpp"
#include "Player.hpp"

using namespace std;

int main() {
    Matchmaking mm;

    // Criando jogadores
    Player p1(1, "Alice", 150, 10);
    Player p2(2, "Bob", 100, 20);
    Player p3(3, "Carol", 200, 30);
    Player p4(4, "Dave", 120, 40);
    Player p5(5, "Eve", 180, 50);

    // Inserindo
    mm.insert(p1);
    mm.insert(p2);
    mm.insert(p3);
    mm.insert(p4);
    mm.insert(p5);

    cout << "Sorted Players (por score):\n";
    //mm.printSorted();

    return 0;
}