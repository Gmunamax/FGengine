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
#include "FGengine/window/window.hpp"
#include <SDL2/SDL.h>
#include <iostream>

void Window::AddSelf(){
	allwindows.push_back(this);
	vectorpos = allwindows.size() - 1;
}

void Window::RemoveSelf(){
	allwindows.erase(allwindows.begin() + vectorpos);
}

Window::Window(){
	AddSelf();
}

Window::~Window(){
	RemoveSelf();
	Close();
}

void Window::Load(){
	scene->Loading(this);
}

void Window::CloseAll(){
	for(Window* w : allwindows){
		w->Close();
	}
}

bool needupdateevent = true;
SDL_Event event;
void Window::SendEvent(){

	WindowBase* windowptr;
	while(SDL_PollEvent(&event)){
		
		switch(event.type){

		case SDL_KEYDOWN:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr) 
				windowptr->EventKeyPressed(event.key);
			break;

		case SDL_KEYUP:
			windowptr = GetWindowFromID(event.key.windowID);
			if(windowptr != nullptr)
				windowptr->EventKeyReleased(event.key);
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

void Window::DrawAll(){
	for(Window* w : allwindows){
		w->Select();
		w->GetScene()->Cycle();
		w->Apply();

		w->Draw();
	}		
}