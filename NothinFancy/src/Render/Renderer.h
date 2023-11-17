#pragma once
#include <d3d11_3.h>
#include <wrl/client.h>

#include "Window.h"

#include "ShaderSet.h"
#include "Buffer.h"
#include "InputLayout.h"
#include "SamplerState.h"
#include "Texture.h"
#include "BlendState.h"
#include "Framebuffer.h"
#include "Model.h"

using Microsoft::WRL::ComPtr;

template <typename T>
using UP = std::unique_ptr<T>;

namespace nf::render {
	class Renderer {
	public:
		Renderer(Window& window, DisplayConfig& dispConfig);

		void setDisplay(DisplayConfig& conf);
		void doFrame();

		~Renderer();
	private:
		void outputRTV(ComPtr<ID3D11RenderTargetView> rtv);

		Window& m_window;
		const UINT m_scFlags;

		ComPtr<ID3D11Device3> m_device;
		ComPtr<ID3D11DeviceContext4> m_context;
		ComPtr<IDXGISwapChain2> m_sc;
		ComPtr<ID3D11RenderTargetView1> m_outRTV;

		//Test stuff
		UP<ShaderSet> m_testShaders;
		UP<Buffer> m_testConstantBuffer;
		UP<InputLayout> m_testLayout;
		UP<SamplerState> m_testSampler;
		UP<Texture> m_testTexture;
		UP<BlendState> m_testBlendState;
		UP<Framebuffer> m_testFramebuffer;
		UP<Model> m_testModel;
	};
}