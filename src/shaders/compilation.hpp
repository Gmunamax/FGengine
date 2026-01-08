#include "FGengine/shaders/shader.hpp"

static std::string ReadFile(const char*);
static GLuint CompilePart(Shader::ObjectDescription);
static void PrintLinkStatus(GLuint);
static std::vector<GLuint> CompileAllParts(std::vector<Shader::ObjectDescription>);
static GLuint LinkShader(std::vector<GLuint>);
static void DeleteParts(std::vector<GLuint>);