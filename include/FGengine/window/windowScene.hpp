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
#include <chrono>
#include "FGengine/scene/scene.hpp"

class WindowSceneCore{
protected:
	Scene* scene = nullptr;
	bool needupdate = true;

public:
	void Update(){
		needupdate = true;
	}

	Scene* GetScene(){
		return scene;
	}
	void SetScene(Scene* newscene){
		scene = newscene;
	}

};

class WindowDrawing: virtual public WindowSceneCore{
	double frametime;
	Uint8 frameskip = 0;
	Color3d bgcolor;

	double stepsize;

	std::chrono::time_point<std::chrono::steady_clock> secs;

	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
protected:

	WindowDrawing(){}

	void Draw();

public:
	double GetStepCoefficient(){
		return stepsize;
	}
	
	void SetFPS(short fps){
		frametime = 1.0/fps*1000;
	}

	
};

class WindowEvents: virtual public WindowSceneCore{
protected:

	void EventDelete(){
		if(scene != nullptr){
			scene->Deleting();
		}
	}
	void EventDrawing(){
		if(scene != nullptr){
			scene->Drawing();
		}
	}
	void EventKeyPressed(SDL_KeyboardEvent& key){
		if(scene != nullptr){
			scene->KeyPressed(key);
		}
	}
	void EventKeyReleased(SDL_KeyboardEvent& key){
		if(scene != nullptr){
			scene->KeyReleased(key);
		}
	}
	void EventCycle(){
		if(scene != nullptr){
			scene->Cycle();
		}
	}
};

class WindowScene: public WindowDrawing, public WindowEvents{

};