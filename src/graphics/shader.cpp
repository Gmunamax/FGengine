// FGengine - a free and open-source library for game development
// Copyright (C) 2025, 2026 Gmunamax <https://github.com/Gmunamax/FGengine>

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, see <https://www.gnu.org/licenses/>.
#include <FGengine/graphics/shader.hpp>
#include <gl/gl.hpp>
#include <print>

using namespace FGengine::Graphics;

Shader::Shader(std::string_view vertexShader, std::string_view fragmentShader){
	unsigned int vert = CreateShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int frag = CreateShader(GL_FRAGMENT_SHADER, fragmentShader);
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vert);
	glAttachShader(shaderProgram, frag);
	glLinkProgram(shaderProgram);
	glDeleteShader(vert);
	glDeleteShader(frag);
}

void Shader::Use(){
	glUseProgram(shaderProgram);
}

unsigned int Shader::CreateShader(GLenum type, std::string_view source){
	unsigned int shader = glCreateShader(type);
	const char* csource = source.data();
	glShaderSource(shader, 1, &csource, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::println("ERROR::SHADER::COMPILATION_FAILED");
		std::println("{}", infoLog);
	}
	return shader;
}
