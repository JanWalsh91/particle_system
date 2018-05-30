#include <sstream>
#include <vector>
#include <cstdlib>
#include <string>

#include "ParticleSystem.hpp"

int    main ( int ac, char **av ) {

	std::vector<std::string> args;

	long int pcount = 100000;
	std::string layout = "";
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
	std::cout << "pcount: " << pcount << std::endl;

	try {
		ParticleSystem PS;
		PS.init(pcount, layout, true, optimized);
		PS.loop();
	}
	catch(std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return (0);
}