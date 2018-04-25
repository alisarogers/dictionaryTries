#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>
#include <string>

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  	std::pair<std::set<std::string>::iterator,bool> inserted;
	return htbl.insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{

	std::set<std::string>::iterator found;
//	found = htbl.find(word);
	
	if(htbl.find(word) == htbl.end())
	{	
		return false;
	} else { return true; }
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){}
