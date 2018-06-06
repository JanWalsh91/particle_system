#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

#include "ParticleSystem.hpp"

int    main ( int ac, char **av ) {

	std::vector<std::string> args;

	int pcount = 100000;
	std::string layout = "sphere";
	bool optimized = false;

	for (int i = 1; i < ac; ++i)
		args.push_back(av[i]);

	for (std::string &arg : args) {
		if (arg.find("-p=") != std::string::npos) {
			std::string sub = arg.substr(3);
			pcount = std::atoi(sub.c_str());
			if (!pcount)
				pcount = 5000;
		}
		if (arg.find("-l=") != std::string::npos)
			layout = arg.substr(3);
		if (arg.find("-o") != std::string::npos)
			optimized = true;
	}

	std::vector<std::string> faces = {
		"../src/textures/FullMoonLeft.png",
		"../src/textures/FullMoonRight.png",
		"../src/textures/FullMoonUp.png",
		"../src/textures/FullMoonDown.png",
		"../src/textures/FullMoonFront.png",
		"../src/textures/FullMoonBack.png"
		};
	
	if (optimized) {
		pcount = std::min(pcount, 3000000);
	} else {
		pcount = std::min(pcount, 500000);
	}

	try {
		ParticleSystem PS;
		PS.init(pcount, layout, true, optimized, faces);
		PS.loop();
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	glfwTerminate();
	return (0);
}