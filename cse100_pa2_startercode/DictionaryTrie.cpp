#include "util.h"
#include "DictionaryTrie.h"


TrieNode::TrieNode() {}

TrieNode* newNode(char letter) {
	TrieNode* temp = new TrieNode;
	temp->key = letter;
	temp->isWord = false;
	temp->leftChild = temp->middleChild = temp->rightChild = NULL;
	return temp;
}

bool insertNode(std::string word, TrieNode* start) {

	unsigned int index = 0;
	TrieNode * insNode = start;
	char nextChar;
	char currChar = word.at(index);
	
	while(index < (word.length() - 1)) {
		index++;	
		nextChar = word.at(index);
	
		// create the next Node
		TrieNode* insertNextNode = newNode(nextChar);
		insNode->middleChild = insertNextNode;
	
		if(index != (word.length() - 1)) 
		{
			currChar = nextChar;
			insNode = insertNextNode;
		} else {
		
			insertNextNode->isWord = true;
		}
	}	
	return true;


}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
	
	this->root = NULL;
}
/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
 
	// TODO fix the freq
	if(this->find(word)) { return false; }

	//if the string is empty
	if(word.size() == 0) { return false; }

	// check for special characters
	for(int i = 0; i < word.size(); i++) {
		//space bar
		if(word.at(i) == 32) { }

		//97 = 'a', 122 = 'z'
		else if(word.at(i) < 97) { return false; }
		else if(word.at(i) > 122) { return false; }		
	}
	
	unsigned int index = 0;
	char currChar = word.at(index);
	std::string copyWord = word;
	TrieNode * insNode = newNode(currChar);

	//if there's no root, create the root
	if(!root) {
		root = insNode;
		insertNode(word, root);	
		return true;	
	}

	TrieNode* currNode = root;
	//the root already exists
	
	//if the character to insert is larger than the current key
	while(currNode) {
	if(currChar > currNode->key)
	{
		if(currNode->rightChild) 
		{				
			currNode = currNode->rightChild;
		} else {

	TrieNode * insNode = newNode(currChar);
			currNode->rightChild = insNode;
			insertNode(copyWord, currNode->rightChild);
			return true;
		}
	}
	
	//if the character to insert is less than the current key
	else if(currChar < currNode->key) 
	{
		if(currNode->leftChild)
		{
			currNode = currNode->leftChild;
		} else {
		
	TrieNode * insNode = newNode(currChar);
			currNode->leftChild = insNode;
			insertNode(copyWord, currNode->leftChild);
			return true;
		}
	}

	else if(currNode->key == currChar)
	{
		if(currNode->middleChild)
		{
			index++;
			if(index >= word.size()) { return false; }
			currChar = word.at(index);
			copyWord.erase(0,1);
			currNode = currNode->middleChild;
		} else {
	TrieNode * insNode = newNode(currChar);
			currNode->middleChild = insNode;
			insertNode(copyWord, currNode->middleChild);
			return true;
		}
	}
	}
	

	return false;		
	
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  /* if there is no root */
  if(!root) { return false; }
  
  if(word.size() == 0) { return false; }
  unsigned int index = 0;
  
  // check for special characters
  for(int i = 0; i < word.size(); i++) {
	//space bar
	if(word.at(i) == 32) { }

	//97 = 'a', 122 = 'z'
	else if(word.at(i) < 97) { return false; }
	else if(word.at(i) > 122) { return false; }		
  }

  char currChar = word.at(index);
  char checkChar = this->root->key;
  TrieNode * currNode = this->root;

  while(index < (word.size() - 1)){
  if(checkChar == currChar && currNode->middleChild) 
  {
	index++;
	currChar = word.at(index);
	currNode = currNode->middleChild;
	checkChar = currNode->key;
  } else if(currChar < checkChar && currNode->leftChild) 
  {
	checkChar = currNode->leftChild->key;
	currNode = currNode->leftChild;
  } else if(currChar > checkChar && currNode->rightChild) 
  {
	checkChar = currNode->rightChild->key;
	currNode = currNode->rightChild;
  } else { return false; }

//  if(!currNode) { return false; }
  }

  if (checkChar == currChar) {
  return currNode->isWord; } else { return false; }
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
