# Hegzy
**Turn based game, set on hexagonal board. The goal of two opposing players is to eliminate the opponents units.**


## Authors ##
+ @ Wiolarz
+ @ y3snt


Units are represented as tokens with visible art and a set of special "Symbols" on sides.


###### Starting Placement  ######
Players in subsequent turns place their units on their starting positions.
Starting with the Elves faction, Player selects one of his units then chooses one of the starting tiles near his edge of the board.
After all units are placed the game begins with the Elven player making the first move.

###### Movement  ######
Everything in the game revolves around the basic move of the unit.
To perform the move active players selects one of his units the chooses a tile next to it which is either:

- free
- occupied by the enemy unit with the exception of the scenario in which that enemy unit has a shield pointed at the selected unit.

Then the selected unit first:
Rotates toward the target location
It's symbols are "Activated"
Then the unit moves to the target location.
And for the last time its symbols are activated once again.

###### Symbole  ######
Main way to kill enemy units is with the "Symbols" at the edges of your units.
Their effect most of the time affects the unit standing right next to it, with the exception of a bow.
We split symbols into 2 categories based on if they work only during the movement of the unit carrying them "ACTIVE".
Or if they work all the time "PASSIVE"

Active Symbols:

Sword - "Sword" Kills enemy units on an adjacent tile.
ARROW - "Bow" Shoots an arrow that damages the first encountered enemy unit. If the path is blocked by the ally unit, the arrow doesn't travel further.
CIRCLE - "Fist" Pushes enemy unit 1 tile away, if that tile isn't empty or is outside the gameplay area the pushed unit is killed. It's possible to push an enemy unit on top of a tile covered by your spear, in that case the pushed unit is killed. This symbol ignores the shield.

Passive Symbols:

CROSS	- "Spear" Kills any enemy unit that enters this tile. Spear acts before any enemy unit symbol does (except for a shield). If a unit protected by a shield rotates at the start of its movement while this shield is covering the spear, and at its final rotation position the spear can hit the unit rotation ends with the unit death.
TRIANGLE - "Shield" nullifies sources of damage (doesn't work against push)


######   ######
