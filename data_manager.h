#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H
#include <vector>
#include <string>
#include "measurement.h"

class DataManager {
private:
	std::vector<Measurement> measurements;

public:
	void addMeasurement(float value, const std::string& timestamp);
	void displayMeasurements() const;
	void searchMeasurement(float value) const;
	void sortMeasurement(bool ascending);
	void showStatistics() const;
	void thresholdDetection(float criticalTemp) const;
	bool loadFromFile(const std::string& filename);
	bool saveToFile(const std::string& filename) const;
};

#endif