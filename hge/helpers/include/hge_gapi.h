//-------------------------------------------------
// Modifications and additional types, included internally, do not include from your game project
// GAPI dependent includes and defines (DX8/DX9 switch)
// added by kvakvs@yandex.ru
// Forum discussion thread http://relishgames.com/forum/viewtopic.php?t=6235
// GIT repository https://github.com/kvakvs/hge
//-------------------------------------------------

//#include <d3d9.h>
//#include <d3dx9.h>

// #if HGE_DIRECTX_VER == 9
//     typedef IDirect3D9              hgeGAPI;
//     typedef IDirect3DDevice9        hgeGAPIDevice;
//     typedef IDirect3DVertexBuffer9  hgeGAPIVertexBuffer;
//     typedef IDirect3DIndexBuffer9   hgeGAPIIndexBuffer;
//     typedef IDirect3DTexture9       hgeGAPITexture;
//     typedef IDirect3DSurface9       hgeGAPISurface;
//     typedef D3DVIEWPORT9            hgeGAPIViewport;
//     typedef D3DADAPTER_IDENTIFIER9  hgeGAPIAdapterIdentifier;
// 	typedef D3DCAPS9				hgeGAPICaps;
// #endif


#if HGE_DIRECTX_VER == 11
#include <d3d11.h>
#include <d3dx11.h>

	// global declarations
// 	IDXGISwapChain *swapchain;             // the pointer to the swap chain interface
// 	ID3D11Device *dev;                     // the pointer to our Direct3D device interface
// 	ID3D11DeviceContext *devcon;           // the pointer to our Direct3D device context
// 	ID3D11RenderTargetView *backbuffer;    // the pointer to our back buffer
// 	ID3D11InputLayout *pLayout;            // the pointer to the input layout
// 	ID3D11VertexShader *pVS;               // the pointer to the vertex shader
// 	ID3D11PixelShader *pPS;                // the pointer to the pixel shader
// 	ID3D11Buffer *pVBuffer;                // the pointer to the vertex buffer
// 	ID3D11Texture2D;
#endif