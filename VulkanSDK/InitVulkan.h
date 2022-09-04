#ifndef __InitVulkan_h
#define __InitVulkan_h
	
	#define GLFW_INCLUDE_VULKAN
	#include <GLFW/glfw3.h>

	#include <iostream>
	#include <fstream>
	#include <stdexcept>
	#include <algorithm>
	#include <chrono>
	#include <vector>
	#include <cstring>
	#include <cstdlib>
	#include <cstdint>
	#include <optional>
	#include <set>

	#include "Device.h"
	#include "Model.h"

	const std::vector<const char*> validationLayers = {
		"VK_LAYER_KHRONOS_validation"
	};

#ifdef NDEBUG
	const bool enableValidationLayers = false;
#else
	const bool enableValidationLayers = true;
#endif

struct UniformBufferObject {
		alignas(16) glm::mat4 model;
		alignas(16) glm::mat4 view;
		alignas(16) glm::mat4 proj;
	};

	class InitVulkan {
		
		public:
			void createInstance(const bool enableValidationLayers, const std::vector<const char*> validationLayers, VkInstance &instance);

			//
			void createSurface(VkInstance instance, GLFWwindow* &window, VkSurfaceKHR &surface);

			//
			void createSwapChain(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window, VkDevice device, VkSwapchainKHR &swapChain,
				std::vector<VkImage>& swapChainImages, VkExtent2D &swapChainExtent, VkFormat &swapChainImageFormat, QueueFamilyIndices indices);

			//
			void createImageViews(std::vector<VkImageView> &swapChainImageViews, std::vector<VkImage> swapChainImages, VkDevice device, VkFormat swapChainImageFormat, VkImageView &imageView);

			//
			void createRenderPass(VkFormat swapChainImageFormat, VkDevice device, VkRenderPass &renderPass, VkPhysicalDevice physicalDevice);

			//
			void createDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout &descriptorSetLayout);

			//
			void createRenderPipeline(VkDevice device, VkExtent2D swapChainExtent, VkDescriptorSetLayout descriptorSetLayout, VkPipelineLayout& pipelineLayout,
				VkRenderPass renderPass, VkPipeline& renderPipeline);

			//
			void createCommandPool(VkPhysicalDevice &physicalDevice, VkDevice device, VkSurfaceKHR surface, VkCommandPool &commandPool, QueueFamilyIndices indices);

			//
			void createDepthImage(VkExtent2D swapChainExtent, VkPhysicalDevice physicalDevice, VkImage& depthImage, VkImageView& depthImageView, VkDeviceMemory& depthImageMemory, VkDevice device, VkImageView& imageView);

			//
			void createFramebuffers(std::vector<VkFramebuffer>& swapChainFramebuffers, std::vector<VkImageView> swapChainImageViews, VkImageView depthImageView,
				VkRenderPass renderPass, VkExtent2D swapChainExtent, VkDevice device);

			//
			void createTextureImage(const std::string TEXTURE_PATH, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue,
				VkImage &textureImage, VkDeviceMemory &textureImageMemory, VkPhysicalDevice physicalDevice);

			//
			void createTextureImageView(VkImageView &textureImageView, VkImage &textureImage, VkDevice device, VkImageView &imageView);

			//
			void createTextureSampler(VkDevice device, VkSampler &textureSampler);

			//
			void createVertexAndIndexBuffer(std::vector<Vertex> vertices, std::vector<uint32_t> indices, VkDevice device, VkCommandPool commandPool, VkQueue graphicsQueue,
				VkBuffer& vertexBuffer, VkDeviceMemory& vertexBufferMemory, VkBuffer& indexBuffer, VkDeviceMemory& indexBufferMemory, VkPhysicalDevice physicalDevice);

			//
			void createUniformBuffers(std::vector<VkBuffer>& uniformBuffers, std::vector<VkDeviceMemory>& uniformBuffersMemory, std::vector<VkImage> swapChainImages,
				VkPhysicalDevice physicalDevice, VkDevice device);

			//
			void createDescriptorPool(std::vector<VkImage> swapChainImages, VkDevice device, VkDescriptorPool &descriptorPool);

			void createDescriptorSets(std::vector<VkImage> swapChainImages, VkDescriptorSetLayout descriptorSetLayout, VkDescriptorPool descriptorPool,
				std::vector<VkDescriptorSet>& descriptorSets, VkDevice device, std::vector<VkBuffer> uniformBuffers, VkImageView textureImageView, VkSampler textureSampler);

			//
			void createCommandBuffers(std::vector<VkCommandBuffer>& commandBuffers, std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, VkDevice device,
				VkRenderPass renderPass, VkExtent2D swapChainExtent, VkPipeline renderPipeline, VkBuffer vertexBuffer, VkBuffer indexBuffer,
				VkPipelineLayout pipelineLayout, std::vector<VkDescriptorSet> descriptorSets, std::vector<uint32_t> indices, uint32_t width, uint32_t height, std::vector<Vertex> vertices);

			//
			void createSyncObjects(std::vector<VkSemaphore> &imageAvailableSemaphores, std::vector<VkSemaphore> &renderFinishedSemaphores, std::vector<VkFence> &inFlightFences,
				std::vector<VkFence> &imagesInFlight, const int MAX_FRAMES_IN_FLIGHT, std::vector<VkImage> swapChainImages, VkDevice device);
	};

#endif