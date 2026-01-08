#pragma once
#include <vector>
#include <string>
#include <forward_list>
#include <fstream>
#include <iostream>
#include <GL/glew.h>
#include "uniform.hpp"

class Shader{

	class ShadersList{
		std::forward_list<Shader*> shaderslist;

		std::forward_list<Shader*>::size_type size;

	public:
		class iterator{
			std::forward_list<Shader*>::iterator listiterator;

		public:
			iterator(std::forward_list<Shader*>::iterator i): listiterator(i){}

			Shader*& operator*(){
				return *listiterator;
			}
			iterator& operator++(){
				++listiterator;
				return *this;
			}
			bool operator==(const iterator& other){
				return listiterator == other.listiterator;
			}
			bool operator!=(const iterator& other){
				return listiterator != other.listiterator;
			}
			bool isFree(){
				return *listiterator == nullptr;
			}
			const std::forward_list<Shader*>::iterator toStl(){
				return listiterator;
			}
		};

		iterator begin(){
			return {shaderslist.begin()};
		}
		iterator end(){
			return {shaderslist.end()};
		}

		using size_type = std::forward_list<Shader*>::size_type;

		//returns true on success, false otherwise
		bool setElement(unsigned long id, Shader* element){
			if(id > size){
				return false;
			}
			else{
				std::forward_list<Shader*>::iterator itr = shaderslist.begin();
				for(int i = 0; i != id; i++){
					++itr;
				}
				*itr = element;
				return true;
			}
		}

		std::forward_list<Shader*>::size_type pushBack(Shader* element){
			iterator beforeit = shaderslist.before_begin();
			iterator it = shaderslist.begin();
			for(std::forward_list<Shader*>::size_type id = 0; id < size; id++){
				if(it.isFree()){
					*it = element;
					return id;
				}
				++it;
				++beforeit;
			}
			shaderslist.insert_after(beforeit.toStl(), element);
			size++;
			return size;
		}

		void remove(unsigned long id){
			if(id == size){
				iterator i = shaderslist.before_begin();
				iterator afteri = shaderslist.begin();
				while(afteri.isFree()){
					shaderslist.erase_after(i.toStl());
					++i;
					++afteri;
				}
			}
			else if(id < size){
				setElement(id, nullptr);
			}
		}

		unsigned long getSize(){
			return size;
		}

		ShadersList(){
			size = 0;
		}
	};

	static inline ShadersList shaderslist;
	ShadersList::size_type listid;
	
	GLuint shaderid = 0;

public:

	struct ObjectDescription{
		GLuint type;
		std::vector<const char*> filepathes;
	};
	
	void Load(std::vector<ObjectDescription> descriptions);

	template<typename UniformType>
	static void SendUniformToAll(UniformType& value){
		for(Shader*& element : shaderslist){
			if(element->shaderid != 0){
				value.SetShader(element->shaderid);
				value.Send();
			}
		}
	}
	void Delete(){
		glDeleteProgram(shaderid);
	}

	const GLuint& ToGL(){
		return shaderid;
	}

	Shader(){
		listid = shaderslist.pushBack(this);
	}
	Shader(const Shader& shader){
		this->shaderid = shader.shaderid;
		this->listid = shader.listid;
	}
	~Shader(){
		shaderslist.remove(listid);
	}
};

extern Shader nullshader;