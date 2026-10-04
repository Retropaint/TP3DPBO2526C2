class Gun:
    def __init__(self, name="", fireRate=0.0, damage=0.0):
        self.name = name
        self.fireRate = fireRate
        self.damage = damage


class Ship:
    def __init__(self, name=""):
        self.name = name
        self.__guns = []

    def addGun(self, gun):
        if len(self.__guns) < 3:
            self.__guns.append(gun)
            return True
        else:
            return False

    def getGuns(self):
        return self.__guns


# Ships obtained and stored by the player
class PlayerShip(Ship):
    def __init__(self, name="", obtainDate="", obtainSource=""):
        super().__init__(name)
        self.obtainDate = obtainDate
        self.obtainSource = obtainSource


# NPC ships that appear in sorties
class EnemyShip(Ship):
    def __init__(self, name="", appearLevel=0, aggroLevel=0.0, isBoss=False):
        super().__init__(name)
        self.appearLevel = appearLevel
        self.aggroLevel = aggroLevel
        self.isBoss = isBoss


def findShip(ships, name):
    for s, ship in enumerate(ships):
        if ship.name == name:
            return s
    return -1


def printArguments():
    print("Available commands:")
    print('add [name] ["player" or "enemy"]')
    print("addgun [name of ship] [gun name] [gun damage] [gun fire rate]")
    print("info - shows all ships")
    print("help - shows this list")
    print("exit - closes this program")
    print()


def printShips(ships):
    print()
    for ship in ships:
        print(f"{ship.name} ({len(ship.getGuns())} guns):")
        for gun in ship.getGuns():
            print(f"  {gun.name}:")
            print(f"    damage: {gun.damage}")
            print(f"    fire rate: {gun.fireRate}")
        print()


ships = []

while True:
    try:
        action = input("action: ").split()
        if not action:
            continue

        command = action[0]

        if command == "add":
            name = action[1]
            if findShip(ships, name) != -1:
                print("This ship already exists!")
            else:
                ship = Ship(name)
                ships.append(ship)
                print(f"Added {ship.name}!")

        elif command == "addgun":
            name, gunName, damage, fireRate = action[1:5]
            shipIdx = findShip(ships, name)

            if shipIdx == -1:
                print(f"Couldn't find {name}!")
            else:
                gun = Gun(gunName, float(fireRate), float(damage))
                if ships[shipIdx].addGun(gun):
                    print(f"Added {gun.name} to {name}!")
                else:
                    print(f"Added {gun.name} to {name}!")

        elif command == "show":
            if ships:
                printShips(ships)
            else:
                print("No ships!")
        elif command == "exit":
            print("bye!")
            break
        elif command == "help":
            printArguments()
        else:
            print(f"{command} unrecognized.")
    except (IndexError, ValueError):
        print("Invalid input!")
