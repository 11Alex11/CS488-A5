#include "A5.hpp"

using namespace std;

#include "cs488-framework/GlErrorCheck.hpp"
#include "cs488-framework/MathUtils.hpp"
#include <time.h>       /* time */

#include <imgui/imgui.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/io.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "Player.hpp"
#include "Water.hpp"
#include "Door.hpp"
#include "Skybox.hpp"

#include "Sound.hpp"
using namespace glm;

static bool show_gui = true;

const size_t CIRCLE_PTS = 48;


// Testing variables
bool A5::TEXTURES = true;
bool A5::NORMALMAP = true;
bool A5::SHADOWS = true;
bool A5::VFC = true;
bool A5::ENVMAP = true;
bool A5::SKYBOX = true;
int A5::MeshesDrawn = 0;


//----------------------------------------------------------------------------------------
// Constructor
A5::A5()
	: m_positionAttribLocation(0),
	  m_normalAttribLocation(0),
	  m_vao_meshData(0),
	  m_vbo_vertexPositions(0),
	  m_vbo_vertexNormals(0)
{

}

//----------------------------------------------------------------------------------------
// Destructor
A5::~A5()
{
	for(int i=0;i<objects.size();i++){
		delete objects[i];
	}

	for(int i=0;i<lights.size();i++){
		delete lights[i];
	}

	delete skybox;
	alutExit();
}

//----------------------------------------------------------------------------------------
/*
 * Called once, at program start.
 */
void A5::init()
{
	  alutInit(0, NULL);
	// Set the background colour.
	glClearColor(0.5,0.5,0.5, 1.0);
	srand(time(NULL));
	createShaderProgram();

	glGenVertexArrays(1, &m_vao_meshData);
	glBindVertexArray(m_vao_meshData);

	const char* front = "Assets/Skybox/sky_ft.png";
	const char* back = "Assets/Skybox/sky_bk.png";
	const char* up = "Assets/Skybox/sky_up.png";
	const char* down = "Assets/Skybox/sky_dn.png";
	const char* left = "Assets/Skybox/sky_rt.png";
	const char* right = "Assets/Skybox/sky_lf.png";

	skybox = new Skybox(front,back,up,down,left,right);


	float aspect = ((float)m_windowWidth) / m_windowHeight;

	player = new Player(degreesToRadians(60.0f),aspect,0.1f,300.0f);
	objects.push_back(player);
	objects.push_back(new Water());
	objects[1]->trans = glm::translate(objects[1]->trans,glm::vec3(-2.75,-.41,11.22));
	objects.push_back(new Water());
	objects[2]->trans = glm::translate(objects[2]->trans,glm::vec3(13.35,-.41,11.22));
	objects.push_back(new Object("Assets/House/scene.obj"));
	objects.push_back(new Door());
	objects.push_back(new Door());
	objects[5]->trans = glm::rotate(objects[5]->trans,glm::radians(-90.0f),glm::vec3(0,1,0));
objects[5]->trans = glm::translate(objects[5]->trans,glm::vec3(-40.5,0,-3.75));



	createDepthTexture();

	glBindVertexArray( 0 );




	initPerspectiveMatrix();

	initViewMatrix();

	initLightSources();


	//A5

	leftMouse=rightMouse=middleMouse=false;
	keyW=keyA=keyS=keyD=keySpace=false;
	renderPicker=false;
	dTime=pTime=0;
	xOffset=yOffset=0;
	prevMouseX=prevMouseY=0;



}

//----------------------------------------------------------------------------------------

void A5::createDepthTexture(){



	glGenFramebuffers(1, &frameBuffer);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


//----------------------------------------------------------------------------------------
void A5::createShaderProgram()
{
	m_shader.generateProgramObject();
	m_shader.attachVertexShader( getAssetFilePath("Shaders/VertexShader.vs").c_str() );
	m_shader.attachFragmentShader( getAssetFilePath("Shaders/FragmentShader.fs").c_str() );
	m_shader.link();

	m_outline.generateProgramObject();
	m_outline.attachVertexShader( getAssetFilePath("Shaders/OutlineVertShader.vs").c_str() );
	m_outline.attachFragmentShader( getAssetFilePath("Shaders/OutlineFragShader.fs").c_str() );
	m_outline.link();

	m_shadow.generateProgramObject();
	m_shadow.attachVertexShader( getAssetFilePath("Shaders/ShadowVertShader.vs").c_str() );
	m_shadow.attachFragmentShader( getAssetFilePath("Shaders/ShadowFragShader.fs").c_str() );
	m_shadow.link();

	m_sky.generateProgramObject();
	m_sky.attachVertexShader( getAssetFilePath("Shaders/SkyboxVert.vs").c_str() );
	m_sky.attachFragmentShader( getAssetFilePath("Shaders/SkyboxFrag.fs").c_str() );
	m_sky.link();

	m_pick.generateProgramObject();
	m_pick.attachVertexShader( getAssetFilePath("Shaders/PickVert.vs").c_str() );
	m_pick.attachFragmentShader( getAssetFilePath("Shaders/PickFrag.fs").c_str() );
	m_pick.link();

}

//----------------------------------------------------------------------------------------
void A5::initPerspectiveMatrix()
{

	m_perpsective =player->getPerspective();
}


//----------------------------------------------------------------------------------------
void A5::initViewMatrix() {
	m_view = player->getCamera();
}

//----------------------------------------------------------------------------------------
void A5::initLightSources() {
	// World-space position
		//First is directional
		lights.push_back(new Light(0,glm::vec3(1,1,-1),vec3(0.75f)));
		//second is point
		lights.push_back(new Light(1,glm::vec3(-8,4,8),vec3(0.5f)));
}

//----------------------------------------------------------------------------------------
void A5::uploadCommonSceneUniforms() {
	m_shader.enable();
	{
		//-- Set Perpsective matrix uniform for the scene:
		GLint location = m_shader.getUniformLocation("Perspective");
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
		CHECK_GL_ERRORS;

		location = m_shader.getUniformLocation("View");
		mat4 view = m_view;
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(view));

		location = m_shader.getUniformLocation("hasShadow");
		glUniform1f(location,SHADOWS);


		//-- Set LightSource uniform for the scene:
		{


			// either use all lights or find a way to disable unused ones
			for(int i=0;i<lights.size();i++){
				Light * light = lights[i];
				std::string  xx= "light" + std::to_string(i) + ".position";
				location = m_shader.getUniformLocation(xx.c_str());
				glUniform3fv(location, 1, value_ptr(light->position));

				xx="light" + std::to_string(i) + ".rgbIntensity";
				location = m_shader.getUniformLocation(xx.c_str());
				glUniform3fv(location, 1, value_ptr(light->colour));

				xx="light" + std::to_string(i) + ".attenuation";
				location = m_shader.getUniformLocation(xx.c_str());
				glUniform3fv(location,1,value_ptr(light->attenuation));

				xx="light" + std::to_string(i) + ".type";
				location = m_shader.getUniformLocation(xx.c_str());
				glUniform1f(location,light->type);


				xx="light" + std::to_string(i) + ".enabled";
				location = m_shader.getUniformLocation(xx.c_str());
				glUniform1f(location,light->enabled);

				CHECK_GL_ERRORS;
			}
		}

	}
	m_shader.disable();

	m_outline.enable();
	// Outline shader
	{
	GLint location = m_outline.getUniformLocation("Perspective");
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(m_perpsective));
	CHECK_GL_ERRORS;
	}
	m_outline.disable();
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, before guiLogic().
 */
void A5::appLogic()
{

	 // ------- Update Camera ------
	//Disabling cursor just wont work
	int width, height;
	glfwGetWindowSize(m_window, &width, &height);
	glfwSetCursorPos (m_window,width/2,height/2	);
	prevMouseX=width/2;
	prevMouseY=height/2;
	// Update player movement
	m_view = player->getCamera();;
	float currentTime = glfwGetTime();
	dTime = currentTime - pTime;
	pTime = currentTime;
	if( keyW) {
		player->moveCamera('z',dTime);
	}
	else if( keyS) {
		player->moveCamera('z',-dTime);
	}
	else{
		player->moveCamera('z',0);
	}

	if( keyA ) {
		player->moveCamera('x',-dTime);
	}
	else if( keyD) {
		player->moveCamera('x',dTime);
	}
	else{
		player->moveCamera('x',0);
	}
	player->rotateCamera(xOffset,yOffset);
	player->updateCamera();

	// ------ Update Lights ----
	for(int i=0;i<lights.size();i++){
		Light* light = lights[i];
		if(light->type==0){
			glm::mat4 depthProj = glm::ortho<float>(-40, 40, -40, 40, -100, 100);
			glm::mat4 depthView = glm::lookAt(player->getPos(),-light->position+player->getPos(),glm::vec3(0,1,0));
			light->depthMV= depthProj*depthView;
		}
	}


	uploadCommonSceneUniforms();
	xOffset=yOffset=0;
}

//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after appLogic(), but before the draw() method.
 */
void A5::guiLogic()
{
	if( !show_gui ) {
		return;
	}

	static bool firstRun(true);
	if (firstRun) {
		ImGui::SetNextWindowPos(ImVec2(50, 50));
		firstRun = false;
	}

	static bool showDebugWindow(true);
	ImGuiWindowFlags windowFlags(ImGuiWindowFlags_AlwaysAutoResize);
	windowFlags |= ImGuiWindowFlags_MenuBar;
	float opacity(0.5f);

	ImGui::Begin("Properties", &showDebugWindow, ImVec2(100,100), opacity,
			windowFlags);

			if (ImGui::MenuItem("Textures", "1",TEXTURES)) {
		    	TEXTURES=!TEXTURES;
		    }
		    if (ImGui::MenuItem("Normal Maps", "2",NORMALMAP)) {
		    	NORMALMAP=!NORMALMAP;
		    }
			    if (ImGui::MenuItem("Shadows", "3",SHADOWS)) {
		    	SHADOWS=!SHADOWS;
		    }
		    if (ImGui::MenuItem("View Frustum Culling", "4",VFC)) {
		    	VFC=!VFC;
		    }
				if (ImGui::MenuItem("Environment Maps", "5",ENVMAP)) {
		    	ENVMAP=!ENVMAP;
		    }
				if (ImGui::MenuItem("Skybox", "6",SKYBOX)) {
		    	SKYBOX=!SKYBOX;
		    }
				if (ImGui::MenuItem("Directional Light", "7",lights[0]->enabled)) {
		    	lights[0]->enabled=!lights[0]->enabled;
		    }
				if (ImGui::MenuItem("Point Light", "8",lights[1]->enabled)) {
					lights[1]->enabled=!lights[1]->enabled;
				}

				ImGui::Text( "Meshes Drawn: %i ", MeshesDrawn );
				MeshesDrawn=0;
		// Add more gui elements here here ...





		ImGui::Text( "Framerate: %.1f FPS", ImGui::GetIO().Framerate );

	ImGui::End();
}


//----------------------------------------------------------------------------------------


// Picking
// Not a good approach
void A5::clickObject(int id){
	for(int  i=0;i<objects.size();i++){
		if(objects[i]->getId()==id){
			objects[i]->clicked();
		}
	}
}


//----------------------------------------------------------------------------------------
/*
 * Called once per frame, after guiLogic().
 */
void A5::draw() {
	glBindVertexArray(m_vao_meshData);


	glEnable( GL_DEPTH_TEST );
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	// ------------ Picking -----------------
	if(renderPicker){
		renderPicker=false;
		m_pick.enable();
		for(int i=0;i<objects.size();i++) {
			//update shader uniforms
			GLint location = m_pick.getUniformLocation("MVP");
			mat4 MVP = m_perpsective*m_view * objects[i]->trans;
			glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(MVP));
			CHECK_GL_ERRORS;
			objects[i]->pick(m_pick,player);
		}
		m_pick.disable();
		glFlush();
		glFinish();


		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		unsigned char data[4];
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glReadPixels(prevMouseX, viewport[3]-prevMouseY,1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);

		// Convert the color back to an integer ID
		int id = data[0] + data[1] * 256 + data[2] * 256*256;
		std::cout << id << std::endl;
		if(id<=objects.size()){
			clickObject(id);
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


	// --------------------------------------



	// ------------ Shadows -----------------
	if(SHADOWS){
	for(int k=0;k<lights.size();k++){
		Light* curLight = lights[k];
		m_shadow.enable();
		glViewport(0,0,curLight->shadowmapSize,curLight->shadowmapSize);
		glBindFramebuffer(GL_FRAMEBUFFER,frameBuffer);
		// Directional light
		if(curLight->type==0){
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, curLight->shadowMap, 0);
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
			glClear(GL_DEPTH_BUFFER_BIT);
			mat4 depthMV = lights[k]->depthMV;
			for(int i=0;i<objects.size();i++){
				mat4 depthMVP = depthMV*objects[i]->trans;
				GLint loc = m_shadow.getUniformLocation("depthMVP");
				glUniformMatrix4fv(loc,1,GL_FALSE,value_ptr(depthMVP));
				objects[i]->drawVerts(m_shadow);
			}
		}
		else{

			// Point Light source , NOT WORKING
			float aspect = ((float)m_windowWidth) / m_windowHeight;
			glm::mat4 depthProj = glm::perspective(90.0f, aspect, .1f, 300.0f);
			std::vector<glm::mat4> shadowTransforms;
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(-1.0,0.0,0.0), glm::vec3(0.0,-1.0,0.0)));
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(0.0,1.0,0.0), glm::vec3(0.0,0.0,1.0)));
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(0.0,-1.0,0.0), glm::vec3(0.0,0.0,-1.0)));
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(0.0,0.0,1.0), glm::vec3(0.0,-1.0,0.0)));
			shadowTransforms.push_back(depthProj *
			                 glm::lookAt(curLight->position, curLight->position + glm::vec3(0.0,0.0,-1.0), glm::vec3(0.0,-1.0,0.0)));
			for(int i=0;i<6;i++){
				CHECK_GL_ERRORS;
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, curLight->shadowCubeMap, 0);
				CHECK_GL_ERRORS;
				glDrawBuffer(GL_NONE);
				glReadBuffer(GL_NONE);
				glClear(GL_DEPTH_BUFFER_BIT);
				CHECK_GL_ERRORS;
				for(int j=0;j<objects.size();j++){
					mat4 depthMVP = shadowTransforms[i]*objects[j]->trans;
					GLint loc = m_shadow.getUniformLocation("depthMVP");
					glUniformMatrix4fv(loc,1,GL_FALSE,value_ptr(depthMVP));
					objects[j]->drawVerts(m_shadow);
				}

			}

		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		m_shadow.disable();
	}


	int width, height;
	glfwGetWindowSize(m_window, &width, &height);

	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	}
	// ------------  -----------------



	glDisable(GL_CULL_FACE);
	glDepthFunc(GL_LEQUAL);
	// ----- SKYBOX ----
	if(SKYBOX){
		m_sky.enable();

		GLint location = m_sky.getUniformLocation("MVP");
		mat4 MVP =m_perpsective*glm::rotate(mat4(),glm::radians(player->pitch),glm::vec3(-1,0,0))*glm::rotate(mat4(),glm::radians(player->yaw),glm::vec3(0,1,0));
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(MVP));
		CHECK_GL_ERRORS;
		skybox->draw(m_sky);

		m_sky.disable();
	}
	// -------------------





	// ------------ Outlines-----------------

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);

	m_outline.enable();
	for(int i=0;i<objects.size();i++) {
		//update shader uniforms
		GLint location = m_outline.getUniformLocation("ModelView");
		mat4 modelView = m_view * objects[i]->trans;
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
		CHECK_GL_ERRORS;


		objects[i]->drawOutline(m_outline,player);
	}
	m_outline.disable();


	// ------------  -----------------



	// ------------ Geometry-----------------
	glFrontFace(GL_CW);
	glCullFace(GL_FRONT);
	m_shader.enable();


	// No mesh should have more than 9 textures, should be ok

	// Update skybox uniform for env map
	GLuint skyLoc = m_shader.getUniformLocation("envMap");
	glActiveTexture(GL_TEXTURE0+9);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skybox->getSkyboxTexture());
	glUniform1i(skyLoc,9);
	CHECK_GL_ERRORS;

	for(int i=0;i<lights.size();i++){
		Light* light = lights[i];
		if(light->type==0){
			std::string  uniName= "shadowMap" + std::to_string(i);
			GLint mapLoc = m_shader.getUniformLocation(uniName.c_str());
			glActiveTexture(GL_TEXTURE0+10+i);
			glBindTexture(GL_TEXTURE_2D, light->shadowMap);
			glUniform1i(mapLoc,10+i);
			CHECK_GL_ERRORS;
		}
		else{
			std::string  uniName= "cubeShadowMap0";
			GLint mapLoc = m_shader.getUniformLocation(uniName.c_str());
			glActiveTexture(GL_TEXTURE0+10+i);
			glBindTexture(GL_TEXTURE_CUBE_MAP, light->shadowCubeMap);
			glUniform1i(mapLoc,10+i);
			CHECK_GL_ERRORS;
		}
	}


	CHECK_GL_ERRORS;
	for(int i=0;i<objects.size();i++) {
		CHECK_GL_ERRORS;
		for(int k=0;k<lights.size();k++){
			CHECK_GL_ERRORS;
			Light* light = lights[k];
			if(light->type==0){
				CHECK_GL_ERRORS;
				mat4 depthBiasMVP =light->depthMV*objects[i]->trans;
				CHECK_GL_ERRORS;
				std::string  uniName= "depthBiasMVP" + std::to_string(k);
				GLint loc = m_shader.getUniformLocation(uniName.c_str());
				CHECK_GL_ERRORS;
				glUniformMatrix4fv(loc,1,GL_FALSE,value_ptr(depthBiasMVP));
				CHECK_GL_ERRORS;
			}else{
				CHECK_GL_ERRORS;
				mat4 depthBiasMVP =objects[i]->trans;
				CHECK_GL_ERRORS;
				std::string  uniName= "depthBiasMVP" + std::to_string(k);
				GLint loc = m_shader.getUniformLocation(uniName.c_str());
				CHECK_GL_ERRORS;
				glUniformMatrix4fv(loc,1,GL_FALSE,value_ptr(depthBiasMVP));
				CHECK_GL_ERRORS;
			}
		}

		GLint location = m_shader.getUniformLocation("ModelView");
		mat4 modelView = m_view * objects[i]->trans;
		glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(modelView));
		CHECK_GL_ERRORS;

		location = m_shader.getUniformLocation("NormalMatrix");
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(mat3(modelView)));
		glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(normalMatrix));


		CHECK_GL_ERRORS;
		objects[i]->draw(m_shader,player);
	}



	m_shader.disable();





	glBindVertexArray(0);
	glDisable( GL_DEPTH_TEST );
	CHECK_GL_ERRORS;
}




//----------------------------------------------------------------------------------------
/*
 * Called once, after program is signaled to terminate.
 */
void A5::cleanup()
{

}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles cursor entering the window area events.
 */
bool A5::cursorEnterWindowEvent (
		int entered
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse cursor movement events.
 */
bool A5::mouseMoveEvent (
		double xPos,
		double yPos
) {
	bool eventHandled(false);

	// Fill in with event handling code...



	if (!ImGui::IsMouseHoveringAnyWindow()) {
		xOffset=(xPos- prevMouseX);
		yOffset=(yPos- prevMouseY);
	}
	return eventHandled;
}



//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse button events.
 */
bool A5::mouseButtonInputEvent (
		int button,
		int actions,
		int mods
) {
	bool eventHandled(false);
	bool changed=false;
	bool changed2=false;
	// Fill in with event handling code...
	if (!ImGui::IsMouseHoveringAnyWindow()) {
		if(button==GLFW_MOUSE_BUTTON_LEFT){
			if(actions==GLFW_PRESS){
				renderPicker=true;
			}
		}
		else if(button==GLFW_MOUSE_BUTTON_MIDDLE){

		}

		else if(button==GLFW_MOUSE_BUTTON_RIGHT){
			if(actions==GLFW_RELEASE){
				rightMouse=false;

			}
			else if (actions==GLFW_PRESS){

			}
		}
	}

	return eventHandled;
}



//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles mouse scroll wheel events.
 */
bool A5::mouseScrollEvent (
		double xOffSet,
		double yOffSet
) {
	bool eventHandled(false);

	// Fill in with event handling code...

	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles window resize events.
 */
bool A5::windowResizeEvent (
		int width,
		int height
) {
	bool eventHandled(false);
	initPerspectiveMatrix();
	return eventHandled;
}

//----------------------------------------------------------------------------------------
/*
 * Event handler.  Handles key input events.
 */
bool A5::keyInputEvent (
		int key,
		int action,
		int mods
) {
	bool eventHandled(false);
	float speed = 0.05f;
	if( action == GLFW_PRESS ) {
		if( key == GLFW_KEY_W ) {
			keyW=true;
		}
		if( key == GLFW_KEY_A ) {
			keyA=true;
		}
		if( key == GLFW_KEY_S ) {
			keyS=true;
		}
		if( key == GLFW_KEY_D ) {
			keyD=true;
		}
		if( key == GLFW_KEY_SPACE ) {
			keySpace=true;
		}
		if( key == GLFW_KEY_F11 ) {

		}
		if(key==GLFW_KEY_Q){
			glfwSetWindowShouldClose(m_window, GL_TRUE);
		}
		if(key==GLFW_KEY_1){
			TEXTURES=!TEXTURES;
		}
		if(key==GLFW_KEY_2){
			NORMALMAP=!NORMALMAP;
		}
		if(key==GLFW_KEY_3){
			SHADOWS=!SHADOWS;
		}
		if(key==GLFW_KEY_4){
			VFC=!VFC;
		}
		if(key==GLFW_KEY_7){
			lights[0]->enabled = !lights[0]->enabled;
		}
		if(key==GLFW_KEY_8){
			lights[1]->enabled = !lights[1]->enabled;
		}
		if(key==GLFW_KEY_5){
			ENVMAP=!ENVMAP;
		}
		if(key==GLFW_KEY_6){
			SKYBOX=!SKYBOX;
		}

	}
	if( action == GLFW_RELEASE ) {
		if( key == GLFW_KEY_W ) {
			keyW=false;
		}
		if( key == GLFW_KEY_A ) {
			keyA=false;
		}
		if( key == GLFW_KEY_S ) {
			keyS=false;
		}
		if( key == GLFW_KEY_D ) {
			keyD=false;
		}
		if( key == GLFW_KEY_SPACE ) {
			keySpace=false;
		}
	}
	// Fill in with event handling code...

	return eventHandled;
}
