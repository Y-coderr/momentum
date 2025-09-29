#include "Shader.hpp"

#include <fstream>
#include <sstream>

#include <iostream>
bool Shader::checkErrors(const unsigned int shader_id)
{
	{
		int result;
		glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			int length;
			glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
			char* error = (char*)malloc(length * sizeof(char));
			glGetShaderInfoLog(shader_id, length, &length, error);
			std::cout << "GLSL-ERROR >" << error << "\n";
			return true;
		}
	}
	return false;
}
Shader::Shader(const std::string vertexpath, const std::string fragpath)
{
	try {
		unsigned int vert_id, frag_id;

		std::cout << "Loading vertex shader from: " << vertexpath << std::endl;
		std::ifstream V_file_stream(vertexpath);
		if (!V_file_stream) {
			throw std::runtime_error("Failed to open vertex shader file: " + vertexpath);
		}

		std::stringstream vertCache;
		vertCache << V_file_stream.rdbuf();
		V_file_stream.close();
		std::string vertSource = vertCache.str();
		const char* vertstr = vertSource.c_str();

		std::cout << "Loading fragment shader from: " << fragpath << std::endl;
		std::ifstream F_file_stream(fragpath);
		if (!F_file_stream) {
			throw std::runtime_error("Failed to open fragment shader file: " + fragpath);
		}

		std::stringstream fragCache;
		fragCache << F_file_stream.rdbuf();
		F_file_stream.close();
		std::string fragSource = fragCache.str();
		const char* fragstr = fragSource.c_str();

		vert_id = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vert_id, 1, &vertstr, nullptr);
		glCompileShader(vert_id);

		frag_id = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(frag_id, 1, &fragstr, nullptr);
		glCompileShader(frag_id);

		if (checkErrors(vert_id)) {
			throw std::runtime_error("Vertex shader compilation failed");
		}
		if (checkErrors(frag_id)) {
			throw std::runtime_error("Fragment shader compilation failed");
		}


		m_prog_id = glCreateProgram();
		glAttachShader(m_prog_id, vert_id);
		glAttachShader(m_prog_id, frag_id);
		glLinkProgram(m_prog_id);

		glDeleteShader(vert_id);
		glDeleteShader(frag_id);


		try {
			m_model_loc = glGetUniformLocation(m_prog_id, "ModelMatrix");
			if (m_model_loc == -1)throw "SHADER > Model mat defination not found\n";

			m_view_loc = glGetUniformLocation(m_prog_id, "ViewMatrix");
			if (m_view_loc == -1)throw "SHADER > View mat defination not found\n";

            m_pers_loc = glGetUniformLocation(m_prog_id, "ProjMatrix");
            if (m_pers_loc == -1) {
                throw std::runtime_error("Perspective matrix definition not found");
            }

            m_color_loc = glGetUniformLocation(m_prog_id, "u_Color");
            if (m_color_loc == -1) {
                throw std::runtime_error("Color uniform not found");
            }			glUseProgram(0);
			std::cout << "[DEBUG]=> Shader Loaded !\n";
		}
		catch (const std::runtime_error& e) {
			std::cerr << "Shader error: " << e.what() << std::endl;
			throw;
		}
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		throw;
	}
}

void Shader::upload2GPU(matrix_type type, const float* Value)
{
	switch (type)
	{
	case MODEL:
		glUniformMatrix4fv(m_model_loc, 1, GL_FALSE, Value);
		break;
	case VIEW:
		glUniformMatrix4fv(m_view_loc, 1, GL_FALSE, Value);
		break;
	case PERS:
		glUniformMatrix4fv(m_pers_loc, 1, GL_FALSE, Value);
		break;
	default:
		std::cout << "AMAN > wrong type to upload matrix to GPU\n";
		break;
	}
}

void Shader::Activate()
{
    glUseProgram(m_prog_id);
}

void Shader::setColor(float r, float g, float b, float a)
{
    glUniform4f(m_color_loc, r, g, b, a);
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(m_prog_id);
}
