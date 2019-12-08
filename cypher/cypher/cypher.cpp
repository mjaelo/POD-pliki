// cypher.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <bitset>  
#include <vector> 
using namespace std;

int main()
{
	
	try
	{
		/*ofstream off("zera.txt");
		for (int i = 0; i < 20000; i++)
		off << 0;*/


		string key,text,give;
	vector<bitset<8>>keys, texts;
		//podawanie klucza
		cout << "podaj nazwe pliku z kluczem: ";
		cin >> give;
		ifstream getkey(give + ".txt");
		getkey >> key;
		if (key.size() < 1) { cout << "file not found or empty"; throw("bad"); }
		cout << "klucz: ";
		string temp = "";
		for (int i = 0; i < key.size(); i++)
		{
			if ((i + 1) % 8 == 0 || i == key.size() - 1)
			{
				temp += key[i];
				keys.push_back(bitset<8>(temp));
				cout << temp << " " << char(bitset<8>(temp).to_ulong()) << " ";
				temp = "";
			}
			else temp += key[i];
		}
		cout << "\n";

		//podawaie textu
		cout << "podaj nazwe pliku z tekstem: ";
		cin >> give;
		ifstream data(give + ".txt");
		data >> text;
		if (text.size() < 1) { cout << "file not found or empty"; throw("bad"); }
		cout << "text:  ";
		if (give[0] == 'b')
		{
			temp = "";
			for (int i = 0; i < text.size(); i++)
			{
				if ((i + 1) % 8 == 0 || i == text.size() - 1)
				{
					temp += text[i];
					texts.push_back(bitset<8>(temp));
					cout << temp << " " << char(bitset<8>(temp).to_ulong()) << " ";
					temp = "";
				}
				else temp += text[i];
			}

		

			//przedluzanie klucza
			int i = 0;
			cout << "klucz2:";
			while (keys.size() < texts.size())
			{
				keys.push_back(keys[i]);
				cout << keys[i] << " " << char(keys[i].to_ulong()) << " ";
				i++;
			}
			cout << "\n";

			//szyfrowanie
			cout << "szyfr: ";
			for (int i = 0; i < texts.size(); i++)
			{
				bitset<8> k = keys[i], t = texts[i];
				for (int j = 0; j < 8; j++)
				{
					if (t[j] == k[j])
						t[j] = 0;
					else
						t[j] = 1;
				}
				texts[i] = t;
				text[i] = char(texts[i].to_ulong());
				cout << texts[i] << " " << text[i] << " ";
			}
			string btext = "";
			for (int i = 0; i < texts.size(); i++)
				btext += texts[i].to_string();
			ofstream off("bszyfr.txt");
			off << btext;
		}
		else
		{
			for (int i = 0; i < text.size(); i++)
			{
				texts.push_back(bitset<8>(text[i]));
				cout << texts[i] << " " <<text[i] << " ";
			}


			cout << "\n";

			//przedluzanie klucza
			int i = 0;
			cout << "klucz2:";
			while (keys.size() < texts.size())
			{
				keys.push_back(keys[i]);
				cout << keys[i] << " " << char(keys[i].to_ulong()) << " ";
				i++;
			}
			cout << "\n";

			//szyfrowanie
			cout << "szyfr: ";
			for (int i = 0; i < texts.size(); i++)
			{
				bitset<8> k = keys[i], t = texts[i];
				for (int j = 0; j < 8; j++)
				{
					if (t[j] == k[j])
						t[j] = 0;
					else
						t[j] = 1;
				}
				texts[i] = t;
				text[i] = char(texts[i].to_ulong());
				cout << texts[i] << " " << text[i] << " ";
			}
			ofstream off("szyfr.txt");
			off << text;

		}
		
	}
	catch (exception e) { cout <<"zlapano blad: "<< e.what(); }
}