#include "../lib/std_lib_facilities.h"

using std::string;
using std::cin;
using std::cout;

int main()
{
	string friend_01 = "Unknown";
	string friend_02 = "Unknown";
	string sender = "Unknown";
	char friend_02_gender = 'm';
	string friend_02_gender_str_01 = "he";
	string friend_02_gender_str_02 = "him";
	string friend_02_gender_str_03 = "his";
	string friend_02_gender_str_04 = "father";
	int friend_01_age = 0;
	string friend_01_age_comment = "";
	cout << "Greetings! What is your name?\n";
	cin >> sender;
	cout << "Nice to meet you, " << sender << "! Please enter the name of a friend whom you'd like to write to.\n";
	cin >> friend_01;
	cout << "How old is your friend?\n";
	cin >> friend_01_age;
	if (friend_01_age <= 0 || friend_01_age > 110) simple_error("You're kidding!");
	if (friend_01_age < 12) friend_01_age_comment = "Next year you will be " + to_string(friend_01_age+1) + '.';
	if (friend_01_age == 17) friend_01_age_comment = "Next year you will be able to vote.";
	if (friend_01_age > 70) friend_01_age_comment = "I hope you are enjoying retirement.";
	cout << "Please enter the name of another friend.\n";
	cin >> friend_02;
	cout << "Is this other friend male or female? (Enter, without the single quotes, 'm' for male or 'f' for female).\n";
	cin >> friend_02_gender;
	if (friend_02_gender == 'f') {
		friend_02_gender_str_01 = "she";
		friend_02_gender_str_02 = "her";
		friend_02_gender_str_03 = "her";
		friend_02_gender_str_04 = "mother";
	}
	cout << "Dear " << friend_01 << ",\n";
	cout << "  How are you doing these days? I am quite well, although the weather's rather dull and the damn cat has gone missing again, can you believe it?";
	cout << " It seems as if some thing or person is always amiss in this dreadful existence of mine.\n";
	cout << "  Which reminds me: Have you seen " << friend_02 << " lately? Should you see "
		<< friend_02_gender_str_02 << ", please tell " << friend_02_gender_str_02 << " I'm worried that if "
		<< friend_02_gender_str_01 << " does not take matters seriously, " << friend_02_gender_str_01 << " may permanently tarnish the family name. "
		<< "It was, after all, " << friend_02_gender_str_03 << " great grand" << friend_02_gender_str_04
		<< ", also named " << friend_02 << ", who once established this proud institution.\n"
		<< "I hear you just had your birthday and you are now " << friend_01_age << " years old. "
		<< friend_01_age_comment << "\nYours sincerely,\n\n\n" << sender
		<< std::endl;
	keep_window_open();
	return 0;
}
