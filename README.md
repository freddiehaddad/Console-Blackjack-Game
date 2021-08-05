# C++ Console Blackjack Game

A console-based game of Blackjack supporting multiple players.

Standard Blackjack rules apply such as:

- Ace and any ten-point card is a Blackjack.
- A hand exceeding twenty one points is a bust.
- Ace can be treated as soft or hard.
- Dealer stays on 17.

## Overview

The game is written in C++ using language features from C++ 17 specification.
The goals of this project included an object-oriented approach and the use of a
state machine (graph) to apply the correct game logic given the current state
and the action taken in that state (either by the player or computer).

A test-driven development model was used and all components have corresponding
unittests designed with the intention of illustrating how each of the
comoponents is expected to work and be used.

Further refactoring will continue with the goals of hardening the design,
implementing interfaces, and ensuring interfaces are easy to correctly and hard
to use incorrectly.

## Gameplay and Output

Output from an actual round of Blackjack with a player and dealer.

```
Welcome to Console
__________.__                 __         __               __
\______   \  | _____    ____ |  | __    |__|____    ____ |  | __
 |    |  _/  | \__  \ _/ ___\|  |/ /    |  \__  \ _/ ___\|  |/ /
 |    |   \  |__/ __ \\  \___|    <     |  |/ __ \\  \___|    <
 |______  /____(____  /\___  >__|_ \/\__|  (____  /\___  >__|_ \
        \/          \/     \/     \/\______|    \/     \/     \/

[A]dd Player [Q]uit: A

Player's name: Freddie

Freddie added to the game.

[A]dd Player [P]lay [Q]uit: p

Shuffling...
Dealing...

Dealer
 Six of Clubs

Freddie
 Six of Diamonds
 Five of Clubs

 11

[H]it [Q]uit [S]tand: h

 Nine of Hearts

 20

[H]it [Q]uit [S]tand: s

Dealer
 Six of Clubs
 Four of Hearts

 10

 Three of Clubs

 13

 Three of Spades

 16

 Eight of Clubs

 24
__________               __             .___._.
\______   \__ __  ______/  |_  ____   __| _/| |
 |    |  _/  |  \/  ___|   __\/ __ \ / __ | | |
 |    |   \  |  /\___ \ |  | \  ___// /_/ |  \|
 |______  /____//____  >|__|  \___  >____ |  __
        \/           \/           \/     \/  \/

[A]dd Player [P]lay [Q]uit: q

Thanks for playing!
```
