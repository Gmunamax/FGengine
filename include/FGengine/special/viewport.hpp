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
#include "FGengine/structures/geometry.hpp"
#include "FGengine/special/framebuffer.hpp"

namespace FGengine{

class Viewport: public Framebuffer{

	struct Buffer{
		GLuint id;
		GLenum internalformat;
	};
	
	GLuint framebuffer;
	Buffer colorBuffer {0};
	Buffer depthStencilBuffer {0};

//viewport

private:
	Vector<2, unsigned int, VectorType::Size> maxSize;

	void ResizeBuffers(Vector<2, unsigned int, VectorType::Size> newMaxSize){
		maxSize = newMaxSize;
		DefineTextureBuffer();
		DefineDepthStencilBuffer();
	}

	const Vector<2, unsigned int, VectorType::Size>& GetMaxSize() const{
		return maxSize;
	}

//viewport

//tests

public:
	enum Buffers{
		DepthBuffer = GL_DEPTH_BUFFER_BIT,
		StencilBuffer = GL_STENCIL_BUFFER_BIT,
		NoBuffer = 0
	};

//tests

private:
	GLint mip = 0;

	void DefineTextureBuffer(){
		glBindTexture(GL_TEXTURE_2D, colorBuffer.id);
		glTexImage2D(GL_TEXTURE_2D, mip, colorBuffer.internalformat, maxSize.w, maxSize.h, 0, colorBuffer.internalformat, GL_UNSIGNED_BYTE, NULL);
	}

	void DefineDepthStencilBuffer(){
		glBindRenderbuffer(GL_RENDERBUFFER, depthStencilBuffer.id);
		glRenderbufferStorage(GL_RENDERBUFFER, depthStencilBuffer.internalformat, maxSize.w, maxSize.h);
	}

public:
	void Use(){
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
	}

	Viewport(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize): Viewport(buffers, maxSize, {0, 0, (int)maxSize.w, (int)maxSize.h}) {}
	Viewport(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize, Geometry2i geom){
		Init(buffers, maxSize);
		Use();
		SetViewportGeom(geom);
	}

private:
	void Init(Buffers buffers, Vector<2, unsigned int, VectorType::Size> maxSize){
		glGenFramebuffers(1, &framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

		glGenTextures(1, &colorBuffer.id);
		glGenRenderbuffers(1, &depthStencilBuffer.id);
		
		GLuint attachment = 0;
		if(buffers & DepthBuffer){
			if(buffers & StencilBuffer){
				attachment = GL_DEPTH_STENCIL_ATTACHMENT;
				depthStencilBuffer.internalformat = GL_DEPTH_STENCIL;
				buffersToClear |= GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
			}
			else{
				attachment = GL_DEPTH_ATTACHMENT;
				depthStencilBuffer.internalformat = GL_DEPTH_COMPONENT;
				buffersToClear |= GL_DEPTH_BUFFER_BIT;
			}
		}
		else{
			if(buffers & StencilBuffer){
				attachment = GL_STENCIL_ATTACHMENT;
				depthStencilBuffer.internalformat = GL_STENCIL_INDEX;
				buffersToClear |= GL_STENCIL_BUFFER_BIT;
			}
		}
		colorBuffer.internalformat = GL_RGBA;
		buffersToClear |= GL_COLOR_BUFFER_BIT;

		ResizeBuffers(maxSize);

		if(attachment != 0)
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment, GL_RENDERBUFFER, depthStencilBuffer.id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBuffer.id, mip);
	}

public:
	~Viewport(){
		glDeleteRenderbuffers(1, &depthStencilBuffer.id);
		glDeleteTextures(1, &colorBuffer.id);
		glDeleteFramebuffers(1, &framebuffer);
	}
};

}
