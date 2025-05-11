#pragma once
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <d3d9.h>
#include <thread>
#include <chrono>
#include <vector>
#include <string>


#include "imgui\imgui.h"
#include "imgui\imgui_impl_dx9.h"
#include "imgui\imgui_impl_win32.h"
#include "imgui\imgui_internal.h"
#define IMGUI_ENABLE_DOCKING

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

#include "hook.h"

using namespace std;