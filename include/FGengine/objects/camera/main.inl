#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::StartDrawing(){

	glClearColor(backgroundcolor.r,backgroundcolor.g,backgroundcolor.b,backgroundcolor.a);
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);

	Camera::ProceedTransformations();
	Camera::ProceedProjection();
	Camera::SendMatrix();
}