#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm\glm.hpp>
#include <vulkan\vulkan.h>
#include <iostream>
#include "cWindow.h"

int main()
{
	setlocale(LC_ALL, "ru-RU");
	std::string *str = new std::string("Tbl XYu`");
	cWindow window(*str,640,480);
	window.run();
	return 0;
}