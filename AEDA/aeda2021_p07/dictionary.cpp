#include <iostream>
#include <string>
#include <fstream>
#include "dictionary.h"
#include "bst.h"

using namespace std;

BST<WordMeaning> Dictionary::getWords() const {
    return words;
}

//TODO
bool WordMeaning::operator < (const WordMeaning &wm1) const {
    return this->word < wm1.getWord();
}

//TODO
void Dictionary::readDictionary(ifstream &f)
{
     string name, meaning;
     while (getline(f, name)){
         getline(f, meaning);
         WordMeaning* w = new WordMeaning(name, meaning);
         words.insert(*w);
     }
}

//TODO
string Dictionary::searchFor(string word) const
{
    BSTItrIn<WordMeaning> it(words);
    WordMeaning before = it.retrieve();
    while (!it.isAtEnd()){
        if (it.retrieve().getWord() == word) return it.retrieve().getMeaning();
        if (it.retrieve().getWord() > word){
            WordMeaning after = it.retrieve();
            throw WordInexistent(before, after);
        }
        else {
            before = it.retrieve();
            it.advance();
        }
    }
    throw WordInexistent(before, before);
}

//TODO
bool Dictionary::correct(string word, string newMeaning)
{
    BSTItrIn<WordMeaning> it(words);
    WordMeaning before = it.retrieve();
    while (!it.isAtEnd()){
        if (it.retrieve().getWord() == word) {
            words.remove(it.retrieve());
            WordMeaning* newW = new WordMeaning(word, newMeaning);
            words.insert(*newW);
            return true;
        }
        it.advance();
    }
    WordMeaning* newW = new WordMeaning(word, newMeaning);
    words.insert(*newW);
    return false;
}

//TODO
void Dictionary::print() const
{
    BSTItrIn<WordMeaning> it(words);
    while (!it.isAtEnd()){
        cout << it.retrieve().getWord() << endl << it.retrieve().getMeaning() << endl;
        it.advance();
    }
}

