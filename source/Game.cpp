// ------------------------------------------------------------ Project Headers
#include "Game.h"

// ------------------------------------------------------------ Library Headers
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// --------------------------------------------------------------- Constructors
Game::Game() : finished_(false), input_(std::cin)
{
	Initialize();
}

// ------------------------------------------------------- Public Class Methods
void Game::Start()
{
	do {
		if (AvailableOptions() > 0) {
			// User-controlled play
			std::cout << GetAvailableOptions() << ": ";
			char option = std::toupper(input_.GetCharacter());

			if (!IsValidOption(option)) {
				std::cerr << option << " is not a valid option"
					  << std::endl;
				continue;
			}

			ProcessOption(option);
		} else {
			// Computer-controlled play
			ProcessNextAction();
		}

		Draw();
	} while (!End());
}

bool Game::End() const
{
	return finished_;
}

// ------------------------------------------------------ Private Class Methods
void Game::Initialize()
{
	const std::vector<std::string> states{ "Dealer Blackjack",
					       "Dealer Busted",
					       "Dealer Hand",
					       "Dealer Hit",
					       "Dealer Play",
					       "Dealer Playing",
					       "Dealer Stand",
					       "Dealer Turn",
					       "Dealing",
					       "Quit Game",
					       "Waiting for Players",
					       "Next Player",
					       "Player Blackjack",
					       "Player Busted",
					       "Player Hit",
					       "Player Stand",
					       "Playing",
					       "Ready to Play",
					       "Scoring",
					       "Shuffling" };

	enum ACTION_ARGS { KEY, NAME, FUNCTION };

	const std::vector<
		std::tuple<int, std::string, std::function<void(void *)> > >
		actions{
			std::make_tuple('A', "[A]dd Player",
					std::bind(&Game::HandleAddPlayer, this,
						  std::placeholders::_1)),
			std::make_tuple('H', "[H]it",
					std::bind(&Game::HandleHit, this,
						  std::placeholders::_1)),
			std::make_tuple('P', "[P]lay",
					std::bind(&Game::HandlePlay, this,
						  std::placeholders::_1)),
			std::make_tuple('Q', "[Q]uit",
					std::bind(&Game::HandleQuitGame, this,
						  std::placeholders::_1)),
			std::make_tuple('S', "[S]tand",
					std::bind(&Game::DoNothing, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "DoNothing",
					std::bind(&Game::DoNothing, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "HandleDeal",
					std::bind(&Game::HandleDeal, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "HandleDealerAction",
					std::bind(&Game::HandleDealerAction,
						  this, std::placeholders::_1)),
			std::make_tuple(0, "HandleDealerScore",
					std::bind(&Game::HandleDealerScore,
						  this, std::placeholders::_1)),
			std::make_tuple(0, "HandleNextPlayer",
					std::bind(&Game::HandleNextPlayer, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "HandleGameOver",
					std::bind(&Game::HandleGameOver, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "HandleScore",
					std::bind(&Game::HandleScore, this,
						  std::placeholders::_1)),
			std::make_tuple(0, "HandleShuffle",
					std::bind(&Game::HandleShuffle, this,
						  std::placeholders::_1))
		};

	enum TRANSITION_ARGS { FROM, TO, ACTION };

	const std::vector<std::tuple<std::string, std::string, int> >
		userTransitions{
			std::make_tuple("Waiting for Players", "Ready to Play",
					'A'),
			std::make_tuple("Waiting for Players", "Quit Game",
					'Q'),
			std::make_tuple("Ready to Play", "Ready to Play", 'A'),
			std::make_tuple("Ready to Play", "Shuffling", 'P'),
			std::make_tuple("Ready to Play", "Quit Game", 'Q'),
			std::make_tuple("Playing", "Player Hit", 'H'),
			std::make_tuple("Playing", "Player Stand", 'S'),
			std::make_tuple("Playing", "Quit Game", 'Q')
		};

	const std::vector<std::tuple<std::string, std::string, std::string> >
		automatedTransitions{
			std::make_tuple("Shuffling", "Dealing",
					"HandleShuffle"),
			std::make_tuple("Dealing", "Dealer Hand", "HandleDeal"),
			std::make_tuple("Dealer Hand", "Next Player",
					"DoNothing"),
			std::make_tuple("Next Player", "Scoring", "DoNothing"),
			std::make_tuple("Scoring", "Playing", "HandleScore"),
			std::make_tuple("Player Blackjack", "Next Player",
					"HandleNextPlayer"),
			std::make_tuple("Player Busted", "Next Player",
					"HandleNextPlayer"),
			std::make_tuple("Player Hit", "Scoring", "DoNothing"),
			std::make_tuple("Player Stand", "Next Player",
					"HandleNextPlayer"),
			std::make_tuple("Dealer Turn", "Dealer Play",
					"DoNothing"),
			std::make_tuple("Dealer Play", "Dealer Playing",
					"HandleDealerScore"),
			std::make_tuple("Dealer Playing", "Dealer Play",
					"HandleDealerAction"),
			std::make_tuple("Dealer Hit", "Dealer Play",
					"DoNothing"),
			std::make_tuple("Dealer Blackjack", "Ready to Play",
					"HandleGameOver"),
			std::make_tuple("Dealer Busted", "Ready to Play",
					"HandleGameOver"),
			std::make_tuple("Dealer Stand", "Ready to Play",
					"HandleGameOver")
		};

	StateMachine &stateMachine = logic_;

	std::for_each(states.begin(), states.end(),
		      [&stateMachine](std::string_view state) {
			      stateMachine.AddState(state);
		      });

	std::for_each(actions.begin(), actions.end(),
		      [&stateMachine](const auto &tuple) {
			      if (std::get<KEY>(tuple) != 0) {
				      stateMachine.AddAction(
					      std::get<KEY>(tuple),
					      std::get<NAME>(tuple),
					      std::get<FUNCTION>(tuple));
			      } else {
				      stateMachine.AddAction(
					      std::get<NAME>(tuple),
					      std::get<FUNCTION>(tuple));
			      }
		      });

	std::for_each(userTransitions.begin(), userTransitions.end(),
		      [&stateMachine](const auto &tuple) {
			      stateMachine.CreateTransition(
				      std::get<FROM>(tuple),
				      std::get<TO>(tuple),
				      std::get<ACTION>(tuple));
		      });

	std::for_each(automatedTransitions.begin(), automatedTransitions.end(),
		      [&stateMachine](const auto &tuple) {
			      stateMachine.CreateTransition(
				      std::get<FROM>(tuple),
				      std::get<TO>(tuple),
				      std::get<ACTION>(tuple));
		      });

	logic_.SetState("Waiting for Players");

	players_.emplace_back("Dealer");
}

void Game::Draw() const
{
	std::string state = GetState();
	if (state == "Shuffling") {
		std::cout << "Shuffling...\n";
	} else if (state == "Dealing") {
		std::cout << "Dealing...\n";
	} else if (state == "Next Player") {
		std::cout << currentPlayer_->GetName() << "\n";
		std::for_each(currentPlayer_->Begin(), currentPlayer_->End(),
			      [](const Card &card) {
				      std::cout << card.Name() << "\n";
			      });
	} else if (state == "Player Busted") {
		std::cout << "Busted!\n";
	} else if (state == "Player Blackjack") {
		std::cout << "Blackjack!\n";
	} else if (state == "Dealer Busted") {
		std::cout << "Busted!\n";
	} else if (state == "Dealer Blackjack") {
		std::cout << "Blackjack!\n";
	} else if (state == "Player Hit") {
		std::cout << currentPlayer_->Back().Name() << "\n";
	} else if (state == "Dealer Hit") {
		std::cout << currentPlayer_->Back().Name() << "\n";
	} else if (state == "Dealer Hand") {
		std::cout << players_.back().GetName() << "\n";
		std::cout << players_.back().Begin()->Name() << "\n";
		std::cout << "*****************\n";
	} else if (state == "Dealer Turn") {
		std::cout << currentPlayer_->GetName() << "\n";
		std::for_each(currentPlayer_->Begin(), currentPlayer_->End(),
			      [](const Card &card) {
				      std::cout << card.Name() << "\n";
			      });
	} else {
		// std::cerr << "Draw: " << GetState() << ", not implemented\n";
	}
}

void Game::DoNothing(void *)
{
	// Do nothing.. literally! :)
}

void Game::HandleAddPlayer(void *)
{
	const std::string prompt = "Player's name: ";
	std::string name;

	std::cout << prompt;
	name = input_.GetString();
	while (name.empty()) {
		std::cerr << "A name must have at least one character."
			  << std::endl;
		std::cout << prompt;
		name = input_.GetString();
	}

	auto pos = players_.end();
	--pos;

	players_.emplace(pos, name);
	std::cout << name << " added to the game." << std::endl;
}

void Game::HandleDeal(void *)
{
	const int CARDS_PER_PLAYER = 2;

	Deck &deck = deck_;
	for (int cards = 0; cards < CARDS_PER_PLAYER; ++cards) {
		std::for_each(players_.begin(), players_.end(),
			      [&deck](Player &player) {
				      player.Take(deck.Take());
			      });
	}
}

void Game::HandleDealerAction(void *arg)
{
	std::string *state = static_cast<std::string *>(arg);
	size_t score = GetPlayerScore();
	if (score < 17) {
		HandleHit(nullptr);
		*state = "Dealer Hit";
	} else {
		*state = "Dealer Stand";
	}
}

void Game::HandleDealerScore(void *arg)
{
	std::string *state = static_cast<std::string *>(arg);

	int score = GetPlayerScore();
	if (score > 21) {
		*state = "Dealer Busted";
	} else if (score == 21 && currentPlayer_->Cards() == 2) {
		*state = "Dealer Blackjack";
	}

	std::cout << score << "\n";
}

void Game::HandleGameOver(void *)
{
	Deck &deck = deck_;
	std::for_each(players_.begin(), players_.end(),
		      [&deck](Player &player) {
			      while (player.Cards()) {
				      deck.Return(player.Return());
			      }
		      });
}

void Game::HandleHit(void *)
{
	Player &player = *currentPlayer_;
	player.Take(deck_.Take());
}

void Game::HandleNextPlayer(void *arg)
{
	std::string *state = static_cast<std::string *>(arg);

	++currentPlayer_;
	if (currentPlayer_ == players_.end()) {
		throw std::logic_error("No more players");
	}

	Player &player = *currentPlayer_;
	if (player.GetName() == "Dealer") {
		*state = "Dealer Turn";
	}
}

void Game::HandlePlay(void *)
{
	currentPlayer_ = players_.begin();
}

void Game::HandleQuitGame(void *)
{
	finished_ = true;
}

void Game::HandleScore(void *arg)
{
	std::string *state = static_cast<std::string *>(arg);

	int score = GetPlayerScore();
	if (score > 21) {
		*state = "Player Busted";
	} else if (score == 21 && currentPlayer_->Cards() == 2) {
		*state = "Player Blackjack";
	}

	std::cout << score << "\n";
}

void Game::HandleShuffle(void *)
{
	deck_.Shuffle();
}

bool Game::IsValidOption(char option) const
{
	return logic_.IsValidAction(option);
}

void Game::ProcessOption(char option)
{
	auto handler = logic_.GetAction(option);
	handler(nullptr);
	logic_.UpdateState(option);
}

void Game::ProcessNextAction()
{
	auto handler = logic_.GetAction();
	std::string state;
	handler(&state);
	if (state.empty()) {
		logic_.UpdateState();
	} else {
		logic_.SetState(state);
	}
}

std::size_t Game::AvailableOptions() const
{
	return logic_.Actions();
}

std::string Game::GetAvailableOptions() const
{
	return logic_.GetActions();
}

std::string Game::GetState() const
{
	return logic_.GetState();
}

int Game::GetPlayerScore() const
{
	int score = 0;
	bool hasAce = false;
	std::for_each(currentPlayer_->Begin(), currentPlayer_->End(),
		      [&](const Card &card) {
			      int rank = card.Rank() + 1;
			      if (rank >= 10) {
				      score += 10;
			      } else if (rank == 1 && !hasAce) {
				      score += 11;
				      hasAce = true;
			      } else {
				      score += rank;
			      }
		      });

	if (score > 21 && hasAce) {
		score -= 10;
	}
	return score;
}
