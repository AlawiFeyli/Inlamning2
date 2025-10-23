#ifndef MEASUREMENT_H
#define MEASUREMENT_H
#include <string>

// Struct that represents single temperature value
struct Measurement {
	float value;
	std::string timestamp;
};

#endif