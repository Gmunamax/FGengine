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

namespace FGengine{

using Point2d = Vector<2, double, VectorType::Point>;
using Point3d = Vector<3, double, VectorType::Point>;
using Point4d = Vector<4, double, VectorType::Point>;

using Point2i = Vector<2, int, VectorType::Point>;
using Point3i = Vector<3, int, VectorType::Point>;
using Point4i = Vector<4, int, VectorType::Point>;

using Point2f = Vector<2, float, VectorType::Point>;
using Point3f = Vector<3, float, VectorType::Point>;
using Point4f = Vector<4, float, VectorType::Point>;

}
