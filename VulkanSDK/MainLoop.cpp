#include "MainLoop.h"

	InitVulkan init;
	CleanUp cleanUp;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {};

	void recreateSwapChain(GLFWwindow* window, VkDevice device, VkImageView depthImageView, VkImage depthImage, VkDeviceMemory depthImageMemory,
		std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
		VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
		VkSwapchainKHR swapChain, std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers,
		std::vector<VkDeviceMemory> uniformBuffersMemory, VkDescriptorPool descriptorPool, VkPhysicalDevice &physicalDevice, VkSurfaceKHR surface,
		VkExtent2D swapChainExtent, VkFormat swapChainImageFormat, VkDescriptorSetLayout descriptorSetLayout, std::vector<VkDescriptorSet> descriptorSets,
		VkImageView textureImageView, VkSampler textureSampler, VkBuffer vertexBuffer, VkBuffer indexBuffer, std::vector<uint32_t> indices, QueueFamilyIndices indice, VkImageView imageView, std::vector<Vertex> vertices) {
			int width = 0, height = 0;
			while (width == 0 || height == 0) {
				glfwGetFramebufferSize(window, &width, &height);
				glfwWaitEvents();
			}

			vkDeviceWaitIdle(device);

			cleanUp.CleanUpSwapChain(device, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool, commandBuffers,
				renderPipeline, pipelineLayout, renderPass, swapChainImageViews, swapChain, swapChainImages, uniformBuffers,
				uniformBuffersMemory, descriptorPool);

			init.createSwapChain(physicalDevice, surface, window, device, swapChain, swapChainImages, swapChainExtent, swapChainImageFormat, indice);
			init.createImageViews(swapChainImageViews, swapChainImages, device, swapChainImageFormat, imageView);
			init.createRenderPass(swapChainImageFormat, device, renderPass, physicalDevice);
			init.createRenderPipeline(device, swapChainExtent, descriptorSetLayout, pipelineLayout, renderPass, renderPipeline);
			init.createDepthImage(swapChainExtent, physicalDevice, depthImage, depthImageView, depthImageMemory, device,imageView);
			init.createFramebuffers(swapChainFramebuffers, swapChainImageViews, depthImageView, renderPass, swapChainExtent, device);
			init.createUniformBuffers(uniformBuffers, uniformBuffersMemory, swapChainImages, physicalDevice, device);
			init.createDescriptorPool(swapChainImages, device, descriptorPool);
			init.createDescriptorSets(swapChainImages, descriptorSetLayout, descriptorPool, descriptorSets, device, uniformBuffers, textureImageView, textureSampler);
			init.createCommandBuffers(commandBuffers, swapChainFramebuffers, commandPool, device, renderPass, swapChainExtent, renderPipeline, vertexBuffer, indexBuffer, pipelineLayout, descriptorSets, indices, 1080, 1920, vertices);
	}

	void updateUniformBuffer(uint32_t currentImage, VkExtent2D swapChainExtent, VkDevice device, std::vector<VkDeviceMemory> uniformBuffersMemory, float x, float y, float z) {
		static auto startTime = std::chrono::high_resolution_clock::now();

		auto currentTime = std::chrono::high_resolution_clock::now();
		float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

		UniformBufferObject ubo = {};
		ubo.model = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z));
		ubo.model = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
		ubo.model = glm::rotate(glm::mat4(1.0f), glm::radians(225+x), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		ubo.proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 10.0f);
		ubo.proj[1][1] *= -1;

		void* data;
		vkMapMemory(device, uniformBuffersMemory[currentImage], 0, sizeof(ubo), 0, &data);
		memcpy(data, &ubo, sizeof(ubo));
		vkUnmapMemory(device, uniformBuffersMemory[currentImage]);
	}

	void drawFrame(VkDevice device, std::vector<VkFence> inFlightFences, std::vector<VkFence> imagesInFlight, size_t currentFrame, VkSwapchainKHR swapChain,
		std::vector<VkSemaphore> imageAvailableSemaphores, std::vector<VkSemaphore> renderFinishedSemaphores, GLFWwindow* window, VkImageView depthImageView,
		VkImage depthImage, VkDeviceMemory depthImageMemory, std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
		VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
		std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory, bool framebufferResized,
		VkDescriptorPool descriptorPool, VkPhysicalDevice &physicalDevice, VkSurfaceKHR surface, VkQueue graphicsQueue, VkQueue presentQueue,
		VkExtent2D swapChainExtent, VkFormat swapChainImageFormat, VkDescriptorSetLayout descriptorSetLayout, std::vector<VkDescriptorSet> descriptorSets,
		VkImageView textureImageView, VkSampler textureSampler, VkBuffer vertexBuffer, VkBuffer indexBuffer, std::vector<uint32_t> indices,
		const int MAX_FRAMES_IN_FLIGHT, QueueFamilyIndices indice, VkImageView imageView, std::vector<Vertex> vertices, float x, float y, float z) {
			
		vkWaitForFences(device, 1, &inFlightFences[currentFrame], VK_TRUE, UINT64_MAX);

			uint32_t imageIndex;
			VkResult result = vkAcquireNextImageKHR(device, swapChain, UINT64_MAX, imageAvailableSemaphores[currentFrame], VK_NULL_HANDLE, &imageIndex);

			if (result == VK_ERROR_OUT_OF_DATE_KHR) {
				recreateSwapChain(window, device, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool,
					commandBuffers, renderPipeline, pipelineLayout, renderPass, swapChainImageViews, swapChain, swapChainImages,
					uniformBuffers, uniformBuffersMemory, descriptorPool, physicalDevice, surface, swapChainExtent, swapChainImageFormat,
					descriptorSetLayout, descriptorSets, textureImageView, textureSampler, vertexBuffer, indexBuffer, indices, indice, imageView, vertices);
				return;
			}
			else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
				throw std::runtime_error("failed to acquire swap chain image!");
			}

			updateUniformBuffer(imageIndex, swapChainExtent, device, uniformBuffersMemory, x, y, z);

			if (imagesInFlight[imageIndex] != VK_NULL_HANDLE) {
				vkWaitForFences(device, 1, &imagesInFlight[imageIndex], VK_TRUE, UINT64_MAX);
			}
			imagesInFlight[imageIndex] = inFlightFences[currentFrame];

			VkSubmitInfo submitInfo = {};
			submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

			VkSemaphore waitSemaphores[] = { imageAvailableSemaphores[currentFrame] };
			VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT };
			submitInfo.waitSemaphoreCount = 1;
			submitInfo.pWaitSemaphores = waitSemaphores;
			submitInfo.pWaitDstStageMask = waitStages;

			submitInfo.commandBufferCount = 1;
			submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

			VkSemaphore signalSemaphores[] = { renderFinishedSemaphores[currentFrame] };
			submitInfo.signalSemaphoreCount = 1;
			submitInfo.pSignalSemaphores = signalSemaphores;

			vkResetFences(device, 1, &inFlightFences[currentFrame]);

			if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, inFlightFences[currentFrame]) != VK_SUCCESS) {
				throw std::runtime_error("failed to submit draw command buffer!");
			}

			VkPresentInfoKHR presentInfo = {};
			presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

			presentInfo.waitSemaphoreCount = 1;
			presentInfo.pWaitSemaphores = signalSemaphores;

			VkSwapchainKHR swapChains[] = { swapChain };
			presentInfo.swapchainCount = 1;
			presentInfo.pSwapchains = swapChains;

			presentInfo.pImageIndices = &imageIndex;

			result = vkQueuePresentKHR(presentQueue, &presentInfo);

			if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR || framebufferResized) {
				framebufferResized = false;
				recreateSwapChain(window, device, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool,
					commandBuffers, renderPipeline, pipelineLayout, renderPass, swapChainImageViews, swapChain, swapChainImages,
					uniformBuffers, uniformBuffersMemory, descriptorPool, physicalDevice, surface, swapChainExtent, swapChainImageFormat,
					descriptorSetLayout, descriptorSets, textureImageView, textureSampler, vertexBuffer, indexBuffer, indices, indice, imageView, vertices);
			}
			else if (result != VK_SUCCESS) {
				throw std::runtime_error("failed to present swap chain image!");
			}

			currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
	}

	void MainLoop::Loop(VkDevice device, std::vector<VkFence> inFlightFences, std::vector<VkFence> imagesInFlight, size_t currentFrame, VkSwapchainKHR swapChain,
		std::vector<VkSemaphore> imageAvailableSemaphores, std::vector<VkSemaphore> renderFinishedSemaphores, GLFWwindow* window, VkImageView depthImageView,
		VkImage depthImage, VkDeviceMemory depthImageMemory, std::vector<VkFramebuffer> swapChainFramebuffers, VkCommandPool commandPool, std::vector<VkCommandBuffer> commandBuffers,
		VkPipeline renderPipeline, VkPipelineLayout pipelineLayout, VkRenderPass renderPass, std::vector<VkImageView> swapChainImageViews,
		std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, std::vector<VkDeviceMemory> uniformBuffersMemory, bool framebufferResized,
		VkDescriptorPool descriptorPool, VkPhysicalDevice &physicalDevice, VkSurfaceKHR surface, VkQueue graphicsQueue, VkQueue presentQueue,
		VkExtent2D swapChainExtent, VkFormat swapChainImageFormat, VkDescriptorSetLayout descriptorSetLayout, std::vector<VkDescriptorSet> descriptorSets,
		VkImageView textureImageView, VkSampler textureSampler, VkBuffer vertexBuffer, VkBuffer indexBuffer, std::vector<uint32_t> indices,
		const int MAX_FRAMES_IN_FLIGHT, QueueFamilyIndices indice, VkImageView imageView, std::vector<Vertex> vertices, float x, float y, float z) {
		while (!glfwWindowShouldClose(window)) {
			glfwPollEvents();

			glfwSetKeyCallback(window, keyCallback);
			int stateA = glfwGetKey(window, GLFW_KEY_A);
			int stateD = glfwGetKey(window, GLFW_KEY_D);

			if (stateD == GLFW_PRESS) {
				 x -= 3;
			}
			else if (stateA == GLFW_PRESS) {
				 x += 3;
			}

			drawFrame(device, inFlightFences, imagesInFlight, currentFrame, swapChain, imageAvailableSemaphores, renderFinishedSemaphores,
				window, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool, commandBuffers, renderPipeline,
				pipelineLayout, renderPass, swapChainImageViews, swapChainImages, uniformBuffers, uniformBuffersMemory, framebufferResized,
				descriptorPool, physicalDevice, surface, graphicsQueue, presentQueue, swapChainExtent, swapChainImageFormat,
				descriptorSetLayout, descriptorSets, textureImageView, textureSampler, vertexBuffer, indexBuffer, indices, MAX_FRAMES_IN_FLIGHT, indice, imageView, vertices, x, y, z);
		}

		vkDeviceWaitIdle(device);
	}