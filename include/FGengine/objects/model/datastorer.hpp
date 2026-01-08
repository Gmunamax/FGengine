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
#include "elembuffer.hpp"
#include "vertbuffer.hpp"
#include "vertarray.hpp"

template<typename VertexType>
class VertexDataStorage: private VertBuffer<VertexType>, private ElemBuffer, private VertArray<VertexType>{
protected:

	//Must be called once, after Model created and OpenGL context loaded
	void Init(){
		VertexDataStorage::VertArray::Init();
		VertexDataStorage::VertBuffer::Init();
		VertexDataStorage::ElemBuffer::Init();
		VertexDataStorage::VertArray::Select();
		VertexDataStorage::VertBuffer::Select();
		VertexDataStorage::ElemBuffer::Select();
		VertexDataStorage::VertArray::Setup();
		glBindVertexArray(0);
	}

	void Select(){
		VertexDataStorage::VertArray::Select();
	}
	
	void DrawData(){
		VertexDataStorage::ElemBuffer::Draw();
	}

	VertexDataStorage(){};
	~VertexDataStorage(){};

public:
	void Load(const std::vector<VertexType>& vertexes, const std::vector<std::vector<unsigned int>>& elements){
		VertexDataStorage::VertBuffer::Load(vertexes);
		VertexDataStorage::ElemBuffer::Load(elements);
	}

	void Delete(){
		VertexDataStorage::VertArray::Delete();
		VertexDataStorage::VertBuffer::Delete();
		VertexDataStorage::ElemBuffer::Delete();
	}
};