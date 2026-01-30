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

void Window::Draw(){
	if(frameskip <= 0){
		if(drawing_needupdate){

			t1 = std::chrono::steady_clock::now();

			GetScene()->cam.StartDrawing();
			GetScene()->Drawing();

			SDL_GL_SwapWindow(SDL_GL_GetCurrentWindow());

			t2 = std::chrono::steady_clock::now();
			std::chrono::nanoseconds t = (t2 - t1);


			drawing_needupdate = false;

			glFlush();

			frameskip = std::chrono::duration_cast<std::chrono::milliseconds>(t).count()/frametime;

			stepsize = ((double)t.count()/frametime)*(frameskip+1);
			stepsize = stepsize /1000 /1000; //to miliseconds

			/* to avoid false positives */
			if(frameskip == 1)
				frameskip = 0;
			if(frameskip > 0)
				std::cout << "Frameskip: " << (int)frameskip << "frames" << std::endl;
		}
	}
	else{
		frameskip--;
	}
}

double Window::GetStepCoefficient(){
	return stepsize;
}

void Window::SetFPS(short newfps){
	frametime = 1.0/newfps*1000;
}

void Window::Update(){
	drawing_needupdate = true;
}