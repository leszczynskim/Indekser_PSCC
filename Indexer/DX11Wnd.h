#pragma once

#include "DX11Graphics.h"
#include "framework\Mesh.h"
#include "framework\ConstantBuffer.h"
#include "framework\PhongEffect.h"
#include "framework\Camera.h"
// DX11Wnd

class DX11Wnd : public CWnd, public DX11Graphics
{
	DECLARE_DYNAMIC(DX11Wnd)

public:
	DX11Wnd();
	virtual ~DX11Wnd();
	bool Init();
	void SetModel(std::wstring const & path);
	void InitializeConstantBuffers();
	void UpdateCamera();
	bool Render();
	void InitializeCamera();
	void ReleaseObjects();
	void DrawScene();
	Mesh m_model;
	std::shared_ptr<CBMatrix> m_worldCB;
	std::shared_ptr<PhongEffect> m_phongEffect;
	std::shared_ptr<CBMatrix> m_viewCB;
	std::shared_ptr<CBMatrix> m_inverseViewCB;
	std::shared_ptr<CBMatrix> m_projCB;
	std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4, 2>> m_lightPosCB;
	std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4>> m_surfaceColorCB;
	std::shared_ptr<ConstantBuffer<DirectX::XMFLOAT4>> m_cameraPosCB;
	std::shared_ptr<ID3D11InputLayout> m_layout;
	DirectX::XMMATRIX m_projMtx;
	Camera m_camera;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
private:
	 int oldX;
	 int oldY;
	 bool leftClick;
	 bool rightClick;
	 bool middleClick;
	 float AngleX = 0;
	 float AngleY = 0;
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};


