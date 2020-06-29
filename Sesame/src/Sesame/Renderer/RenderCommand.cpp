#include "ssmpch.h"
#include "RenderCommand.h"

#include "Sesame/Platform/OpenGL/OpenGLRendererAPI.h"

namespace Sesame {

    RendererAPI* RenderCommand::s_RenderAPI = new OpenGLRendererAPI;
}