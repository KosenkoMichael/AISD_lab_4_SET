#include <functions/functions.h>

using namespace std;
using namespace set;

string generate_random_string(int length) {
	random_device rd;
	uniform_int_distribution<int> distribution(97, 122); // диапазон символов a-z
	string randomString;
	for (int i = 0; i < length; i++) {
		randomString += static_cast<char>(distribution(rd));
	}
	return randomString;
}

int generate_random_number(int min, int max) {
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> distribution(min, max);
	return distribution(mt);
}