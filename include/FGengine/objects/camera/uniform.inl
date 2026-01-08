#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SendMatrix(){
	Shader::SendUniformToAll(proj);
	Shader::SendUniformToAll(*Camera::WorldPoint::GetMatrix());
}