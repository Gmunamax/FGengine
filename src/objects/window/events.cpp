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

Window* Window::GetWindowFromID(const Uint32& id){
	return (Window*)SDL_GetWindowData(SDL_GetWindowFromID(id), GetSDLWindowDataName());
}

void Window::SendEvents(){
	static SDL_Event event;
	Window* windowptr;
	while(SDL_PollEvent(&event)){

		switch(event.type){

		case SDL_KEYDOWN:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr)
				if(windowptr->scene != nullptr)
					windowptr->scene->KeyPressed(event.key);
			break;

		case SDL_KEYUP:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr)
				if(windowptr->scene != nullptr)
					windowptr->scene->KeyReleased(event.key);
			break;

		case SDL_WINDOWEVENT:
			windowptr = GetWindowFromID(event.window.windowID);
			windowptr->Select();

			switch(event.window.event){

			case SDL_WINDOWEVENT_RESIZED:
				windowptr->Resize({event.window.data1,event.window.data2});
				break;
			case SDL_WINDOWEVENT_EXPOSED:
				windowptr->Update();
				break;
			}
			break;

		}
	}
}

void Window::BindWindowToScene(){
	scene->win = this;
	if(opened){
		Select();
		scene->Load();
	}
}

Scene* const& Window::GetScene(){
	return scene;
}
void Window::SetScene(Scene* const& newscene){
	scene = newscene;
	if(scene->win != nullptr){
		if(scene->win->glcon != this->glcon){
			BindWindowToScene();
		}
	}
	else{
		BindWindowToScene();
	}
}