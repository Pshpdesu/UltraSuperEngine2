#include "cWindow.h"


inline void cWindow::initWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	window = glfwCreateWindow(HEIGHT, WIDTH, title.c_str(), nullptr, nullptr);
}

void cWindow::initVulkan()
{
	createVkInstance();
}

void cWindow::createVkInstance()
{
	if (enableValidationLayers && !checkValidationLayerSupport())
		throw std::runtime_error("validation layers requested, but not available");

	VkApplicationInfo Info = {};
	Info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	Info.pApplicationName = title.c_str();
	Info.pEngineName = "UltraSuperNiggerEngine";
	Info.pEngineName = VK_MAKE_VERSION(0, 0, 0);
	Info.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo crInfo = {};
	crInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	crInfo.pApplicationInfo = &Info;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	crInfo.ppEnabledExtensionNames = glfwExtensions;
	if (enableValidationLayers)
	{
		crInfo.enabledLayerCount = validationLayers.size();
		crInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
		crInfo.enabledLayerCount = 0;

	VkResult result = vkCreateInstance(&crInfo, nullptr, instance.replace());

	if (vkCreateInstance(&crInfo, nullptr, instance.replace()) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create instance!");
	}
}

void cWindow::loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
}


void cWindow::run()
{
	initWindow();
	initVulkan();
	loop();
}

bool cWindow::checkValidationLayerSupport()
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	for (const char* layerName : validationLayers)
	{
		bool layerFound = false;

		for (const auto& layerProperties : availableLayers)
		{
			if (strcmp(layerName, layerProperties.layerName) == 0)
			{
				layerFound = true;
				break;
			}
		}
	if (!layerFound)
		{
		return false;
		}
	}
	return true;
}

void cWindow::setTitle(std::string & str)
{
	glfwSetWindowTitle(window, str.c_str());
}



void cWindow::GetExtensionCount(uint32_t & count)
{
	vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr);
}

cWindow::~cWindow()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}
