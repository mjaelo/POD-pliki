// testy_losowosci.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//


#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <bitset>  
#include <vector>  
using namespace std;


bool monobit_test(string text)
{
	bool monobit = false;
	string temp = ""; int i0 = 0, i1 = 0;
	for (int i = 0; i < 20000; i++)
	{
		if (text[i] == '0')
		{
			i0++;
		}
		else i1++;
	}
	if (i1 < 10275 && i1>9275)
		monobit = true;

	return monobit;
}

bool poker_test(string text)
{
	bool poker = false; string s1 = text;
	vector<int> hex1 = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	string temp = ""; int tempi = 0;
	for (int i = 0; i < 20000; i++)
	{
		if ((i + 1) % 4 == 0)
		{
			temp += s1[i];
			for (int j = 0; j < 4; j++)
				if (temp[j] == '1')
				{
					tempi += pow(2, 3-j);
				}

			hex1[tempi]++;
			temp = "";
			tempi = 0;
		}
		else temp += s1[i];
	}
	int X = 0;
	for (int i = 0; i < 16; i++)
	{
		X += hex1[i] * hex1[i];
	}
	X = 16 * X; X -= 25000000;
	if (X < 10800 && X>230850)
		poker = true;

	return poker;
}

bool runs_test(string text)
{
	vector<int> min_run_limit = { 2315, 1114, 527, 240, 103, 103 };
	vector<int> max_run_limit = { 2685, 1386, 723, 384, 209, 209 };
	vector<int> run = { 0,0,0,0,0,0 };
	bool runs = true; char xi = text[0]; int len = 0;
	for (int i = 1; i < 20000; i++)
	{
		if (text[i] != xi)
		{
			if (len < 6)
				run[len]++;
			else
				run[5]++;
			len = 0;
		} 
		len++;
		xi = text[i];
	}
	for (int i = 0; i < 6; i++)
		if (run[i] < min_run_limit[i] || run[i] > max_run_limit[i])
			runs = false;

	return runs;
}

bool long_runs_test(string text)
{
	bool lruns = true; char xi = text[0]; int len = 0;
	for (int i = 1; i < 20000; i++)
	{
		if (text[i] != xi)
		{
			len = 0;
		}
		else len++;

		xi=text[i];
		if (len >= 26)
			lruns = false;
	}
	return lruns;
}



int main()
{

	string text = "", give;
	cout << "podaj nazwe pliku: ";
	cin >> give;
	//give = "n20000x1234M65961_0_9286_1_10714";
	/*
	n20000x1111M210141_0_8332_1_11668
	n20000x1234M65961_0_9286_1_10714
	n20000x1234M330261_0_9989_1_10011
	n20000x1234M387345_0_6668_1_13332
	n20000x4321M9597477_0_9902_1_10098
	n200000x1111M7273_0_102328_1_97672
	n200000x1234M387345_0_66668_1_133332
	n200000x1234M10869809
	*/
	ifstream getkey(give + ".txt");
	getkey >> text;
	if (text.size() < 1) { cout << "file not found or empty"; throw("error"); }
	if (text.size() < 20000) { cout << "tekst za krotki, zrestartuj program\n"; int("hej"); }

	bool monobit = monobit_test(text);
	bool poker = poker_test(text);
	bool runs = runs_test(text);
	bool lruns = long_runs_test(text);

	cout  << " \nmonobit: "<< monobit << "\npoker: " << poker  << " \nruns: " << runs << " \nlong runs: " << lruns << "\n\n";
	system("PAUSE");

}

// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
