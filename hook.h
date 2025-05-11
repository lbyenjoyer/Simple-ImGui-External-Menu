#pragma once

extern bool MenuVisibilityStatus;

extern LPDIRECT3D9 pd3d;
extern LPDIRECT3DDEVICE9 pdevice;
extern HWND hwnd;
extern D3DPRESENT_PARAMETERS d3dpp;

bool InitialDX(HWND hWnd);
void AllocateWindow();
void FreeWindow();

extern DWORD WINAPI MainThread(LPVOID lpparam);

LRESULT CALLBACK WindowProcess(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);