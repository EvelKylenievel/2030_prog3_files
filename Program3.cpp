// Kyle Wessel
// Programming Assignment 3
// COSC 2030

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "HashMap.h"
#include "HashMap.cpp"
#include "timer.h"

using namespace std;

string cleanWord(string word);

int main()
{
	ifstream dictfile;
	dictfile.open("dictionary.txt");
	if (!dictfile) {
		cout << "dict file not found" << endl;
		return 0;
	}
	else {
		//cout << "dict file found!" << endl;
	}

	Hash<string> hashmap;

	int dictwordcount = 0;
	string word;

	while (dictfile >> word) {
		string newWord = cleanWord(word);
		hashmap.insert(newWord);
		dictwordcount++;
	}

	dictfile.close();

	ifstream bookfile;
	bookfile.open("book.txt");
	if (!bookfile) {
		cout << "bookfile not found" << endl;
		return 0;
	}
	else {
		//cout << "book file found!" << endl;
	}



	Timer watch;
	ofstream misspelled("misspelled");
	int wordsFound = 0;
	int wordsNotFound = 0;
	watch.Start();
	
	while (bookfile >> word) {
		string newWord = cleanWord(word);
		
		if (newWord.empty()) {
			continue;
		}
		else if (!isalpha(newWord[0])) {
			hashmap.incSkips();
			continue;
		}

		else if (hashmap.find(newWord)) {
			wordsFound++;
		}
		else {
			wordsNotFound++;
			misspelled << newWord + '\n';
		}
	}
	

	watch.Stop();
	bookfile.close();
	misspelled.close();
	


	cout << "dictionary size: " << hashmap.getSize() << endl
		<< "Done checking and these the the results \nfinished in time: " << watch.Time() << endl
		<< "finished in Milliseconds Time: " << watch.TimeMS() << endl
		<< "There are " << wordsFound << " words found in the dictionary\n\t"
		<< hashmap.getHitCompares() << " compares.  Average: " << (hashmap.getHitCompares() / wordsFound) << endl
		<< "There are " << wordsNotFound << " words NOT found in the dictionary \n\t"
		<< hashmap.getMissCompares() << " compares.  Average: " << (hashmap.getMissCompares() / wordsNotFound) << endl
		<< "There are " << hashmap.getSkips() << " words not checked.";


	hashmap.~Hash();

	return 0;
}


string cleanWord(string word) {
	string cleanW;
	int len = 0;

	while (word[len] != 0) {
		++len;
	}

	for (int i = 0; i < len; i++) {
		if (!isalnum(word[i])) {
			if (word[i] != '\'') {
				word.erase(i, 0);
			}
			else {
				cleanW += word[i];
			}
		}

		else if (isupper(word[i])) {
			char letter = tolower(word[i]);
			cleanW += letter;
		}
		else {
			cleanW += word[i];
		}
	}
	return cleanW;
}

