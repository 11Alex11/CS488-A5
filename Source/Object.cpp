#include "Object.hpp"

#include "Material.hpp"

#include <iostream>
#include "SOIL.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Material.hpp"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
//---------------------------------------------------------------------------------------

unsigned int Object::objectCount = 0;


Object::Object(const char *fileName){
	objectCount++;
	animType=AREPEAT;
	m_nodeId=objectCount;
	std::string d = fileName;
	std::size_t found = d.find_last_of("/\\");
	directory =d.substr(0,found) + "/";
	curFrame=-1;
	fps=60;
	prevTime=0;
	Assimp::Importer imp;
	const aiScene* scene = imp.ReadFile(fileName,aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
	if(scene==NULL||scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE){
		std::cerr << "Error loading " + std::string(fileName) <<std::endl;
		return;
	}
	//Recursively search for meshes to add
	loadMesh(scene->mRootNode,scene,-1);



	char tmp[250];
	int i=1;
	while(true){
		sprintf(tmp, "_%06d", i);
		std::string animName(fileName);
		int index = animName.find_last_of('.');
		animName = animName.substr(0,index) + std::string(tmp) + animName.substr(index,animName.length());

		Assimp::Importer anim;
		const aiScene* animScene = anim.ReadFile(animName,aiProcess_JoinIdenticalVertices | aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
		if(animScene==NULL){
			break;
		}
		else{
			std::vector <Mesh * > tmp;
			animation.push_back(tmp);
			std::cerr << animName << "   " << i-1 << std::endl;
			loadMesh(animScene->mRootNode,animScene,i-1);
			curFrame=0;
		}
		i++;
	}
	maxFrame = i-1;

}


void Object::loadMesh(aiNode* node,const aiScene*scene,int frame){
	for(int i=0;i<node->mNumMeshes;i++){
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh,scene,frame);
	}
	for(int i=0;i<node->mNumChildren;i++){
		loadMesh(node->mChildren[i],scene,frame);
	}
}

void Object::processMesh(aiMesh* mesh,const aiScene* scene,int frame){
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec3> tangents;
		std::vector<glm::vec2> uvs;
		std::vector<unsigned int> indices;
		std::vector<TextureData> nodeTextData;
		std::vector<glm::vec3> boundBox;

		bool xUnd,yUnd,zUnd;
		xUnd=yUnd=zUnd=true;
		bool xUnd2,yUnd2,zUnd2;
		xUnd2=yUnd2=zUnd2=true;

		glm::vec3 minVert;
		glm::vec3 maxVert;
		// Load material
		aiColor3D diffuse;
		aiColor3D spec;
		aiColor3D amb;
		float shininess;
		float reflect;
		aiMaterial* mat=scene->mMaterials[mesh->mMaterialIndex];
		mat->Get(AI_MATKEY_COLOR_DIFFUSE,diffuse);
		mat->Get(AI_MATKEY_COLOR_SPECULAR,spec);
		mat->Get(AI_MATKEY_COLOR_AMBIENT,amb);
		mat->Get(AI_MATKEY_SHININESS,shininess);
		mat->Get(AI_MATKEY_REFRACTI,reflect);
		reflect = std::max(1.0f,reflect)- std::min(1.0f,reflect);
		glm::vec3 kd(diffuse.r,diffuse.g,diffuse.b);
		glm::vec3 ks(spec.r,spec.g,spec.b);
		glm::vec3 ka(amb.r,amb.g,amb.b);
		Material m(kd,ks,ka,shininess,reflect);

		// Load vertex data
		for(int i=0;i<mesh->mNumVertices;i++){
			glm::vec3 pos;
			glm::vec3 norm;
			glm::vec3 tang;
			glm::vec2 uv;
			pos = glm::vec3(mesh->mVertices[i].x,mesh->mVertices[i].y,mesh->mVertices[i].z);

			// Set bounding boundBox
			if(xUnd||minVert.x>pos.x){
				xUnd=false;
				minVert.x=pos.x;
			}
			if(yUnd||minVert.y>pos.y){
				yUnd=false;
				minVert.y=pos.y;
			}
			if(zUnd||minVert.z>pos.z){
				zUnd=false;
				minVert.z=pos.z;
			}

			if(xUnd2||maxVert.x<pos.x){
				xUnd2=false;
				maxVert.x=pos.x;
			}
			if(yUnd2||maxVert.y<pos.y){
				yUnd2=false;
				maxVert.y=pos.y;
			}
			if(zUnd2||maxVert.z<pos.z){
				zUnd2=false;
				maxVert.z=pos.z;
			}


			vertices.push_back(pos);
			if(mesh->HasNormals()){
				 norm = glm::vec3(mesh->mNormals[i].x,mesh->mNormals[i].y,mesh->mNormals[i].z);
				 normals.push_back(norm);
			}
			if(mesh->HasTangentsAndBitangents()){
				tang= glm::vec3(mesh->mTangents[i].x,mesh->mTangents[i].y,mesh->mTangents[i].z);
				tangents.push_back(tang);
			}
			if(mesh->HasTextureCoords(0)){
				uv= glm::vec2(mesh->mTextureCoords[0][i].x,mesh->mTextureCoords[0][i].y);
				uvs.push_back(uv);
			}
		}

		// Load vertex indice data, should be triangles
		for(int i=0;i<mesh->mNumFaces;i++){
			indices.push_back(mesh->mFaces[i].mIndices[0]);
			indices.push_back(mesh->mFaces[i].mIndices[1]);
			indices.push_back(mesh->mFaces[i].mIndices[2]);

		}

		// Load texture data
		for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++){
			// Get name of texture
			aiString string;
			mat->GetTexture(aiTextureType_DIFFUSE,i,&string);
			std::string loc = directory + string.C_Str();
			int w,h;
			unsigned char* image = SOIL_load_image(loc.c_str(),&w,&h,0,SOIL_LOAD_RGBA);
			if(image==NULL){
				std::cerr << "Error loading " << loc << std::endl;
				continue;
			}
			unsigned int id;
			unsigned int type =DIFFUSE;

			glGenTextures(1,&id);
			glBindTexture(GL_TEXTURE_2D,id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			nodeTextData.push_back(TextureData(id,type));
		}

		for(int i=0;i<mat->GetTextureCount(aiTextureType_HEIGHT);i++){
			// Get name of texture
			aiString string;
			mat->GetTexture(aiTextureType_HEIGHT,i,&string);
			std::string loc = directory + string.C_Str();
			int w,h;
			unsigned char* image = SOIL_load_image(loc.c_str(),&w,&h,0,SOIL_LOAD_RGBA);
			if(image==NULL){
				std::cerr << "Error loading " << loc << std::endl;
				continue;
			}
			unsigned int id;
			unsigned int type =HEIGHT;

			glGenTextures(1,&id);
			glBindTexture(GL_TEXTURE_2D,id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			nodeTextData.push_back(TextureData(id,type));
		}

		// Set bounding boundBox

	boundBox.push_back(glm::vec3(minVert.x,	minVert.y, maxVert.z));
	boundBox.push_back(glm::vec3(maxVert.x, 	minVert.y, maxVert.z));
	boundBox.push_back(glm::vec3(maxVert.x, 	maxVert.y, maxVert.z));
	boundBox.push_back(glm::vec3(minVert.x, maxVert.y, maxVert.z));
	boundBox.push_back(glm::vec3(minVert.x, minVert.y , minVert.z));
	boundBox.push_back(glm::vec3(maxVert.x, minVert.y, minVert.z));
	boundBox.push_back(glm::vec3(maxVert.x, maxVert.y, minVert.z));
	boundBox.push_back(glm::vec3(minVert.x, maxVert.y, minVert.z));

	if(frame==-1){
			meshes.push_back(new Mesh(vertices,normals,tangents,uvs,indices,nodeTextData,m,boundBox));
	}
	else{
		animation[frame].push_back(new Mesh(vertices,normals,tangents,uvs,indices,nodeTextData,m,boundBox));
	}
}


// Pass in picking shader, draws objects based on ID
void Object::pick(ShaderProgram& s, Object* player){


	if(curFrame>=0){
		for(int i=0;i<animation[curFrame].size();i++){
			animation[curFrame][i]->drawPick(s,player,trans,m_nodeId);
		}

	}
	else{
		for(int i=0;i<meshes.size();i++){
			meshes[i] -> drawPick(s,player,trans,m_nodeId);
		}
	}


}



// Draws its meshes using the toon shader
// Also updates animation
void Object::draw(ShaderProgram& s,Object* player){
	if(curFrame>=0){
		for(int i=0;i<animation[curFrame].size();i++){
			animation[curFrame][i]->draw(s,player,trans);
		}

		float currentTime = glfwGetTime();
		float dTime = currentTime - prevTime;
		if(dTime>1/fps){
			prevTime = currentTime;
			if(animType==AREPEAT||animType==AFORWARD){
				curFrame+= 1;
			}
			else if(animType==ABACKWARD){
				curFrame-=1;
			}
		}


		if(curFrame>=maxFrame&&animType==AREPEAT){
			curFrame=0;
		}
		if(curFrame>=maxFrame&&animType==AFORWARD){
			curFrame=maxFrame-1;
			animType=ANONE;
		}
		if(curFrame<0&&animType==ABACKWARD){
			curFrame=0;
			animType=ANONE;
		}
	}
	else{
		for(int i=0;i<meshes.size();i++){
			meshes[i] -> draw(s,player,trans);
		}
	}
}


// Draws its meshes using the outline shader

void Object::drawOutline(ShaderProgram& s,Object* player){

	if(curFrame>=0){
		for(int i=0;i<animation[curFrame].size();i++){
			animation[curFrame][i]->drawOutline(s,player,trans);
		}
	}
	else{
		for(int i=0;i<meshes.size();i++){
			meshes[i] -> drawOutline(s,player,trans);
		}
	}

}

// Draws meshes vertex only for shadow shader
void Object::drawVerts(ShaderProgram& s){

	if(curFrame>=0){
		for(int i=0;i<animation[curFrame].size();i++){
			animation[curFrame][i]->drawVerts(s);
		}
	}
	else{
		for(int i=0;i<meshes.size();i++){
			meshes[i] -> drawVerts(s);
		}
	}

}

// Overwritten in  derived classes if actions needed
void Object::clicked(){

}

unsigned int Object::getId(){
	return m_nodeId;
}

Object::~Object(){
	for(int i=0;i<meshes.size();i++){
		delete meshes[i];
	}
}
