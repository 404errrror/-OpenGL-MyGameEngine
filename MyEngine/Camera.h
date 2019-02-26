#pragma once
#include "Global.h"
class Camera
{
public:
	Camera();
	~Camera();

	static void SetProjection(
		float viewAngle , float screenRatio, 
		float minRender, float maxRender
	);
	static void SetView(glm::vec3 position, glm::vec3 viewPosition, glm::vec3 up);
	static void SetOrthoView(glm::vec3 position, glm::vec3 viewPosition, glm::vec3 up);

	/// <summary>
	/// Projection * View �� �����ɴϴ�.
	/// </summary>
	static glm::mat4 GetVP();
	static glm::mat4 GetOrthoVP();

	/// <summary>
	/// ���ٰ��� ���ų� �մϴ�.
	/// </summary>
	static void PerspectiveButton(bool isPerspective);
private:
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::mat4 ortho;
	static glm::mat4 orthoView;

	static bool m_isPerspective;
};

