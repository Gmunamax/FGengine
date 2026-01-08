#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetBackgroundColor(Color4d newbgcolor){
	backgroundcolor = newbgcolor;
}

template<typename PointType>
Color4d Camera<PointType>::GetBackgroundColor(){
	return backgroundcolor;
}