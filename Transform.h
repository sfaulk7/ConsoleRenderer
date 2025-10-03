#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "glm/gtx/quaternion.hpp"

namespace aie
{

	class Transform
	{
	public:
		glm::vec3 LocalPos;
		glm::quat LocalRot;
		glm::vec3 LocalScl;

		Transform();

		// get/set parent
		void SetParent(Transform* newParent);
		Transform* GetParent() const;

		// get children
		Transform* GetChildAtIndex(size_t index) const;
		size_t GetChildCount() const;

		// get local model matrix
		glm::mat4 LocalMat() const; // already completed in previous exercises
		// get global model matrix
		glm::mat4 WorldMat() const;

		// matrix used for converting transforming local-space coordinates to world-space
		glm::mat4 LocalToWorldMatrix() const;
		// matrix used for converting transforming world-space coordinates to local-space
		glm::mat4 WorldToLocalMatrix() const;

		// get/set world-space position
		glm::vec3 GetPosition() const;
		void SetPosition(glm::vec3 position);

		// get/set world-space rotation
		glm::quat GetRotation() const;
		void SetRotation(glm::quat rotation);

		// get/set world-space forward
		glm::vec3 GetForward() const;
		void SetForward(glm::vec3 forward);

		// get world-space scale (sort of)
		glm::vec3 GetLossyScale() const;


	private:
		// you may want implement any private functions to help with the above
	};

}