#include "application.h"

Application* Application::instance = nullptr;

Application* Application::getInstance(){
    if(instance == nullptr){
        instance = new Application();
    }
    return instance;
}

bool Application::init(const uint32_t width, const uint32_t height){
    this->width = width;
    this->height = height;

    // 初始化GLFW
    if (!glfwInit()){
        std::cout << "glfwInit Failed" << std::endl;
       return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // 创建窗口
    window = glfwCreateWindow(800, 600, "Example", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Create windows Failed" << std::endl;
        return false;
    }
    glfwMakeContextCurrent(window);

     // 初始化GLEW0
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(window, realFbResizeCallback);
    glfwSetKeyCallback(window, realKeyCallback);
    glfwSetWindowUserPointer(window, this);


    return true;
}

bool Application::update(){
    if(glfwWindowShouldClose(window)){
        std::cout << "glfwWindowShouldClose " << std::endl;
        return false;
    }
    glfwSwapBuffers(window);
    glfwPollEvents();
    
    return true;
}

void Application::destory(){
    glfwTerminate();
}

void Application::realFbResizeCallback(GLFWwindow* window, int width, int height){
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    self->frameBufferResizeCallback(width, height);
}

void Application::realKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application *self = (Application *)glfwGetWindowUserPointer(window);
    self->keyCallback(key, scancode, action,  mods);
}

Application::Application()
{
    
}

Application::~Application()
{
}