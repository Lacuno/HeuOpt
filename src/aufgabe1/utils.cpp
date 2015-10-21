#include "utils.h"

using namespace std;

vector<clock_t> Utils::begintimes = vector<clock_t>();

void Utils::startTimeMeasurement() {
	begintimes.push_back(clock());
}

double Utils::endTimeMeasurement() {
	clock_t end = clock();
	clock_t begin = begintimes.back();
	begintimes.pop_back();

	return double(end - begin) / CLOCKS_PER_SEC;
}
