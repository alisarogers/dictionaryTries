#include "util.h"
#include "DictionaryTrie.h"


TrieNode::TrieNode() {}

TrieNode::TrieNode(char letter) {
	key = letter;
	isWord = false;
	leftChild = middleChild = rightChild = nullptr;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  
	// need to add in a check for find
	if(!(this->find(word))) { return false; }

	//if the string is empty
	if(word.size() == 0) { return false; }
	
	int index = 0;
	char currChar = word.at(index);
	char nextChar;
	TrieNode insertNode = TrieNode(currChar);
	
	//if there's no root, create the root
	if(!root) {
		root = &insertNode;	
		//while the character we're examining isn't the last one
		while(index < (word.length() - 1)) {
			index++;	
			nextChar = word.at(index);
	
			// create the next Node
			TrieNode insertNextNode = TrieNode(nextChar);
			insertNode.middleChild = &insertNextNode;
	
			if(index != (word.length() - 1)) 
			{
				currChar = nextChar;
			} else {
			
				insertNextNode.isWord = 1;
			}
		}	
	

	return true;	

	}

	//the root already exists
	if(root->key < currChar) {}


	if(root->key > currChar) {}

	if(root->key == currChar) {}

	

	return false;		
	
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  return false;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

/*
 * Return the most similar word of equal length to the query, based
 * on their Hamming distance. 
 * In case of ties, return the word with the highest frequency (you may
 * assume there will always be one should a tie happen.)
 * In case there isn't any word of equal length to the query in the
 * trie, return an empty string.
 */
std::string DictionaryTrie::checkSpelling(std::string query)
{
  return "";
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
