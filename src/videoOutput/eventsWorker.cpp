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
#include <SDL3/SDL.h>
#include <FGengine/videoOutput/eventsWorker.hpp>

using FGengine::VideoOutput::EventsWorker, FGengine::VideoOutput::EventsPack;

namespace{

	EventsPack::Key SdlToKey(SDL_Scancode scanCode);

}

void EventsWorker::MainCycle(){
	bool run = true;
	SDL_Event event;
	while(run){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_EVENT_QUIT){
				run = false;
			}
			else if(event.type == SDL_EVENT_KEY_DOWN){
				currentPack->KeyPress(SdlToKey(event.key.scancode));
			}
			else if(event.type == SDL_EVENT_KEY_UP){
				currentPack->KeyRelease(SdlToKey(event.key.scancode));
			}
		}
		currentPack->Draw();
	}
}

namespace{

	EventsPack::Key SdlToKey(SDL_Scancode scanCode){
		EventsPack::Key key;
		switch(scanCode){
		case SDL_SCANCODE_W:
			key = EventsPack::Key::W;
			break;
		case SDL_SCANCODE_A:
			key = EventsPack::Key::A;
			break;
		case SDL_SCANCODE_S:
			key = EventsPack::Key::S;
			break;
		case SDL_SCANCODE_D:
			key = EventsPack::Key::D;
			break;
		case SDL_SCANCODE_UP:
			key = EventsPack::Key::Up;
			break;
		case SDL_SCANCODE_LEFT:
			key = EventsPack::Key::Left;
			break;
		case SDL_SCANCODE_DOWN:
			key = EventsPack::Key::Down;
			break;
		case SDL_SCANCODE_RIGHT:
			key = EventsPack::Key::Right;
			break;
		case SDL_SCANCODE_SPACE:
			key = EventsPack::Key::Space;
			break;
		case SDL_SCANCODE_RSHIFT:
			key = EventsPack::Key::Rshift;
			break;
		case SDL_SCANCODE_LSHIFT:
			key = EventsPack::Key::Lshift;
			break;
		case SDL_SCANCODE_B:
			key = EventsPack::Key::B;
			break;
		
		default:
			break;
		}
		return key;
	}

}
