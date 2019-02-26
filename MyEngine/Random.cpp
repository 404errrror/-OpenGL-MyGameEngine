#include "Random.h"

#include <random>
#include <time.h>

Random::Random()
{
}


Random::~Random()
{
}


int Random::Range(int min, int max)
{
	std::random_device rDevice;
	std::mt19937_64 rEngine(rDevice());
	std::uniform_int_distribution<int> rDistribution(min, max);

	return (rDistribution(rEngine));
}


float Random::Range(double min, double max)
{
	std::random_device rDevice;
	std::mt19937_64 rEngine(rDevice());
	std::uniform_real_distribution<double> rDistribution(min, max);

	return (rDistribution(rEngine));
}