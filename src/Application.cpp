#include "Application.h"
#include <stdexcept>

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
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void Application::initVulkan(){

}