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
#include <SDL2/SDL.h>
#include "FGengine/scene/scene.hpp"
#include "FGengine/structures/point.hpp"

class WindowSize: virtual public WindowScene{
	using PointType = Point2i;

	PointType size {0,0};
	bool needupdate = true;

protected:
	void Apply(){
		if(needupdate){
			SDL_SetWindowSize(SDL_GL_GetCurrentWindow(), size.x, size.y);
			Resize(size);
			needupdate = false;
		}

	}

	void Resize(PointType newsize){
		size = newsize;
		GetScene()->cam.Resize({0,0,newsize.x,newsize.y});
		Update();
	}

public:
	void SetSize(PointType newsize){
		size = newsize;
		needupdate = true;
	}
	PointType GetSize(){
		return size;
	}
};