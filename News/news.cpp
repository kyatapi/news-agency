#include <stdio.h>
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

#ifndef ONLINE_JUDGE
#include <fstream>
#endif

class ArticlePaymentCalculator {
public:
	ArticlePaymentCalculator();
	~ArticlePaymentCalculator();
	bool Calculate();
	int  ParseTest();
	bool ParseRule(int table[]);
	int  ParseArticle(const int table[]);
private:
	enum {CHARACTER_TABLE_SIZE = 256};
};

ArticlePaymentCalculator::ArticlePaymentCalculator() {

}

ArticlePaymentCalculator::~ArticlePaymentCalculator() {

}

using namespace std;

bool ArticlePaymentCalculator::Calculate() {
	int testCount = 0;
	string line = "";

	try {
		getline(cin, line);
		istringstream iss(line);
		iss >> testCount;
		int* prices = new int[testCount];

		for (int t = 0; t < testCount; ++t) {
			prices[t] = ParseTest();
		}

		for (int t = 0; t < testCount; ++t) {
			int dollar = prices[t] / 100;
			int cent = prices[t] % 100;
			cout << dollar << '.' << cent / 10 << cent % 10 << '$' << endl;
		}

		delete[] prices;
	}
	catch (ios_base::failure e) {
		return false;
	}

	return true;
}

int ArticlePaymentCalculator::ParseTest() {
	int priceTable[CHARACTER_TABLE_SIZE];
	ParseRule(priceTable);
	return ParseArticle(priceTable);
}

bool ArticlePaymentCalculator::ParseRule(int table[]) {
	memset(table, 0, CHARACTER_TABLE_SIZE * sizeof(int));
	unsigned int ruleCount = 0;
	string line = "";
	getline(cin, line);
	istringstream iss(line);
	iss >> ruleCount;
	for (unsigned int r = 0; r < ruleCount; ++r) {
		unsigned char paidChar = '\0';
		int value = 0;
		getline(cin, line);
		istringstream iss2(line);
		iss2 >> paidChar >> value;
		table[paidChar] = value;
	}
	return true;
}

int ArticlePaymentCalculator::ParseArticle(const int table[]) {
	int lineCount = 0, price = 0;
	string line = "";
	getline(cin, line);
	istringstream iss(line);
	iss >> lineCount;
	for (int l = 0; l < lineCount; ++l) {
		getline(cin, line);
		for (size_t c = 0; c < line.length(); ++c) {
			price += table[static_cast<unsigned char>(line[c])];
		}
	}
	return price;
}

int main() {
#ifndef ONLINE_JUDGE
	//Redirect stdin/out
	ifstream in("D:\\Project\\News\\Debug\\in.txt");
	streambuf *cinbuf = std::cin.rdbuf(); //save old buf
	cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

	ofstream out("D:\\Project\\News\\Debug\\out.txt");
	streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
#endif // !ONLINE_JUDGE

	ArticlePaymentCalculator calculator;
	do {
		calculator.Calculate();
	} while (cin.good());

#ifndef ONLINE_JUDGE
	cin.rdbuf(cinbuf);
	cout.rdbuf(coutbuf);
#endif // !ONLINE_JUDGE

	return 0;
}