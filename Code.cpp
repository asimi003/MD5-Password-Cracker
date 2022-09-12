#include "main.h"
#include <iostream>
#include <fstream>
#include <string>
#include "md5.h"


using namespace std;

const int ALPHABET_SIZE = 26;
const char  ALPHABET_BEGIN = 'a';
const char ALPHABET_END = 'z';

const int PASSWORD_MAX_SIZE = 6;

const string MAGIC = "$1$";
const string SALT = "hfT7jp2q";
const string PRECOMPUTED_HASH = "djvPG0OaooQS80NJ5hhCi0";

const char base64Array[64] = { '.','/','0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F','G','H','I',
'J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

string solve();
string solve(string guess);

string toBinary(int, int);
string toBinaryHelper(string&, int);

int main()
{


	ofstream file;

	file.open("file.txt");

	cout << solve("ndethc");
	//cout << solve();
	file.close();
	return 0;
}

bool isIncrementable(char attempt[], int numChar)
{
	for (int x = 0; x < numChar; x++)
	{
		if (*(attempt + x) < ALPHABET_END)
			return true;
	}
	return false;
}

void incrementGuess(char attempt[], int numChar)
{

	for (int x = (numChar - 1); x >= 0; x--)
	{
		if (*(attempt + x) < ALPHABET_END)
		{
			*(attempt + x) = *(attempt + x) + 1;
			if (x < (numChar - 1))
			{
				*(attempt + x + 1) = ALPHABET_BEGIN;
			}
			break;
		}
	}
}
std::string toBinary(int padding, int n)
{
	string s = "";
	string binaryString = toBinaryHelper(s, n);

	string paddingChars = "";

	if (binaryString.size() < padding)
	{
		int paddingRemaining = padding - binaryString.size();

		for (int i = 0; i < paddingRemaining; i++)
		{
			paddingChars += "0";
		}

	}
	return paddingChars + binaryString;

}
std::string toBinaryHelper(string& r, int n)
{
	r = (n % 2 == 0 ? "0" : "1") + r;
	if (n / 2 != 0) {
		toBinaryHelper(r, n / 2);
	}
	return r;
}

int toDecimal(string n)
{
	string num = n;
	int dec_value = 0;

	// Initializing base value to 1, i.e 2^0
	int base = 1;

	int len = num.length();
	for (int i = len - 1; i >= 0; i--) {
		if (num[i] == '1')
			dec_value += base;
		base = base * 2;
	}

	return dec_value;
}

string getBitSet(string bin, char storedCharacter)
{
	string result = "";


	for (int i = bin.size() - 1; i >= 0; i--)
	{
		if (bin.at(i) == '1')
		{
			result.append(1, 0);
		}
		else
		{
			result.append(1, storedCharacter);
		}
	}
	return result;
}

string solve()
{
	char* guess = new char[PASSWORD_MAX_SIZE];

	for (int numChar = 0; numChar < PASSWORD_MAX_SIZE; numChar++)
	{
		// Init array slots to null
		for (int i = 0; i < PASSWORD_MAX_SIZE; i++)
		{
			*(guess + i) = NULL;
		}

		// Init array values to beginning character.
		for (int i = 0; i < numChar; i++)
		{
			*(guess + i) = ALPHABET_BEGIN;
		}

		while (isIncrementable(guess, numChar))
		{

			string alternateSum = "";
			string bin = "";
			string endConcat = "";
			string intermediateSum = "";
			string nextIntermediateSum = "";
			string finalSum = "";
			string replacedFinalSum = "";
			string binaryReplacedFinalSum = "";
			string splitBinaryReplacedFinalSum[22];
			string hash = "";

			incrementGuess(guess, numChar);

			alternateSum = md5(guess + SALT + guess);

			bin = toBinary(0, numChar);
			endConcat = getBitSet(bin, *guess);

			string intermediateStringConcat = guess + MAGIC + SALT + alternateSum.substr(0, numChar) + endConcat;
			intermediateSum = md5(intermediateStringConcat);


			for (int i = 0; i <= 999; i++)
			{

				if (i % 2 == 0)
					nextIntermediateSum += intermediateSum;
				else
					nextIntermediateSum += guess;

				if (i % 3 != 0)
					nextIntermediateSum += SALT;
				if (i % 7 != 0)
					nextIntermediateSum += guess;

				if (i % 2 == 0)
					nextIntermediateSum += guess;
				else
					nextIntermediateSum += intermediateSum;

				intermediateSum = md5(nextIntermediateSum);
				nextIntermediateSum = "";
			}

			finalSum = intermediateSum.substr(0, 20);

			replacedFinalSum.append(1, finalSum[11]);
			replacedFinalSum.append(1, finalSum[4]);
			replacedFinalSum.append(1, finalSum[10]);
			replacedFinalSum.append(1, finalSum[5]);
			replacedFinalSum.append(1, finalSum[3]);
			replacedFinalSum.append(1, finalSum[9]);
			replacedFinalSum.append(1, finalSum[15]);
			replacedFinalSum.append(1, finalSum[2]);
			replacedFinalSum.append(1, finalSum[8]);
			replacedFinalSum.append(1, finalSum[14]);
			replacedFinalSum.append(1, finalSum[1]);
			replacedFinalSum.append(1, finalSum[7]);
			replacedFinalSum.append(1, finalSum[13]);
			replacedFinalSum.append(1, finalSum[0]);
			replacedFinalSum.append(1, finalSum[6]);
			replacedFinalSum.append(1, finalSum[12]);


			//replacedFinalSum = "" + finalSum[11] + finalSum[4] + finalSum.at(10)+ finalSum.at(5) + finalSum.at(3) + finalSum.at(9)
				//+ finalSum.at(15) + finalSum.at(2) + finalSum.at(8) + finalSum.at(14) + finalSum.at(1) + finalSum.at(7) + finalSum.at(13)
				//+ finalSum.at(0) + finalSum.at(6) + finalSum.at(12);

			for (int i = 0; i < replacedFinalSum.size(); i++)
			{
				char character = replacedFinalSum[i];
				string binaryDefinition = toBinary(8, character);
				binaryReplacedFinalSum += binaryDefinition;
			}

			for (int i = 0; i < 22; i++)
			{
				splitBinaryReplacedFinalSum[i] = binaryReplacedFinalSum.substr(i * 6, 6);
			}

			for (int i = 21; i >= 0; i--)
			{

				hash.append(1, base64Array[toDecimal(splitBinaryReplacedFinalSum[i])]);
			}

			if (hash == PRECOMPUTED_HASH)
			{

				return guess;
			}


		}
	}
	return "[|->{error}<-|]";
}

string solve(string guess)
{
	string alternateSum = "";
	string bin = "";
	string endConcat = "";
	string intermediateSum = "";
	string nextIntermediateSum = "";
	string finalSum = "";
	string replacedFinalSum = "";
	string binaryReplacedFinalSum = "";
	string splitBinaryReplacedFinalSum[22];
	string hash = "";


	alternateSum = md5(guess + SALT + guess);


	cout << alternateSum << endl;

	bin = toBinary(0, guess.size());
	endConcat = getBitSet(bin, guess[0]);

	string intermediateStringConcat = "";
	intermediateStringConcat.append(guess);
	intermediateStringConcat.append(MAGIC);
	intermediateStringConcat.append(SALT);
	intermediateStringConcat.append(alternateSum.substr(0, guess.size()));
	intermediateStringConcat.append(endConcat);

	intermediateSum = md5(intermediateStringConcat);

	cout << intermediateSum << endl;
	for (int i = 0; i < 1000; i++)
	{

		if (i % 2 == 0)
			nextIntermediateSum += intermediateSum;
		if (i % 2 != 0)
			nextIntermediateSum += guess;

		if (i % 3 != 0)
			nextIntermediateSum += SALT;
		if (i % 7 != 0)
			nextIntermediateSum += guess;

		if (i % 2 == 0)
			nextIntermediateSum += guess;
		if (i % 2 != 0)
			nextIntermediateSum += intermediateSum;


		intermediateSum = md5(nextIntermediateSum);
		nextIntermediateSum = "";
	}

	finalSum = intermediateSum;

	replacedFinalSum.append(1, finalSum[11]);
	replacedFinalSum.append(1, finalSum[4]);
	replacedFinalSum.append(1, finalSum[10]);
	replacedFinalSum.append(1, finalSum[5]);
	replacedFinalSum.append(1, finalSum[3]);
	replacedFinalSum.append(1, finalSum[9]);
	replacedFinalSum.append(1, finalSum[15]);
	replacedFinalSum.append(1, finalSum[2]);
	replacedFinalSum.append(1, finalSum[8]);
	replacedFinalSum.append(1, finalSum[14]);
	replacedFinalSum.append(1, finalSum[1]);
	replacedFinalSum.append(1, finalSum[7]);
	replacedFinalSum.append(1, finalSum[13]);
	replacedFinalSum.append(1, finalSum[0]);
	replacedFinalSum.append(1, finalSum[6]);
	replacedFinalSum.append(1, finalSum[12]);

	for (int i = 0; i < replacedFinalSum.size(); i++)
	{
		char character = replacedFinalSum[i];
		string binaryDefinition = toBinary(8, character);
		binaryReplacedFinalSum += binaryDefinition;
	}

	binaryReplacedFinalSum = "0000" + binaryReplacedFinalSum;

	for (int i = 0; i < 22; i++)
	{
		splitBinaryReplacedFinalSum[i] = binaryReplacedFinalSum.substr(i * 6, 6);
	}

	for (int i = 21; i >= 0; i--)
	{

		hash.append(1, base64Array[toDecimal(splitBinaryReplacedFinalSum[i])]);
	}

	if (hash == PRECOMPUTED_HASH)
	{
		return guess;
	}



	return "[|->{error}<-|]";
}


