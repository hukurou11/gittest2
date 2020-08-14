#include "main.h"
#include "renderer.h"
#include "game_object.h"
#include "UI.h"

void CUI::Init(const char* file, D3DXVECTOR2 Position, D3DXVECTOR2 Size, D3DXVECTOR2 texstart, D3DXVECTOR2 texsize)
{
	m_UIPosition = Position;
	m_UISize = Size;
	m_UItexStartPosition = texstart;
	m_UItexSize = texsize;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(m_UIPosition.x - m_UISize.x * 0.5f, m_UIPosition.y - m_UISize.y * 0.5f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x, m_UItexStartPosition.y);

	vertex[1].Position = D3DXVECTOR3(m_UIPosition.x + m_UISize.x * 0.5f, m_UIPosition.y - m_UISize.y * 0.5f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x + m_UItexSize.x, m_UItexStartPosition.y);

	vertex[2].Position = D3DXVECTOR3(m_UIPosition.x - m_UISize.x * 0.5f, m_UIPosition.y + m_UISize.y * 0.5f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x, m_UItexStartPosition.y + m_UItexSize.y);

	vertex[3].Position = D3DXVECTOR3(m_UIPosition.x + m_UISize.x * 0.5f, m_UIPosition.y + m_UISize.y * 0.5f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x + m_UItexSize.x, m_UItexStartPosition.y + m_UItexSize.y);


	//頂点バッファの生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		file,
		NULL,
		NULL,
		&m_Textuer,
		NULL);

}

void CUI::Uninit()
{
	m_VertexBuffer->Release();
	m_Textuer->Release();
}

void CUI::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//
	CRenderer::SetWorldViewProjection2D();

	if (m_Mapflg) {
		D3D11_MAPPED_SUBRESOURCE msr;
		CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

		VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

		vertex[0].Position = D3DXVECTOR3(m_UIPosition.x - m_UISize.x * 0.5f, m_UIPosition.y - m_UISize.y * 0.5f, 0.0f);
		vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[0].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x, m_UItexStartPosition.y);

		vertex[1].Position = D3DXVECTOR3(m_UIPosition.x + m_UISize.x * 0.5f, m_UIPosition.y - m_UISize.y * 0.5f, 0.0f);
		vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[1].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x + m_UItexSize.x, m_UItexStartPosition.y);

		vertex[2].Position = D3DXVECTOR3(m_UIPosition.x - m_UISize.x * 0.5f, m_UIPosition.y + m_UISize.y * 0.5f, 0.0f);
		vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[2].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x, m_UItexStartPosition.y + m_UItexSize.y);

		vertex[3].Position = D3DXVECTOR3(m_UIPosition.x + m_UISize.x * 0.5f, m_UIPosition.y + m_UISize.y * 0.5f, 0.0f);
		vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[3].TexCoord = D3DXVECTOR2(m_UItexStartPosition.x + m_UItexSize.x, m_UItexStartPosition.y + m_UItexSize.y);

		CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);
	}

	//
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;

	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Textuer);

	//
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	//
	CRenderer::GetDeviceContext()->Draw(4, 0);
}