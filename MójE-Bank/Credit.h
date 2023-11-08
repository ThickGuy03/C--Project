#pragma once
using namespace System;

public ref class Credit {
public:
	int id;
	int ownersId;
	String^ source;
	float borrowedMoney;
	float interestRate;
	int numOfMonths;
	int monthsPaid;
};
