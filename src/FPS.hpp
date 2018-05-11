#ifndef FPS_HPP
# define FPS_HPP

# include <string>
# include <iostream>
# include <list>
# include <cmath>
# include <GLFW/glfw3.h>

class FPS {

	public:
		FPS(unsigned int sampleSize = 100);
		~FPS();
		
		void	reset(double startTime = 0.0f);
		void	update();
		
		// Getters
		int		getFPS() const;

	private:
		std::list<double>	timeList;
		int					fps;
		double				sampleSize;
};

#endif