#ifndef __CleanUp_h
#define __CleanUp_h

	#include <vulkan\vulkan_core.h>
	#include <vector>
	#include <GLFW\glfw3.h>

	class CleanUp {
	public:

		void CleanUpSwapChain(VkDevice device, VkImageView depthImageView, VkImage depthImage, VkDeviceMemory depthImageMemory,
			std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
			VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
			VkSwapchainKHR swapChain, std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory, VkDescriptorPool descriptorPool);

		void DestroyResources(VkDevice device, VkImageView depthImageView, VkImage depthImage, VkDeviceMemory depthImageMemory,
			std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
			VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
			VkSwapchainKHR swapChain, std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory,
			VkDescriptorPool descriptorPool, VkSampler textureSampler, VkImageView textureImageView, VkImage textureImage, VkDeviceMemory textureImageMemory,
			VkDescriptorSetLayout descriptorSetLayout, VkBuffer indexBuffer, VkDeviceMemory vertexBufferMemory, VkBuffer vertexBuffer, VkDeviceMemory indexBufferMemory,
			const int MAX_FRAMES_IN_FLIGHT, std::vector<VkSemaphore> renderFinishedSemaphores, std::vector<VkSemaphore> imageAvailableSemaphores,
			std::vector<VkFence> inFlightFences, VkInstance instance, VkSurfaceKHR surface, VkDebugUtilsMessengerEXT debugMessenger, const bool enableValidationLayers,
			GLFWwindow* window);
	};

#endif