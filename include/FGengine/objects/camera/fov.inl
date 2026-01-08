#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetFOV(double newfov){
	this->fov = glm::radians(newfov);
}

template<typename PointType>
double Camera<PointType>::GetFOV(){
	return fov;
}