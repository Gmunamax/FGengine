#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetAspectRatio(double newaspectratio){
	aspectratio = newaspectratio;
}

template<typename PointType>
double Camera<PointType>::GetAspectRatio(){
	return aspectratio;
}