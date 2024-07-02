#include "HashTable.h"
#include <iostream>
#include <vector>
#include <math.h>
#include "DoubleHashing.h"

using namespace std;


class HashTable
{
private:
	int velicinaTab;
	vector<pair<int,string>> tabela;
	int hashFun(int k) { 
		double a;
		modf(0.61803 * k, &a);	
		return 2*a; 
	}
	int brNeNadjenih = 0;
	int popunjenamesta = 0;
	int brPokusajaUk = 0;
	int brPokusajaUspesno = 0;
	int brPokusajaNeuspesno = 0;
	
public:
	HashTable(int vel) :velicinaTab(vel) { tabela.resize(vel,make_pair(0,"")); }
	int findMin();
	int findMax();

	void print() {
		//for (int i = 0; i < tabela.size(); i++) cout << tabela[i].first << " " << tabela[i].second << endl;
		cout << brPokusajaUk << " " << brPokusajaUspesno<<" "<<brPokusajaNeuspesno<<" "<<popunjenamesta<<endl;

		cout << 1 / (1 - (popunjenamesta / velicinaTab));
	}
	void prosiriTabelu();

	string* findKey(int K);
	bool insertKey(int k, string s);
	bool deleteKey(int k);

	int avgAccessSuccess();
	int avgAccessUnsuccess();

	void resetStatistics();
	void clear();
	int keyCount();

	int tableSize();
	friend ostream& operator<<(ostream& os, const HashTable& h1) {
		for (int i = 0; i < h1.tabela.size(); i++) {
			if (h1.tabela[i].first == 0) os << "EMPTY";
			else os << h1.tabela[i].second << " " << h1.tabela[i].first;
			os << endl;
		}
		return os;

	}
	double fillRatio();



};

string* HashTable::findKey(int K) {
	int matAdr = hashFun(K) % velicinaTab;
	int br = 1;
	int tmp = matAdr;
	brPokusajaUk++;
	DoubleHashing dh;
	bool moze = true;
	while (tabela[tmp].first != K && tabela[tmp].first != 0) {
		tmp = dh.getAddress(K, matAdr, br++);
		tmp = tmp % velicinaTab;
		if (tmp == matAdr) {
			moze = false; break;
		}
		brPokusajaNeuspesno++;
		brPokusajaUk++;
	}
	if (tabela[tmp].first != 0 && moze) {
		brPokusajaUspesno++;
		return &tabela[tmp].second;
	}
	else {
		brNeNadjenih++;
		return nullptr;
	}

}

bool HashTable::insertKey(int K, string s) {
	int matAdr = hashFun(K) % velicinaTab;
	int tmp = matAdr;
	int br = 1;
	DoubleHashing dh;
	while (tabela[tmp].first != K && tabela[tmp].first != 0) {
		tmp = dh.getAddress(K, matAdr, br++);
		tmp = tmp % velicinaTab;
		if (tmp == matAdr) break;

	}

	if (tabela[tmp].first == 0) {
		tabela[tmp].first = K;
		tabela[tmp].second = s;
		popunjenamesta++;
		return true;
	}
	else return false;

}

bool HashTable::deleteKey(int K) {
	int matAdr = hashFun(K) % velicinaTab;
	int tmp = matAdr;
	int br = 1;
	DoubleHashing dh;
	while (tabela[tmp].first != K && tabela[tmp].first != 0) {
		tmp = dh.getAddress(K, matAdr, br++);
		tmp = tmp % velicinaTab;
	}
	if (tabela[tmp].first == 0) return false;
	tabela[tmp].second = "";
	tabela[tmp].first = 0;
	popunjenamesta--;
	return true;

}

int HashTable::avgAccessSuccess() {
	return brPokusajaUk / popunjenamesta;
}

int HashTable::avgAccessUnsuccess() {
	return brPokusajaNeuspesno/brNeNadjenih;
}

void HashTable::resetStatistics() {
	brPokusajaNeuspesno = 0;
	brPokusajaUk = 0;
	brPokusajaUspesno = 0;
	// stavi brojace za neuspesno na 0
}

void HashTable::clear() {
	tabela.clear();
	tabela.resize(velicinaTab, make_pair(0, ""));
	popunjenamesta = 0;
}

int HashTable::keyCount() {
	return popunjenamesta;
}

int HashTable::tableSize() {
	return velicinaTab;
}

double HashTable::fillRatio() {
	return (double)popunjenamesta /(double) velicinaTab;
}

int HashTable::findMin() {
	int min = INT_MAX;
	for (int i = 0; i < velicinaTab; i++) {
		if (tabela[i].first < min && tabela[i].first!=0) {
			min = tabela[i].first;
		}
	}
	return min;
}
int HashTable::findMax() {
	int max = INT_MIN;
	for (int i = 0; i < velicinaTab; i++) {
		if (tabela[i].first > max && tabela[i].first != 0) {
			max = tabela[i].first;
		}
	}
	return max;

}

void HashTable::prosiriTabelu() {
	vector<pair<int, string>> t = tabela;
	clear();
	tabela.resize(velicinaTab * 1.5, make_pair(0, ""));
	int tmp = velicinaTab;
	velicinaTab = velicinaTab * 1.5;
	for (int i = 0; i < tmp; i++) {
		if (t[i].first != 0) {
			insertKey(t[i].first, t[i].second);
		}

	}
}