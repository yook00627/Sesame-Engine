#include "ssmpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Sesame {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle) 
    {
        SSM_CORE_ASSERT(windowHandle, "Failed Window handle is null")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        SSM_CORE_ASSERT(status, "Failed to initialize Glad");

        SSM_CORE_INFO("OpenGL Vendor: {0}", glGetString(GL_VENDOR));
        SSM_CORE_INFO("OpenGL Renderer: {0}", glGetString(GL_RENDERER));
        SSM_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}