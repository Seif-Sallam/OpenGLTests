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
        Shader *m_Shader;
        Texture *m_Texture;
        VertexBufferLayout m_VBLayout;
        glm::vec3 m_TranslationA, m_TranslationB;
    };
}