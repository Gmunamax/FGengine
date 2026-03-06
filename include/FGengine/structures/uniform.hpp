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
#pragma once
#include <glm/matrix.hpp>
#include <GL/glew.h>
#include "FGengine/special/shader.hpp"

namespace FGengine{

class _Uniform{
	const char* name;
	GLuint shaderId = 0;

	void UpdateLocation(){
		glUseProgram(shaderId);
		location = glGetUniformLocation(shaderId, name);
	}

protected:
	GLint location = 0;

	template<typename ValueType>
	void TemplateSend(unsigned count, const ValueType* value) const;

public:
	const char* GetName() const{
		return name;
	}

	void SetShader(const GLuint& newshader){
		this->shaderId = newshader;
		UpdateLocation();
	}

	const GLuint& GetShader() const{
		return shaderId;
	}

	_Uniform(const char* name): name(name) {}
	_Uniform(const char* name, const Shader& shader): name(name), shaderId(shader.ToGL()) {
		UpdateLocation();
	}
};

template<unsigned Count, typename ValueType>
class Uniform: public _Uniform{

	ValueType value[Count];

	void SetValue(const ValueType newvalue[Count]){
		for(unsigned e = 0; e < Count; ++e){
			value[e] = newvalue[e];
		}
	}

public:
	const ValueType* GetValue() const{
		return value;
	}

	void Send() const{
		glUseProgram(GetShader());
		TemplateSend(Count, value);
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ValueType value[Count]): _Uniform(name) {
		SetValue(value);
	}
	Uniform(const char* const name, const Shader& shader): _Uniform(name, shader) {}
	Uniform(const char* const name, const Shader& shader, const ValueType value[Count]): _Uniform(name, shader){
		SetValue(value);
	}

	void operator=(const ValueType newvalue[Count]){
		SetValue(newvalue);
	}
	const ValueType& operator[](const unsigned index) const{
		return Uniform::value[index];
	}
};

template<typename ValueType>
class Uniform<1, ValueType>: public _Uniform{

	ValueType value;

	void TemplateSend() const;

public:
	const ValueType& GetValue() const{
		return value;
	}
	void Send() const{
		glUseProgram(GetShader());
		TemplateSend();
	}

	Uniform(const char* const name): _Uniform(name) {}
	Uniform(const char* const name, const ValueType& value): _Uniform(name), value(value) {}
	Uniform(const char* const name, const Shader& shader): _Uniform(name, shader) {}
	Uniform(const char* const name, const Shader& shader, const ValueType& value): _Uniform(name, shader), value(value) {}

	void operator=(const ValueType& newvalue){
		Uniform::value = newvalue;
	}
};

using Umat4d = Uniform<1, glm::dmat4>;
using Umat4f = Uniform<1, glm::mat4>;
using Umat3d = Uniform<1, glm::dmat3>;
using Umat3f = Uniform<1, glm::mat3>;
using Uvec4d = Uniform<1, glm::dvec4>;
using Uvec4f = Uniform<1, glm::vec4>;
using Uvec3d = Uniform<1, glm::dvec3>;
using Uvec3f = Uniform<1, glm::vec3>;


}
