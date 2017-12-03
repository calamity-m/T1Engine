#include "Text2D.h"

Text2D::Text2D() {
	setFontStyle(GLUT_BITMAP_HELVETICA_10);
}

Text2D::Text2D(void * fStyle) {
	fontStyle = fStyle;
}

void Text2D::setFontStyle(void * fStyle) {
	fontStyle = fStyle;
}

void Text2D::set2D(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)width, 0.0, (GLfloat)height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // load 'no' transformation so the text works 
}

void Text2D::renderText(int x, int y, char * format, ...) {
	va_list args;
	char buffer[256];
	char *s;

	va_start(args, format);
	vsprintf(buffer, format, args);
	va_end(args);

	glRasterPos2i(x, y);
	for (s = buffer; *s; s++)
		glutBitmapCharacter(fontStyle, *s);
}