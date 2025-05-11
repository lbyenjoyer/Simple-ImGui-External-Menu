#include "dllmain.h"


LPDIRECT3D9 pD3D = NULL;
LPDIRECT3DDEVICE9 pDevice = NULL;
HWND hwnd = NULL;
bool isMenuVisible = true;
void SetImGuiStyle() {
    // Set rounding and padding
    // Set the colors based on the given palette
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // General background - dark, close to #030d1a with added transparency
    colors[ImGuiCol_WindowBg] = ImVec4(0.01f, 0.05f, 0.10f, 0.90f); // Background theme with transparency
    colors[ImGuiCol_ChildBg] = ImVec4(0.01f, 0.05f, 0.10f, 0.90f); // Background theme with transparency
    colors[ImGuiCol_PopupBg] = ImVec4(0.01f, 0.05f, 0.10f, 0.85f); // Popup background with transparency

    // Text color - light off-white with a blueish hint
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f); // Soft white text
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f); // Disabled text

    // Border colors - Dark with slight contrast
    colors[ImGuiCol_Border] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);

    // Frame colors - main accent color #1779ac
    colors[ImGuiCol_FrameBg] = ImVec4(0.21f, 0.47f, 0.67f, 0.85f); // Main theme accent with transparency
    colors[ImGuiCol_FrameBgHovered] = ImVec4(0.21f, 0.47f, 0.67f, 0.90f); // Hover accent with transparency
    colors[ImGuiCol_FrameBgActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Active accent

    // Title bar - a bit more transparent to differentiate it from the background
    colors[ImGuiCol_TitleBg] = ImVec4(0.01f, 0.05f, 0.10f, 0.75f); // Title bar background with transparency
    colors[ImGuiCol_TitleBgActive] = ImVec4(0.01f, 0.05f, 0.10f, 1.00f); // Title bar active state
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f); // Collapsed title bar

    // Menu bar - matching the background theme
    colors[ImGuiCol_MenuBarBg] = ImVec4(0.01f, 0.05f, 0.10f, 0.90f); // Menu bar background with transparency

    // Scrollbar background and grab - dark with an accent of the main color
    colors[ImGuiCol_ScrollbarBg] = ImVec4(0.02f, 0.02f, 0.02f, 0.39f); // Dark scrollbar background
    colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Main theme for scrollbar grab
    colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Hovered scrollbar grab
    colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Active scrollbar grab

    // Button colors - main theme, with a slightly darker hover
    colors[ImGuiCol_Button] = ImVec4(0.21f, 0.47f, 0.67f, 0.90f); // Button color with transparency
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.21f, 0.47f, 0.67f, 0.95f); // Hover button color with transparency
    colors[ImGuiCol_ButtonActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Active button color

    // Header - with a transparent effect on hover and active
    colors[ImGuiCol_Header] = ImVec4(0.21f, 0.47f, 0.67f, 0.55f); // Header background
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.21f, 0.47f, 0.67f, 0.80f); // Hovered header background
    colors[ImGuiCol_HeaderActive] = ImVec4(0.21f, 0.47f, 0.67f, 0.80f); // Active header background

    // Separator - accentuated with main theme
    colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
    colors[ImGuiCol_SeparatorHovered] = ImVec4(0.21f, 0.47f, 0.67f, 0.78f); // Hovered separator
    colors[ImGuiCol_SeparatorActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Active separator

    // Resize grip - slightly visible, matches the main color
    colors[ImGuiCol_ResizeGrip] = ImVec4(0.21f, 0.47f, 0.67f, 0.25f); // Resize grip
    colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.21f, 0.47f, 0.67f, 0.67f); // Hovered resize grip
    colors[ImGuiCol_ResizeGripActive] = ImVec4(0.21f, 0.47f, 0.67f, 0.95f); // Active resize grip

    // Tab - uses main accent color
    colors[ImGuiCol_Tab] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Tab color
    colors[ImGuiCol_TabHovered] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Hovered tab color
    colors[ImGuiCol_TabActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Active tab color
    colors[ImGuiCol_TabUnfocused] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Unfocused tab color
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Unfocused active tab

    // Plot lines - light gray with an orange hover
    colors[ImGuiCol_PlotLines] = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f); // Orange hover

    // Plot histogram - yellow with a bright orange hover
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f); // Yellow
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f); // Orange hover

    // Selected text background - transparent with the main color
    colors[ImGuiCol_TextSelectedBg] = ImVec4(0.21f, 0.47f, 0.67f, 0.35f); // Main theme background for selected text

    // Drag-drop target - red color for highlighting
    colors[ImGuiCol_DragDropTarget] = ImVec4(1.00f, 0.00f, 0.00f, 0.90f); // Drag-drop target red highlight

    // Navigation highlight - using main accent color
    colors[ImGuiCol_NavHighlight] = ImVec4(0.21f, 0.47f, 0.67f, 1.00f); // Main theme highlight color

    // Set rounding for UI elements
    style.WindowRounding = 8.0f; // Rounded corners for windows
    style.ChildRounding = 6.0f; // Rounded corners for child windows
    style.FrameRounding = 6.0f; // Rounded corners for frames (buttons, inputs, etc.)
    style.PopupRounding = 8.0f; // Rounded corners for popups
    style.ScrollbarRounding = 6.0f; // Rounded corners for scrollbars
    style.GrabRounding = 6.0f; // Rounded corners for grabbers
    style.TabRounding = 6.0f; // Rounded corners for tabs
}
D3DPRESENT_PARAMETERS d3dpp;
bool InitialD3D(HWND hWnd) {
    if ((pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) {
        return false;
    }

    ZeroMemory(&d3dpp, sizeof(d3dpp));
    d3dpp.Windowed = 1;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    if (pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDevice) < 0) {
        return false;
    }

    ImGui::CreateContext();
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX9_Init(pDevice);
    // Set ImGui style
    SetImGuiStyle();
    return true;
}
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, message, wParam, lParam))
        return 1;
    switch (message) {
    case WM_DESTROY: {
        PostQuitMessage(0);
        return 0;
    }
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}
void CreateImGuiWindow() {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WindowProc, 0L, 0L, GetModuleHandle(0), 0, 0, 0, 0, L"ImGuiWindow", 0 };
    RegisterClassEx(&wc);
    int windowWidth = 380;
    int windowHeight = 420;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int x = (screenWidth - windowWidth) / 2;
    int y = (screenHeight - windowHeight) / 2;

    hwnd = CreateWindow(L"ImGuiWindow", L"Neverlose Nightly", WS_POPUP | WS_VISIBLE, x, y, windowWidth, windowHeight, 0, 0, wc.hInstance, 0);

    SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_SIZEBOX & ~WS_MAXIMIZEBOX);
    SetWindowPos(hwnd, NULL, x, y, windowWidth, windowHeight, SWP_NOZORDER | SWP_FRAMECHANGED);

    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    if (!InitialD3D(hwnd)) {
        MessageBox(0, L"Failed to initialize Direct3D!", L"Error", MB_ICONERROR | MB_OK);
    }
}

void DestroyImGuiWindow() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    pDevice->Release();
    pD3D->Release();
    DestroyWindow(hwnd);
    UnregisterClass(L"ImGuiWindow", GetModuleHandle(0));
}

DWORD WINAPI MainThread(LPVOID lpParam) {
    CreateImGuiWindow();
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, 0, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        }
        if ((GetAsyncKeyState(VK_INSERT) & 0x8000) && (GetAsyncKeyState('I') & 1)) {
            isMenuVisible = !isMenuVisible;
            if (isMenuVisible) {
                ShowWindow(hwnd, SW_SHOW);
                SetForegroundWindow(hwnd);
                SetFocus(hwnd);
                BringWindowToTop(hwnd);
            }
            else ShowWindow(hwnd, SW_HIDE);

            this_thread::sleep_for(chrono::milliseconds(16));
        }
        if (isMenuVisible) {
            ImGui_ImplDX9_NewFrame();
            ImGui_ImplWin32_NewFrame();
            ImGui::NewFrame();
            RenderGui();
            ImGui::EndFrame();
            ImGui::Render();
            pDevice->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
            pDevice->BeginScene();
            ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
            pDevice->EndScene();
            if (pDevice->Present(0, 0, 0, 0) == D3DERR_DEVICELOST) {
                if (pDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
                    ImGui_ImplDX9_InvalidateDeviceObjects();
                    pDevice->Reset(&d3dpp);
                    ImGui_ImplDX9_CreateDeviceObjects();
                }
            }
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(36));
        }
    }
    DestroyImGuiWindow();
    return 0;
}

// Main Entry Of DLL
BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        NL::Load();
        this_thread::sleep_for(chrono::seconds(1));
        CreateThread(0, 0, MainThread, 0, 0, 0);
    }
    return 1;
}
