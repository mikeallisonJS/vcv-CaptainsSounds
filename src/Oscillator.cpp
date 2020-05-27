#include "Oscillator.hpp"

using namespace captainssounds;

void Oscillator::process(float modelSampleTime) {
	// Calculate internal sampleTime
	if (sampleTime == 2.f) {
		sampleTime = 0.00f;
		sampleOffset = modelSampleTime;
	}
	sampleTime = modelSampleTime + sampleOffset;
	if (sampleTime > 1) 
		sampleTime--;
	
	// Calculate phase
	phase += frequency * sampleTime;
	if (phase >= 0.5f)
		phase--;
}
void Oscillator::sync() {
	sampleTime = 2.f; // bogus value to force offset calc
}
float Oscillator::buildWave() {
	switch (wave) {
		case 1:
			return triangle(phase);	
		case 2:
			return saw(phase);	
		case 3:
			return square(phase, 0.5f);
		default:
			return sine(phase);
	}	
}
float Oscillator::getVoltage() {
	return 5.f * buildWave();
}
