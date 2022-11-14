//Fill out this comment with your names and which bullet points you did
//Partners:Samuel Garnica (1 & 2), Spencer Ha (3 & 4), Ayanna Avalos (5)
//Partners:Samuel Garnica (1 & 2), Ayanna Avalos(5), Spencer Ha
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
	string pokemon1type1;//ADDED FOR 5, variable to hold the type 1
	string pokemon2type1;
	string pokemon1type2;//ADDED for 5, variable to hold type 2
	string pokemon2type2;
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
			pokemon1type1 = poke.type1;//ADDED FOR 5, when true, type 1 from database is put into variable pokemon1type1 (same with line below)
			pokemon1type2 = poke.type2;
			//  cout << poke.type1 << poke.type2 << endl; //ADDED FOR 5, simply to see if worked

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
	while (true) {
		if (turn % 2 == 0) {
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
			if (temp_move2.type == activeP2.type1 or temp_move2.type == activeP2.type2) { // Checks if move type matches either of the attacking pokemon's types.
				activeP1.hp = activeP1.hp - double(temp_move2.power * activeP2.attack) / activeP1.defense * 1.5;
			} // Formula for damage with STAB modifier and no type modifier.
			else activeP1.hp = activeP1.hp - double(temp_move2.power * activeP2.attack) / activeP1.defense; // Formula for no STAB and no type modifier.
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
//Have them do damage to each other based on their move * power * type modifier
//Target Pokémon reduces damage based on its defense or special defense

//ADDED FOR 5 below ----- using typessystem
//pokemon player 1 , using type 1 & type 2
//pokemon player 2, using type 1 & type 2
	int p1t1 = 0;
	if (pokemon1type1 == "Normal") {//four if statements to use the type to "lookup" col/row for both types of both pokemon
		int zero = 0;
		p1t1 = zero;
	} else if (pokemon1type1 == "Fighting") {

		p1t1     += 1;
	} else if (pokemon1type1 == "Flying") {
		p1t1 += 2;
	} else if (pokemon1type1 == "Poison") {
		p1t1 += 3;
	} else if (pokemon1type1 == "Ground") {
		p1t1 += 4;
	} else if (pokemon1type1 == "Rock") {
		p1t1 += 5;
	} else if (pokemon1type1 == "Bug") {
		p1t1 += 6;
	} else if (pokemon1type1 == "Ghost") {
		p1t1 += 7;
	} else if (pokemon1type1 == "Steel") {
		p1t1 += 8;
	} else if (pokemon1type1 == "Fire") {
		p1t1 += 9;
	} else if (pokemon1type1 == "Water") {
		p1t1 += 10;
	} else if (pokemon1type1 == "Grass") {
		p1t1 += 11;
	} else if (pokemon1type1 == "Electric") {
		p1t1 += 12;
	} else if (pokemon1type1 == "Psychic") {
		p1t1 += 13;
	} else if (pokemon1type1 == "Ice") {
		p1t1 += 14;
	} else if (pokemon1type1 == "Dragon") {
		p1t1 += 15;
	} else if (pokemon1type1 == "Dark") {
		p1t1 += 16;
	} else if (pokemon1type1 == "Fairy") {
		p1t1 += 17;
	} else {
		//  p1t1 = -1;
	}

	int p1t2 = 0;
	if (pokemon1type2 == "Normal") {
		int zero = 0;
		p1t2 = zero;
	} else if (pokemon1type2 == "Fighting") {

		p1t2 += 1;
	} else if (pokemon1type2 == "Flying") {
		p1t2 += 2;
	} else if (pokemon1type2 == "Poison") {
		p1t2 += 3;
	} else if (pokemon1type2 == "Ground") {
		p1t2 += 4;
	} else if (pokemon1type2 == "Rock") {
		p1t2 += 5;
	} else if (pokemon1type2 == "Bug") {
		p1t2 += 6;
	} else if (pokemon1type2 == "Ghost") {
		p1t2 += 7;
	} else if (pokemon1type2 == "Steel") {
		p1t2 += 8;
	} else if (pokemon1type2 == "Fire") {
		p1t2 += 9;
	} else if (pokemon1type2 == "Water") {
		p1t2 += 10;
	} else if (pokemon1type2 == "Grass") {
		p1t2 += 11;
	} else if (pokemon1type2 == "Electric") {
		p1t2 += 12;
	} else if (pokemon1type2 == "Psychic") {
		p1t2 += 13;
	} else if (pokemon1type2 == "Ice") {
		p1t2 += 14;
	} else if (pokemon1type2 == "Dragon") {
		p1t2 += 15;
	} else if (pokemon1type2 == "Dark") {
		p1t2 += 16;
	} else if (pokemon1type2 == "Fairy") {
		p1t2 += 17;
	} else {
		//  p1t2 = -1;
	}

	int p2t1 = 0;
	if (pokemon2type1 == "Normal") {
		int zero = 0;
		p2t1 = zero;
	} else if (pokemon2type1 == "Fighting") {

		p2t1 += 1;
	} else if (pokemon2type1 == "Flying") {
		p2t1 += 2;
	} else if (pokemon2type1 == "Poison") {
		p2t1 += 3;
	} else if (pokemon2type1 == "Ground") {
		p2t1 += 4;
	} else if (pokemon2type1 == "Rock") {
		p2t1 += 5;
	} else if (pokemon2type1 == "Bug") {
		p2t1 += 6;
	} else if (pokemon2type1 == "Ghost") {
		p2t1 += 7;
	} else if (pokemon2type1 == "Steel") {
		p2t1 += 8;
	} else if (pokemon2type1 == "Fire") {
		p2t1 += 9;
	} else if (pokemon2type1 == "Water") {
		p2t1 += 10;
	} else if (pokemon2type1 == "Grass") {
		p2t1 += 11;
	} else if (pokemon2type1 == "Electric") {
		p2t1 += 12;
	} else if (pokemon2type1 == "Psychic") {
		p2t1 += 13;
	} else if (pokemon2type1 == "Ice") {
		p2t1 += 14;
	} else if (pokemon2type1 == "Dragon") {
		p2t1 += 15;
	} else if (pokemon2type1 == "Dark") {
		p2t1 += 16;
	} else if (pokemon2type1 == "Fairy") {
		p2t1 += 17;
	} else {
		//  p2t1 = -1;
	}

	int p2t2 = 0;
	if (pokemon2type2 == "Normal") {
		int zero = 0;
		p2t2 = zero;
	} else if (pokemon2type2 == "Fighting") {

		p2t2 += 1;
	} else if (pokemon2type2 == "Flying") {
		p2t2 += 2;
	} else if (pokemon2type2 == "Poison") {
		p2t2 += 3;
	} else if (pokemon2type2 == "Ground") {
		p2t2 += 4;
	} else if (pokemon2type2 == "Rock") {
		p2t2 += 5;
	} else if (pokemon2type2 == "Bug") {
		p2t2 += 6;
	} else if (pokemon2type2 == "Ghost") {
		p2t2 += 7;
	} else if (pokemon2type2 == "Steel") {
		p2t2 += 8;
	} else if (pokemon2type2 == "Fire") {
		p2t2 += 9;
	} else if (pokemon2type2 == "Water") {
		p2t2 += 10;
	} else if (pokemon2type2 == "Grass") {
		p2t2 += 11;
	} else if (pokemon2type2 == "Electric") {
		p2t2 += 12;
	} else if (pokemon2type2 == "Psychic") {
		p2t2 += 13;
	} else if (pokemon2type2 == "Ice") {
		p2t2 += 14;
	} else if (pokemon2type2 == "Dragon") {
		p2t2 += 15;
	} else if (pokemon2type2 == "Dark") {
		p2t2 += 16;
	} else if (pokemon2type2 == "Fairy") {
		p2t2 += 17;
	} else {
		//  p2t2 = -1;
	}

	const int ARRAY_SIZE = 18; // Array size 18x18??
	float numbers[ARRAY_SIZE][ARRAY_SIZE];//this mess below because i couldn't fix an out of bounds error when i loaded from type_system.txt

	numbers[0][0] = 1;
	numbers[0][1] = 1;
	numbers[0][2] = 1;
	numbers[0][3] = 1;
	numbers[0][4] = 1;
	numbers[0][5] = 0.5;
	numbers[0][6] = 1;
	numbers[0][7] = 0;
	numbers[0][8] = 0.5;
	numbers[0][9] = 1;
	numbers[0][10] = 1;
	numbers[0][11] = 1;
	numbers[0][12] = 1;
	numbers[0][13] = 1;
	numbers[0][14] = 1;
	numbers[0][15] = 1;
	numbers[0][16] = 1;
	numbers[0][17] = 1;


	numbers[1][0] = 2;
	numbers[1][1] = 1;
	numbers[1][2] = 0.5;
	numbers[1][3] = 0.5;
	numbers[1][4] = 1;
	numbers[1][5] = 2;
	numbers[1][6] = 0.5;
	numbers[1][7] = 0;
	numbers[1][8] = 2;
	numbers[1][9] = 1;
	numbers[1][10] = 1;
	numbers[1][11] = 1;
	numbers[1][12] = 1;
	numbers[1][13] = 0.5;
	numbers[1][14] = 2;
	numbers[1][15] = 1;
	numbers[1][16] = 2;
	numbers[1][17] = 0.5;

	numbers[2][0] = 1;
	numbers[2][1] = 2;
	numbers[2][2] = 1;
	numbers[2][3] = 1;
	numbers[2][4] = 1;
	numbers[2][5] = 0.5;
	numbers[2][6] = 2;
	numbers[2][7] = 1;
	numbers[2][8] = 0.5;
	numbers[2][9] = 1;
	numbers[2][10] = 1;
	numbers[2][11] = 1;
	numbers[2][12] = 2;
	numbers[2][13] = 0.5;
	numbers[2][14] = 1;
	numbers[2][15] = 1;
	numbers[2][16] = 1;
	numbers[2][17] = 1;

	numbers[3][0] = 1;
	numbers[3][1] = 1;
	numbers[3][2] = 1;
	numbers[3][3] = 0.5;
	numbers[3][4] = 0.5;
	numbers[3][5] = 0.5;
	numbers[3][6] = 1;
	numbers[3][7] = 0.5;
	numbers[3][8] = 0;
	numbers[3][9] = 1;
	numbers[3][10] = 1;
	numbers[3][11] = 2;
	numbers[3][12] = 1;
	numbers[3][13] = 1;
	numbers[3][14] = 1;
	numbers[3][15] = 1;
	numbers[3][16] = 1;
	numbers[3][17] = 2;

	numbers[4][0] = 1;
	numbers[4][1] = 1;
	numbers[4][2] = 0;
	numbers[4][3] = 2;
	numbers[4][4] = 1;
	numbers[4][5] = 2;
	numbers[4][6] = 0.5;
	numbers[4][7] = 1;
	numbers[4][8] = 2;
	numbers[4][9] = 2;
	numbers[4][10] = 1;
	numbers[4][11] = 0.5;
	numbers[4][12] = 2;
	numbers[4][13] = 1;
	numbers[4][14] = 1;
	numbers[4][15] = 1;
	numbers[4][16] = 1;
	numbers[4][17] = 1;

	numbers[5][0] = 1;
	numbers[5][1] = 0.5;
	numbers[5][2] = 2;
	numbers[5][3] = 1;
	numbers[5][4] = 0.5;
	numbers[5][5] = 1;
	numbers[5][6] = 2;
	numbers[5][7] = 1;
	numbers[5][8] = 0.5;
	numbers[5][9] = 2;
	numbers[5][10] = 1;
	numbers[5][11] = 1;
	numbers[5][12] = 1;
	numbers[5][13] = 1;
	numbers[5][14] = 2;
	numbers[5][15] = 1;
	numbers[5][16] = 1;
	numbers[5][17] = 1;

	numbers[6][0] = 1;
	numbers[6][1] = 0.5;
	numbers[6][2] = 0.5;
	numbers[6][3] = 0.5;
	numbers[6][4] = 1;
	numbers[6][5] = 1;
	numbers[6][6] = 1;
	numbers[6][7] = 0.5;
	numbers[6][8] = 0.5;
	numbers[6][9] = 0.5;
	numbers[6][10] = 1;
	numbers[6][11] = 2;
	numbers[6][12] = 1;
	numbers[6][13] = 2;
	numbers[6][14] = 1;
	numbers[6][15] = 1;
	numbers[6][16] = 2;
	numbers[6][17] = 0.5;

	numbers[7][0] = 0;
	numbers[7][1] = 1;
	numbers[7][2] = 1;
	numbers[7][3] = 1;
	numbers[7][4] = 1;
	numbers[7][5] = 1;
	numbers[7][6] = 1;
	numbers[7][7] = 2;
	numbers[7][8] = 1;
	numbers[7][9] = 1;
	numbers[7][10] = 1;
	numbers[7][11] = 1;
	numbers[7][12] = 1;
	numbers[7][13] = 2;
	numbers[7][14] = 1;
	numbers[7][15] = 1;
	numbers[7][16] = 0.5;
	numbers[7][17] = 1;

	numbers[8][0] = 1;
	numbers[8][1] = 1;
	numbers[8][2] = 1;
	numbers[8][3] = 1;
	numbers[8][4] = 1;
	numbers[8][5] = 2;
	numbers[8][6] = 1;
	numbers[8][7] = 1;
	numbers[8][8] = 0.5;
	numbers[8][9] = 0.5;
	numbers[8][10] = 0.5;
	numbers[8][11] = 1;
	numbers[8][12] = 0.5;
	numbers[8][13] = 1;
	numbers[8][14] = 2;
	numbers[8][15] = 1;
	numbers[8][16] = 1;
	numbers[8][17] = 2;

	numbers[9][0] = 1;
	numbers[9][1] = 1;
	numbers[9][2] = 1;
	numbers[9][3] = 1;
	numbers[9][4] = 1;
	numbers[9][5] = 0.5;
	numbers[9][6] = 2;
	numbers[9][7] = 1;
	numbers[9][8] = 2;
	numbers[9][9] = 0.5;
	numbers[9][10] = 0.5;
	numbers[9][11] = 2;
	numbers[9][12] = 1;
	numbers[9][13] = 1;
	numbers[9][14] = 2;
	numbers[9][15] = 0.5;
	numbers[9][16] = 1;
	numbers[9][17] = 1;

	numbers[10][0] = 1;
	numbers[10][1] = 1;
	numbers[10][2] = 1;
	numbers[10][3] = 1;
	numbers[10][4] = 2;
	numbers[10][5] = 2;
	numbers[10][6] = 1;
	numbers[10][6] = 1;
	numbers[10][7] = 1;
	numbers[10][8] = 1;
	numbers[10][9] = 2;
	numbers[10][10] = 0.5;
	numbers[10][11] = 0.5;
	numbers[10][12] = 1;
	numbers[10][13] = 1;
	numbers[10][14] = 1;
	numbers[10][15] = 0.5;
	numbers[10][16] = 1;
	numbers[10][17] = 1;


	numbers[11][0] = 1;
	numbers[11][1] = 1;
	numbers[11][2] = 0.5;
	numbers[11][3] = 0.5;
	numbers[11][4] = 2;
	numbers[11][5] = 2;
	numbers[11][6] = 0.5;
	numbers[11][7] = 1;
	numbers[11][8] = 0.5;
	numbers[11][9] = 0.5;
	numbers[11][10] = 2;
	numbers[11][11] = 0.5;
	numbers[11][12] = 1;
	numbers[11][13] = 1;
	numbers[11][14] = 1;
	numbers[11][15] = 0.5;
	numbers[11][16] = 1;
	numbers[11][17] = 1;

	numbers[12][0] = 1;
	numbers[12][1] = 1;
	numbers[12][2] = 2;
	numbers[12][3] = 1;
	numbers[12][4] = 0;
	numbers[12][5] = 1;
	numbers[12][6] = 1;
	numbers[12][7] = 1;
	numbers[12][8] = 1;
	numbers[12][9] = 1;
	numbers[12][10] = 2;
	numbers[12][11] = 0.5;
	numbers[12][12] = 0.5;
	numbers[12][13] = 1;
	numbers[12][14] = 1;
	numbers[12][15] = 0.5;
	numbers[12][16] = 1;
	numbers[12][17] = 1;

	numbers[13][0] = 1;
	numbers[13][1] = 2;
	numbers[13][2] = 1;
	numbers[13][3] = 2;
	numbers[13][4] = 1;
	numbers[13][5] = 1;
	numbers[13][6] = 1;
	numbers[13][7] = 1;
	numbers[13][8] = 0.5;
	numbers[13][9] = 1;
	numbers[13][10] = 1;
	numbers[13][11] = 1;
	numbers[13][12] = 1;
	numbers[13][13] = 0.5;
	numbers[13][14] = 1;
	numbers[13][15] = 1;
	numbers[13][16] = 0;
	numbers[13][17] = 1;

	numbers[14][0] = 1;
	numbers[14][1] = 1;
	numbers[14][2] = 2;
	numbers[14][3] = 1;
	numbers[14][4] = 2;
	numbers[14][5] = 1;
	numbers[14][6] = 1;
	numbers[14][7] = 1;
	numbers[14][8] = 0.5;
	numbers[14][9] = 0.5;
	numbers[14][10] = 0.5;
	numbers[14][11] = 2;
	numbers[14][12] = 1;
	numbers[14][13] = 1;
	numbers[14][14] = 0.5;
	numbers[14][15] = 2;
	numbers[14][16] = 1;
	numbers[14][17] = 1;

	numbers[15][0] = 1;
	numbers[15][1] = 1;
	numbers[15][2] = 1;
	numbers[15][3] = 1;
	numbers[15][4] = 1;
	numbers[15][5] = 1;
	numbers[15][6] = 1;
	numbers[15][7] = 1;
	numbers[15][8] = 0.5;
	numbers[15][9] = 1;
	numbers[15][10] = 1;
	numbers[15][11] = 1;
	numbers[15][12] = 1;
	numbers[15][13] = 1;
	numbers[15][14] = 1;
	numbers[15][15] = 2;

	numbers[15][16] = 1;
	numbers[15][17] = 0;

	numbers[16][0] = 1;
	numbers[16][1] = 0.5;
	numbers[16][2] = 1;
	numbers[16][3] = 1;
	numbers[16][4] = 1;
	numbers[16][5] = 1;
	numbers[16][6] = 1;
	numbers[16][7] = 2;
	numbers[16][8] = 1;
	numbers[16][9] = 1;
	numbers[16][10] = 1;
	numbers[16][11] = 1;
	numbers[16][12] = 1;
	numbers[16][13] = 2;
	numbers[16][14] = 1;
	numbers[16][15] = 1;
	numbers[16][16] = 0.5;
	numbers[16][17] = 0.5;

	numbers[17][0] = 1;
	numbers[17][1] = 2;
	numbers[17][2] = 1;
	numbers[17][3] = 0.5;
	numbers[17][4] = 1;
	numbers[17][5] = 1;
	numbers[17][6] = 1;
	numbers[17][7] = 1;
	numbers[17][8] = 0.5;
	numbers[17][9] = 0.5;
	numbers[17][10] = 1;
	numbers[17][11] = 1;
	numbers[17][12] = 1;
	numbers[17][13] = 1;
	numbers[17][14] = 1;
	numbers[17][15] = 2;
	numbers[17][16] = 2;
	numbers[17][17] = 1;
//when attacker = pokemon1
	float damagetypesyst = 0;
	float damagetypesyst2 = 0;
	if (activeP1.speed > activeP2.speed) {
		damagetypesyst = numbers[p1t1][p2t1];
		damagetypesyst2 = numbers[p1t2][p2t2];
	}
//attacker = pokemon2
	if (activeP1.speed == activeP2.speed) {

		damagetypesyst = numbers[p2t1][p1t1];
		damagetypesyst2 = numbers[p2t2][p1t2];
	}
//END of 5 ----
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
