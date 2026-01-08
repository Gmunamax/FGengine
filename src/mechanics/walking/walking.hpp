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

//Why nobody didn't add this value to default definitions
#define degtorad 0.017453293

class Walking: virtual public Scene{

	bool walkw = false;
	bool walka = false;
	bool walks = false;
	bool walkd = false;
	bool walkmoving = false;

	SDL_KeyCode forwardkey;
	SDL_KeyCode backwardkey;
	SDL_KeyCode leftkey;
	SDL_KeyCode rightkey;

	bool walkslide = false;
	double friction = 0;
	double startpower = 2;
	bool move2d = true;
	float speed = 0.1;
	
	Point3d MakeStep();

	void UpdateFlags(SDL_KeyboardEvent& key, bool newval);

public:

	void WalkSetKeys(SDL_KeyCode forward, SDL_KeyCode backward, SDL_KeyCode left, SDL_KeyCode right);

	void WalkStart(SDL_KeyboardEvent& key);

	void WalkEnd(SDL_KeyboardEvent& key);

	void WalkMove();
};