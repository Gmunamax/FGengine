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
#ifdef __INTELLISENSE__
#include "FGengine/objects/camera.hpp"
#endif

template<typename PointType>
void Camera<PointType>::SetNearDistance(const double& newNearDistance){
	viewdistance[0] = newNearDistance;
}

template<typename PointType>
void Camera<PointType>::SetFarDistance(const double& newFarDistance){
	viewdistance[1] = newFarDistance;
}

template<typename PointType>
void Camera<PointType>::SetDistance(const Point2d& newDistance){
	viewdistance = newDistance;
}

template<typename PointType>
const double& Camera<PointType>::GetNearDistance() const{
	return viewdistance[0];
}

template<typename PointType>
const double& Camera<PointType>::GetFarDistance() const{
	return viewdistance[1];
}

template<typename PointType>
const Point2d& Camera<PointType>::GetDistance() const{
	return viewdistance;
}
