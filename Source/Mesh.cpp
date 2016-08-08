#include <iostream>
#include <fstream>
#include "cs488-framework/GlErrorCheck.hpp"
#include <glm/ext.hpp>
#include "cs488-framework/ObjFileDecoder.hpp"

// #include "cs488-framework/ObjFileDecoder.hpp"
#include "Mesh.hpp"
#include "A5.hpp"
#include "Plane.hpp"
#define RENDER_BOUNDING 0



Mesh::Mesh(std::vector<glm::vec3>& vertices,std::vector<glm::vec3>& normals, std::vector<glm::vec3>& tangents, std::vector<glm::vec2>& uvs, std::vector<unsigned int>& indices,std::vector<TextureData>& tex, Material& mat,std::vector<glm::vec3>& bound )
:material(mat){
	boundVertices = bound;

	textures=tex;
	numIndices = indices.size();

	// Calculate bitangents
	std::vector<glm::vec3> bitangents;
	for(int i=0;i<tangents.size();i++){
		bitangents.push_back(glm::cross(tangents[i],normals[i]));
	}




	//Element buffer
	glGenBuffers(1,&buffers[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*indices.size(), &indices[0], GL_STATIC_DRAW);
	CHECK_GL_ERRORS;

	//Vertex Buffer
	glGenBuffers(1,&buffers[1]);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[1]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
	CHECK_GL_ERRORS;

	// Normal Buffer
	glGenBuffers(1,&buffers[2]);
	glBindBuffer(GL_ARRAY_BUFFER,buffers[2]);
	glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);
	CHECK_GL_ERRORS;

	if(textures.size()>0){
		// UV Buffer
		glGenBuffers(1,&buffers[3]);
		glBindBuffer(GL_ARRAY_BUFFER,buffers[3]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec2)*uvs.size(), &uvs[0], GL_STATIC_DRAW);
		CHECK_GL_ERRORS;

		// Tangent Buffer
		glGenBuffers(1,&buffers[4]);
		glBindBuffer(GL_ARRAY_BUFFER,buffers[4]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*tangents.size(), &tangents[0], GL_STATIC_DRAW);
		CHECK_GL_ERRORS;

		// Bitangent Buffer
		glGenBuffers(1,&buffers[5]);
		glBindBuffer(GL_ARRAY_BUFFER,buffers[5]);
		glBufferData(GL_ARRAY_BUFFER,sizeof(glm::vec3)*bitangents.size(), &bitangents[0], GL_STATIC_DRAW);
		CHECK_GL_ERRORS;
	}



	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}


// Draw objects using mapping from id to color to allow for object selection
void Mesh::drawPick(ShaderProgram& s,Object* player,glm::mat4 trans,unsigned int id){
	if(A5::VFC){
		bool drawMesh = viewFrustumCull(player,trans);
		if(!drawMesh){
			return;
		}
	}
	// Position is first in data struct
	GLint posAttrib = s.getAttribLocation( "position" );
	GLint col = s.getUniformLocation("colour");

	int r=(id& 0x000000FF) >>  0;
	int g=(id & 0x0000FF00) >>  8;
	int b=(id & 0x00FF0000) >> 16;
	glUniform3f(col,r/255.0f,g/255.0f,b/255.0f);
	// Position is first
	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
	A5::MeshesDrawn++;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
	glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


// Use the outline shader to render the mesh outline
void Mesh::drawOutline(ShaderProgram& s,Object* player,glm::mat4 trans){
	if(A5::VFC){
		bool drawMesh = viewFrustumCull(player,trans);
		if(!drawMesh){
			return;
		}
	}

	// Position is first in data struct
	GLint posAttrib = s.getAttribLocation( "position" );
	// Normal is second in data struct
	GLint normAttrib = s.getAttribLocation( "normal" );

	// Position is first
	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );
	// Normal is second
	glEnableVertexAttribArray(normAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glVertexAttribPointer( normAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	A5::MeshesDrawn++;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
 	glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);


	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

// Draws only the object shape, used for shadow shader
void Mesh::drawVerts(ShaderProgram& s){
	// Position is first in data struct
	GLint posAttrib = s.getAttribLocation( "position" );

	// Position is first
	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
 	glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
	A5::MeshesDrawn++;

	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


// Draw the mesh using toon shader
void Mesh::draw(ShaderProgram& s,Object* player,glm::mat4 trans){
	if(A5::VFC){
		bool drawMesh = viewFrustumCull(player,trans);
		if(!drawMesh){
			return;
		}
	}
	// Update uniforms
	GLint location = s.getUniformLocation("material.kd");
	glm::vec3 kd = material.getKd();
	glUniform3fv(location, 1, value_ptr(kd));
	CHECK_GL_ERRORS;

	location = s.getUniformLocation("material.ks");
	glm::vec3 ks = material.getKs();
	glUniform3fv(location, 1, value_ptr(ks));
	CHECK_GL_ERRORS;

	location = s.getUniformLocation("material.shininess");
	glUniform1f(location, material.getShininess());
	CHECK_GL_ERRORS;
	location = s.getUniformLocation("ambientIntensity");
	glUniform3fv(location, 1, value_ptr(0.2*kd));
	CHECK_GL_ERRORS;


	// Position is first in data struct
	GLint posAttrib = s.getAttribLocation( "position" );
	// Normal is second in data struct
	GLint normAttrib = s.getAttribLocation( "normal" );
	// UV is third in data struct
	GLint uvAttrib = s.getAttribLocation( "uv" );
	// Tangent is fourth
	GLint tangAttrib = s.getAttribLocation( "tangent" );
	// Bitangent is second in data struct
	GLint bitangAttrib = s.getAttribLocation( "bitangent" );

	// Booleans
	GLint hasTexture = s.getUniformLocation( "hasTexture" );
	GLint hasNormalTexture = s.getUniformLocation( "hasNormalMap" );
	GLint hasEnvMap = s.getUniformLocation( "hasEnvMap" );
	glUniform1i(hasTexture,0);
	glUniform1i(hasNormalTexture,0);
	glUniform1i(hasEnvMap,0);
	if(A5::ENVMAP&&material.getReflect()>0.1){
		glUniform1i(hasEnvMap,1);
	}

	//Texture mapping
		for(int i=0;i<textures.size();i++){
			glActiveTexture(GL_TEXTURE0+i);
			glBindTexture(GL_TEXTURE_2D,textures[i].id);
			GLint tex;
			if(textures[i].type==DIFFUSE&&A5::TEXTURES){
				glUniform1i(hasTexture,1);
				 tex= s.getUniformLocation("diffuseTexture");
				 glUniform1i(tex,i);
			}
			else if(textures[i].type==HEIGHT&&A5::NORMALMAP){
				glUniform1i(hasNormalTexture,1);
				tex = s.getUniformLocation("normalTexture");
				glUniform1i(tex,i);
			}
	}

	// Position is first
	glEnableVertexAttribArray(posAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glVertexAttribPointer( posAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0 );

	// Normal is second
  glEnableVertexAttribArray(normAttrib);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glVertexAttribPointer( normAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	if(textures.size()>0){
		// UV is third
	  glEnableVertexAttribArray(uvAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[3]);
		glVertexAttribPointer( uvAttrib, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Tangent is fourth
		glEnableVertexAttribArray(tangAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[4]);
		glVertexAttribPointer( tangAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

		// Bitangent is fifth
		glEnableVertexAttribArray(bitangAttrib);
		glBindBuffer(GL_ARRAY_BUFFER, buffers[5]);
		glVertexAttribPointer( bitangAttrib, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
 	glDrawElements(GL_TRIANGLES,numIndices,GL_UNSIGNED_INT,0);
	A5::MeshesDrawn++;




	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

// Cull out mesh if it isnt seen
// Thanks to lighthouse3d.com for helpful tutorial

bool Mesh::viewFrustumCull(Object* obj,glm::mat4 trans){
	bool ret = true;
	Player* player = dynamic_cast<Player*>(obj);

	glm::vec3 pos = player->getPos();
	glm::vec3 dir = pos+player->getDir();
	glm::vec3 up = player->getUp();
	glm::vec3 right = player->getRight();

	float nearDist =player->getNear();
	float farDist = player->getFar();
	float aspect =player->getAspect();
	float fov =player->getFov();


	//Half hight and widths
	float hNear = tan(fov/2)*nearDist;
	float wNear = hNear * aspect;

	float hFar = tan(fov/2)*farDist;
	float wFar = hFar*aspect;

	glm::vec3 Z = glm::normalize(pos- dir);
	glm::vec3 X = glm::normalize(glm::cross(up,Z));
	glm::vec3 Y = glm::normalize(glm::cross(Z,X));


	//Calculate back points of Frustum
	glm::vec3 fc = pos-Z*farDist;

	glm::vec3 ftl = fc + Y*hFar - X*wFar;
	glm::vec3 ftr = fc + Y*hFar + X*wFar;
	glm::vec3 fbl = fc - Y*hFar -X*wFar;
	glm::vec3 fbr = fc - Y*hFar + X*wFar;

	//Calcuate front points of Frustum
	glm::vec3 nc = pos-Z*nearDist;

	glm::vec3 ntl = nc + Y*hNear - X*wNear;
	glm::vec3 ntr = nc + Y*hNear + X*wNear;
	glm::vec3 nbl = nc - Y*hNear - X*wNear;
	glm::vec3 nbr = nc - Y*hNear + X*wNear;

	std::vector<glm::vec3> transformedBox;
	std::vector<Plane> planes;
	planes.push_back(Plane(ntr,ntl,ftl));
	planes.push_back(Plane(nbl,nbr,fbr));
	planes.push_back(Plane(ntl,nbl,fbl));
	planes.push_back(Plane(nbr,ntr,fbr));
	planes.push_back(Plane(ntl,ntr,nbr));
	planes.push_back(Plane(ftr,ftl,fbl));

	// Apply transformation to the original bounding box
	for(int i=0;i<boundVertices.size();i++){
		transformedBox.push_back(glm::vec3(trans*glm::vec4(boundVertices[i],1)));
	}
	int in;
	for(int i=0;i<6;i++){
		in =0;
		for(int k=0;k<8&&(in==0);k++){
			// Get distance
			if(planes[i].getDistance(transformedBox[k])<0){
			}
			else{
				in++;
			}
		}
		if(!in){
			return false;
		}
	}
	return ret;
}



Mesh::~Mesh(){
	glDeleteBuffers(1,&buffers[0]);
	glDeleteBuffers(1,&buffers[1]);
	glDeleteBuffers(1,&buffers[2]);
	glDeleteBuffers(1,&buffers[3]);
	glDeleteBuffers(1,&buffers[4]);
	glDeleteBuffers(1,&buffers[5]);
}
