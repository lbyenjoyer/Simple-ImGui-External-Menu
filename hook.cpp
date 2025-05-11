#include "dllmain.h"

bool MenuVisibilityStatus = TRUE;

LPDIRECT3D9 pd3d = NULL;
LPDIRECT3DDEVICE9 pdevice = NULL;
HWND hwnd = NULL;
D3DPRESENT_PARAMETERS d3dpp;

bool InitialDX(HWND hwnd) {
	if ((pd3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
		return FALSE;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	if (pd3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pdevice) < 0) 
		return FALSE;
	ImGui::CreateContext();
	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplDX9_Init(pdevice);
	return TRUE;
}
LRESULT CALLBACK WindowProcess(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
void AllocateWindow() {
	WNDCLASSEX WindowClass = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProcess, 0L, 0L, GetModuleHandle(0), NULL, NULL, NULL, NULL, L"ImGuiWindow", NULL };
	RegisterClassEx(&WindowClass);
	
	int WindowWidth = 300;
	int WindowHeight = 350;
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int WindowLocationX = (ScreenWidth - WindowWidth) / 2;
	int WindowLocationY = (ScreenHeight - WindowHeight) / 2;

	hwnd = CreateWindow(L"ImGuiWindow", L"Menu", WS_POPUP | WS_VISIBLE, WindowLocationX, WindowLocationY, WindowWidth, WindowHeight, NULL, NULL, WindowClass.hInstance, NULL);

	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
	SetWindowPos(hwnd, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);

	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);
}
void FreeWindow() {
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
	pdevice->Release();
	pd3d->Release();
	DestroyWindow(hwnd);
	UnregisterClass(L"ImGuiWindow", GetModuleHandle(0));
}
DWORD WINAPI MainThread(LPVOID lpparam) {
	AllocateWindow();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT) {
		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		// Menu Visibility Status
		if (GetAsyncKeyState(VK_INSERT) & 0x8000) {
			MenuVisibilityStatus = !MenuVisibilityStatus;

			if (MenuVisibilityStatus) {
				ShowWindow(hwnd, SW_SHOW);
				SetForegroundWindow(hwnd);
				SetFocus(hwnd);
				BringWindowToTop(hwnd);
			}
			else ShowWindow(hwnd, SW_HIDE);

			this_thread::sleep_for(chrono::milliseconds(16));
		}
		if (MenuVisibilityStatus) {
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			// GUI RELATED CODE HERE



			ImGui::EndFrame();
			ImGui::Render();
			pdevice->Clear(NULL, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0F, NULL);
			pdevice->BeginScene();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			pdevice->EndScene();
			if (pdevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST) {
				if (pdevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
					ImGui_ImplDX9_InvalidateDeviceObjects();
					pdevice->Reset(&d3dpp);
					ImGui_ImplDX9_CreateDeviceObjects();
				}
			}
		}
		else this_thread::sleep_for(chrono::milliseconds(36));
	}
	FreeWindow();
	return FALSE;
}