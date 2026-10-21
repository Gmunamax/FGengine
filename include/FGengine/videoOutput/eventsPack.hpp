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

namespace FGengine::VideoOutput{

struct EventsPack{
	enum class Key{
		W,A,S,D,
		Up,Left,Down,Right,
		Space,
		Lshift, Rshift,
		B
	};

	virtual void Draw() = 0;
	virtual void KeyPress(Key key) = 0;
	virtual void KeyRelease(Key key) = 0;

	virtual ~EventsPack() = 0;
};

inline EventsPack::~EventsPack() = default;

}
