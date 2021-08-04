# C++ Console Blackjack Game

A console-based game of blackjack supporting multiple players.  Standard
Blackjack rules implmented.

- Blackjack on opening hand when first two cards are an Ace and any ten-point
  card.
- Hand value exceeding twenty one points is a bust.
- Ace can be treated as soft or hard.
- Dealer stays on 17.

## Overview

The game is written in C++ using some language features from C++ 17.  The goals
of this project were to think through an object-oriented software design
approach and the use of a state machine (graph) to apply the correct logic
given the current state and action take (either by the player or computer).

A test-driven approach was used and all components have corresponding unit
tests designed with the intention of also showing how the comoponents are
expected to work and be used.

Further refactoring is ongoing with the attempts of hardening the design and
ensuring interfaces are easy to correctly and hard to use incorrectly.

## Gameplay and Output

Output from an actual round of blackjack with a single player and dealer.

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
