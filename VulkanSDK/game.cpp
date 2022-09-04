#include "Window.h"
#include "InitVulkan.h"
#include "Device.h"
#include "MainLoop.h"
#include "Cleanup.h"
#include "Model.h"


class Game : public InitVulkan, public Device, public MainLoop, public CleanUp, public Window {
public:
	Game() {};
};

int main(){
	
	Game game;

	GLFWwindow* window = glfwCreateWindow(0, 0, "", nullptr, nullptr);
	float x = 2.0f, y = 2.0f, z = 2.0f;

	VkInstance instance = 0;
	VkDebugUtilsMessengerEXT debugMessenger = 0;
	VkSurfaceKHR surface = 0;

	QueueFamilyIndices indice;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice device = 0;

	VkQueue graphicsQueue = 0;
	VkQueue presentQueue = 0;

	VkSwapchainKHR swapChain = 0;
	VkImageView imageView = NULL;
	std::vector<VkImage> swapChainImages;
	VkFormat swapChainImageFormat = {};
	VkExtent2D swapChainExtent = {};
	std::vector<VkImageView> swapChainImageViews;
	std::vector<VkFramebuffer> swapChainFramebuffers;

	VkRenderPass renderPass = 0;
	VkDescriptorSetLayout descriptorSetLayout = 0;
	VkPipelineLayout pipelineLayout = 0;
	VkPipeline renderPipeline = 0;

	VkCommandPool commandPool = 0;

	VkImage depthImage = 0;
	VkDeviceMemory depthImageMemory = 0;
	VkImageView depthImageView = 0;

	VkImage textureImage = 0;
	VkDeviceMemory textureImageMemory = 0;
	VkImageView textureImageView = 0;
	VkSampler textureSampler = 0;

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	VkBuffer vertexBuffer = 0;
	VkDeviceMemory vertexBufferMemory = 0;
	VkBuffer indexBuffer = 0;
	VkDeviceMemory indexBufferMemory = 0;

	std::vector<VkBuffer> uniformBuffers;
	std::vector<VkDeviceMemory> uniformBuffersMemory;

	VkDescriptorPool descriptorPool = 0;
	std::vector<VkDescriptorSet> descriptorSets;

	std::vector<VkCommandBuffer> commandBuffers;

	std::vector<VkSemaphore> imageAvailableSemaphores;
	std::vector<VkSemaphore> renderFinishedSemaphores;
	std::vector<VkFence> inFlightFences;
	std::vector<VkFence> imagesInFlight;
	size_t currentFrame = 0;

	bool framebufferResized = false;

	const std::vector<const char*> deviceExtensions = {
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
	};

	const std::string MODEL_PATH = "models/house.obj";
	std::string TEXTURE_PATH = "textures/house.jpg";

		Model model(MODEL_PATH, vertices, indices);


		game.initWindow(window, 1920, 1080);


		game.createInstance(enableValidationLayers, validationLayers, instance);

		game.createSurface(instance, window, surface);


		game.pickPhysicalDevice(instance, physicalDevice, surface, deviceExtensions, indice);

		game.createLogicalDevice(physicalDevice, deviceExtensions, enableValidationLayers, validationLayers, device, graphicsQueue, presentQueue, indice);

		game.createSwapChain(physicalDevice, surface, window, device, swapChain, swapChainImages, swapChainExtent, swapChainImageFormat, indice);
		game.createImageViews(swapChainImageViews, swapChainImages, device, swapChainImageFormat, imageView);
		game.createRenderPass(swapChainImageFormat, device, renderPass, physicalDevice);
		game.createDescriptorSetLayout(device, descriptorSetLayout);
		game.createRenderPipeline(device, swapChainExtent, descriptorSetLayout, pipelineLayout, renderPass, renderPipeline);
		game.createCommandPool(physicalDevice, device, surface, commandPool, indice);
		game.createDepthImage(swapChainExtent, physicalDevice, depthImage, depthImageView, depthImageMemory, device, imageView);
		game.createFramebuffers(swapChainFramebuffers, swapChainImageViews, depthImageView, renderPass, swapChainExtent, device);
		game.createTextureImage(TEXTURE_PATH, device, commandPool, graphicsQueue, textureImage, textureImageMemory, physicalDevice);
		game.createTextureImageView(textureImageView, textureImage, device, imageView);
		game.createTextureSampler(device, textureSampler);
		game.createVertexAndIndexBuffer(vertices, indices, device, commandPool, graphicsQueue, vertexBuffer,  vertexBufferMemory, indexBuffer, indexBufferMemory, physicalDevice);
		game.createUniformBuffers(uniformBuffers, uniformBuffersMemory, swapChainImages, physicalDevice, device);
		game.createDescriptorPool(swapChainImages, device, descriptorPool);
		game.createDescriptorSets(swapChainImages, descriptorSetLayout, descriptorPool, descriptorSets, device, uniformBuffers, textureImageView, textureSampler);
		game.createCommandBuffers(commandBuffers, swapChainFramebuffers, commandPool, device, renderPass, swapChainExtent, renderPipeline, vertexBuffer, indexBuffer, pipelineLayout, descriptorSets, indices, 1920, 1080, vertices);
		game.createSyncObjects(imageAvailableSemaphores, renderFinishedSemaphores, inFlightFences, imagesInFlight, 2, swapChainImages, device);

		game.Loop(device, inFlightFences, imagesInFlight, currentFrame, swapChain, imageAvailableSemaphores, renderFinishedSemaphores, window,
			depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool, commandBuffers, renderPipeline, pipelineLayout, renderPass,
			swapChainImageViews, swapChainImages, uniformBuffers, uniformBuffersMemory, framebufferResized, descriptorPool, physicalDevice, surface, graphicsQueue,
			presentQueue, swapChainExtent, swapChainImageFormat, descriptorSetLayout, descriptorSets, textureImageView, textureSampler, vertexBuffer,
			indexBuffer, indices, 2, indice, imageView, vertices, x, y, z);

		game.DestroyResources(device, depthImageView, depthImage, depthImageMemory, swapChainFramebuffers, commandPool, commandBuffers, renderPipeline,
			pipelineLayout, renderPass, swapChainImageViews, swapChain, swapChainImages, uniformBuffers, uniformBuffersMemory, descriptorPool, textureSampler,
			textureImageView, textureImage, textureImageMemory, descriptorSetLayout, indexBuffer, vertexBufferMemory, vertexBuffer, indexBufferMemory, 2,
			renderFinishedSemaphores, imageAvailableSemaphores, inFlightFences, instance, surface, debugMessenger, enableValidationLayers, window);
	
}
