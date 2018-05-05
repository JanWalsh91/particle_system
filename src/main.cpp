#include "OpenGLWindow.hpp"

#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.hpp>
#endif

int    main ( void ) {

	OpenGLWindow::initOpenGL();

	OpenGLWindow w(1280, 720, "Particle System");

	w.loop();

	return (0);
}