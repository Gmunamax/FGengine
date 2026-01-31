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
#include <vector>
#include <chrono>
#include <SDL2/SDL.h>
#include "FGengine/structures/point.hpp"
#include "FGengine/scene/scene.hpp"

class Window{
//minsize

private:
	using MinSizeType = Point2i;
	MinSizeType minsize {0};
	bool minsize_needupdate = true;

	void ApplyMinSize();

public:
	void SetMinSize(MinSizeType newminsize);
	MinSizeType GetMinSize();

//minsize


//vsync

private:
	bool vsync = false;
	bool adaptive = true;

	bool vsync_needupdate = true;

	void ApplyVsync();

public:
	bool GetVsync();

//vsync


//size

private:
	using SizeType = Point2i;

	SizeType size {0,0};
	bool size_needupdate = true;

	void ApplySize();

	void Resize(SizeType newsize);

public:
	void SetSize(SizeType newsize);
	SizeType GetSize();

//size


//title

private:
	std::string title;
	bool title_needupdate = true;

protected:
	void ApplyTitle();

public:
	void SetTitle(std::string newtitle);
	std::string GetTitle();

//title


//flags

private:
	Uint32 flags = SDL_WINDOW_OPENGL;

public:
	void SetFlags(Uint32 newflags);
	Uint32 GetFlags();

//flags


//position

private:
	Point2i position {SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED};
	bool position_needupdate = false;

protected:
	void ApplyPosition();

public:
	void SetPosition(Point2i newposition);
	Point2i GetPosition();

//position


//drawing

private:
	double frametime;
	Uint8 frameskip = 0;

	double stepsize;

	std::chrono::time_point<std::chrono::steady_clock> secs;

	std::chrono::steady_clock::time_point t1;
	std::chrono::steady_clock::time_point t2;
	bool drawing_needupdate = true;

	void Draw();

public:
	double GetStepCoefficient();
	
	void SetFPS(short newfps);

	void Update();

//drawing


//events

private:
	Scene* scene = nullptr;

	static constexpr const char* const GetSDLWindowDataName() { return "Scene"; }
	static Window* GetWindowFromID(Uint32 id);

	static void SendEvents();

	void BindWindowToScene();
	
public:
	Scene* GetScene();
	void SetScene(Scene* newscene);

//events


//cycle

private:
	static inline std::vector<Window*> allwindows;
	std::vector<Window*>::size_type vectorpos;

public:
	static void CycleAll();
	void Cycle();

//cycle


//main

private:
	SDL_GLContext glcon;
	SDL_Window* win;
	bool opened = false;

public:
	void Select();

	void Open();
	void Close();

	static void CloseAll();

	Window();
	~Window();

//main
};