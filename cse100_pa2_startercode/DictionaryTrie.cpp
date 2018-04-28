#include "util.h"
#include "DictionaryTrie.h"

/* empty constructor */
TrieNode::TrieNode() {}

/*creates a new Node */
TrieNode* newNode(char letter) {
	TrieNode* temp = new TrieNode;
	temp->key = letter;
	temp->isWord = false;
	temp->frequency = 0;
	temp->leftChild = temp->middleChild = temp->rightChild = NULL;
	return temp;
}

/*helper method for insert*/
bool insertNode(std::string word, TrieNode* start, unsigned int freq) {

	unsigned int index = 0;
	TrieNode * insNode = start;

	char nextChar;
	char currChar = word.at(index);

	if(word.length() == 1) {
		
		insNode->isWord = true;
		insNode->frequency = freq;
		return true;
	}
	
	/*inserts the length of the word*/
	while(index < (word.length() - 1)) {
		index++;	
		nextChar = word.at(index);
	
		/* create the next Node */
		TrieNode* insertNextNode = newNode(nextChar);
		insNode->middleChild = insertNextNode;

		/* checks that the node isn't the last one*/	
		if(index != (word.length() - 1)) 
		{
			currChar = nextChar;
			insNode = insertNextNode;
		} else {
			
			/*if this is the last node, mark it as a word */
			insertNextNode->isWord = true;
			insertNextNode->frequency = freq;
		}
	}	
	return true;


}


/* helper method to change the frequency of a word */
TrieNode* findNode(std::string word, TrieNode* start, unsigned int freq) {

  
  if(word.size() == 0) { return NULL; }

  /* check for special characters*/
  for(unsigned int i = 0; i < word.size(); i++) {
	/*space bar */
	if(word.at(i) == 32) { }

	/*97 = 'a', 122 = 'z'*/
	else if(word.at(i) < 97) { return NULL; }
	else if(word.at(i) > 122) { return NULL; }		
  }

  int index = 0;
  char currChar = word.at(index);
  TrieNode * currNode = start;
  

  while(currNode){
	if(currNode->key == currChar) 
 	{
		index++;
		if(index < word.size())  
		{
			currChar = word.at(index);
			currNode = currNode->middleChild;
		} else 
		{
			return currNode;
		}
	} else if(currChar < currNode->key && currNode->leftChild) 
 	{
		currNode = currNode->leftChild;
	} else if(currChar > currNode->key && currNode->rightChild) 
	{
		currNode = currNode->rightChild;
	} else {
		currNode = NULL;
	}
  }
	return NULL;
}
  /* looks for the word in the tree*/
/*  while(index <= word.size() -1){
 	 if(checkChar == currChar)
 	 {
		if(currNode->middleChild) 
		{
			currNode = currNode->middleChild;
			checkChar = currNode->key; 
			index++;
			currChar = word.at(index);
		}
		return currNode;
	} else if(currChar < checkChar && currNode->leftChild) 
 	{
		currNode = currNode->leftChild;
		checkChar = currNode->key;
	} else if(currChar > checkChar && currNode->rightChild) 
	{
		currNode = currNode->rightChild;
		checkChar = currNode->key;
	} else
	{
		return NULL;
	}

  }


  checks to make sure the last character truly is the last character in the word 
  if (checkChar == currChar) {
	  return currNode; 

  } else { return NULL; }


}
*/
void TrieNode::deleteAllNodes(TrieNode* start) {

	if(!start) { return; }

	if(start->leftChild)
	{ start->deleteAllNodes(start->leftChild); }

	if(start->rightChild) 
	{ start->deleteAllNodes(start->rightChild); }
	
	if(start->middleChild)
	{ start->deleteAllNodes(start->middleChild); }
	delete start;

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
	//if the string is empty
	if(word.size() == 0) { return false; }

	unsigned int index = 0;
	char currChar = word.at(index);

	//if there's no root, create the root
	if(!root) {
		root = newNode(currChar);
		insertNode(word, root, freq);	
		return true;	
	}
	
	
	//this changes the frequency of a duplicate word OR it'll mark
	//a substring as a word 
	TrieNode* changeFreqNode = findNode(word, root, freq);	
	if(changeFreqNode)
	{ 
		changeFreqNode->frequency = freq;
	 	if(!changeFreqNode->isWord) {
	  		changeFreqNode->isWord = true;
			return true;
		}
		return false;
	} 
	
	// check for special characters
	for(unsigned int i = 0; i < word.size(); i++) {
		//space bar
		if(word.at(i) == 32) { }

		//97 = 'a', 122 = 'z'
		else if(word.at(i) < 97) { return false; }
		else if(word.at(i) > 122) { return false; }		
	}
	
	std::string copyWord = word;


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
			insertNode(copyWord, currNode->rightChild, freq);
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
			insertNode(copyWord, currNode->leftChild, freq);
			return true;
		}
	}

	/*if the character to insert is the same as the current key*/
	else if(currNode->key == currChar)
	{

		/*if the currNode has a middle child already, we recurse with the middle Child,
		but we also want to only search for the rest of the word*/
		if(currNode->middleChild)
		{
			index++;
			/*if the word is over, we're done. */
			if(index >= word.size()) { return false; }
			currChar = word.at(index);
			copyWord.erase(0,1);
			currNode = currNode->middleChild;
		} 
		/* if there's no middle child yet, this is it */
		else {
		
	//		TrieNode * insNode = newNode(currChar);
	//		currNode->middleChild = insNode;
			insertNode(copyWord, currNode, freq);
			return true;
		}
	}
	}
	

	return false;		
	
}
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	TrieNode* wasItFound = findNode(word, root, 0);
	if(wasItFound) {
		return wasItFound->isWord;
	}
	return false;

}
  /* if there is no root */
/*  if(!root) { return false; }
  
  if(word.size() == 0) { return false; }
  unsigned int index = 0;
  
  // check for special characters
  for(unsigned int i = 0; i < word.size(); i++) {
	//space bar
	if(word.at(i) == 32) { }

	//97 = 'a', 122 = 'z'
	else if(word.at(i) < 97) { return false; }
	else if(word.at(i) > 122) { return false; }		
  }

  char currChar = word.at(index);
  char checkChar = this->root->key;
  TrieNode * currNode = this->root;

  * checks to find the word in the tree 
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

  }


 * this checks that the last character is truly the same as the last character of the word *
  if (checkChar == currChar) {
  return currNode->isWord; } else { return false; }
}
*/
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

void DictionaryTrie::deleteTree() {

	root->deleteAllNodes(root);
	delete this->root;
	delete this;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
