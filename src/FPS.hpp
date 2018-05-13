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
		
		void	reset(float startTime = 0.0f);
		void	update();
		void	updateLast();
		float	getDeltaTime();

		// Getters
		int		getFPS() const;
		
	private:
		std::list<float>	timeList;
		int					fps;
		float				sampleSize;
};

#endif