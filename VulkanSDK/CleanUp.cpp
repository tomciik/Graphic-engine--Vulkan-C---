#include "CleanUp.h"

	void CleanUp::CleanUpSwapChain(VkDevice device, VkImageView depthImageView, VkImage depthImage, VkDeviceMemory depthImageMemory,
		std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
		VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
		VkSwapchainKHR swapChain, std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory, VkDescriptorPool descriptorPool) {
		vkDestroyImageView(device, depthImageView, nullptr);
		vkDestroyImage(device, depthImage, nullptr);
		vkFreeMemory(device, depthImageMemory, nullptr);

		for (auto framebuffer : swapChainFramebuffers) {
			vkDestroyFramebuffer(device, framebuffer, nullptr);
		}

		vkFreeCommandBuffers(device, commandPool, static_cast<uint32_t>(commandBuffers.size()), commandBuffers.data());

		vkDestroyPipeline(device, renderPipeline, nullptr);
		vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
		vkDestroyRenderPass(device, renderPass, nullptr);

		for (auto imageView : swapChainImageViews) {
			vkDestroyImageView(device, imageView, nullptr);
		}

		vkDestroySwapchainKHR(device, swapChain, nullptr);

		for (size_t i = 0; i < swapChainImages.size(); i++) {
			vkDestroyBuffer(device, uniformBuffers[i], nullptr);
			vkFreeMemory(device, uniformBuffersMemory[i], nullptr);
		}

		vkDestroyDescriptorPool(device, descriptorPool, nullptr);
	}

	void CleanUp::DestroyResources(VkDevice device, VkImageView depthImageView, VkImage depthImage, VkDeviceMemory depthImageMemory,
		std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
		VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
		VkSwapchainKHR swapChain, std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory,
		VkDescriptorPool descriptorPool, VkSampler textureSampler, VkImageView textureImageView, VkImage textureImage, VkDeviceMemory textureImageMemory,
		VkDescriptorSetLayout descriptorSetLayout, VkBuffer indexBuffer, VkDeviceMemory vertexBufferMemory, VkBuffer vertexBuffer, VkDeviceMemory indexBufferMemory,
		const int MAX_FRAMES_IN_FLIGHT, std::vector<VkSemaphore> renderFinishedSemaphores, std::vector<VkSemaphore> imageAvailableSemaphores,
		std::vector<VkFence> inFlightFences, VkInstance instance, VkSurfaceKHR surface, VkDebugUtilsMessengerEXT debugMessenger, const bool enableValidationLayers,
		GLFWwindow* window) {
		CleanUpSwapChain(device, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool,
			commandBuffers, renderPipeline, pipelineLayout, renderPass, swapChainImageViews, swapChain, swapChainImages,
			uniformBuffers, uniformBuffersMemory, descriptorPool);

		vkDestroySampler(device, textureSampler, nullptr);
		vkDestroyImageView(device, textureImageView, nullptr);

		vkDestroyImage(device, textureImage, nullptr);
		vkFreeMemory(device, textureImageMemory, nullptr);

		vkDestroyDescriptorSetLayout(device, descriptorSetLayout, nullptr);

		vkDestroyBuffer(device, indexBuffer, nullptr);
		vkFreeMemory(device, indexBufferMemory, nullptr);

		vkDestroyBuffer(device, vertexBuffer, nullptr);
		vkFreeMemory(device, vertexBufferMemory, nullptr);

		for (size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
			vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
			vkDestroyFence(device, inFlightFences[i], nullptr);
		}

		vkDestroyCommandPool(device, commandPool, nullptr);

		vkDestroyDevice(device, nullptr);

		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);

		glfwDestroyWindow(window);

		glfwTerminate();
	}
