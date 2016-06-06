#include <DirectXMath.h>
using namespace DirectX;
class Camera
{
public:
	Camera();
	DirectX::XMMATRIX GetViewMatrix() const;
	void GetViewMatrix(DirectX::XMMATRIX& viewMatrix) const;
	void Rotate(float dx, float dy);
	void Move(XMFLOAT3 v);
	XMFLOAT4 GetPosition() const;
private:
	float m_angleX;
	float m_angleY;
	XMFLOAT4 m_position;
};