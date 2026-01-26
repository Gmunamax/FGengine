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
#include "vector.hpp"

template<_Vector::length_t Length, typename DataType>
union Geometry{
	struct{
		_Vector::Vector<Length, DataType, _Vector::VectorType::Point> position;
		_Vector::Vector<Length, DataType, _Vector::VectorType::Size> size;
	};
};

template<typename DataType>
union Geometry<2, DataType>{
	struct{
		_Vector::Vector<2, DataType, _Vector::VectorType::Point> position;
		_Vector::Vector<2, DataType, _Vector::VectorType::Size> size;
	};
	struct{
		DataType x;
		DataType y;
		DataType w;
		DataType h;
	};
	Geometry(){
		this->x = 0;
		this->y = 0;
		this->w = 0;
		this->h = 0;
	}
	Geometry(DataType x, DataType y, DataType w, DataType h){
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
};

template<typename DataType>
union Geometry<3, DataType>{
	struct{
		_Vector::Vector<3, DataType, _Vector::VectorType::Point> position;
		_Vector::Vector<3, DataType, _Vector::VectorType::Size> size;
	};
	struct{
		DataType x;
		DataType y;
		DataType z;
		DataType w;
		DataType h;
		DataType d;
	};
	Geometry(){
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
		this->h = 0;
		this->d = 0;
	}
	Geometry(DataType x, DataType y, DataType z, DataType w, DataType h, DataType d){
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
		this->h = h;
		this->d = d;
	}
};

using Geometry2i = Geometry<2, int>;
using Geometry2s = Geometry<2, short>;
using Geometry2f = Geometry<2, float>;
using Geometry2d = Geometry<2, double>;
