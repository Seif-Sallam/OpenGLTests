#include "Test.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"

namespace test
{
    class TestTexture : public Test
    {
    public:
        TestTexture();
        ~TestTexture();

        void OnImGuiRender() override;
        void OnRender() override;

    private:
        VertexArray m_VAO;
        VertexBuffer *m_VBO;
        IndexBuffer *m_IBO;
        VertexBufferLayout m_VBLayout;
        Shader *m_Shader;
        Texture *m_Texture;
        glm::vec3 m_TranslationA, m_TranslationB;
    };
}