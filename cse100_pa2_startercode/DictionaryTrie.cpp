#include "util.h"
#include "DictionaryTrie.h"


TrieNode::TrieNode() {}

TrieNode* TrieNode::newNode(char letter) {
	TrieNode* temp = new TrieNode;
	temp->key = letter;
	temp->isWord = false;
	leftChild = middleChild = rightChild = NULL;
	return temp;
}

bool TrieNode::insertNode(std::string word, TrieNode* start) {

	unsigned int index = 0;
	char currChar = word.at(index);
	TrieNode* currNode = start;

	if(currChar == currNode->key) {
		index++;
		currNode = currNode->middleChild;		
		currChar = word.at(index);
	} else if(currChar == currNode->leftChild->key) 
	{
	} else if (currChar == currNode->rightChild->key)
	

	return false;
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
 
	return 	root->insertNode(word, root);

 
/*	// need to add in a check for find
	// TODO fix the freq
	if(this->find(word)) { return false; }

	//if the string is empty
	if(word.size() == 0) { return false; }
	
	unsigned int index = 0;
	char currChar = word.at(index);
	char nextChar;
	TrieNode * iisertNode = newNode(currChar);

	//if there's no root, create the root
	if(!root) {
		this->root = insertNode;	
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
				insertNode = insertNextNode;
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
*/	
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  /* if there is no root */
  if(!root) { return false; }
  unsigned int index = 0;
  
  char currChar = word.at(index);
  char checkChar = this->root->key;
  TrieNode * currNode = this->root;

  while(index < (word.size() - 1)){
  if(checkChar == currChar && currNode->middleChild) 
  {
	index++;
	currChar = word.at(index);
	currNode = currNode->middleChild;
  } else if(currChar == currNode->leftChild->key) 
  {
	index++;
	currChar = word.at(index);
	currNode = currNode->leftChild;
  } else if(currChar == currNode->rightChild->key) 
  {
	index++;
	currChar = word.at(index);
	currNode = currNode->middleChild;
  } else { return false; }
  }
  return currNode->isWord;
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
