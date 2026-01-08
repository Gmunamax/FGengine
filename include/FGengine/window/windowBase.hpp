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
#include <GL/glew.h>
#include <iostream>

#include "windowScene.hpp"
#include "data/position.hpp"
#include "data/flags.hpp"
#include "data/title.hpp"
#include "data/size.hpp"
#include "data/vsync.hpp"
#include "data/minSize.hpp"

class WindowBase: public WindowPosition, public WindowFlags, public WindowTitle, public WindowSize, public WindowVsync, public WindowMinSize{
	friend class Window;
	static inline const char* windowdataname = "Scene";

	SDL_GLContext glcon;
	SDL_Window* win;
	bool opened = false;

	void InitBackend();

protected:
	static WindowBase* GetWindowFromID(Uint32 id);

	void Apply();

public:
	void Select();

	void Open();
	void Close();
};