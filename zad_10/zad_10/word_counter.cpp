#include "word_counter.h"
#include <sstream>
#include <iostream>
#include <map>

std::istream& word_counter::add_words(std::istream& words_stream)
{
	std::string word;


	while (words_stream)
	{		
		word.clear();
		words_stream >> word;
		for (auto& ch : word)
		{
			ch = tolower(ch);
		}
		if (word == "")
			continue;
		map_words[word]++;
	}

	return words_stream;
}

std::ostream& operator<< (std::ostream& os, const word_counter& mp)
{
	std::map<std::string, int> val = mp.map_words;
	os << '[';
	for (auto it = val.begin(); it != val.end(); it++)
		os << '[' << (*it).first << ' ' << (*it).second << "] ";
	return os << ']';
}

std::ostream& operator<< (std::ostream& os, const std::pair<std::string, int>& dt)
{
	return os << '[' << dt.first << ' ' << dt.second << ']';
}

void word_counter::desciter::moveto(int upper_limit)
{
		std::map<std::string, int>::const_iterator itter = aparent.begin(); // to itterate
		std::map<std::string, int>::const_iterator itter_mem = aparent.begin(); // to save itteration desirable result

		for (auto itt = aparent.begin(); itt != aparent.end(); itt++)
			if ((*itt).second < (*itter_mem).second)
				itter_mem = itt;

		const std::pair<const std::string, int> aparent_min = (*itter_mem); // min value of aparent

		if ((*it) == aparent_min)
		{
			it = aparent.end();
		}			
		else
		{
			for (int i = 0; i < aparent.size(); i++, itter++)
			{
				//std::cout << "Upper: " << upper_limit << " Itter.second: " << (*itter).second << std::endl;
				if ((*itter).second < upper_limit)
				{
					if ((*itter).second > (*itter_mem).second)
					{
						//std::cout << "I was here" << std::endl;
						itter_mem = itter;
					}
				}
			}
			it = itter_mem;
			word_counter::desciter::upper_limit = (*it).second;
		}	
}

word_counter::desciter word_counter::desciter::operator++()
{	
	std::map<std::string, int>::const_iterator temp = it;
	if (it == aparent.end())
	{
		std::cout << "You are on the end of map!" << std::endl;
	}
	else
	{	
		moveto(upper_limit);
	}
	
	return *this;
}

