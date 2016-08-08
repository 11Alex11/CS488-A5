#pragma once

#include "cs488-framework/CS488Window.hpp"
#include "cs488-framework/OpenGLImport.hpp"
#include "cs488-framework/ShaderProgram.hpp"
#include "cs488-framework/MeshConsolidator.hpp"


#include <glm/glm.hpp>
#include <memory>

//A5
#include "Mesh.hpp"
#include "Object.hpp"
#include "Player.hpp"
#include "Light.hpp"
#include "Skybox.hpp"




class A5 : public CS488Window {
public:
	A5();
	virtual ~A5();
	static bool TEXTURES;
	static bool NORMALMAP;
	static bool SHADOWS;
	static bool ENVMAP;
	static bool VFC;
	static bool SKYBOX;
	static int MeshesDrawn;


protected:
	virtual void init() override;
	virtual void appLogic() override;
	virtual void guiLogic() override;
	virtual void draw() override;
	virtual void cleanup() override;

	//-- Virtual callback methods
	virtual bool cursorEnterWindowEvent(int entered) override;
	virtual bool mouseMoveEvent(double xPos, double yPos) override;
	virtual bool mouseButtonInputEvent(int button, int actions, int mods) override;
	virtual bool mouseScrollEvent(double xOffSet, double yOffSet) override;
	virtual bool windowResizeEvent(int width, int height) override;
	virtual bool keyInputEvent(int key, int action, int mods) override;

	//-- One time initialization methods:
	void createShaderProgram();
	void initViewMatrix();
	void initLightSources();
	void createDepthTexture();
	void initPerspectiveMatrix();
	void uploadCommonSceneUniforms();


	// Other functions
	void clickObject(int id);

	std::vector<Object*> objects;
	std::vector<Light*> lights;
	Player* player;
	bool keyW,keyA,keyS,keyD,keySpace;
	float dTime,pTime;


	glm::mat4 m_perpsective;
	glm::mat4 m_view;


	//-- GL resources for mesh geometry data:
	GLuint m_vao_meshData;
	GLuint m_vbo_vertexPositions;
	GLuint m_vbo_vertexNormals;
	GLint m_positionAttribLocation;
	GLint m_normalAttribLocation;

	GLuint frameBuffer;


	ShaderProgram m_shader;
	ShaderProgram m_outline;
	ShaderProgram m_shadow;
	ShaderProgram m_sky;
	ShaderProgram m_pick;

	Skybox* skybox;

	//color picker
	GLint P_uni; // Uniform location for Projection matrix.
	GLint V_uni; // Uniform location for View matrix.
	GLint MVP_uni; // Uniform location for Model matrix.
	GLint col_uni;   // Uniform location for cube colour.
	GLuint m_vao_simpleMeshData;
	GLuint m_vbo_simpleVertexPositions;
	GLint posAttrib;
	ShaderProgram m_shader_picker;
	// BatchInfoMap is an associative container that maps a unique MeshId to a BatchInfo
	// object. Each BatchInfo object contains an index offset and the number of indices
	// required to render the mesh with identifier MeshId.
	BatchInfoMap m_batchInfoMap;


	//A5
	float prevMouseX; float prevMouseY;
	float xOffset,yOffset;
	bool leftMouse;bool rightMouse; bool middleMouse;
	bool renderPicker;
	//better have lots o mem dawg
};
