#pragma once
#include <glm\glm\glm.hpp>
#include <glm\glm\gtx\transform.hpp>
#include <iostream>
#include <string>

class Transform
{
public:
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) {
		m_position = pos;
		m_rotation = rot;
		m_scale = scale;
	}

	inline glm::mat4 GetModel() const {
		glm::mat4 posMatrix = glm::translate(m_position);
		glm::mat4 rotXMatrix = glm::rotate(m_rotation.x, glm::vec3(1, 0, 0));
		glm::mat4 rotYMatrix = glm::rotate(m_rotation.y, glm::vec3(0, 1, 0));
		glm::mat4 rotZMatrix = glm::rotate(m_rotation.z, glm::vec3(0, 0, 1));
		glm::mat4 scaleMatrix = glm::scale(m_scale);

		glm::mat4 rotMatrix = rotXMatrix * rotYMatrix * rotZMatrix;

		return posMatrix * rotMatrix * scaleMatrix;
	}
	
	inline glm::vec3& GetPos() {
		return m_position;
	}

	inline glm::vec3& GetRotation() {
		return m_rotation;
	}

	inline glm::vec3& GetScale() {
		return m_scale;
	}

	inline void SetPosition(const glm::vec3& position) {
		m_position = position;
	}

	inline void SetRotation(const glm::vec3& rotation) {
		m_rotation = rotation;
	}

	inline void SetScale(const glm::vec3& scale) {
		m_scale = scale;
	}

	virtual ~Transform();

private:
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
};

