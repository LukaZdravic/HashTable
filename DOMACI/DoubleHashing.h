#pragma once
#include "AddressFunction.h"

class DoubleHashing:public AddressFunction
{
public:
	int getAddress(int k, int a, int i) override {
		int p = 61, q = 83;
		return a + i * (q + (k % p));
	}
	
};

