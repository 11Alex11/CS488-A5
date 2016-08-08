#pragma once


#include "Material.hpp"
#include "Mesh.hpp"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include "DataStructures.hpp"
enum AnimType{
	AREPEAT = 0,
	AFORWARD = 1,
	ABACKWARD=2,
	ANONE=3,
};

class Object{
public:
	Object(const char * filename);
	void draw(ShaderProgram& s, Object* player);
	void drawOutline(ShaderProgram& s,Object* player);
	void drawVerts(ShaderProgram& s);
	void pick(ShaderProgram& s, Object* player);
	unsigned int getId();
	glm::mat4 trans;
	virtual void clicked();
	virtual ~Object();
protected:
	int animType;
	int curFrame;
	int maxFrame;
private:
	static unsigned int objectCount;
	unsigned int loadTexture(const char* filename);
	void loadMesh(aiNode* node, const aiScene* scene,int frame);
	void processMesh(aiMesh* mesh,const aiScene* scene,int frame);
	std::string directory;
	Material *material;

	//Should really combine these two vectors
	// Keep seperate for now
	std::vector<Mesh *> meshes;
	std::vector <std::vector<Mesh *> > animation;
	float prevTime;
	int fps;
	unsigned int m_nodeId;

};
