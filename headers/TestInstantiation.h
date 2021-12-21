#include "Test.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_integer.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Renderer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"

namespace test
{
    class TestInstantiation : public Test
    {
    public:
        TestInstantiation();
        ~TestInstantiation();
        void OnUpdate(float deltaTime) override;
        void OnImGuiRender() override;
        void OnRender() override;

    private:
        void AddEntity(const glm::vec3 &transformation, const glm::vec4 &color);

        std::vector<glm::vec3> m_Transformations;
        std::vector<glm::vec4> m_Colors;
        VertexArray m_VAO;
        VertexBuffer *m_VBO;
        VertexBufferLayout m_Layout;
        IndexBuffer *m_IBO;
        Shader *m_Shader;
    };
}