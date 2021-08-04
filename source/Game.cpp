// ------------------------------------------------------------ Project Headers
#include "Game.h"

// ------------------------------------------------------------ Library Headers
#include <algorithm>
#include <iostream>

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
			std::cout << std::endl << GetAvailableOptions() << ": ";
			char option = std::toupper(input_.GetCharacter());

			if (!IsValidOption(option)) {
				std::cerr << std::endl
					  << option << " is not a valid option"
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
	enum ACTION_ARGS { KEY, NAME, FUNCTION };
	enum TRANSITION_ARGS { FROM, TO, ACTION };

	auto &states = GetStates();
	auto &actions = GetActions();
	auto &automatedTransitions = GetAutomatedTransitions();
	auto &userTransitions = GetUserTransitions();

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
		std::cout << std::endl << "Shuffling..." << std::endl;
	} else if (state == "Dealing") {
		std::cout << "Dealing..." << std::endl;
	} else if (state == "Next Player") {
		std::cout << std::endl
			  << currentPlayer_->GetName() << std::endl;
		std::for_each(currentPlayer_->Begin(), currentPlayer_->End(),
			      [](const Card &card) {
				      std::cout << " " << card.Name()
						<< std::endl;
			      });
	} else if (state == "Dealer Busted" || state == "Player Busted") {
		std::cout
			<< "__________               __             .___._."
			<< std::endl
			<< "\\______   \\__ __  ______/  |_  ____   __| _/| |"
			<< std::endl
			<< " |    |  _/  |  \\/  ___|   __\\/ __ \\ / __ | | |"
			<< std::endl
			<< " |    |   \\  |  /\\___ \\ |  | \\  ___// /_/ |  \\|"
			<< std::endl
			<< " |______  /____//____  >|__|  \\___  >____ |  __"
			<< std::endl
			<< "        \\/           \\/           \\/     \\/  \\/"
			<< std::endl;
	} else if (state == "Dealer Blackjack" || state == "Player Blackjack") {
		std::cout
			<< "__________.__                 __         __               __   ._."
			<< std::endl
			<< "\\______   \\  | _____    ____ |  | __    |__|____    ____ |  | _| |"
			<< std::endl
			<< " |    |  _/  | \\__  \\ _/ ___\\|  |/ /    |  \\__  \\ _/ ___\\|  |/ / |"
			<< std::endl
			<< " |    |   \\  |__/ __ \\\\  \\___|    <     |  |/ __ \\\\  \\___|    < \\|"
			<< std::endl
			<< " |______  /____(____  /\\___  >__|_ \\/\\__|  (____  /\\___  >__|_ \\__"
			<< std::endl
			<< "        \\/          \\/     \\/     \\/\\______|    \\/     \\/     \\/\\/"
			<< std::endl;
	} else if (state == "Player Hit") {
		std::cout << std::endl
			  << " " << currentPlayer_->Back().Name() << std::endl;
	} else if (state == "Dealer Hit") {
		std::cout << std::endl
			  << " " << currentPlayer_->Back().Name() << std::endl;
	} else if (state == "Dealer Hand") {
		std::cout << std::endl
			  << players_.back().GetName() << std::endl;
		std::cout << " " << players_.back().Begin()->Name()
			  << std::endl;
	} else if (state == "Dealer Turn") {
		std::cout << std::endl
			  << currentPlayer_->GetName() << std::endl;
		std::for_each(currentPlayer_->Begin(), currentPlayer_->End(),
			      [](const Card &card) {
				      std::cout << " " << card.Name()
						<< std::endl;
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

	std::cout << std::endl << prompt;
	name = input_.GetString();
	while (name.empty()) {
		std::cerr << std::endl
			  << "A name must have at least one character."
			  << std::endl;
		std::cout << std::endl << prompt;
		name = input_.GetString();
	}

	auto pos = players_.end();
	--pos;

	players_.emplace(pos, name);
	std::cout << std::endl << name << " added to the game." << std::endl;
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

	std::cout << std::endl << " " << score << std::endl;
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

	std::cout << std::endl << " " << score << std::endl;
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

const Game::States &Game::GetStates() const
{
	static const States states{ "Dealer Blackjack",
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
	return states;
}

const Game::Actions &Game::GetActions()
{
	static Actions actions{
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
				std::bind(&Game::HandleDealerAction, this,
					  std::placeholders::_1)),
		std::make_tuple(0, "HandleDealerScore",
				std::bind(&Game::HandleDealerScore, this,
					  std::placeholders::_1)),
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
	return actions;
}

const Game::UserTransitions &Game::GetUserTransitions() const
{
	static const UserTransitions userTransitions{
		std::make_tuple("Waiting for Players", "Ready to Play", 'A'),
		std::make_tuple("Waiting for Players", "Quit Game", 'Q'),
		std::make_tuple("Ready to Play", "Ready to Play", 'A'),
		std::make_tuple("Ready to Play", "Shuffling", 'P'),
		std::make_tuple("Ready to Play", "Quit Game", 'Q'),
		std::make_tuple("Playing", "Player Hit", 'H'),
		std::make_tuple("Playing", "Player Stand", 'S'),
		std::make_tuple("Playing", "Quit Game", 'Q')
	};
	return userTransitions;
}

const Game::AutomatedTransitions &Game::GetAutomatedTransitions() const
{
	static const AutomatedTransitions automatedTransitions{
		std::make_tuple("Shuffling", "Dealing", "HandleShuffle"),
		std::make_tuple("Dealing", "Dealer Hand", "HandleDeal"),
		std::make_tuple("Dealer Hand", "Next Player", "DoNothing"),
		std::make_tuple("Next Player", "Scoring", "DoNothing"),
		std::make_tuple("Scoring", "Playing", "HandleScore"),
		std::make_tuple("Player Blackjack", "Next Player",
				"HandleNextPlayer"),
		std::make_tuple("Player Busted", "Next Player",
				"HandleNextPlayer"),
		std::make_tuple("Player Hit", "Scoring", "DoNothing"),
		std::make_tuple("Player Stand", "Next Player",
				"HandleNextPlayer"),
		std::make_tuple("Dealer Turn", "Dealer Play", "DoNothing"),
		std::make_tuple("Dealer Play", "Dealer Playing",
				"HandleDealerScore"),
		std::make_tuple("Dealer Playing", "Dealer Play",
				"HandleDealerAction"),
		std::make_tuple("Dealer Hit", "Dealer Play", "DoNothing"),
		std::make_tuple("Dealer Blackjack", "Ready to Play",
				"HandleGameOver"),
		std::make_tuple("Dealer Busted", "Ready to Play",
				"HandleGameOver"),
		std::make_tuple("Dealer Stand", "Ready to Play",
				"HandleGameOver")
	};
	return automatedTransitions;
}
