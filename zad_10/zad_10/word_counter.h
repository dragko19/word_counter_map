#pragma once
#include <string>
#include <iostream>
#include <map>



class word_counter
{
	std::map<std::string, int> map_words;

public:

//****************************************************************

	class desciter
	{
		const std::map<std::string, int>& aparent;
		std::map<std::string, int>::const_iterator it;
		int upper_limit = std::numeric_limits<int>::max();
		void moveto(int upper_limit);		
	public:
		desciter(const std::map<std::string, int>& parent,
			const std::map<std::string, int>::const_iterator& cur)
			: aparent(parent)
		{
			if (cur != aparent.end())
			{
				it = cur;
				moveto(upper_limit);
			}
			else
				it = aparent.end();
		}
		const std::pair<std::string, int> operator*() const
		{ 
			return *it; 
		}
		desciter operator++();
		bool operator!=(const desciter& rha)
		{
			return it != rha.it;
		}


	};

//*************************************************************

	word_counter() {};
	~word_counter() {};

	int size() const { return map_words.size(); }

	std::istream& add_words(std::istream& words_stream);

	friend std::ostream& operator<< (std::ostream& os, const word_counter& mp);
	friend std::ostream& operator<< (std::ostream& os, const std::pair<std::string,int>& dt);

	desciter descbegin() const
	{
		return desciter(map_words, map_words.begin());
	}
	desciter descend() const
	{
		return desciter(map_words, map_words.end());
	}
};





