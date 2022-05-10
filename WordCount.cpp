// WordCount.cpp

#include "WordCount.h"

using namespace std;

struct compOperator1{
    bool operator() (pair<string, int> p1, pair<string, int> p2) {
        if ((p1.first).compare(p2.first) < 0){
            return true;
        }
        return false;
    }
}comp1;

struct compOperator2{
    bool operator() (pair<string, int> p1, pair<string, int> p2) {
        if (p1.second < p2.second){
            return true;
        }
		else if (p1.second == p2.second){
			if ((p1.first).compare(p2.first) < 0){
				return true;
			}
			return false;
		}
        return false;
    }
}comp2;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(const std::string& word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int numWords = 0;
	vector<pair<string, int>> wordVector;

	for (size_t i = 0; i < CAPACITY; i++){
		wordVector = table[i];

		for (auto wordPair: wordVector){
		//for (int i = 0; i < wordVector.size(); i++){
			//cout << wordPair.second << endl;
			numWords+=(wordPair.second);
		}
	}
	return numWords;
}

int WordCount::getNumUniqueWords() const {
	int numWords = 0;
	vector<pair<string, int>> wordVector;

	for (size_t i = 0; i < CAPACITY; i++){
		wordVector = table[i];
		//cout << wordVector.size() << endl;
		numWords+=(wordVector.size());
	}
	//cout << numWords << endl;
	return numWords;
}

int WordCount::getWordCount(const std::string & word) const {
	string validWord = makeValidWord(word);
	int wordIndex = hash(validWord);
	vector<pair<string, int>> wordVector = table[wordIndex];
	
	for (size_t i = 0; i < wordVector.size(); i++){
		if (wordVector.at(i).first == validWord){
			return table[wordIndex].at(i).second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(const std::string & word) {
	//first put word through hash function
	//then use hash function to index the table
	//then iterate through the vector at that index
	//if one pair already includes the keyword, then add one to the 'amount'
	//if the keyword doesn't exist, then append a new pair
	string validWord = makeValidWord(word);

	if (validWord != ""){
		int wordIndex = hash(validWord);
		//cout << "wordIndex:" << wordIndex << endl;
		vector<pair<string, int>> wordVector = table[wordIndex];
		
		bool wordInTable = false;
		//cout << wordVector.size() << endl;
		// if (wordVector.size() == 0){
			
		// }
		for (size_t i = 0; i < wordVector.size(); i++){
			if (wordVector.at(i).first == validWord){
				wordInTable = true;
				table[wordIndex].at(i).second++;
				return table[wordIndex].at(i).second;
				// wordVector.at(i).second++;
				// return wordVector.at(i).second;
			}
		}
		if (!wordInTable){
			//cout << "INSIDE IF" << endl;
			pair<string, int> p(validWord, 1);
			table[wordIndex].push_back(p);
			//cout << wordVector.size() << endl;
		}
		return 1;
	}
	return 0;
}

int WordCount::decrWordCount(const std::string & word) {
	//first put word through hash function
	//then use hash function to index the table
	//then iterate through the vector at that index
	//if one pair already includes the keyword, then add one to the 'amount'
	//if the keyword doesn't exist, then append a new pair
	string validWord = makeValidWord(word);
	int wordIndex = hash(validWord);
	vector<pair<string, int>> wordVector = table[wordIndex];
	
	//bool wordInTable = false;
	//cout << "size: " << wordVector.size() << endl;
	for (size_t i = 0; i < wordVector.size(); i++){
		//cout << "Hello" << endl;
		if (wordVector.at(i).first == validWord){
			//wordInTable = true;
			//cout << "Count: " << wordVector.at(i).second << endl;
			if (wordVector.at(i).second > 1){
				table[wordIndex].at(i).second--;
				return table[wordIndex].at(i).second;
				// wordVector.at(i).second--;
				// return wordVector.at(i).second;
			}
			else if ((wordVector.at(i).second == 1)){
				table[wordIndex].erase(table[wordIndex].begin() + i);
				//wordVector.erase(wordVector.begin() + i);
				return 0;
			}
		}
	}

	return -1;
}

bool WordCount::isWordChar(char c) {
	if (isalpha(c) || c == '\'' || c == '-'){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(const std::string & word) {
	string validWord = "";
	char c;

    bool isAlpha = false;
	int validStartingIndex = 0;
	int validEndingIndex = 0;

	for (size_t i = 0; i < word.size(); i++){
		if (isalpha(word.at(i))){
            isAlpha = true;
			validStartingIndex = i;
			break;
		}
	}

    if (!isAlpha){
        return "";
    }
    
	for (int i = word.size() - 1; i >= 0; i--){
		if (isalpha(word.at(i))){
			validEndingIndex = i;
			break;
		}
	}

	for (int i = validStartingIndex; i < validEndingIndex + 1; i++){
		c = word.at(i);

		if (isalpha(c)){
			validWord+=(tolower(c));
		}
		else if (c == '\'' || c == '-'){
			validWord+=(c);
		}
	}

	return validWord;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	//this is simple
	//first define an overloaded comparison operator that would allow the set to store the pairs in alphabetical order (maybe even define this operator for a 'Pair' object itself)
	//then as we're iterating through the set, store each element (line by line) in the given file

	vector<pair<string, int>> wordVector;
	vector<pair<string, int>> dumpVector;

	for (size_t i = 0; i < CAPACITY; i++){
		wordVector = table[i];
		for (auto wordPair: wordVector){
			dumpVector.push_back(wordPair);
		}
	}
	sort(dumpVector.begin(), dumpVector.end(), comp1);

	for (auto wordPair: dumpVector){
		out << wordPair.first << "," << wordPair.second << "\n";
	}
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	//iterate through the hash table and store it into a binary search tree (set i think)
	//define overloaded comparison operators that allow ordering in terms of multiple objects (first by occurrences and then alphabetical order)
	//figure out how i implemented multiple operators for different data values in pa02 last year!!

	vector<pair<string, int>> wordVector;
	vector<pair<string, int>> dumpVector;

	for (size_t i = 0; i < CAPACITY; i++){
		wordVector = table[i];
		for (auto wordPair: wordVector){
			dumpVector.push_back(wordPair);
		}
	}
	sort(dumpVector.begin(), dumpVector.end(), comp2);

	for (auto wordPair: dumpVector){
		out << wordPair.first << "," << wordPair.second << "\n";
	}
}

void WordCount::addAllWords(const std::string& text) {
	//the main thing with this function is implementing proper parsing (since we already have the increment function)
	//iterate through each character (append it to a string object) until we reach a whitespace, comma, or \n and \t (for these last two, we can check if a given character is a backslash, and if it is, we check if the next character is t or n, and if not, we append it to the string object, and if it is either n or t, we skip it and go to the next character)
	//so once we hit one of the above four symbols, we add the word to the hash table using the increment function and then reset the string to continue
	//can use if...else chain to check for the value of the characters
	string word = "";

	for (int i = 0; i < text.length(); i++){
		cout << text.at(i) << endl;
		if (text.at(i) == ' ' || text.at(i) == ','){
			incrWordCount(word);
			cout << word << endl;
			word = "";
		}
		else{
			if (text.at(i) == '\\'){
				if (i + 1 < text.length()){
					if (text.at(i + 1) == 't' || text.at(i + 1) == 'n'){
						incrWordCount(word);
						cout << word << endl;
						word = "";
					}
				}
			}
			else{
				word+=(text.at(i));
			}
		}
	}
	incrWordCount(word);
}