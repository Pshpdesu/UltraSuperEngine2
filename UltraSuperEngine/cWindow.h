#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW\glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm\glm.hpp>
#include <functional>
#include <iostream>
#include <vector>
#include <cstring>

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

class cWindow
{
	template <class T>
	class VKDeleter
	{
	public:
		VKDeleter() :VKDeleter([](T, VkAllocationCallbacks*) {}) {};

		VKDeleter(std::function<void(T, VkAllocationCallbacks*)>deletef)
		{
			this->deleter = [=](T obj) {deletef(obj, nullptr); };
		}

		VKDeleter(const VKDeleter<VkInstance>& instance, std::function<void(VkInstance, T, VkAllocationCallbacks*)>deletef)
		{
			this->deleter = [&instance, deletef](T obj) {deletef(instance, obj, nullptr); };
		}

		VKDeleter(const VKDeleter<VkDevice>& device, std::function<void(VkDevice, T, VkAllocationCallbacks*)>deletef)
		{
			this->deleter = [&device, deletef](T obj) {deletef(device, obj, nullptr); };
		}

		~VKDeleter() 
		{
			cleanup();
		}

		const T* operator &() const 
		{
			return &object;
		}

		T* replace()
		{
			cleanup();
			return &object;
		}

		operator T() const
		{
			return object;
		}

		void operator=(T rhs)
		{
			if (rhs != object)
			{
				cleanup();
				object = rhs;
			}
		}

		template<typename V>
		bool operator==(V rhs)
		{
			return object == T(rhs);
		}

	private:
		T object{ VK_NULL_HANDLE };
		std::function <void(T)> deleter;

		void cleanup()
		{
			if (object != VK_NULL_HANDLE)
				deleter(object);

			object = VK_NULL_HANDLE;
		}
};

	GLFWwindow* window;
	uint32_t HEIGHT, WIDTH;
	std::string title;
	VKDeleter<VkInstance> instance{ vkDestroyInstance };
	const std::vector<const char*> validationLayers;

	inline void initWindow();
	void initVulkan();
	void createVkInstance();
	void loop();

public:
	cWindow(uint32_t xRes = 640, uint32_t yRes = 480) :HEIGHT(xRes), WIDTH(yRes), title("Title"), validationLayers({ "VK_LAYER_LUNARG_standard_validation" }) {};
	cWindow(std::string &str, uint32_t xRes = 640, uint32_t yRes = 480) :HEIGHT(xRes), WIDTH(yRes), title(str.c_str()) {};
	void run();

	bool checkValidationLayerSupport();
	void setTitle(std::string &str);
	//bool ShouldClose() { return glfwWindowShouldClose(window); }
	void GetExtensionCount(uint32_t &);

	~cWindow();
};

