#ifndef __Window_h
#define __Window_h

	#include<iostream>

	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>
	
	#include <glm/glm.hpp>

	class Window {
	public:
		bool framebufferResized;

		void initWindow(GLFWwindow* &window, const int WIDTH, const int HEIGHT);
	};

#endif