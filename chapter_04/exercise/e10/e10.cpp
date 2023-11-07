#include "../../lib/std_lib_facilities.h"

// Exercise 10, Rock Paper Scissors
// Implement by grabbing 'answers' from a predefined vector of values.
// Try to fake randomness by asking for some user values that affect the answers

int name_to_number(std::string s) {
	int num{ 0 };
	for (int i = 0; i < s.length(); ++i) {
		num += s[i];
	}
	return num;
}

bool move_is_valid(std::string s) {
	return (s == "rock" || s == "paper" || s == "scissors");
}

std::string int_to_move(int m) {
	if (m == 0) {
		return "rock";
	}
	if (m == 1) {
		return "paper";
	}
	return "scissors";
}

bool its_a_draw(std::string player_move, std::string computer_move) {
	return player_move == computer_move;
}

bool player_wins(std::string player_move, std::string computer_move) {
	return (
		(player_move == "rock" && computer_move == "scissors") ||
		(player_move == "paper" && computer_move == "rock") ||
		(player_move == "scissors" && computer_move == "paper")
	);
}

int main()
{
	vector<int> computer_move_int_v{
		0,1,1,1,2,1,2,0,0,1,2,1,0,0,1,2,0,0,1,2,2,2,1,0,2,1,1,0,1,0,2,2,1,0,0,1,2,0,0,0
	};

	std::cout << "Let's play Rock Paper Scissors!" << '\n';
	std::cout << "Before we start the game, what is your name?" << '\n';

	std::string player_name{};
	std::cin >> player_name;

	int player_number{ name_to_number(player_name) };

	std::cout << "Hi there " << player_name << ", how many times have you "
	 << "played this game before? Please, be specific!" << '\n';

	int games_played { -1 };
	while (games_played < 0) {
		std::cin >> games_played;
	}

	if (games_played < 10) {
		std::cout << "Alright rookie, let the games begin!";
	} else {
		std::cout << "Already that many eh?";
	}
	std::cout << '\n';

	std::cout << "Enter 'rock', 'paper' or 'scissors'" << '\n';

	int player_win_count { 0 };
	int computer_win_count { 0 };
	std::string player_move{};
	while (std::cin >> player_move) {
		if(move_is_valid(player_move)) {
			int computer_move_int{
				computer_move_int_v[
					((player_number + 1) * games_played) %
					computer_move_int_v.size()
			]};
			std::string computer_move{ int_to_move(computer_move_int) };
			std::cout << "Player chooses > " << player_move << " <"
				<< '\t' << '\t'
				<< "Computer chooses > " << computer_move << " <"
				<< '\n';
			if (its_a_draw(player_move, computer_move)) {
				std::cout << "It's a draw!" << '\n';
			} else if (player_wins(player_move, computer_move)) {
				std::cout << "Player wins!" << '\n';
				++player_win_count;
			} else {
				std::cout << "Computer wins!" << '\n';
				++computer_win_count;
			}
			std::cout << "SCOREBOARD" << '\t' << "Player: " << player_win_count
				<< '\t' << '\t' << "Computer: " << computer_win_count
				<< '\n' << '\n';
			++games_played;
			std::cout << "Want to go again? "
				<< "Enter 'rock', 'paper' or 'scissors'" << '\n';
		}
	}


	keep_window_open();

    return 0;
}
