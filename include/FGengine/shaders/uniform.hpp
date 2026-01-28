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
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <GL/glew.h>

namespace Uniforms{

	template<typename ValueType>
	class Uniform{

		const char* name;
		ValueType value;
		GLint location = 0;
		GLint shaderId = 0;

		void SetValue(const ValueType& value){
			this->value = value;
		}

		void TemplateSend() const;

	public:

		const char* GetName() const{
			return name;
		}
	
		void SetShader(const GLuint& newshader){
			this->shaderId = newshader;
			location = glGetUniformLocation(newshader, name);
		}

		const ValueType& GetValue() const{
			return value;
		}

		void Send() const{
			glUseProgram(shaderId);
			TemplateSend();
		}

		Uniform(const char* const name, const GLuint shaderid = 0, const ValueType value = 1){
			location = glGetUniformLocation(shaderid, name);
			this->name = name;
			SetValue(value);
		}
		void operator=(const ValueType& newvalue){
			SetValue(newvalue);
		}
		
	};

	using Umat4 = Uniform<glm::dmat4>;
	using Umat3 = Uniform<glm::dmat3>;
	using Uvec4 = Uniform<glm::dvec4>;
	using Uvec3 = Uniform<glm::dvec3>;

}