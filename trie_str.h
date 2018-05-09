#include <string>


const size_t ALPHABET_SIZE = 26; //for english words

struct TrieNode
{
	bool isEndOfWord;
	TrieNode *children[ALPHABET_SIZE];

	TrieNode():
		isEndOfWord(false)
	{
		for (size_t i = 0; i < ALPHABET_SIZE; ++i)
			children[i] = nullptr;
	}
	~TrieNode()
	{
		//TODO: clean allocated memory
	}

	void insert(const std::string& key)
	{
		TrieNode* iterator = this;
		for (size_t i = 0; i < key.length(); ++i)
		{
			size_t index = key[i] - 'a';
			if (!iterator->children[index])
				iterator->children[index] = new TrieNode;
			
			iterator = iterator->children[index];
		}
		iterator->isEndOfWord = true;
	}

	bool search(const std::string& key)
	{
		TrieNode* current = this;
		for (size_t i = 0; i < key.length(); ++i)
		{
			size_t index = key[i] - 'a';
			if (!current->children[index])
				return false;

			current = current->children[index];
		}

		return (current != nullptr && current->isEndOfWord);
	}

};


