#include "plugin.hpp"

Plugin* pluginInstance;

void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	p->addModel(modelBlank901);
	p->addModel(modelBlank902);
	p->addModel(modelBlank904);
	p->addModel(modelNip);
	p->addModel(modelPow);
	p->addModel(modelVBNO);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}

float captainssounds::clamp10VUnipolar(float x) {
	return clamp(x, 0.f, 10.f);
}

float captainssounds::clamp5VBipolar(float x) {
	return clamp(x, -5.f, 5.f);
}