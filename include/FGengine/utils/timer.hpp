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
#include <chrono>

namespace FGengine::Utils{

class Timer{
public:
	using DataType = float;
	using Unit = std::ratio<1>;
	using TimeType = std::chrono::duration<DataType, Unit>;

	DataType GetTime(){
		TimeType time = GetCurrentTime() - startTime;
		return time.count();
	}

	void Reset(){
		startTime = GetCurrentTime();
	}

private:
	std::chrono::steady_clock::time_point GetCurrentTime(){
		return std::chrono::steady_clock::now();
	}

	std::chrono::steady_clock::time_point startTime = GetCurrentTime();
};

}
