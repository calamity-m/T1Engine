#ifndef text2d_h
#define text2d_h

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "glut.h"

/*
Common call for drawing one string/text to the screen:
glPushMatrix();
glDisable(GL_LIGHTING);
text2d->set2D(WindowWidth, WindowHeight);
text2d->renderText(10, 500, "testing 123");
glEnable(GL_LIGHTING);
*/
class Text2D {
protected:
	GLvoid *fontStyle;

public:
	// Default constructor, defaults font style  to GLUT_BITMAP_HELVETICA_10
	Text2D();
	// Constructor with default font style
	Text2D(void *fStyle);
	// Sets the font style for this text object
	void setFontStyle(void *fStyle);
	// Sets the projection to ortho 2D, call this before rendering any text
	void set2D(int width, int height);
	// Render string to the screen
	void renderText(int x, int y, char *format, ...);
};

#endif // !h_h



