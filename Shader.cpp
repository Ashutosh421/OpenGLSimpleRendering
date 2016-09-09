#include "Shader.h"

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string LoadShader(const std::string& fileName);
static GLuint CreateShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
	//Create a Shader Program
	m_program = glCreateProgram();

	//Create Shaders
	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"), GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"), GL_FRAGMENT_SHADER);

	//Attach the Shaders to the Shader Program
	for (unsigned int i = 0; i < NUM_SHADERS; i ++) {
		glAttachShader(m_program, m_shaders[i]);
	}

	//Set Attribute Location - Variables to be read from the Shader Program
	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "textCord");
	glBindAttribLocation(m_program, 2, "normal");

	//Linking the Shader Program
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Shader Program Linking Failed");

	//After Linking check if the Shader Program is Valid
	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Shader Program Validation Failed");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}


Shader::~Shader()
{
	//Detach the Shaders
	for (unsigned int i = 0; i < NUM_SHADERS; i ++) {
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	//Delete the Shader Program
	glDeleteProgram(m_program);
}

void Shader::Bind() {
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform, const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1 , GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const std::string& text, GLenum shaderType) 
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0) {
		std::cerr << "Error! Shader creation failed!" << std::endl;
	}

	const GLchar* shaderSourceStrings[1];
	GLint shaderSourceStringLengths[1];

	shaderSourceStrings[0] = text.c_str();
	shaderSourceStringLengths[0] = text.length();

	glShaderSource(shader,1, shaderSourceStrings, shaderSourceStringLengths);
	glCompileShader(shader);
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error! Shader Compilation Failed");	
	
	return shader;
}

/*
	Loading the Shader File 
*/
static std::string LoadShader(const std::string& fileName) {
	std::ifstream file;
	file.open(fileName.c_str());

	std::string output;
	std::string line;

	if (file.is_open()) {
		while (file.good()) {
			getline(file,line);
			output.append(line + "\n");
		//	std::cout << line << "\n";
		}
	}
	else {
		std::cerr << "Unable to Load the Shader "<< fileName << std::endl;
	}
	return output;
}

/*
	Checking for any Shader Errors
*/

static void CheckShaderError(GLuint shader, GLuint flag,bool isProgram, const std::string& errorMessage) {
	GLint success = 0;
	GLchar error[1024] = { 0 };

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);

		std::cerr << errorMessage << ": '" << error << "'" << std::endl;
	}
}
