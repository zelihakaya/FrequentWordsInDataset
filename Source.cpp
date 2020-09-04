#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <Windows.h>

#include "hasht.h"

using namespace std;

long long now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

//time checkpoint for benchmarking
void cp() {
	long long t = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - now;

	cout << endl << "Total Elapsed Time: " << t/1000 <<" seconds " << t%1000 << " miliseconds" << endl;
	now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

//database and stopword file location


//string dbloc = "./data/training.1600000.processed.noemoticon.csv";
//string stopwordloc = "./data/stopwords.txt";
string dbloc = "D:/4/kuantum/VS/prohe/data/training.1600000.processed.noemoticon.csv";
string stopwordloc = "D:/4/kuantum/VS/prohe/data/stopwords.txt";


//Open the file and write it into given string parsed
void openandparse(string &dataset, string fileloc, bool isStopwordFile) {
	ifstream data;
	data.open(fileloc);

	dataset = "";

	string::iterator parser;


	if (data.is_open())
	{
		string temp;

		while (getline(data, temp)) {

			//if the input file is db, start after the id, date, username info
			//and skip 2 quotation marks to start from the tweet
			if (!isStopwordFile) {
				parser = temp.begin() + 60;

				int quotecount = 0;
				while (quotecount < 2)
				{
					if (*parser == '"')
						quotecount++;

					parser++;
				}
			}else parser = temp.begin();

			//if a *it symbol add space to dataset go next char, turn non-symbol char to lowercase, add char to dataset, for every char
			for (parser; parser != temp.end(); parser++)
			{
				if (*parser != '"' &&
					*parser != ':' &&
					*parser != '.' &&
					*parser != '-' &&
					*parser != '_' &&
					*parser != '*' &&
					*parser != '!' &&
					*parser != '/' &&
					*parser != '?' &&
					*parser != ',' &&
					*parser != '(' &&
					*parser != ')' &&
					*parser != '~' &&
					*parser != '#' &&
					*parser != '&' &&
					*parser != ';' &&
					*parser != '@') {

					*parser |= 0x20;// lowercaser
					dataset += *parser;
				}
				else
					dataset += " ";

			}

			dataset += " "; //last space after the line
		}
	}
	else cout << "Unable to open file";

}

//insert words to table- old version, hasht::betterfeed() is better
void feedTable(hasht &table,string &data) {

	string::iterator it;
	it = data.begin();

	string temp = "";
	for (it; it != data.end(); it++)
	{
		if (*it == ' ') {

			if (temp != "") {
				table.insert(temp);
			}
			temp = "";

		}
		else {
			temp += *it;
		}
	}

}

void main() {

	string dataset;
	string stopwords;
	
	openandparse(dataset, dbloc,0);
	openandparse(stopwords, stopwordloc,1);

	hasht table(dataset.length()/83);

	table.betterfeed(dataset);
	//feedTable(table, dataset);

	table.stopwordCleaner(stopwords);

	table.heapSort(table.gettablesize());


	table.print(20);
	cp();

	Sleep(10000);
}
