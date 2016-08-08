#include "Material.hpp"
Material::Material(
	const glm::vec3& kd, const glm::vec3& ks, const glm::vec3& ka, float shininess,float reflect )
	: m_kd(kd)
	, m_ks(ks)
	,m_ka(ka)
	, m_shininess(shininess)
	, m_reflect(reflect)
{}

Material::~Material()
{}


  glm::vec3 Material::getKd(){
  	return m_kd;
  }
  glm::vec3 Material::getKs(){
  	return m_ks;
  }
	glm::vec3 Material::getKa(){
  	return m_ka;
  }
  double Material::getShininess(){
  	return m_shininess;
  }
	float Material::getReflect(){
  	return m_reflect;
  }
