#include "Application.h"
#include <stdexcept>
#include <iostream>
#include <cstring>

void Application::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
}

void Application::initWindow() {
    int glfw_init = glfwInit();

    if(glfw_init == GLFW_FALSE){
        throw std::runtime_error("Erro ao inicializar GLFW");
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    m_window = glfwCreateWindow(m_width, m_height, "Naive Engine", nullptr, nullptr);

    // erro ao criar a janela? Encerra o processo
    if(m_window == nullptr){
        glfwTerminate();
        throw std::runtime_error("Erro ao criar janela");
    }

}

void Application::mainLoop() {
    while(!glfwWindowShouldClose(m_window)){
        glfwPollEvents();
    }
}

void Application::cleanup(){
    vkDestroyInstance(m_instance, nullptr);
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::initVulkan(){
    createInstance();
}

void Application::createInstance(){
    //se queremos uma layer, ela precisa existir
    if(m_enableValidationLayers && !checkValidationLayerSupport()){
        throw std::runtime_error("Validation layers pedidas, mas não disponíveis.");
    }

    //informações do programa
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Naive Engine App";
    appInfo.applicationVersion = VK_MAKE_API_VERSION(0,1,0,0);
    appInfo.pEngineName = "Naive Engine";
    appInfo.engineVersion = VK_MAKE_API_VERSION(0,1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_3;


    //extensões para o GLFW
    uint32_t glfwExtensionCount = 0;
    const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    //config da instance

    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions;

    //ativar as validation layers
    if(m_enableValidationLayers){
        createInfo.enabledLayerCount = static_cast<uint32_t>(m_validationLayers.size());
        createInfo.ppEnabledLayerNames = m_validationLayers.data();
        std::cout << "Validation layers ativadas\n";
    } else {
        createInfo.enabledLayerCount = 0;
    }

    //criar instance
    VkResult result = vkCreateInstance(&createInfo, nullptr, &m_instance);
    if(result != VK_SUCCESS){
        throw std::runtime_error("Erro ao criar instância vulkan");
    }
    std::cout << "Instancia Vulkan criada!\n";
}

bool Application::checkValidationLayerSupport(){
    //quantas layers existe?
    uint32_t layerCount = 0;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    //informações das layers
    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    //para cada layer que queremos
    for(const char* layerName : m_validationLayers){
        bool found = false;

        //procura na lista
        for(const VkLayerProperties& layer : availableLayers){
            if(strcmp(layerName, layer.layerName) == 0){
                found = true;
                break;
            }
        }

        if(!found){
            return false;
        }
    }
    return true;
}