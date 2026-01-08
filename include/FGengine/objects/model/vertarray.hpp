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
#include <iostream>
#include "FGengine/structures/vertex.hpp"

template<typename VertexType>
class VertArray{
	GLuint buf;

	void ApplyPosition(){
		glVertexAttribPointer(0, VertexType::VertexPosition::GetLength(), VertexType::VertexPosition::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexPosition::GetOffset());
		glEnableVertexAttribArray(0);
	}
	void ApplyColor(){
		glVertexAttribPointer(1, VertexType::VertexColor::GetLength(), VertexType::VertexColor::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexColor::GetOffset());
		glEnableVertexAttribArray(1);
	}
	void ApplyNormal(){
		glVertexAttribPointer(2, VertexType::VertexNormal::GetLength(), VertexType::VertexNormal::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexNormal::GetOffset());
		glEnableVertexAttribArray(2);
	}

protected:
	void Select(){
		glBindVertexArray(buf);
	}

	void Init(){
		glGenVertexArrays(1,&buf);
	}

	void Setup(){
		VertArray::ApplyPosition();
		VertArray::ApplyColor();
		VertArray::ApplyNormal();
	}

	void Delete(){
		glDeleteVertexArrays(1,&buf);
	}
};