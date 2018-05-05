#ifndef GUI_HPP
#define GUI_HPP

#include "OpenGLWindow.hpp"

class GUI {

public:
	GUI(OpenGLWindow* screen);
	~GUI();

	void createSettings();

private:

	OpenGLWindow* screen;

};


#endif
