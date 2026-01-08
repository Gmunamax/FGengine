#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetFrustum(){
	glDepthFunc(GL_LESS);
	
	cameratype = CAMERA_FRUSTUM;
}

template<typename PointType>
void Camera<PointType>::SetOrtho(){
	glDepthFunc(GL_LESS);
	
	cameratype = CAMERA_ORTHO;
}

template<typename PointType>
void Camera<PointType>::SetUI(){
	glDepthFunc(GL_GEQUAL);
	proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
	cameratype = CAMERA_UI;
}

template<typename PointType>
void Camera<PointType>::ProceedProjection(){
	switch(cameratype){
	case CAMERA_FRUSTUM:
		proj = glm::perspective(fov,aspectratio,nearz,farz);
		break;

	case CAMERA_ORTHO:
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		break;

	case CAMERA_UI:
		proj = glm::ortho<double>(-aspectratio,aspectratio,-1,1,nearz,farz);
		break;
	}
	needupdateprojection = false;
}