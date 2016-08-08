#pragma once

#include <vector>
#include <iosfwd>
#include <string>

#include <glm/glm.hpp>

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"

#include "DataStructures.hpp"
#include "Material.hpp"
class Object;
enum TextureType{
	DIFFUSE = 0,
	HEIGHT = 1,
};

// A polygonal mesh.
class Mesh  {
public:
	Mesh(std::vector<glm::vec3>& vertices,std::vector<glm::vec3>& normals, std::vector<glm::vec3>& tangents, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices,std::vector<TextureData>& tex, Material& mat, std::vector<glm::vec3>& bound );
	bool viewFrustumCull(Object* player,glm::mat4 trans);
	void draw(ShaderProgram& s,Object* player,glm::mat4 trans);
	void drawOutline(ShaderProgram& s,Object* player,glm::mat4 trans);
	void drawVerts(ShaderProgram& s);
	void drawPick(ShaderProgram& s,Object* player,glm::mat4 trans,unsigned int id);
	~Mesh();
private:
	GLuint buffers[10];
	int numIndices;
	Material material;

	std::vector<TextureData> textures;


	std::string objName;
	std::vector<glm::vec3> boundVertices;

};
