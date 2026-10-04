#include <iostream>
#include <string>
#include <vector>

using namespace std;

// all Ships have at least 1 gun that they use to attack with
class Gun {
public:
  string name;
  float fireRate;
  float damage;
};

class Ship {
public:
  string name;

  bool addGun(Gun gun) {
    if (guns.size() < 4) {
      guns.push_back(gun);
      return true;
    } else {
      return false;
    }
  }

  vector<Gun> getGuns() { return guns; }

private:
  vector<Gun> guns;
};

// ships obtained and stored by the player
class PlayerShip : public Ship {
  string obtainDate;
  string obtainSource;
};

// NPC ships that appear in sorties
class EnemyShip : public Ship {
  int appearLevel;
  float aggroLevel;
  bool isBoss;
};

// resets input buffer, to prevent registering excess inputs
void clearInput() {
  return;
  std::cin.clear();
}

int findShip(vector<Ship> ships, string name) {
  for (int s = 0; s < ships.size(); s++) {
    if (ships[s].name == name) {
      return s;
    }
  }
  return -1;
}

void printArguments() {
  cout << "Available commands:\n";
  cout << "add [name] [\"player\" or \"enemy\"]\n";
  cout << "addgun [name of ship] [gun name] [gun damage] [gun fire rate]\n";
  cout << "info - shows all ships\n";
  cout << "help - shows this list\n";
  cout << "exit - closes this program\n";
  cout << "\n";
}

void printShips(vector<Ship> ships) {
  cout << endl;
  string tab1 = "  ";
  string tab2 = "    ";
  for (int s = 0; s < ships.size(); s++) {
    Ship ship = ships[s];
    cout << ship.name << " (" << ship.getGuns().size() << " guns):\n";
    for (int g = 0; g < ship.getGuns().size(); g++) {
      Gun gun = ship.getGuns()[g];
      cout << tab1 << gun.name << ":\n";
      cout << tab2 << "damage: " << gun.damage << endl;
      cout << tab2 << "fire rate: " << gun.fireRate << endl;
    }
    cout << endl;
  }
}

int main() {
  vector<Ship> ships;

  while (true) {
    string action;
    cout << "action: ";
    cin >> action;

    if (action == "add") {
      Ship ship = Ship();
      cin >> ship.name;
      if (findShip(ships, ship.name) != -1) {
        cout << "This ship already exists!\n";
      } else {
        ships.push_back(ship);
        cout << "Added " << ship.name << "!\n";
      }
      clearInput();
    } else if (action == "addgun") {
      string name;
      cin >> name;
      int shipIdx = findShip(ships, name);
      if (shipIdx == -1) {
        cout << "Couldn't find " << name << "!";
      } else {
        Gun gun;
        cin >> gun.name >> gun.damage >> gun.fireRate;
        if (ships[shipIdx].addGun(gun)) {
          cout << "Added " << gun.name << " to " << name << "!\n";
        } else {
          cout << "Couldn't add gun!\n";
        }
      }
      clearInput();
    } else if (action == "show") {
      if (ships.size() > 0) {
        printShips(ships);
      } else {
        cout << "No ships!\n";
      }
      clearInput();
    } else if (action == "exit") {
      cout << "bye!\n";
      break;
    } else if (action == "help") {
      printArguments();
      clearInput();
    } else if (action != "") {
      cout << action << " unrecognized.\n";
      clearInput();
    }
  }
}
