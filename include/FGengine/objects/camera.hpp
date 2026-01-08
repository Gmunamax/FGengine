#pragma once
#include "FGengine/structures/geometry.hpp"
#include "FGengine/structures/point.hpp"
#include "FGengine/properties/transform/worldpoint.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType = Point3d>
class Camera: public WorldPoint<PointType>{
//uniform

	Uniforms::Umat4 proj {"fg_projectionmatrix"};

protected:
	void SendMatrix();

//uniform


//aspectratio

private:
	double aspectratio = 1;

public:
	void SetAspectRatio(double newaspectratio);
	double GetAspectRatio();

//aspectratio


//fov

private:
	double fov = 75;

public:
	void SetFOV(double newfov);
	double GetFOV();

//fov


//viewdistance

private:
	double nearz = 1;
	double farz = 200;

//viewdistance


//viewport

private:

	Geometry2i viewportgeom;

public:
	void SetViewportGeom(Geometry2i newgeom);

	Geometry2i GetViewportGeom(){
		return viewportgeom;
	}

	void Resize(Geometry2i newviewport);

//viewport


//background

private:
	Color4d backgroundcolor = {0,0,0,1};

public:
	void SetBackgroundColor(Color4d newbgcolor);
	Color4d GetBackgroundColor();

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