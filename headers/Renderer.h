#pragma once
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <assert.h>

#include "Vec.h"

#define ASSERT(x) \
    if (!(x))     \
        throw;

#define GLCall(x)   \
    GLClearError(); \
    x;              \
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();

bool GLLogCall(const char *function, const char *file, int line);

class IndexBuffer;
class VertexArray;
class Shader;

class Renderer
{
public:
    static void Clear();
    static void Draw(const VertexArray &va, const IndexBuffer &ib, const Shader &shader);
};