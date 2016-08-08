#version 330
#define MAX_LIGHTS 12
struct LightSource {
    vec3 position;
    vec3 rgbIntensity;
    vec3 attenuation;
    float type;

    float enabled;
    vec4 shadowCoord;
};




// Model-Space coordinates
in vec3 position;
in vec3 normal;
in vec3 tangent;
in vec3 bitangent;
in vec2 uv;

uniform LightSource light0;
uniform LightSource light1;

uniform mat4 ModelView;
uniform mat4 View;
uniform mat4 Perspective;


uniform mat3 NormalMatrix;
uniform mat4 depthBiasMVP0;
uniform mat4 depthBiasMVP1;
out VsOutFsIn {
	vec3 position_ES; // Eye-space position
	vec3 normal_ES;   // Eye-space normal
  vec2 uvCoord;
  mat3 TBN;
  mat4 invView;
	LightSource light0;
  LightSource light1;
} vs_out;


// GLSL + ARRAYS = THE WORST
void setUpLights(){
  vec4 pos4 = vec4(position, 1.0);
    vec4 light4;
  // Light 0
  vs_out.light0 = light0;
  if(light0.type==0.0){
      light4 =vec4(light0.position.xyz,0);
    }
    else{
      light4 =vec4(light0.position.xyz,1);
     }

  vs_out.light0.position = (View *light4).xyz;
  vs_out.light0.shadowCoord=depthBiasMVP0*pos4;


  //Light 1
  vs_out.light1 = light1;
  if(light1.type==0.0){
      light4 =vec4(light1.position.xyz,0);
    }
    else{
      light4 =vec4(light1.position.xyz,1);
     }
     vs_out.light1.shadowCoord=depthBiasMVP1*pos4;
  vs_out.light1.position = (View *light4).xyz;
}

void main() {
	vec4 pos4 = vec4(position, 1.0);
	//-- Convert position and normal to Eye-Space:
	vs_out.normal_ES = normalize(NormalMatrix * normal);
  vec3 tangentCamera = normalize(NormalMatrix* tangent);
  vec3 bitangentCamera = normalize(NormalMatrix * bitangent);
  vs_out.TBN = transpose(mat3(tangentCamera,bitangentCamera,vs_out.normal_ES));


  setUpLights();


  vs_out.position_ES = (ModelView * pos4).xyz;
  vs_out.uvCoord=uv;
  vs_out.invView = inverse(View);


	gl_Position = Perspective * ModelView * vec4(position, 1.0);
}
