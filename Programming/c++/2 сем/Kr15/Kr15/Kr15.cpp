// Kr15.cpp: определяет точку входа для консольного приложения.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
using namespace std;

multimap <string, pair<string, int>>::iterator it;

int main()
{
	ifstream DATA("D.TXT");
	ifstream QUERY("QUERY.TXT");
	ofstream ANSWER("ANSWER.TXT");

	multimap <string, pair<string, int>> students;

	string actor, movie;
	int year;

	if (DATA.is_open())
	{
		while (getline(DATA, actor, ','))
		{
			getline(DATA, movie, ',');
			DATA >> year;

			students.insert(make_pair(actor, (make_pair(movie, year))));
			DATA.ignore();
		}
	}


	char answer;
	string aactor;
	int ayear;
	while (QUERY >> answer)
	{
		switch (answer)
		{
		case '1':
		{
			QUERY.ignore();
			getline(QUERY, aactor);

			pair<multimap <string, pair<string, int>>::iterator, multimap <string, pair<string, int>>::iterator> inf;
			inf = students.equal_range(aactor);
			if (inf.first != students.end())
			{
				for (it = inf.first; it != inf.second; ++it)
					ANSWER << it->second.first << " " << it->second.second << endl;
			}
			else
				ANSWER << "ad1" << endl;
			break;
		}
		case '2':
		{
			QUERY.ignore();
			QUERY >> ayear;
			int count = 0;
			for (auto it = students.begin(); it != students.end(); ++it)
				if (ayear == it->second.second)
					count++;
			if (count != 0)
				ANSWER << count << endl;
			else
				ANSWER << "as2" << endl;
			break;

		}
		case '3':
		{
			set< pair<string, int>> para;
			for (auto it = students.begin(); it != students.end(); ++it)
				para.insert(make_pair(it->first, it->second.second));
			for (auto it = para.begin(); it != para.end(); ++it)
				ANSWER << it->first << " " << it->second << endl;
			break;
		}
		}
	}
	return 0;
}