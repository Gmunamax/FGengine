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
#include "walking.hpp"
#include <iostream>
#include <math.h>
#include "FGengine/structures/point.hpp"
#include "FGengine/objects/camera/camera.hpp"
#include "FGengine/objects/window.hpp"

Point3d Walking::MakeStep(){

	enum AxisRotators{
		MoveForward = 0,
		MoveLeft = 1,
		MoveBackward = 2,
		MoveRight = 3,
	};
	constexpr short axisangle = 90;

	double walkaxisrotation = 0;
	unsigned short keyspressed;

	static double fpower = 0;
	static double bpower = 0;
	static double lpower = 0;
	static double rpower = 0;

	static double realspeed = win->GetStepCoefficient();

	if(walkslide){

	}
	else{
		fpower = walkw * speed;
		bpower = walks * speed;
		lpower = walka * speed;
		rpower = walkd * speed;

		realspeed = realspeed * speed;
	}

	keyspressed+= walkw;
	keyspressed+= walks;
	keyspressed+= walka;
	keyspressed+= walkd;

	Point3d movevector {
		(-1*lpower) + (1*rpower),
		(1*fpower) + (-1*bpower),
		0
	};

	Point3d step{
		std::cos(cam.GetRotation().z * degtorad) * movevector.x + std::sin(cam.GetRotation().z * degtorad) * movevector.y,
		std::cos(cam.GetRotation().z * degtorad) * movevector.y - std::sin(cam.GetRotation().z * degtorad) * movevector.x,
		std::sin(cam.GetRotation().x * degtorad) * movevector.z
	};

	if(keyspressed == 0)
		walkmoving = false;


	return {-step.x,-step.y,0};
}

void Walking::UpdateFlags(SDL_KeyboardEvent& key, bool newval){
	if(key.keysym.sym == forwardkey)
		walkw = newval;
	else if(key.keysym.sym == backwardkey)
		walks = newval;
	else if(key.keysym.sym == leftkey)
		walka = newval;
	else if(key.keysym.sym == rightkey)
		walkd = newval;
	
	if(walkw or walka or walks or walkd)
		walkmoving = true;
}

void Walking::WalkSetKeys(SDL_KeyCode forward, SDL_KeyCode backward, SDL_KeyCode left, SDL_KeyCode right){
	forwardkey = forward;
	backwardkey = backward;
	leftkey = left;
	rightkey = right;
}

void Walking::WalkStart(SDL_KeyboardEvent& key){
	UpdateFlags(key, true);
}

void Walking::WalkEnd(SDL_KeyboardEvent& key){
	UpdateFlags(key, false);
}

void Walking::WalkMove(){
	Point3d& position = cam.GetPosition();

	if(walkmoving){

		cam.SetPosition(cam.GetPosition() + MakeStep());
		win->Update();
	}
}