#ifndef fpscounter_h
#define fpscounter_h
#pragma once

#include <stdio.h>
#include "glut.h"


class fpscounter {

protected:
	float base;
	int frames;

public:

	fpscounter();
	void init();
	float getFPS();
	void displayFPSTitle(char *title);

};
#endif // !fpscounter_h
