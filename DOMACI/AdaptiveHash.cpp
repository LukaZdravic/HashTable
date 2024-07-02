#include "AdaptiveHash.h"

void AdaptiveHash::prosiriTabelu() {
	vector<pair<int, string>> t = tabela;
	tabela.clear();
	tabela.resize(velicinaTab * 1.5, make_pair(0, ""));
	int tmp = velicinaTab;
	velicinaTab = velicinaTab * 1.5;
	for (int i = 0; i < tmp; i++) {
		if (t[i].first != 0) {
			insertKey(t[i].first, t[i].second);
		}
		
	}
	

}
