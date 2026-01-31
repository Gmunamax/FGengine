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
#include "FGengine/objects/window.hpp"

void Window::ApplySize(){
	if(size_needupdate){
		SDL_SetWindowSize(SDL_GL_GetCurrentWindow(), size.x, size.y);
		Resize(size);
		size_needupdate = false;
	}
}

void Window::Resize(const SizeType& newsize){
	size = newsize;
	GetScene()->cam.Resize({0,0,newsize.x,newsize.y});
	Update();
}

void Window::SetSize(const SizeType& newsize){
	size = newsize;
	size_needupdate = true;
}
const Window::SizeType& Window::GetSize(){
	return size;
}