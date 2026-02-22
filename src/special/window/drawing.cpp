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
#include "FGengine/special/window.hpp"

namespace FGengine{

void Window::ProceedUpdate(){
	if(!frametimelimit.toDataType())
		UpdateByNoneLimit();
	else{
		switch(limittype){
		case FramerateLimitType::Delay:
			UpdateByDelayLimit();
		case FramerateLimitType::Check:
			UpdateByCheckLimit();
		}
	}
}

void Window::UpdateByNoneLimit(){
	t1 = std::chrono::steady_clock::now();
	RenderScene();
	t2 = std::chrono::steady_clock::now();
	realframetime = t1-t2;
}

void Window::UpdateByDelayLimit(){
	t1 = std::chrono::steady_clock::now();
	RenderScene();
	t2 = std::chrono::steady_clock::now();
	realframetime = t1-t2;
	if(realframetime < frametimelimit){
		SDL_Delay(Frametime(frametimelimit - realframetime).toDataType());
		realframetime = frametimelimit;
	}
}

void Window::UpdateByCheckLimit(){
	if(realframetime > frametimelimit){
		RenderScene();
		realframetime = 0;
	}
	else{
		t2 = std::chrono::steady_clock::now();
		std::chrono::duration<Frametime::DataType, Frametime::ratio> t = t2-t1;
		t1 = std::chrono::steady_clock::now();
		realframetime += t;
	}
}

void Window::RenderScene(){
	if(!drawing_needupdate) return;
	GetScene()->cam.ProceedUpdate();
	GetScene()->Drawing();
	SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());
	drawing_needupdate = false;
}

void Window::SetFrametimeLimit(const Frametime& newframetime){
	frametimelimit = newframetime;
}
const Frametime& Window::GetFrametimeLimit(){
	return frametimelimit;
}

void Window::SetFramerateLimitType(const FramerateLimitType& newlimittype){
	limittype = newlimittype;
}
const Window::FramerateLimitType& Window::GetFramerateLimitType(){
	return limittype;
}

void Window::RequestNewFrame(){
	drawing_needupdate = true;
}

}
