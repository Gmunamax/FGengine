#pragma once
// #include "params/position.hpp"
// #include "params/rotation.hpp"
// #include "params/scale.hpp"
#include "FGengine/shaders/uniform.hpp"
#include "FGengine/shaders/shader.hpp"

template<typename PointType>
class Transform{

	Uniforms::Umat4 objm;

	bool needupdate = true;

	Uniforms::Umat3 normalm;
protected:
	void ProceedTransformations(){
		if(needupdate){

			objm = 1;
			objm = glm::translate(objm.GetValue(), position);

			if(rotation.x != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.x), glm::dvec3{1,0,0});
			if(rotation.y != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.y), glm::dvec3{0,1,0});
			if(rotation.z != 0)
				objm = glm::rotate(objm.GetValue(), glm::radians(rotation.z), glm::dvec3{0,0,1});

			objm = glm::scale(objm.GetValue(), scale);

			normalm = glm::transpose(glm::inverse(objm.GetValue()));
			
			needupdate = false;
		}
	}

	Uniforms::Umat4* GetMatrix(){
		return &objm;
	}

	void SendMatrix(){
		objm.Send();
		normalm.Send();
	}

	void SetShader(Shader*& newshader){
		objm.SetShader(newshader->ToGL());
		normalm.SetShader(newshader->ToGL());
	}

	Transform(){};

	PointType position{0};
	PointType rotation{0};
	PointType scale{1};


public:
	PointType& GetPosition(){
		return position;
	}
	void SetPosition(PointType newposition){
		position = newposition;
		needupdate = true;
	}

	

	PointType& GetRotation(){
		return rotation;
	}
	void SetRotation(PointType newrotation){
		rotation = newrotation;
		needupdate = true;
	}

	

	PointType& GetScale(){
		return scale;
	}
	void SetScale(PointType newscale){
		scale = newscale;
		needupdate = true;
	}

	Transform(const char* uniformname, const char* normaluniformname): objm(uniformname), normalm(normaluniformname){}

};