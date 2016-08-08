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

struct Material {
    vec3 kd;
    vec3 ks;
    float shininess;
};


in VsOutFsIn {
	vec3 position_ES; // Eye-space position
	vec3 normal_ES;   // Eye-space normal
  vec2 uvCoord;
  mat3 TBN;
  mat4 invView;
  LightSource light0;
  LightSource light1;
} fs_in;

uniform int numLights;


// Booleans
uniform bool hasTexture;
uniform bool hasNormalMap;
uniform bool hasEnvMap;
uniform bool hasShadow;

out vec4 fragColour;



uniform Material material;

// Ambient light intensity for each RGB component.
uniform vec3 ambientIntensity;

// Textures
uniform sampler2D diffuseTexture;
uniform sampler2D normalTexture;

uniform sampler2D shadowMap0;
uniform sampler2D shadowMap1;
uniform samplerCube cubeShadowMap0;

uniform samplerCube envMap;



// Had to split up directional from point calculations, if statements and arrays cause problems

// Thanks to learnopengl.com for help with shadows, prideout.com for toon shading antialiasing and opengl-tutorial.org for info on normal mapping

// Calculate the shadow for directional light
// returns the visibility of the shadow ( 1 actually means not visible)
float calcShadow(vec4 fragPos,LightSource light,sampler2D shadowMap){
  vec3 mapCoord = fragPos.xyz / fragPos.w;
  mapCoord = mapCoord * 0.5 + 0.5;

  float closestDepth = texture(shadowMap, mapCoord.xy).r;
  float currentDepth = mapCoord.z;

  vec3 normal = normalize(fs_in.normal_ES);
  vec3 lightDir = normalize(light.position - fs_in.position_ES);

  // Bias to combat shadow acne, still doesn't work well
  float bias=min(0.05 * (1.0 - dot(normal, lightDir)), 0.0005);
  float visibility = 0.0;
  vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

  // Perform PCF
  for(int x = -1; x <= 1; ++x){
    for(int y = -1; y <= 1; ++y){
      float pcf = texture(shadowMap, mapCoord.xy + vec2(x,y)*texelSize ).r;
      visibility += currentDepth - bias > pcf ? 0.0 : 1.0;
    }
  }
  visibility /= 9.0;
    // Shadow outside visible range, dont draw shadow
    if(mapCoord.z > 1.0)
        visibility = 1.0;
    return visibility;
}

// Calculate the shadow for point light
// returns the visibility of the shadow ( 1 actually means not visible)
// Currently Does not work
float calcPointShadow(vec4 fragPos,LightSource light,samplerCube depthMap)
{

  vec3 fragToLight = normalize(fragPos.xyz/fragPos.w - light.position);
  // Use the light to fragment vector to sample from the depth map
  float closestDepth = texture(depthMap, fragToLight).r*300;
  // It is currently in linear range between [0,1]. Re-transform back to original value
  // Now get current linear depth as the length between the fragment and light position
  float currentDepth = length(fragToLight)*300;
  // Now test for shadows
  float bias = 0.05;
  float shadow = currentDepth -  bias > closestDepth ? 0.0 : 1.0;

  return shadow;
}




// Calculate point light of fragment using toon shading technique
vec3 celShadePoint(LightSource light,samplerCube shadow){
  vec3 lightVec;
  vec3 normalVec;
  vec3 viewVec = -fs_in.position_ES.xyz;
  vec3 halfWayVec;
  float attenuation = 1.0;
  float visibilitySpec =1;
  float visibilityDiff =1;

    // Light is point
   lightVec =(light.position.xyz-fs_in.position_ES);
   float dist = length(lightVec);
   attenuation = 1.0/(light.attenuation.x + light.attenuation.y*dist + light.attenuation.z*pow(dist,2));
   if(hasShadow){
     visibilitySpec = calcPointShadow(light.shadowCoord,light,shadow);
     visibilityDiff=min(visibilitySpec, 0.75);
   }
  if(hasNormalMap){
    normalVec=texture2D(normalTexture, vec2(fs_in.uvCoord.x,fs_in.uvCoord.y)).rgb*2.0 - 1.0;
    lightVec= fs_in.TBN*lightVec;
    viewVec=fs_in.TBN*viewVec;
  }
  else{
    normalVec=fs_in.normal_ES;
 }

  // Normalize everything
  lightVec = normalize(lightVec);
  normalVec = normalize(normalVec);
  viewVec = normalize(viewVec);
  halfWayVec = normalize(viewVec +lightVec);

  //Edge detection (Disabled for now, doesn't work well with sharp corners)
  float edge=(dot(normalVec,viewVec)>  0.3) ? 1 : 0;


  float dIntensity = max(0,dot(normalVec,lightVec));
  float sIntensity = max(0,dot(normalVec,halfWayVec));
  sIntensity = pow(sIntensity,material.shininess);

  //Cel shading with antialiasing
  float dEpsilon = fwidth(dIntensity);
  float steps[5]=float[](0.05,0.15,0.3,0.5,1.0);
  if(dIntensity<steps[0]+dEpsilon&&dIntensity>steps[0]-dEpsilon){
    dIntensity=mix(steps[0],steps[1],smoothstep(steps[0]-dEpsilon, steps[0]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[1]+dEpsilon&&dIntensity>steps[1]-dEpsilon){
    dIntensity=mix(steps[1],steps[2],smoothstep(steps[1]-dEpsilon, steps[1]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[2]+dEpsilon&&dIntensity>steps[2]-dEpsilon){
    dIntensity=mix(steps[2],steps[3],smoothstep(steps[2]-dEpsilon, steps[2]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[3]+dEpsilon&&dIntensity>steps[3]-dEpsilon){
    dIntensity=mix(steps[3],steps[4],smoothstep(steps[3]-dEpsilon, steps[3]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[0]){
    dIntensity=0;
  }
  else if(dIntensity<steps[1]){
    dIntensity=steps[1];
  }
  else if(dIntensity<steps[2]){
    dIntensity=steps[2];
  }
  else if(dIntensity<steps[3]){
    dIntensity=steps[3];
  }
  else if(dIntensity<steps[4]){
    dIntensity=steps[4];
  }


  float sEpsilon = fwidth(sIntensity);
  if(sIntensity >0.5-sEpsilon&&sIntensity<0.5+sEpsilon){
    sIntensity = clamp(0.5 * (sIntensity - 0.5 + sEpsilon) / sEpsilon, 0.0, 1.0);
  }
  else{
    sIntensity = step(0.5,sIntensity);
  }

  vec3 color =  attenuation*light.rgbIntensity*(visibilityDiff*dIntensity*material.kd +visibilitySpec*sIntensity*material.ks);
  return color;
}



// Calculate directional light of fragment using toon shading technique
vec3 celShadeDir(LightSource light, sampler2D shadowMap){
  vec3 lightVec;
  vec3 normalVec;
  vec3 viewVec = -fs_in.position_ES.xyz;
  vec3 halfWayVec;
  float attenuation = 1.0;
  float visibilitySpec =1;
  float visibilityDiff =1;
  lightVec = light.position.xyz;
  float dist = length(lightVec);
  attenuation = 1.0/(light.attenuation.x + light.attenuation.y*dist + light.attenuation.z*pow(dist,2));
  if(hasShadow){
    visibilitySpec =calcShadow(light.shadowCoord,light,shadowMap);
    visibilityDiff = min(visibilitySpec, 0.75);
  }


  vec3 tempNorm = texture2D(normalTexture, vec2(fs_in.uvCoord.x,fs_in.uvCoord.y)).rgb*2.0 - 1.0;
  if(hasNormalMap){
    normalVec+=tempNorm;
    lightVec= fs_in.TBN*lightVec;
    viewVec=fs_in.TBN*viewVec;
  }
  else{
    normalVec=fs_in.normal_ES;
 }

  // Normalize everything
  lightVec = normalize(lightVec);
  normalVec = normalize(normalVec);
  viewVec = normalize(viewVec);
  halfWayVec = normalize(viewVec +lightVec);

  //Edge detection (Disabled for now, doesn't work well with sharp corners)
  float edge=(dot(normalVec,viewVec)>  0.3) ? 1 : 0;





  float dIntensity = max(0,dot(normalVec,lightVec));
  float sIntensity = max(0,dot(normalVec,halfWayVec));
  sIntensity = pow(sIntensity,material.shininess);

  //Cel shading with antialiasing
  float dEpsilon = fwidth(dIntensity);
  float steps[5]=float[](0.05,0.15,0.4,0.8,1.0);
  if(dIntensity<steps[0]+dEpsilon&&dIntensity>steps[0]-dEpsilon){
    dIntensity=mix(steps[0],steps[1],smoothstep(steps[0]-dEpsilon, steps[0]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[1]+dEpsilon&&dIntensity>steps[1]-dEpsilon){
    dIntensity=mix(steps[1],steps[2],smoothstep(steps[1]-dEpsilon, steps[1]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[2]+dEpsilon&&dIntensity>steps[2]-dEpsilon){
    dIntensity=mix(steps[2],steps[3],smoothstep(steps[2]-dEpsilon, steps[2]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[3]+dEpsilon&&dIntensity>steps[3]-dEpsilon){
    dIntensity=mix(steps[3],steps[4],smoothstep(steps[3]-dEpsilon, steps[3]+dEpsilon, dIntensity));
  }
  else if(dIntensity<steps[0]){
    dIntensity=0;
  }
  else if(dIntensity<steps[1]){
    dIntensity=steps[1];
  }
  else if(dIntensity<steps[2]){
    dIntensity=steps[2];
  }
  else if(dIntensity<steps[3]){
    dIntensity=steps[3];
  }
  else if(dIntensity<steps[4]){
    dIntensity=steps[4];
  }


  float sEpsilon = fwidth(sIntensity);
  if(sIntensity >0.5-sEpsilon&&sIntensity<0.5+sEpsilon){
    sIntensity = clamp(0.5 * (sIntensity - 0.5 + sEpsilon) / sEpsilon, 0.0, 1.0);
  }
  else{
    sIntensity = step(0.5,sIntensity);
  }

  vec3 color =  attenuation*light.rgbIntensity*(visibilityDiff*dIntensity*material.kd +visibilitySpec*sIntensity*material.ks);
  return color;
}

vec3 calcReflection(){
  vec3 reflection =reflect(fs_in.position_ES, fs_in.normal_ES);
  reflection =  vec3(fs_in.invView*vec4(reflection,0.0));
  return reflection;

}

void main() {
  vec3 color =vec3(0,0,0);
  float opacity = 1.0;

  if(fs_in.light0.enabled>0.5){
    color+=celShadeDir(fs_in.light0,shadowMap0);
  }
  if(fs_in.light1.enabled>0.5){
    color+=celShadePoint(fs_in.light1,cubeShadowMap0);
  }

  color+=ambientIntensity ;

  if(hasEnvMap){
    vec3 reflection = calcReflection();
    color *= texture(envMap,reflection).xyz;
  }
  if(hasTexture){
    color= color * texture2D(diffuseTexture,fs_in.uvCoord).xyz;
  }
	fragColour = vec4(color,opacity);



}
