#pragma once
//
// Game - Wrapper for the common game components.
//

// ------------------------------------------------------------ Project Headers
#include "Deck.h"
#include "Input.h"
#include "Player.h"
#include "StateMachine.h"

// ------------------------------------------------------------ Library Headers
#include <list>

// ----------------------------------------------------------- Class Definition
class Game {
    public:
	Game();
	void Start();
	bool End() const;

    private:
	void Initialize();

	void Draw() const;

	void DoNothing(void *);
	void HandleAddPlayer(void *);
	void HandleDeal(void *);
	void HandleDealerAction(void *);
	void HandleDealerScore(void *);
	void HandleGameOver(void *);
	void HandleHit(void *);
	void HandleNextPlayer(void *);
	void HandlePlay(void *);
	void HandleQuitGame(void *);
	void HandleScore(void *);
	void HandleShuffle(void *);

	bool IsValidOption(char option) const;
	void ProcessOption(char option);
	void ProcessNextAction();
	std::size_t AvailableOptions() const;
	std::string GetAvailableOptions() const;
	std::string GetState() const;

	int GetPlayerScore() const;

	bool finished_;
	Input input_;
	StateMachine logic_;

	Deck deck_;
	std::list<Player> players_;
	std::list<Player>::iterator currentPlayer_;
};