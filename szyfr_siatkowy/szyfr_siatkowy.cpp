

// branie siatki i danych z pliku
// pytanie sie kroki i sposob siatki na poczatku
// blad przy szyfrowaniu tab > 4x4: obcinanie ostatniej czesci danych
// zle wyswietlanie tablicy przy odszyfrowywaniu
// zamiana cin na getline

#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;


void print_matrix(vector <vector<char>> mat,int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%c ", mat[i][j]);

		printf("\n");
	}
	printf("\n");
}

vector <vector<char>> rotate_matrix(vector <vector<char>> mat,int n,int ile)
{
	for (int x = 0;x < ile;x++)
	{
		for (int i = 0; i < n/2; i++)
		for (int j = i; j < n-1-i; j++)
		{
			//[y,x]
			char temp = mat[i][j];

			// move values from tr to tl 
			mat[i][j] = mat[n-1-j][i];

			// move values from br to tr
			mat[n-1-j][i] = mat[n - 1 - i][n - 1 - j];

			// move values from bl to br
			mat[n - 1 - i][n - 1 - j] = mat[j][n-1-i];

			// assign temp to left 
			mat[j][n - 1 - i] = temp;
		}
	}
	//displayMatrix(mat,n);
	return mat;
}

vector <vector<char>> string_to_matrix(string str,int n)
{
	vector <vector<char>> v;
	for (int i = 0; i < n; i++)
	{
		vector<char> c;
		for (int j = 0; j < n; j++)
		{
			c.push_back(str[i*n+j]);
		}
		v.push_back(c);
	}
	//displayMatrix(v,n);
	return v;
}

vector <vector<string>> string_to_matrix_nr(string str, int n)
{
	vector <vector<string>> v;
	for (int i = 0; i < n; i++)
	{
		vector<string> c;
		for (int j = 0; j < n; j++)
		{
			c.push_back(str[i*n + j]+"");
		}
		v.push_back(c);
	}
	//displayMatrix(v,n);
	return v;
}

string matrix_to_string(vector <vector<char>> v, int n)
{
	string str="";
	for (int i = 0; i < n; i++)
	{
		vector<char> c;
		for (int j = 0; j < n; j++)
		{
			str += v[i][j];
		}
	}
	//std::cout << str<<"\n";
	return str;
}


class net_cypher
{
	public:
	std::string base_data, begin, tab1, tab2, tab3, tab4;
	int size=1, s4, wymiar;
	bool krok = false, manual_s=false, manual_d=false;

	vector <vector<char>> v, v1, v2, v3, v4, secret_data;
	vector<vector<int>> siatka;

	void start();
	void give_data();
	void write_in_net();
	vector<vector<int>> make_net();
	void decypher();
	void setup();
};

void net_cypher::give_data()
{
	if(manual_d)
	{ 
		base_data = "";
		cout << "podaj dane do zaszyfrowania, zakoncz podajac \"end\"\n";
		string t="";
		while (t != "end")
		{
			cin >> t;
			if(t != "end")
			base_data += t;
		}
	}

	size = base_data.size();
		wymiar = sqrt(size);
	
	if(size>1)
	while(wymiar*wymiar != size||wymiar%2!=0)
	{
		wymiar++;
		int n=wymiar*wymiar - size;
		for (int i = 0;i < n;i++)
			base_data += '-';
		size = base_data.size();
	}
}

vector<vector<int>> net_cypher::make_net()
{
	//4 tab z wartosciami 1-n
	tab1 = "", tab2 = "", tab3 = "", tab4 = "";
	for (int i = 1;i <= s4;i++)
		tab1 += to_string(i);
	tab2 = tab3 = tab4 = tab1;
	//obrocenie tych tablic
	if (wymiar != 1 && wymiar != 2)
	{
		v1 = string_to_matrix(tab1, wymiar / 2);
		v1 = rotate_matrix(v1, wymiar / 2, 0);
		tab1 = matrix_to_string(v1, wymiar / 2);

		vector <vector<char>> v2 = string_to_matrix(tab2, wymiar / 2);
		v2 = rotate_matrix(v2, wymiar / 2, 1);
		tab2 = matrix_to_string(v2, wymiar / 2);

		vector <vector<char>> v3 = string_to_matrix(tab3, wymiar / 2);
		v3 = rotate_matrix(v3, wymiar / 2, 2);
		tab3 = matrix_to_string(v3, wymiar / 2);

		vector <vector<char>> v4 = string_to_matrix(tab4, wymiar / 2);
		v4 = rotate_matrix(v4, wymiar / 2, 3);
		tab4 = matrix_to_string(v4, wymiar / 2);
	}

	//zrobienie z nich jednego, duzego matrix
	string big = "";int nr1, nr2, nr3, nr4;
	nr1 = nr2 = nr3 = nr4 = 0;
	for (int i = 1;i <= wymiar;i++)
		for (int j = 1;j <= wymiar;j++)
		{
			if (i <= wymiar / 2 && j <= wymiar / 2) { big += tab1[nr1]; nr1++; }
			if (i <= wymiar / 2 && j > wymiar / 2) { big += tab2[nr2]; nr2++; }
			if (i > wymiar / 2 && j <= wymiar / 2) { big += tab4[nr4]; nr4++; }
			if (i > wymiar / 2 && j > wymiar / 2) { big += tab3[nr3]; nr3++; }
		}

	v = string_to_matrix(big, wymiar);


	//stworzenie siatki	
	siatka.clear();
	if (!manual_s)
	{
		cout << "tablica numerow na siatke\n";
		print_matrix(v, wymiar);
		cout << "\nwspolzedne siatki\n";

		int nr = 1, x, y;
		while (nr <= s4)
		{
			x = rand() % wymiar;
			y = rand() % wymiar;
			if (v[y][x] == nr + '0')
			{
				cout <<"{"<< x+1 << " , " << y+1 << "}: " << v[y][x] << "\n";
				siatka.push_back({ x,y });
				nr++;
			}
		}
	}
	else
	{
		int nr = 1, x=0, y=0;
		while (nr<=s4)
		{
			system("cls");
			cout << "tablica numerow na siatke\n";
			print_matrix(v, wymiar);
			cout << "podaj wspolrzedne {x,y} numeru "<<nr<<"\n";
			cin >> x>> y;
			x--;y--;
			if (v[y][x] == nr + '0')
			{
				//cout << x << " , " << y << ": " << v[y][x] << " /" << nr << "\n";
				siatka.push_back({ x,y });
				nr++;
			}
		}
	}
	return siatka;
}
	
void net_cypher::write_in_net() 
{
	int nr=0;
	string komunikat = "";
	vector <vector<char>> tempsiatka=secret_data;
	for (int i = 0;i < 4;i++)
	{
		//wpisanie danych w siatke od lewej do prawej
		komunikat = "";
		for(int x=0;x<wymiar;x++)
		{
			for(int y=0;y<wymiar;y++)
			{
				vector<int> temp = { x,y };
				for (int j=0;j < siatka.size();j++)
					if(temp==siatka[j])
					{ 
						secret_data[x][y]=base_data[nr];
						tempsiatka[x][y] = 'X';

						if (krok)
						{
							komunikat+= "{" +to_string( y + 1)+ "," +to_string( x + 1)+ "} " +secret_data[x][y] + "\n";
						}
						nr++;
					}
			}
		}
		
		if(krok || i==0)
				{
					system("cls");
					cout << "SZYFROWANIE\n\n";
					cout << "siatka\n";
					print_matrix(tempsiatka, wymiar);
				}	
		//obrocenie siatki
		int nr2 = 0;		
		tempsiatka = rotate_matrix(tempsiatka, wymiar, 1);
		for (int x = 0;x < wymiar;x++)
			for (int y = 0;y < wymiar;y++)
				if (tempsiatka[x][y] != '-')
				{ 
					siatka[nr2] = { x,y };
					nr2++;
				}
		if (krok)
		{
			cout << "szyfr\n";		print_matrix(secret_data, wymiar);
			cout << komunikat+"\n";
			cout << "przed szyfrem:     " << begin << "\n";
			cout << "zaszyfrowane dane: " << matrix_to_string(secret_data, wymiar) << "\n";
			system("PAUSE");
		}
		
	}
}

void net_cypher::decypher()
{
	base_data = "";
	//danie siatki
	vector <vector<char>> tempsiatka;
	string t = "";
	for (int x = 0;x < wymiar;x++)
		for (int y = 0;y < wymiar;y++)
		{
			vector<int> temp = { y,x };
			bool ok = false;
			for (int j = 0;j < siatka.size();j++)
				if (temp == siatka[j])
				{
					t += "X";
					ok = true;
				}
			if(!ok)t += '-';
		}
	tempsiatka = string_to_matrix(t, wymiar);

	for (int i = 0;i < 4;i++)
	{
		//obrocenie siatki
		int nr2 = 0;
		tempsiatka = rotate_matrix(tempsiatka, wymiar, 1);
		for (int x = 0;x < wymiar;x++)
			for (int y = 0;y < wymiar;y++)
				if (tempsiatka[x][y] != '-')
				{
					siatka[nr2] = { x,y };
					nr2++;
				}

		if (krok)
		{
			system("cls");
			cout << "ODSZYFROWANIE\n\n";
			cout << "siatka\n";		print_matrix(tempsiatka, wymiar);
			cout << "szyfr\n";		print_matrix(secret_data, wymiar);
		}

		//wpisanie danych w siatke
		string temp_base = "";
		for (int x = 0;x < wymiar;x++)
		{
			for (int y = 0;y < wymiar;y++)
			{
				vector<int> temp = { y,x };
				for (int j = 0;j < siatka.size();j++)
					if (temp == siatka[j])
					{
						if (krok)
						cout << "{" << y+1 << "," << x+1 << "} " << secret_data[x][y] << "\n";
						temp_base += secret_data[x][y];
					}
			}
		}
		base_data = temp_base+base_data;

		if(krok)
		{ 
			cout << "\n";
			cout << "przed szyfrem:     " << begin << "\n";
			cout << "zaszyfrowane dane: " << matrix_to_string(secret_data,wymiar)<< "\n";
			cout << "odszyfrowane dane: " << base_data << "\n";
			if (i!=3)system("PAUSE");
		}
	}

}

void net_cypher::setup()
{
	system("cls");
	cout << "SETUP\n\n";
	cout << "Czy chcesz zobaczyc prace krokowa?\n 1- tak, 0- nie\n";
	string kr = "";
	while (kr != "1"&&kr != "0")
	{
		cin >> kr;
	}
	krok = stoi(kr);

	cout << "\nPodaj sposob generacji siatki\n 1- manualny, 0- losowo wygenerowany\n";
	kr = "";
	while (kr != "1"&&kr != "0")
	{
		cin >> kr;
	}
	manual_s = stoi(kr);

	cout << "\nPodaj sposob podawania danych\n 1- manualny, 0- z pliku\n";
	kr = "";
	while (kr != "1"&&kr != "0")
	{
		cin >> kr;
		if (kr == "0")
		{
			string slowo;
			cout << "Podaj nazwe pliku\n";
			cin >> slowo;
			std::ifstream plik;
			plik.open(slowo);
			base_data = "";
			if(plik.good())
			{
				 while(plik.eof()!=true)
				 { 
					plik >> slowo;
					base_data += slowo; 
				 }
			}
			else
			{
				cout << "nie znaleziono pliku\n\n";
				kr = "error";
				cout << "Podaj sposob podawania doanych\n 1- manualny, 0- z pliku\n";
			}
		}
	}
	manual_d = stoi(kr);
}

void net_cypher::start() 
{
	while (true)
	{
		
		try 
		{
			//pytania o setup
			setup();


			//podanie danych
			system("cls");
			give_data();
			begin = base_data;
			cout << "tablica " + to_string(wymiar) + "x" + to_string(wymiar) + "\n";
			print_matrix(string_to_matrix(base_data, wymiar), wymiar);
			size = base_data.size();
			s4 = size / 4;
			system("PAUSE");

			//stworzenie siatki i szyfrowanie
			system("cls");
			string temp = "";
			for (int i = 0;i < size;i++)
				temp += '-';
			secret_data = string_to_matrix(temp, wymiar);

			siatka = make_net();
			system("PAUSE");
			write_in_net();

			//wyswietlenie zaszyfrowanych danych
			string wynik = matrix_to_string(secret_data, wymiar);

			if (!krok)
			{
				cout << "zaszyfrowane dane:\n";
				print_matrix(secret_data, wymiar);
				std::cout << "przed szyfrem:     " << begin << "\n";
				std::cout << "zaszyfrowane dane: " + wynik << "\n";
				system("PAUSE");
			}

			// odszyfrowanie

			decypher();
			if (!krok)
			{
				system("cls");
				cout << "ODSZYFROWANIE\n\n";
				cout << "przed szyfrem:     " << begin << "\n";
				cout << "zaszyfrowane dane: " << matrix_to_string(secret_data, wymiar) << "\n";
				cout << "odszyfrowane dane: " << base_data << "\n";

			}
			if (begin == base_data)
				cout << "odszyfrowanie zakonczone sukcesem\n";
			else
				cout << "odszyfrowanie zakonczone z bledami\n";
			system("PAUSE");
		}
		catch (exception e)
		{
			cout << e.what();
			system("PAUSE");
		}
	}
}


int main()
{
	net_cypher n;
	n.start();
}