#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <vector>
#include <string>
#include "measurement.h"
// Class that handles all the measurements and logic around them
class DataManager {
private:
	std::vector<Measurement> measurements; // List with all the measurements

public:
	// Adds a new temperature/value
	void addMeasurement(float value, const std::string& timestamp);

	// Displays all the temperatures
	void displayMeasurements() const;

	// Searches for a specific tempvalue
	void searchMeasurement(float value) const;

	// Sorts the list either ascending or descending
	void sortMeasurement(bool ascending);

	// Shows statistics, mean, min, max & standard deviation
	void showStatistics() const;

	// Shows how many values is under/over a specific temp
	void thresholdDetection(float criticalTemp) const;

	// Loads in measurements from file
	bool loadFromFile(const std::string& filename);

	// Saves measurements to file
	bool saveToFile(const std::string& filename) const;
};

#endif