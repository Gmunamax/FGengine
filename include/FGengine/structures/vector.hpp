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
#include <GL/glew.h>
#include <glm/glm.hpp>

template<glm::length_t Length, typename SizeType, glm::qualifier Q = glm::packed>
struct Vector: public glm::vec<Length, SizeType, Q> {
	using glm::vec<Length, SizeType, Q>::vec;

	Vector(glm::vec<Length, SizeType, Q> c): glm::vec<Length, SizeType, Q>::vec(c){}
};

template<glm::length_t Length, glm::qualifier Q>
struct Vector<Length, short, Q>: public glm::vec<Length, short, Q>{
	using glm::vec<Length, short, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_SHORT;}

	Vector(glm::vec<Length, short, Q> c): glm::vec<Length, short, Q>::vec(c){}
};

template<glm::length_t Length, glm::qualifier Q>
struct Vector<Length, int, Q>: public glm::vec<Length, int, Q>{
	using glm::vec<Length, int, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_INT;}

	Vector(glm::vec<Length, int, Q> c): glm::vec<Length, int, Q>::vec(c){}
};

template<glm::length_t Length, glm::qualifier Q>
struct Vector<Length, float, Q>: public glm::vec<Length, float, Q>{
	using glm::vec<Length, float, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_FLOAT;}

	Vector(glm::vec<Length, float, Q> c): glm::vec<Length, float, Q>::vec(c){}
};

template<glm::length_t Length, glm::qualifier Q>
struct Vector<Length, double, Q>: public glm::vec<Length, double, Q>{
	using glm::vec<Length, double, Q>::vec;

	static constexpr GLenum gldatatype() {return GL_DOUBLE;}

	Vector(glm::vec<Length, double, Q> c): glm::vec<Length, double, Q>::vec(c){}
};
