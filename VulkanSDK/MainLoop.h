#ifndef _MainLoop_h_
#define _MainLoop_h_

	#include <glm\trigonometric.hpp>
	#include <glm\ext\matrix_transform.hpp>
	#include <glm\ext\matrix_clip_space.hpp>

	#include "CleanUp.h"
	#include "InitVulkan.h"


	class MainLoop {
	public:
		void Loop(VkDevice device, std::vector<VkFence> inFlightFences, std::vector<VkFence> imagesInFlight, size_t currentFrame, VkSwapchainKHR swapChain,
			std::vector<VkSemaphore> imageAvailableSemaphores, std::vector<VkSemaphore> renderFinishedSemaphores, GLFWwindow* window, VkImageView depthImageView,
			VkImage depthImage, VkDeviceMemory depthImageMemory, std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
			VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
			std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory, bool framebufferResized,
			VkDescriptorPool descriptorPool, VkPhysicalDevice &physicalDevice, VkSurfaceKHR surface, VkQueue graphicsQueue, VkQueue presentQueue,
			VkExtent2D swapChainExtent, VkFormat swapChainImageFormat, VkDescriptorSetLayout descriptorSetLayout, std::vector<VkDescriptorSet> descriptorSets,
			VkImageView textureImageView, VkSampler textureSampler, VkBuffer vertexBuffer, VkBuffer indexBuffer, std::vector<uint32_t> indices,
			const int MAX_FRAMES_IN_FLIGHT, QueueFamilyIndices indice, VkImageView imageView, std::vector<Vertex> vertices, float x, float y, float z);
	};
#endif

