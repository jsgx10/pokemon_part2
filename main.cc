//Fill out this comment with your names and which bullet points you did
//Partners:Samuel Garnica (1 & 2), Spencer Ha (3 & 4), Ayanna Avalos (5)
//Bullet Points:
//Extra Credit:
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <sstream>
#include <string>
#include <cctype>
using namespace std;

void die(string s = "INVALID INPUT!") {
	cout << s << endl;
	exit(EXIT_FAILURE);
}

//Holds a record for a single species of Pokemon, such as Pikachu
class Pokemon {
  public:
	//YOU: Add member variable ints for each of the following:

	int index;
	string name;
	int hp;
	int attack;
	int defense;
	int speed;
	int special;
	string type1;
	string type2;

	//index - what index it is in the pokedex
	//name (this is a string not an int)
	//hp - how much damage it takes before dying fainting
	//attack - this number gets multiplied by the move's power to determine damage
	//defense - incoming damage gets divided by this number
	//speed - whichever pokemon has the highest speed attacks first, flip a coin on a tie
	//special - like attack and defense both, but for special moves
	//Note: this is also the order the data is ordered in the file
	//YOU: Add member variables of type string for type1 and type2
};
vector<Pokemon> pokemon_db; //Holds all pokemon known to mankind

//This function reads from the "pokemon.txt" file in the directory and loads the data into the pokemon_db global vector
//Each row has: pokemon number, name, hp, etc.
void load_pokemon_db(string filename = "pokemon.txt", string filename2 = "types.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load file "s + filename);
	ifstream ins2(filename2);
	if (!ins2) die("Couldn't load file"s + filename2);
	while (ins and ins2) {
		try {
			//YOU: Read from the files the data into a temporary Pokemon, getting the stats from pokemon.txt and its types from types.txt
			//YOU: After vetting it (make sure you handle Mr. Mime properly) push it back into pokemon_db

			Pokemon tempClass;
			string s;
			getline(ins, s);
			if (!ins) break;
			stringstream sts(s);
			string temp;
			int tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.index = tempInt;

			string tempName;
			getline(sts, temp, '\t');
			tempName = temp;
			tempClass.name = tempName;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.hp = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.attack = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.defense = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.speed = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempClass.special = tempInt;
			getline(ins2, s);
			if (!ins2) break;
			stringstream type(s);
			getline(type, temp, '\t');
			getline(type, temp, '\t');
			getline(type, temp, '\t');
			tempName = temp;
			tempClass.type1 = tempName;
			getline(type, temp, '\t');
			tempName = temp;
			tempClass.type2 = tempName;
			pokemon_db.push_back(tempClass);
		} catch (...) {
			continue;
		}
	}
}

//This class holds a record for each move in the game
class Move {
  public:
	//YOU: Add member variable for each of these:
	//int index, string name, string type, string category, int PP, int power, int accuracy
	int index;
	string name;
	string type;
	string category;
	int PP;
	int power;
	int accuracy;

};
vector<Move> move_db;

//Reads all moves from moves.txt into move_db
//Be sure to discard all status moves
void load_move_db(string filename = "moves.txt") {
	ifstream ins(filename);
	if (!ins) die("Couldn't load "s + filename);
	while (ins) {

		try {
			Move tempMove;
			string m;
			getline(ins, m);
			if (!ins) break;
			stringstream sts(m);
			string temp;
			int tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempMove.index = tempInt;
			string tempName;
			getline(sts, temp, '\t');
			tempName = temp;
			tempMove.name = tempName;
			getline(sts, temp, '\t');
			tempName = temp;
			tempMove.type = tempName;
			getline(sts, temp, '\t');
			tempName = temp;
			tempMove.category = tempName;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempMove.PP = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempMove.power = tempInt;
			getline(sts, temp, '\t');
			tempInt = stoi(temp);
			tempMove.accuracy = tempInt;
			move_db.push_back(tempMove);
		} catch (...) {
			continue;
		}
		//YOU: Read from the file, make a temp Move with all the data read in
		//YOU: Push it back into the move_db
	}
}

//PART 2
//This conducts a one versus one battle between two pokemon of your choice
void battle_mode() {
	//Pick a Pokemon and a move for team one
	int turn = 0;
	string input;
	cout << "Please enter the pokedex entry number or name of the first pokemon." << endl;
	cin.ignore();
	getline(cin, input);
	int pokemonInd1 = 0;
	string pokemonStr1;
	if (input.size() and isdigit(input.at(0))) {
		pokemonInd1 = stoi(input);
		if (pokemonInd1 < 0 or pokemonInd1 > pokemon_db.size()) die();
	} else {
		pokemonStr1 = input;
		pokemonStr1.at(0) = toupper(pokemonStr1.at(0));
	}
	Pokemon activeP1;
	bool check = false;
	for (const Pokemon &poke : pokemon_db) {
		if (pokemonInd1 == poke.index or pokemonStr1 == poke.name) {
			activeP1 = poke;
			check = true;
		}
	}
	if (!check) die();//if false then string name doesn't exist in pokemon_db, invalid input
	cout << "You picked: "  << activeP1.name << endl;
	cout << "Please enter a move index number or name. Enter -1 when done" << endl;
	cin.clear();
	getline(cin, input);
	vector<Move> p1Moves;
	while (input != "-1") {
		int p1Move = 0;
		string p1StrMove;
		if (input.size() and isdigit(input.at(0))) {
			p1Move = stoi(input);
			if (p1Move < 0 or p1Move > pokemon_db.size()) die();
		} else {
			p1StrMove = input;
			p1StrMove.at(0) = toupper(p1StrMove.at(0));
			p1StrMove.at(p1StrMove.find(" ") + 1) = toupper(p1StrMove.at(p1StrMove.find(" ") + 1));
		}
		//cout << p1StrMove << endl;// seeing if the uppercasing works
		Move temp_move;
		check = false;
		for (const Move &M : move_db) {
			if (p1Move == M.index or p1StrMove == M.name) {
				temp_move = M;
				p1Moves.push_back(temp_move);
				check = true;
			}
		}
		if (!check) die();
		cout << "You picked: " << temp_move.name << endl;
		if (p1Moves.size() >= 4) break;
		cout << "Please enter a move index or name. Enter -1 when done" << endl;
		cin.clear();
		getline(cin, input);
	}

//Pick a Pokemon and a move for team two
	cout << "Please enter the pokedex entry number of the second pokemon." << endl;
	cin.clear();
	getline(cin, input);
	//cout << input << endl;
	int pokemonInd2 = 0;
	string pokemonStr2;
	if (input.size() and isdigit(input.at(0))) {
		pokemonInd2 = stoi(input);
		if (pokemonInd2 < 0 or pokemonInd2 > pokemon_db.size()) die();
	} else pokemonStr2 = input;
	Pokemon activeP2;
	check = false;
	for (const Pokemon &poke : pokemon_db) {
		if (pokemonInd2 == poke.index or pokemonStr2 == poke.name) {
			activeP2 = poke;
			check = true;
		}
	}
	if (!check) die();
	cout << "You picked: " << activeP2.name << endl;
	cout << "Please enter a move index or name. Enter -1 when done" << endl;
	cin.clear();
	getline(cin, input);
	vector<Move> p2Moves;
	while (input != "-1") {
		int p2Move = 0;
		string p2StrMove;
		if (input.size() and isdigit(input.at(0))) {
			p2Move = stoi(input);
			if (p2Move < 0 or p2Move > pokemon_db.size()) die();
		} else {
			p2StrMove = input;
			p2StrMove.at(0) = toupper(p2StrMove.at(0));
			p2StrMove.at(p2StrMove.find(" ") + 1) = toupper(p2StrMove.at(p2StrMove.find(" ") + 1));
		}
		//cout << p1StrMove << endl;// seeing if the uppercasing works
		Move temp_move;
		check = false;
		for (const Move &M : move_db) {
			if (p2Move == M.index or p2StrMove == M.name) {
				temp_move = M;
				p2Moves.push_back(temp_move);
				check = true;
			}
		}
		if (!check) die();
		cout << "You picked: " << temp_move.name << endl;
		if (p2Moves.size() >= 4) break;
		cout << "Please enter a move index or name. Enter -1 when done" << endl;
		cin.clear();
		getline(cin, input);
	}

	//Whichever Pokemon has the higher speed goes first

	cout << "The battle begins! It's " << activeP1.name << " vs " << activeP2.name << "!" << endl;
	if (activeP1.speed > activeP2.speed) { // p1 goes first if speed stat is higher
		turn = 0;
	} else if (activeP2.speed > activeP1.speed) { // p2 goes first if speed stat is higher
		turn = 1;
	} else if (activeP1.speed == activeP2.speed) {
		srand(time(0));
		if (rand() % 2 == 0) { //If coinflip lands head pokemon 1 moves first
			turn = 0;
		}
		if (rand() % 2 == 1) { //If coinflip lands tails pokemon 2 moves first
			turn = 1;
		}
	}
	if (turn % 2 == 0) { //Pokemon turn 1 code
		cout << "What will " << activeP1.name << " do?" << endl;
		cin.clear();
		getline(cin, input);
		int p1MoveChoice = 0;
		string p1MoveChoiceString;
		if (isdigit(input.at(0))) {
			p1MoveChoice = stoi(input);
			if (p1MoveChoice < 0 or p1MoveChoice > p1Moves.size())
				die();
		} else {
			p1MoveChoiceString = input;
			p1MoveChoiceString.at(0) = toupper(p1MoveChoiceString.at(0));
			p1MoveChoiceString.at(p1MoveChoiceString.find(" ") + 1) = toupper(p1MoveChoiceString.at(p1MoveChoiceString.find(" ") + 1));
		}
		Move temp_move1;
		check = false;
		for (const Move &M : move_db) {
			if (p1MoveChoice == M.index or p1MoveChoiceString == M.name) {
				temp_move1 = M;
				p1Moves.push_back(temp_move1);
				check = true;
			}
		}
		if (!check) die();
		cout << activeP1.name << " used " << temp_move1.name << "!" << endl;
		if (temp_move1.type == activeP1.type1 or temp_move1.type == activeP1.type2) // Checks if move type matches either of the attacking pokemon's types.
			activeP2.hp = activeP2.hp - double(temp_move1.power * activeP1.attack) / activeP2.defense * 1.5; // Formula for damage with STAB modifier and no type modifier.
		else
			activeP2.hp = activeP2.hp - double(temp_move1.power * activeP1.attack) / activeP2.defense; // Formula for no STAB and no type modifier.
		if (activeP2.hp <= 0) {
			cout << activeP2.name << " has fainted. " << activeP1.name << " wins!" << endl;
			exit(0);
		} else if (activeP2.hp > 0) {
			turn++;
		}

		if (turn % 2 == 1) { // Pokemon turn 2 code
			cout << "What will " << activeP2.name << " do?" << endl;
			cin.clear();
			getline(cin, input);
			int p2MoveChoice = 0;
			string p2MoveChoiceString;
			if (isdigit(input.at(0))) {
				p2MoveChoice = stoi(input);
				if (p2MoveChoice < 0 or p2MoveChoice > p2Moves.size())
					die();
			} else {
				p2MoveChoiceString = input;
				p2MoveChoiceString.at(0) = toupper(p2MoveChoiceString.at(0));
				p2MoveChoiceString.at(p2MoveChoiceString.find(" ") + 1) = toupper(p2MoveChoiceString.at(p2MoveChoiceString.find(" ") + 1));
			}
			Move temp_move2;
			check = false;
			for (const Move &M : move_db) {
				if (p2MoveChoice == M.index or p2MoveChoiceString == M.name) {
					temp_move2 = M;
					p2Moves.push_back(temp_move2);
					check = true;
				}
			}
			if (!check) die();
			cout << activeP2.name << " used " << temp_move2.name << "!" << endl;
			if (temp_move2.type == activeP2.type1 or temp_move2.type == activeP2.type2) // Checks if move type matches either of the attacking pokemon's types.
				activeP1.hp = activeP1.hp - double(temp_move2.power * activeP2.attack) / activeP1.defense * 1.5; // Formula for damage with STAB modifier and no type modifier.
			else
				activeP1.hp = activeP1.hp - double(temp_move2.power * activeP2.attack) / activeP1.defense; // Formula for no STAB and no type modifier.
			if (activeP1.hp <= 0) {
				cout << activeP1.name << " has fainted. " << activeP1.name << " wins!" << endl;
				exit(0);
			} else if (activeP1.hp > 0) {
				turn++;
			}

		}
	}



//Have them do damage to each other based on their move * power * type modifier
//Target Pokémon reduces damage based on its defense or special defense
}

//PART 2
void explore_mode() {
}

int main() {
	srand(0); //Fixed seed - don't change this
	system("figlet POKEMON");
	system("figlet ++ and \\#");
	cout << "Do you want to use the Gen1 Pokémon? (Type \"NO\" for no, anything else for yes.)\n";
	string answer;
	getline(cin, answer);
	for (char &c : answer) c = toupper(c); //Uppercaseify
	string filename1, filename2;
	if (answer == "NO") {
		cout << "Please enter the two files containing the Pokémon and types for the Pokémon.\n";
		cin >> filename1 >> filename2;
		load_pokemon_db(filename1, filename2);
	} else
		load_pokemon_db();

	/* Debug the load - uncomment this to see everything
	for (Pokemon p : pokemon_db) {
		cerr << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
		cerr << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
		cerr << " type1: " << p.type1 << " type2: " << p.type2 << endl;
	}
	*/

	string filename3;
	if (answer == "NO") {
		cout << "Please enter the file containing the moves for your Pokémon.\n";
		cin >> filename3;
		load_move_db(filename3);
	} else
		load_move_db();

	/*
	// DEBUG the load - uncomment this to see the results
	for (Move m : move_db) {
		if (m.index == 0) continue;
		cerr << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
	}
	*/

	cout << "Do you want to\n1) Print Pokémon Data?\n2) Print Move Data?\n3) Pokemon Battle (1v1)\n4) Explore the World?\n";
	int choice = 0;
	cin >> choice;
	if (!cin || choice < 1 || choice > 4) die();
	if (choice == 1 && answer != "NO") {
		cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin || index < 1 || index > pokemon_db.size()) die();
		//	Pokemon p = pokemon_db.at(index+1); //Pokedex starts at 1, this only works for Gen1 Pokémon
		Pokemon p;
		for (const Pokemon &poke : pokemon_db) if (index == poke.index) p = poke;
		cout << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
		cout << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
		cout << " type1: " << p.type1 << " type2: " << p.type2 << endl;
	} else if (choice == 1 && answer == "NO") {
		cout << "Please enter the Pokedex number of the Pokémon whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin || index < 1 || index > pokemon_db.size()) die();
		//  Pokemon p = pokemon_db.at(index+1); //Pokedex starts at 1, this only works for Gen1 Pokémon
		Pokemon p;
		for (const Pokemon &poke : pokemon_db) if (index == poke.index) p = poke;
		cout << "Pokedex Entry " << p.index << ": " << p.name << " hp: " << p.hp << " attack: " << p.attack;
		cout << " defense: " << p.defense << " speed: " << p.speed << " special: " << p.special;
		cout << " type1: " << p.type1 << " type2: " << p.type2 << endl;

	}

	else if (choice == 2) {
		cout << "Please enter the move number of the move whose data you want to print:\n";
		int index = 0;
		cin >> index;
		if (!cin) die();
		Move m;
		for (const Move &mo : move_db) if (index == mo.index) m = mo;
		if (m.name == "Error") cout << "No move loaded with that index.\n";
		else
			cout << "Move Index " << m.index << ": " << m.name << " " << " type: " << m.type << " category: " << m.category << " PP: " << m.PP << " power: " << m.power << " accuracy: " << m.accuracy << "%\n";
	}
	if (choice == 3) battle_mode(); //PART 2
	else explore_mode(); //PART 2
}
