# TP 3

This is a basic database for ships (characters), inspired by Azur Lane.

## Design & Architecture

- `Ship` - contains base ship data (superclass)
- `PlayerShip` - Player-obtained ship
- `EnemyShip` - Enemy ship (appear in levels as NPCs)
- `Gun` - Ships can have any amount of guns

The `guns` vector of ships is private, but has getters and setters. This is
because ships can only have 3 guns at time.

```cpp
bool addGun(Gun gun) {
  if (guns.size() < 4) {
    guns.push_back(gun);
    return true;
  } else {
    return false;
  }
}
```

## Code Flow

This program essentially acts like a CLI:

- Infinite `while` loop
- Accepts a few commands:
    - `add` - adds a ship
    - `addgun` - adds a gun to existing ship
    - `show` - shows all ship data (including guns)
    - `help` - shows this list of commands
    - `exit` - exits the CLI
