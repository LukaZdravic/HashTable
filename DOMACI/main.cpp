#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "HashTable.h"
#include "AdaptiveHash.h"
using namespace std;

int main() {


	//umetanje preko fajla ili console
	int velicinatabele;
	cout << "Unesite velicinu tabele"<<endl;
	cin >> velicinatabele;
	HashTable h(velicinatabele);
	while (1) {
		cout << endl << "1:PREKO KOZNOLE" << endl;
		cout << "2:PREKO FAJLA" << endl;
		cout << "3:ISPISI HASHTABLE" << endl;
		cout << "4:PROSEK USPESNO" << endl;
		cout << "5:PROSEK NEUSPESNO" << endl;
		cout << "6:NADJI KEY" << endl;
		cout << "7:OBRISI KEY" << endl;
		cout << "8:STEPEN POPUNJENOSTI" << endl;
		cout << "9:EVALUACIJA PERFORMANSI" << endl;
		cout << "10:ADAPTIVNA HES" << endl;
		cout << "11:KRAJ" << endl;
		string c;
		cin >> c;
		if (c == "1") {
			cout << "Unesite (string key)" << endl;
			string s;
			int key;
			cin >> s >> key;
			h.insertKey(key, s);

		}
		if (c == "2") {
			ifstream datoteka;
			datoteka.open("Test123.txt");
			if (!datoteka.is_open()) {
				cout << "NEUSPESNO OTV DAT";
				continue;

			}
			cout << "Koliko linija fajla?";
			int linija;
			string line;
			cin >> linija;
			char delimiter = '\t';
			while (getline(datoteka, line) && linija > 0) {
				vector <string>s1;
				string temp = "";
				for (int i = 0; i < line.size(); i++) {
					if (line[i] != delimiter) temp += line[i];
					else {
						s1.push_back(temp);
						temp = "";
					}
				}
				s1.push_back(temp);
				h.insertKey(stoi(s1[1]), s1[0]);
				s1.clear();

				linija--;
			}
			//preko fajla
		}
		if (c == "3") {
			cout << h<<endl;

		}
		if (c == "4") {
			cout << h.avgAccessSuccess() << endl;
		}
		if (c == "5") {
			cout << h.avgAccessUnsuccess() << endl;
		}
		if (c == "6") {
			cout << "KOJI KEY ZELITE DA NADJETE" << endl;
			int key;
			cin >> key;
			string* s = h.findKey(key);
			if (s == nullptr) cout << "NE POSTOJI TAJ KEY!";
			else cout << "NADJEN JE KEY ->" << *s;
		}
		if (c == "7") {
			cout << "KOJI KEY ZELITE DA OBRISETE" << endl;
			int key;
			cin >> key;
			if (h.deleteKey(key) == true) cout << "USPESNO BRISANJE";
			else cout << "NEUSPESNO BRISANJE";
		}
		if (c == "8") {
			cout << h.fillRatio();
		}
		if (c == "9") {
			int min = h.findMin();
			int max = h.findMax();
			h.resetStatistics();
			cout << min << " " << max<<endl;
			for (int i = 0; i < 10 * h.keyCount(); i++) {
				int random = min + rand() % (max - min + 1);
				if(h.findKey(random)!=nullptr) cout<<"NASAO JEDNOGGGG";
			}
			cout << h.avgAccessSuccess()<<" ";
			cout << h.avgAccessUnsuccess() << endl;
			h.print();

		}
		if (c == "10") {
			
			while (h.fillRatio() > 0.7 || h.avgAccessSuccess()>5) { 
				h.prosiriTabelu();
			}
			cout << h;

		}

		if (c == "11") break;
	
	}
	return 0;
}