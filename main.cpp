// Inlämningsuppgift 1, Temperatur analys verktyg
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <ctime>
#include "data_manager.h" // Added new header file into main.cpp
using namespace std;

// Function for getting timestamp
std::string getCurrentTimestamp() {
	time_t now = time(nullptr);
	char buf[80];
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", localtime(&now));
	return std::string(buf);
}
// Function for inputting temperature data
void inputTemperature(vector<float>& temps) {
	float t;
	cout << "Input temperature: ";
	cin >> t;
	temps.push_back(t);
	cout << "Temperature added!\n\n";
}

// Function to show all temperaturess inputted
void displayData(const vector<float>& temps) {
	cout << "Temperatures:\n";
	for (float t : temps) {
		cout << t << "*C" << "\n";
	}
	cout << "\n\n";
}
// Function to search for a specific temperatur in input list
void searchData(const vector<float>& temps) {
	if (temps.empty()) {
		cout << "List is empty. Input a temperature first. \n\n";
		return;
	}

	float searchValue;
	cout << "Search for a temperature: ";
	cin >> searchValue;

	bool found = false;

	int position = 0;

	for (int i = 0; i < temps.size(); ++i) {
		if (temps[i] == searchValue) {
			found = true;
			position = i;
			break;
		}
	}

	if (found) {
		cout << "Temperature " << searchValue << " found on position " << position << ".\n\n";
	}
	else {
		cout << "Temperature " << searchValue << " is not in list.\n\n";
	}
}

// Function that shows the list of temperatures ascending or descending
void sortList(vector<float>& temps) {
	if (temps.empty()) {
		cout << "The list is empty, please add temperatures first.\n\n";
		return;
	}

	int orderChoice;
	cout << "Choose how you would like to sort the list:\n";
	cout << "1. Ascending\n";
	cout << "2. Descending\n";
	cout << "Your choice: ";
	cin >> orderChoice;

	if (orderChoice == 1) {
		sort(temps.begin(), temps.end());
		cout << "List will be shown ascending!\n\n";
	}
	else if (orderChoice == 2) {
		sort(temps.rbegin(), temps.rend());
		cout << "List will be shown descending!\n\n";
	}
	else {
		cout << "Invalid choice.\n\n";
		return;
	}

	cout << "Sorted list: ";
	for (float t : temps)
		cout << t << " ";
	cout << "\n\n";
}
// Function that shows statistics of temperatures
void showStatistics(const vector<float> temps) {
	if (temps.empty()) {
		cout << "The list is empty, please input temperatures first.\n\n";
		return;
	}

	int n = temps.size();
	// Sum
	float sum = accumulate(temps.begin(), temps.end(), 0.0f);
	// Average
	float mean = sum / n;
	// Min and Max
	float minChoice = *min_element(temps.begin(), temps.end());
	float maxChoice = *max_element(temps.begin(), temps.end());
	// Variance
	float variance = 0.0f;
	for (float t : temps) {
		variance += pow(t - mean, 2);
	}
	variance /= n;

	// Standardavvikelse / Difference?
	float stdDev = sqrt(variance);

	// Choices of menu
	cout << "==============================\n";
	cout << "Statistics:\n";
	cout << "==============================\n";
	cout << "Number of tempereatures: " << n << "\n";
	cout << "Sum: " << sum << "\n";
	cout << "Average: " << mean << "\n";
	cout << "Minimum: " << minChoice << "\n";
	cout << "Maximum: " << maxChoice << "\n";
	cout << "Variance: " << variance << "\n";
	cout << "Standard deviation: " << stdDev << "\n";
	cout << "==============================\n\n";
}

// Threshold detection function 
void thresholdDetection(const vector<float>& temps) {
	if (temps.empty()) {
		cout << "List is empty, add temperatures first. \n";
		return;
	}

	float criticalTemp;
	cout << "Input a critical temperature: ";
	cin >> criticalTemp;

	int overCount = 0;
	int underCount = 0;

	for (float t : temps) {
		if (t > criticalTemp)
			overCount++;
		else if (t < criticalTemp)
			underCount++;

	}

	cout << "==============================\n";
	cout << "Threshold Detection\n";
	cout << "==============================\n";
	cout << "Critical temperature: " << criticalTemp << "*C\n";
	cout << "Times over: " << overCount << "\n";
	cout << "Times under: " << underCount << "\n";
	cout << "==============================\n";
}


int main()
{
	DataManager manager;
	manager.loadFromFile("temperatures.csv");

	int choice = 0;
	while (choice != 7) {
		// The menu
		cout << "==============================" << "\n";
		cout << "Data Analysis tool" << "\n";
		cout << "==============================" << "\n";
		cout << "1. Input Temperature" << "\n";
		cout << "2. Display temperature list" << "\n";
		cout << "3. Search Data" << "\n";
		cout << "4. Sort List (Ascending or Descending)" << "\n";
		cout << "5. Show statistics\n";
		cout << "6. Threshold detection\n";
		cout << "7. Exit" << "\n";
		cout << "==============================" << "\n";
		cout << "Select an option (1-7): ";
		cin >> choice; // Get user choice
		cout << "\n";
		
		switch (choice) {
		case 1: {
			float temp;
			cout << "Input temperature: ";
			cin >> temp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Invaldi input, please enter a number.\n";
			}
			else {
				manager.addMeasurement(temp, getCurrentTimestamp());
			}
			break;
		}
		case 2: manager.displayMeasurements(); break;
		case 3: {
			float search;
			cout << "Search for temperature: ";
			cin >> search;
			manager.searchMeasurement(search);
			break;
		}
		case 4: {
			int sortChoice;
			cout << "1. Ascending\n2. Descending\nChoice: ";
			cin >> sortChoice;
			manager.sortMeasurement(sortChoice == 1);
			break;
		}
		case 5: manager.showStatistics(); break;
		case 6: {
			float threshold;
			cout << "Input critical temperature: ";
			cin >> threshold;
			manager.thresholdDetection(threshold);
			break;
		}
		case 7: {
			manager.saveToFile("temperatures.csv");
			cout << "Exiting program.\n";
			break;
		}
		default: cout << "Invalid choice.\n"; break;
		}
	}
	return 0;

}

 