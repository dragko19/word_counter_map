#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "word_counter.h"
using namespace std;
using namespace std::chrono;

template <class Typ>
void compare_values(const string& msg, const Typ& act, const Typ& prop)
{
	if (act != prop)
	{
		cerr << msg << endl;
		cerr << "    Produced: " << act << endl;
		cerr << "Proper value: " << prop << endl;
	}
}

int main()
{
	vector<pair<string,int>> tst {
		{ "", 0 },
		{ "Alina ", 1 },
		{ "hElEnA HaLiNa helena ", 2 },
		{ "helena halina hanna halina helena ", 3 },
		{ "helena halina hanna halina helena halina ", 3 },
	};
	vector<pair<string, string>> prop {
		{ "[]", "[]" },
		{ "[[alina 1] ]", "[[alina 1] ]" },
		{ "[[halina 1] [helena 2] ]", "[[helena 2] [halina 1] ]" },
		{ "[[halina 2] [hanna 1] [helena 2] ]", "[[halina 2] [helena 2] [hanna 1] ]" },
		{ "[[halina 3] [hanna 1] [helena 2] ]", "[[halina 3] [helena 2] [hanna 1] ]" },
	};

	for (int i = 0; i < (int)tst.size(); ++i)
	{
		ostringstream msg;
		msg << "Test " << i + 1;

		istringstream ss(tst[i].first);
		word_counter wc;
		wc.add_words(ss);

		compare_values(msg.str(), wc.size(), tst[i].second);

		ostringstream os;
		os << wc;
		compare_values(msg.str(), os.str(), prop[i].first);
		cout << wc << endl;
	}

    
	// testy desciter na ma³ych danych
	
    string itst = "uno due due tre tre tre quattro quattro quattro quattro";
    stringstream ss(itst);
    word_counter it_test;
    it_test.add_words(ss);
	

    // sprawdzmy najpierw, czy zawartoœæ licznika jest poprawna
    // niestandardowo poœmiecê tym razem na konsoli
    cout << "\nCaly licznik:\n";
    cout << it_test << endl;
	
	
    // zacznijmy od sprawdzenia, czy funkcja begin() z word_counter
    // daje s³owo o maksymalnej liczbie wyst¹pieñ


    word_counter::desciter itt = it_test.descbegin();
    cout << "\nIterator po begin:\n";
    cout << *itt << endl;
	
    // jesli jest [quattro 4] można spróbować całości
    int pos = 0;
	word_counter::desciter itt2 = it_test.descend();

    while (itt != it_test.descend())
    {
        cout << pos << ": " << *itt << endl;
        ++itt;
        ++pos;
    }

	

    // teraz można spróbować z większym tekstem
    ifstream is("TheVoyageofBeagle.txt");
    if (!is.good())
    {
        cout << "Smuteczek :(\n";
        return -1;
    }

    high_resolution_clock::time_point start = high_resolution_clock::now();
    word_counter wc;
    wc.add_words(is);

    high_resolution_clock::time_point now = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(now - start);
    cerr << "Counting in " << time_span.count() << " seconds." << endl;

	cout << "\n\nThe Voyage of Beagle by Charles Darwin most frequent words\n\n";
	int limit = 20;
	int disp_count = 0;
    word_counter::desciter it = wc.descbegin();
    while (it != wc.descend())
    {
        cout << *it << endl;
        ++it;
        ++disp_count;
        if (disp_count >= limit)
            break;
    }
    
	system("pause");
    return 0;
}
