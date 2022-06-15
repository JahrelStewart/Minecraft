#include "../Headers/utility.h"

Shaders readShaders(const std::string& file) {
    std::ifstream stream(file);

    enum class whichShader {
        EMPTY = -1, FLOORVERTEXSHADER, CUBEVERTEXSHADER, FRAGMENTSHADER
    };

    std::stringstream shaderStream[3];
    std::string line;
    whichShader which = whichShader::EMPTY;

    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("GridVertexShader") != std::string::npos) {
                which = whichShader::FLOORVERTEXSHADER;
            }
            else if (line.find("CubeVertexShader") != std::string::npos) {
                which = whichShader::CUBEVERTEXSHADER;
            }
            else if (line.find("GridFragmentShader") != std::string::npos) {
                which = whichShader::FRAGMENTSHADER;
            }
        }
        else {
            if (which != whichShader::EMPTY) {
                shaderStream[(int) which] << line << "\n";
            }
        }
    }

    return { shaderStream[0].str(), shaderStream[1].str(), shaderStream[2].str() };
}

//Function gets the shaders and determine if they can be compiled properly
static int setupVertexAndFragmentShader(GLuint shaderType, const std::string& shaderSRC) {
    int shader = glCreateShader(shaderType);
    const char* shaderSource = shaderSRC.c_str();
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cerr << shaderSource << std::endl;
    }

    return shader;
}

//Function that gets the vertex and fragment shader and checks to make sure the linking was successful
int compileAndLinkShaders(const std::string& vertexShaderSRC, const std::string& fragmentShaderSRC, const std::string* geometryShaderSRC) {
    // TODO
    // compile and link shader program
    // return shader program id
    // ------------------------------------

    // vertex shader
    int vertexShader = setupVertexAndFragmentShader(GL_VERTEX_SHADER, vertexShaderSRC);
    // fragment shader
    int fragmentShader = setupVertexAndFragmentShader(GL_FRAGMENT_SHADER, fragmentShaderSRC);

    int geometryShader;
    if (geometryShaderSRC != nullptr) {
        geometryShader = setupVertexAndFragmentShader(GL_GEOMETRY_SHADER, *geometryShaderSRC);
    }

    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    if (geometryShaderSRC != nullptr)
        glAttachShader(shaderProgram, geometryShader);
    glLinkProgram(shaderProgram);

    int success;
    char infoLog[512];
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    if (geometryShaderSRC != nullptr)
        glDeleteShader(geometryShader);

    return shaderProgram;

}