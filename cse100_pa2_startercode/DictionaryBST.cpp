#include "util.h"
#include "DictionaryBST.h"
#include <set>
#include <string>

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
//	std::set<std::string> bst;
	//this = &bst;
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
	std::pair<std::set<std::string>::iterator,bool> inserted;
	inserted = bst.insert(word);
	return inserted.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
	std::set<std::string>::iterator found;
	found = bst.find(word);
	
	if(found == bst.end()) {
		return false;
	} else { return true; }

}

/* Destructor */
DictionaryBST::~DictionaryBST(){
//	delete this;
}
