#include "main.h"
#include "fade.h"
#include "manager.h"
#include "scene.h"
#include "title.h"

#include <typeinfo>

ID3D11Buffer*				CFade::m_VertexBuffer = NULL;
ID3D11ShaderResourceView*	CFade::m_Texture = NULL;

FADE_STATE CFade::m_fade = FADE_STATE_NONE;
CScene* CFade::m_nextscene = NULL;
float CFade::m_fadealpha = 0.0f;
float CFade::m_addalpha = 1 / 20.0f;

D3DXCOLOR CFade::m_fadecolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);

void CFade::Init(void)
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

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
		"asset/texture/fade.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);

	assert(m_Texture);
}

void CFade::Uninit(void)
{
	m_Texture->Release();
	m_VertexBuffer->Release();
}

void CFade::Update(void)
{
	if (m_fade == FADE_STATE_OUT) {
		if (m_fadealpha >= 1.0f) {
			m_fadealpha = 1.0f;
			m_fade = FADE_STATE_IN;
			CManager::SetScene(m_nextscene);
			m_nextscene = NULL;
		}
		m_fadealpha += m_addalpha;
	}
	else if (m_fade == FADE_STATE_IN) {
		if (m_fadealpha <= 0.0f) {
			m_fadealpha = 0.0f;
			m_fade = FADE_STATE_NONE;
		}
		m_fadealpha -= m_addalpha;
	}
}

void CFade::Draw(void)
{
	if (m_fade == FADE_STATE_NONE) {
		return;
	}

	m_fadecolor.a = m_fadealpha;

	//　マトリクス設定
	CRenderer::SetWorldViewProjection2D();

	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	VERTEX_3D *vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);


	vertex[1].Position = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(m_fadecolor.r, m_fadecolor.g, m_fadecolor.b, m_fadecolor.a);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//　頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(
		0, 1, &m_VertexBuffer, &stride, &offset);

	//　マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);

	//　テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//　プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//　ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}