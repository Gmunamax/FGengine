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

		void SetValue(ValueType& value){
			this->value = value;
		}

		void TemplateSend();

	public:

		const char* GetName(){
			return name;
		}
	
		void SetShader(GLuint newshader){
			this->shaderId = newshader;
			location = glGetUniformLocation(newshader, name);
		}

		const ValueType& GetValue(){
			return value;
		}

		void Send(){
			// if(needupdate){
			glUseProgram(shaderId);
				TemplateSend();
				// needupdate = false;
			// }
		}

		Uniform(const char* name, GLuint shaderid = 0, ValueType value = 1){
			location = glGetUniformLocation(shaderid, name);
			this->name = name;
			SetValue(value);
		}
		void operator=(ValueType newvalue){
			SetValue(newvalue);
		}
		
	};

	using Umat4 = Uniform<glm::dmat4>;
	using Umat3 = Uniform<glm::dmat3>;
	using Uvec4 = Uniform<glm::dvec4>;
	using Uvec3 = Uniform<glm::dvec3>;

}