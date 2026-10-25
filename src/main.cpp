#include <iostream>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

int main(){
    std::cout << "Engine iniciando...";
    int glfw_init = glfwInit();
    if(glfw_init == GLFW_FALSE){
        std::cerr << "Erro ao inicializar GLFW";
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    const int largura = 860;
    const int altura = 640;
    GLFWwindow* janela = glfwCreateWindow(largura, altura, "título", nullptr, nullptr);

    // erro ao criar a janela? Encerra o processo
    if(janela == nullptr){
        std::cerr << "Erro ao criar janela";
        glfwTerminate();
        return -1;
    }

    while(!glfwWindowShouldClose(janela)){
        glfwPollEvents();
    }
    glfwDestroyWindow(janela);
    glfwTerminate();
    return 0;
}