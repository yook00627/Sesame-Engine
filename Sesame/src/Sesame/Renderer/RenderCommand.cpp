#include "ssmpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sesame {

    RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI;
}