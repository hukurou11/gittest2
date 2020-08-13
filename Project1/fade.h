#pragma once

enum FADE_STATE {
	FADE_STATE_NONE = 0,
	FADE_STATE_IN,
	FADE_STATE_OUT
};

class CFade
{
	static ID3D11Buffer*				m_VertexBuffer;
	static ID3D11ShaderResourceView*	m_Texture;		// テクスチャセットすることでフェードの時に画像でできる

	static FADE_STATE m_fade;
	static class CScene* m_nextscene;
	static float m_fadealpha;
	static float m_addalpha;

	static D3DXCOLOR m_fadecolor;
public:
	static void Init(void);			//初期化
	static void Uninit(void);		//解放
	static void Update(void);		//更新
	static void Draw(void);			//描画

	template<typename T>
	static void SetFade()
	{
		m_fade = FADE_STATE_OUT;

		T* scene = new T();
		m_nextscene = scene;
	}

	static FADE_STATE GetFadeState() { return m_fade; }			//現在のFadeの状態を取得する
};