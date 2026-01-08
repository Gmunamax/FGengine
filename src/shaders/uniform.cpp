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
#include "FGengine/shaders/uniform.hpp"

namespace Uniforms{

	template<>
	void Uniform<glm::dmat4>::TemplateSend(){
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr( (glm::mat4)value ));
	}
	template<>
	void Uniform<glm::dmat3>::TemplateSend(){
		glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr( (glm::mat3)value ));
	}
	template<>
	void Uniform<glm::dvec4>::TemplateSend(){
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}
	template<>
	void Uniform<glm::dvec3>::TemplateSend(){
		glUniform3f(location, value.x, value.y, value.z);
	}
	
}