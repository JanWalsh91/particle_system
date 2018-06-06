#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <algorithm>

#include "ParticleSystem.hpp"

void printUsage();
void printInstructions();

int    main ( int ac, char **av ) {

	std::vector<std::string> args;

	int pcount = 100000;
	std::string layout = "sphere";
	bool optimized = false;

	if (ac < 2) {
		printUsage();
		return (0);
	}
	else {
		printInstructions();
	}

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
		pcount = std::min(pcount, 700000);
	}

	try {
		std::cout << "number of particles: " << pcount << std::endl;
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

void printUsage() {
	std::cout << "Usage: ./particle_system -p=[number of particles] [-l=[sphere/cube]] [-o]" << std::endl;
	std::cout << "-p= : specify number of particles" << std::endl;
	std::cout << "-l= : specify layout" << std::endl;
	std::cout << "-o : use optmized version" << std::endl;
}

void printInstructions() {
	std::cout << std::endl;
	std::cout << "=================== INSTRUCTIONS: ===================" << std::endl;
	std::cout << "Move Camera:\t\t\tUP, DOWN, LEFT, RIGHT" << std::endl;
	std::cout << "Rotate Camera:\t\t\tW, A, S, D" << std::endl;
	std::cout << "Pause:\t\t\t\tP" << std::endl;
	std::cout << "Toggle Mouse to Control Force:\tL" << std::endl;
	std::cout << "Control Froce Depth:\t\tMouse Wheel" << std::endl;
	std::cout << "Move Force:\t\t\tMouse Left Click" << std::endl;
	std::cout << "New Force:\t\t\tN" << std::endl;
	std::cout << "Next Force:\t\t\tTAB" << std::endl;
	std::cout << "Reset / Change init config:\tSPACE" << std::endl;
	std::cout << std::endl;
}