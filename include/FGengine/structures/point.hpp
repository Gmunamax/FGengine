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
#include "vector.hpp"

using Point2d = _Vector::Vector<2, double, _Vector::VectorType::Point>;
using Point3d = _Vector::Vector<3, double, _Vector::VectorType::Point>;
using Point4d = _Vector::Vector<4, double, _Vector::VectorType::Point>;

using Point2i = _Vector::Vector<2, int, _Vector::VectorType::Point>;
using Point3i = _Vector::Vector<3, int, _Vector::VectorType::Point>;
using Point4i = _Vector::Vector<4, int, _Vector::VectorType::Point>;

using Point2f = _Vector::Vector<2, float, _Vector::VectorType::Point>;
using Point3f = _Vector::Vector<3, float, _Vector::VectorType::Point>;
using Point4f = _Vector::Vector<4, float, _Vector::VectorType::Point>;