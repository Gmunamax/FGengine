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
#include "FGengine/structures/aspectratio.hpp"
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/color.hpp"

namespace FGengine{

class Framebuffer{
private:
	AspectRatio aspectRatio;

public:
	const AspectRatio& GetAspectRatio(){
		return aspectRatio;
	}

public:
	void SetViewportGeom(const Geometry2i& newgeom){
		glViewport(newgeom.x, newgeom.y, newgeom.w, newgeom.h);
		aspectRatio = AspectRatio{(float)newgeom.w, (float)newgeom.h}; 
	}

	Geometry2i GetViewportGeom() const{
		int rawgeom[4];
		glGetIntegerv(GL_VIEWPORT, rawgeom);
		return {rawgeom[0], rawgeom[1], rawgeom[2], rawgeom[3]};
	}

public:
	void SetBackgroundColor(const Color4f& newbgcolor){
		glClearColor(newbgcolor.r, newbgcolor.g, newbgcolor.b, newbgcolor.a);
	}

	Color4f GetBackgroundColor() const{
		Color4f color;
		glGetFloatv(GL_COLOR_CLEAR_VALUE, color.value);
		return color;
	}

private:
	GLbitfield buffersToClear = 0;

public:
	void SetBuffersToClear(GLbitfield newMask){
		buffersToClear = newMask;
	}

	const GLbitfield& GetBuffersToClear() const{
		return buffersToClear;
	}

public:
	enum Tests{
		DepthTest = GL_DEPTH_TEST,
		StencilTest = GL_STENCIL_TEST
	};

	void EnableTest(Tests test){
		glEnable((GLenum)test);
	}

	void DisableTest(Tests test){
		glDisable((GLenum)test);
	}


public:
	void Clear(){
		glClear(buffersToClear);
	}
};

}
