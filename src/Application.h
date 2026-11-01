#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <vector>

class Application {
    public:
        void run();

    private:
        void initWindow();
        void initVulkan();
        void mainLoop();
        void cleanup();

        void createInstance();
        bool checkValidationLayerSupport();

        GLFWwindow* m_window = nullptr;
        const int m_width = 860;
        const int m_height = 640;

        VkInstance m_instance = VK_NULL_HANDLE;

        const std::vector<const char*> m_validationLayers = {
            "VK_LAYER_KHRONOS_validation"
        };

        #ifdef NDEBUG
            const bool m_enableValidationLayers = false;
        #else
            const bool m_enableValidationLayers = true;
        #endif
};