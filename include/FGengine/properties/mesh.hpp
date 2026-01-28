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
#include <GL/glew.h>
#include <vector>

template<typename VertexType, typename ElementsType>
class Mesh{
private:
	static inline constexpr int VBOusage = GL_STATIC_DRAW;
	static constexpr int EBOusage = GL_STATIC_DRAW;

	GLuint vbo;
	GLuint vao;
	GLuint ebo;

	struct FaceLocation{
		using SizeType = short;

		SizeType offset;
		SizeType size;

		void Draw(){
			glDrawElements(GL_TRIANGLE_STRIP, size, GL_UNSIGNED_INT, (void*)(sizeof(ElementsType) * offset));
		}
	};
	
	std::vector<FaceLocation> facelocators;

public:

	using VertexesList = std::vector<VertexType>;
	using Face = std::vector<ElementsType>;
	using ElementsList = std::vector<Face>;

	//Must be called once, after Model created and OpenGL context loaded
	void Init(){
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		glVertexAttribPointer(0, VertexType::VertexPosition::GetLength(), VertexType::VertexPosition::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexPosition::GetOffset());
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, VertexType::VertexColor::GetLength(), VertexType::VertexColor::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexColor::GetOffset());
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, VertexType::VertexNormal::GetLength(), VertexType::VertexNormal::DataType::gldatatype(), false, VertexType::GetStride(), (void*)VertexType::VertexNormal::GetOffset());
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

	void Select(){
		glBindVertexArray(vao);
	}
	
	void Draw(){
		for(typename std::vector<FaceLocation>::reference modelface : facelocators){
			modelface.Draw();
		}
	}

	void Load(const VertexesList& vertexes, const ElementsList& elements){
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexType)*vertexes.size(), vertexes.data(), VBOusage);
		std::vector<ElementsType> newbuffer;
		long long maxsize = 0;
		for(const Face& face : elements){
			facelocators.emplace_back(maxsize, face.size());
			maxsize+=face.size();
			for(short i = 0; i < face.size(); ++i)
				newbuffer.emplace_back(face.at(i));
		}
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, newbuffer.size()*sizeof(ElementsType), newbuffer.data(), EBOusage);
	}

	void Delete(){
		glDeleteVertexArrays(1,&vao);
		glDeleteBuffers(1, &vbo);
		facelocators.clear();
		facelocators.shrink_to_fit();
		glDeleteBuffers(1, &ebo);
	}

};
