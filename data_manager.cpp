#include "data_manager.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <numeric>

using namespace std;

void DataManager::addMeasurement(float value, const string& timestamp) {
	measurements.push_back({ value, timestamp });
	cout << "Temperature added!\n";
}

void DataManager::displayMeasurements() const {
	if (measurements.empty()) {
		cout << "No measurements available.\n";
		return;
	}

	cout << "Measurements:\n";
	for (const auto& m : measurements) {
		cout << m.timestamp << " - " << m.value << "*C\n";
	}
	cout << "\n";
}

void DataManager::searchMeasurement(float value) const {
	bool found = false;
	for (size_t i = 0; i < measurements.size(); ++i) {
		if (measurements[i].value == value) {
			cout << "Found " << value << "*C at position " << i << " (" << measurements[i].timestamp << ")\n";
			found = true;
			break;
		}
	}
	if (!found) {
		cout << "Temperature " << value << "*C not found.\n";
	}
}

void DataManager::sortMeasurement(bool ascending) {
	if (ascending) {
		sort(measurements.begin(), measurements.end(),
			[](const Measurement& a, const Measurement& b) { return a.value < b.value; });
		cout << "Sorted ascending.\n";
	} else {
		sort(measurements.begin(), measurements.end(),
			[](const Measurement& a, const Measurement& b) { return a.value > b.value; });
		cout << "Sorted descending.\n";
	}
}

void DataManager::showStatistics() const {
	if (measurements.empty()) {
		cout << "No data to analyze.\n";
		return;
	}

	int n = measurements.size();
	vector<float> values;
	for (const auto& m : measurements) values.push_back(m.value);

	float sum = accumulate(values.begin(), values.end(), 0.0f);
	float mean = sum / n;
	float minVal = *min_element(values.begin(), values.end());
	float maxVal = *max_element(values.begin(), values.end());

	float variance = 0.0f;
	for (float v : values) variance += pow(v - mean, 2);
	variance /= n;
	float stdDev = sqrt(variance);

	cout << "==============================\n";
	cout << "Statistics:\n";
	cout << "==============================\n";
	cout << "Count: " << n << "\n";
	cout << "Sum: " << sum << "\n";
	cout << "Average: " << mean << "\n";
	cout << "Min: " << minVal << "\n";
	cout << "Max: " << maxVal << "\n";
	cout << "Variance: " << variance << "\n";
	cout << "Standard deviation: " << stdDev << "\n";
	cout << "==============================\n";
}

void DataManager::thresholdDetection(float criticalTemp) const {
	int over = 0, under = 0;
	for (const auto& m : measurements) {
		if (m.value > criticalTemp) over++;
		else if (m.value < criticalTemp) under++;
	}

	cout << "==============================\n";
	cout << "Threshold Detection\n";
	cout << "==============================\n";
	cout << "Critical temperature: " << criticalTemp << "*C\n";
	cout << "Above: " << over << "\n";
	cout << "Below: " << under << "\n";
	cout << "==============================\n";
}

bool DataManager::loadFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) return false;

	string line;
	while (getline(file, line)) {
		stringstream ss(line);
		string timestamp;
		float value;
		if (getline(ss, timestamp, ',') && ss >> value) {
			measurements.push_back({ value, timestamp });
		}
	}
	file.close();
	return true;
}

bool DataManager::saveToFile(const string& filename) const {
	ofstream file(filename);
	if (!file.is_open()) return false;

	for (const auto& m : measurements) {
		file << m.timestamp << "," << fixed << setprecision(1) << m.value << "\n";
	}
	file.close();
	return true;
}
