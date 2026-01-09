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
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/structures/color.hpp"
#include "FGengine/properties/transform/worldpoint.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType = Point3d>
class Camera: public WorldPoint<PointType>{
//uniform
	bool needupdateprojection = true;
	Uniforms::Umat4 proj {"fg_projectionmatrix"};

protected:
	void SendMatrix();

//uniform


//aspectratio

private:
	double aspectratio = 1;

public:
	void SetAspectRatio(const double& newaspectratio);
	const double& GetAspectRatio();

//aspectratio


//fov

private:
	double fov = 75;

public:
	void SetFOV(const double& newfov);
	const double& GetFOV();

//fov


//viewdistance

private:
	Point2d viewdistance {1, 200};

public:
	void SetNearDistance(const double& newNearDistance);
	void SetFarDistance(const double& newFarDistance);
	void SetDistance(const Point2d& newDistance);
	const double& GetNearDistance();
	const double& GetFarDistance();
	const Point2d& GetDistance();

//viewdistance


//viewport

private:

	Geometry2i viewportgeom;

public:
	void SetViewportGeom(const Geometry2i& newgeom);

	const Geometry2i& GetViewportGeom();

	void Resize(const Geometry2i& newviewport);

//viewport


//background

private:
	Color4d backgroundcolor = {0,0,0,1};

public:
	void SetBackgroundColor(const Color4d& newbgcolor);
	const Color4d& GetBackgroundColor();

//background


//projection

protected:
	enum CameraProjectionEnum{
		CAMERA_FRUSTUM, /* Perspective */
		CAMERA_ORTHO, 	/* Orthogonal */
		CAMERA_UI		/* Orthogonal with inverted depth-test */
	};

	CameraProjectionEnum cameratype = CAMERA_ORTHO;

public:
	void SetFrustum();
	void SetOrtho();
	void SetUI();

	void ProceedProjection();

//projection


//main

	Camera(): Camera::WorldPoint("fg_viewmatrix"){};

	void StartDrawing();

//main
};

#include "camera/uniform.inl"
#include "camera/aspectratio.inl"
#include "camera/fov.inl"
#include "camera/viewdistance.inl"
#include "camera/viewport.inl"
#include "camera/background.inl"
#include "camera/projection.inl"
#include "camera/main.inl"
