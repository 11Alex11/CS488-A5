#pragma once
#include <glm/glm.hpp>

class Material {
public:
  Material(const glm::vec3& kd, const glm::vec3& ks,const glm::vec3& ka, float shininess,float reflect =0.0f);
  glm::vec3 getKd();
  glm::vec3 getKs();
  glm::vec3 getKa();
  double getShininess();
  float getReflect();
  virtual ~Material();

private:
  glm::vec3 m_kd;
  glm::vec3 m_ks;
  glm::vec3 m_ka;
  float m_reflect;
  float m_shininess;
};
