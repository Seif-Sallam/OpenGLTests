#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include <assert.h>

#define ASSERT(x) \
    if (!(x))     \
        throw;

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{
public:
    void Clear() const;
    void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
};