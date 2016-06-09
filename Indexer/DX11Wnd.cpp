#include "stdafx.h"
#include "Indexer.h"
#include "DX11Wnd.h"

IMPLEMENT_DYNAMIC(DX11Wnd, CWnd)

DX11Wnd::DX11Wnd() : m_camera()
{
	leftClick = false;
	rightClick = false;
	middleClick = false;
	m_model = Mesh(m_device);
	AngleX = 0;
	AngleY = 0;
}

DX11Wnd::~DX11Wnd()
{
}

bool DX11Wnd::Init()
{
	CPaintDC dc(this);
	CRect rect;
	GetWindowRect(&rect);
	if (!Initialize(GetSafeHwnd(), 1300, 700))
	{
		return false;
	}
	InitializeConstantBuffers();
	InitializeCamera();

	m_worldCB.reset(new CBMatrix(m_device));
	m_phongEffect.reset(new PhongEffect(m_device, m_layout));
	m_phongEffect->SetProjMtxBuffer(m_projCB);
	m_phongEffect->SetViewMtxBuffer(m_viewCB);
	m_phongEffect->SetWorldMtxBuffer(m_worldCB);
	m_phongEffect->SetLightPosBuffer(m_lightPosCB);
	m_phongEffect->SetSurfaceColorBuffer(m_surfaceColorCB);
	return true;
}

void DX11Wnd::SetModel(std::wstring const &path)
{
	std::wstring s = path;
	if (s.empty()) return;
	s += L"1.fb2.stl";
	if (!m_model.LoadMesh(s, m_device)) return;
	m_model.setWorldMatrix(XMMatrixIdentity());
	m_camera = Camera();
	AngleX = 0;
	AngleY = 0;
}

void DX11Wnd::InitializeConstantBuffers()
{
	m_projCB.reset(new CBMatrix(m_device));
	m_viewCB.reset(new CBMatrix(m_device));
	m_inverseViewCB.reset(new CBMatrix(m_device));
	m_worldCB.reset(new CBMatrix(m_device));
	m_lightPosCB.reset(new ConstantBuffer<XMFLOAT4, 2>(m_device));
	m_surfaceColorCB.reset(new ConstantBuffer<XMFLOAT4>(m_device));
	m_cameraPosCB.reset(new ConstantBuffer<XMFLOAT4>(m_device));
}
BEGIN_MESSAGE_MAP(DX11Wnd, CWnd)
	ON_WM_ERASEBKGND()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
END_MESSAGE_MAP()

void DX11Wnd::UpdateCamera()
{
	XMMATRIX view; 
	CRect rect;
	GetWindowRect(&rect);
	auto ar = static_cast<float>(rect.Width()) / rect.Height();
	m_projMtx = XMMatrixPerspectiveFovLH(XM_PIDIV4, ar, 0.01f, 10000);
	m_camera.GetViewMatrix(view);
	m_viewCB->Update(m_context, view);
	m_inverseViewCB->Update(m_context, XMMatrixInverse(nullptr, view));
	m_cameraPosCB->Update(m_context, m_camera.GetPosition());
}

bool DX11Wnd::Render() {
	if (m_context == nullptr)
		return false;

	m_projCB->Update(m_context, m_projMtx);
	UpdateCamera();
	float bgColor[4] = { 0,0,0,1.0f };
	m_context->ClearRenderTargetView(m_backBuffer.get(), bgColor);
	m_context->ClearDepthStencilView(m_depthStencilView.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	DrawScene();
	m_swapChain->Present(0, 0);
	return true;
}

void DX11Wnd::InitializeCamera()
{
	CRect rect;
	GetWindowRect(&rect);
	auto ar = static_cast<float>(rect.Width()) / rect.Height();
	m_projMtx = XMMatrixPerspectiveFovLH(XM_PIDIV4, ar, 0.01f, 10000);
	m_projCB->Update(m_context, m_projMtx);
	UpdateCamera();
}

void DX11Wnd::ReleaseObjects()
{
	m_context->Release();
	m_swapChain->Release();
}

void DX11Wnd::DrawScene()
{
	m_phongEffect->Begin(m_context);
	m_surfaceColorCB->Update(m_context, XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	m_worldCB->Update(m_context, m_model.getWorldMatrix());
	m_model.Render(m_context);
	m_phongEffect->End();
}

BOOL DX11Wnd::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}

void DX11Wnd::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	__super::OnLButtonDblClk(nFlags, point);
}

void DX11Wnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	leftClick = true;
	SetCapture();
}

void DX11Wnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	leftClick = false;
	ReleaseCapture();
}

void DX11Wnd::OnMouseMove(UINT nFlags, CPoint point)
{
	int dx = point.x - oldX;
	int dy = point.y - oldY;
	oldX = point.x;
	oldY = point.y;
	if (leftClick)
	{
		AngleX += dy / 300.0f;
		AngleY += dx / 300.0f;
		m_model.setWorldMatrix(XMMatrixRotationX(AngleX)*XMMatrixRotationY(AngleY));
	}
	else if (rightClick)
		m_camera.Move(XMFLOAT3(dx / 3.0f, -dy / 3.0f, 0));
	else if (middleClick)
		m_camera.Move(XMFLOAT3(0.0f, 0.0f, dy / 1.0f));
}

void DX11Wnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	rightClick = true;
	SetCapture();
}

void DX11Wnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	rightClick = false;
	ReleaseCapture();
}

void DX11Wnd::OnMButtonDown(UINT nFlags, CPoint point)
{
	middleClick = true;
	SetCapture();
}

void DX11Wnd::OnMButtonUp(UINT nFlags, CPoint point)
{
	middleClick = false;
	ReleaseCapture();
}
