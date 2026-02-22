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
#include "FGengine/special/scene.hpp"
#include "FGengine/special/defaults.hpp"
#include "FGengine/structures/frametime.hpp"

namespace FGengine{

class Window{
//flags

private:
	using FlagFieldType = Uint8;
	FlagFieldType flagsfield = 0;
	enum class Flags{
		MinSize    = 0b00000001,
		Vsync      = 0b00000010,
		Size       = 0b00000100,
		Title      = 0b00001000,
		Position   = 0b00010000,
		Drawing    = 0b00100000,
	};

	void SetFlags(Flags flags){
		flagsfield |= (FlagFieldType)flags;
	}
	void RemoveFlags(Flags flags){
		flagsfield &= ~(FlagFieldType)flags;
	}
	void InverseFlags(Flags flags){
		flagsfield &= (FlagFieldType)flags;
	}
	FlagFieldType GetFlags(Flags flags){
		return flagsfield & (FlagFieldType)flags;
	}

//flags


//minsize

private:
	using MinSizeType = Point2i;
	MinSizeType minsize {0};

	void ApplyMinSize();

public:
	void SetMinSize(const MinSizeType& newminsize);
	const MinSizeType& GetMinSize();

//minsize


//vsync

public:
	enum class VsyncModes{
		Off = 0,
		On = 1,
		Adaptive = -1
	};

private:
	VsyncModes vsyncmode {VsyncModes::Off};

	void ApplyVsync();

public:
	void SetVsyncMode(const VsyncModes& newstate);
	const VsyncModes& GetVsyncMode();

//vsync


//size

private:
	using SizeType = Point2i;

	SizeType size {0,0};

	void ApplySize();

	void Resize(const SizeType& newsize);

public:
	void SetSize(const SizeType& newsize);
	const SizeType& GetSize();

//size


//title

private:
	std::string title{};

protected:
	void ApplyTitle();

public:
	void SetTitle(const std::string& newtitle);
	const std::string& GetTitle();

//title


//sdlflags

private:
	Uint32 sdlflags {SDL_WINDOW_OPENGL};

public:
	void SetSDLFlags(const Uint32& newflags);
	const Uint32& GetSDLFlags();

//sdlflags


//position

private:
	using PositionType = Point2i;
	PositionType position {SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED};

protected:
	void ApplyPosition();

public:
	void SetPosition(const PositionType& newposition);
	const PositionType& GetPosition();

//position


//drawing
public:
	enum class FramerateLimitType{
		Delay,
		Check,
	};

private:
	Frametime frametimelimit {0};
	FramerateLimitType limittype{FramerateLimitType::Delay};
	std::chrono::steady_clock::time_point t1, t2;

	Frametime realframetime;

	void RenderScene();
	
	void ProceedUpdate();
	void UpdateByDelayLimit();
	void UpdateByCheckLimit();
	void UpdateByNoneLimit();

public:	
	void SetFrametimeLimit(const Frametime& ms);
	const Frametime& GetFrametimeLimit();
	void SetFramerateLimitType(const FramerateLimitType& limittype);
	const FramerateLimitType& GetFramerateLimitType();

	void RequestNewFrame();

//drawing


//events

private:
	Scene* scene {Defaults::scene};

	static Window* GetWindowFromID(const Uint32& id);

	static void SendEvents();

	void BindWindowToScene();
	
public:
	Scene* const& GetScene();
	void SetScene(Scene* const& newscene);

//events


//cycle

private:
	static inline std::forward_list<Window*> allwindows;
	std::forward_list<Window*>::iterator elementBeforeThisInList;

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

}
