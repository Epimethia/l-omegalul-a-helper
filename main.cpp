// Dear ImGui: standalone example application for DirectX 11
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"
#include <d3d11.h>
#include <tchar.h>


#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>
#include "HelperFunctions.h"
#include "valtan.h"
#include "vykas.h"
#include "mainmenu.h"


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Data
static ID3D11Device* g_pd3dDevice = nullptr;
static ID3D11DeviceContext* g_pd3dDeviceContext = nullptr;
static IDXGISwapChain* g_pSwapChain = nullptr;
static UINT g_ResizeWidth = 0, g_ResizeHeight = 0;
static ID3D11RenderTargetView* g_mainRenderTargetView = nullptr;

static int                      WindowWidth = 400;
static int                      WindowHeight = 100;
static int                      WindowHeightExpanded = 300;

static bool                     mbdown = false;
static POINT                    mbdown_offset = {};

// Forward declarations of helper functions
bool CreateDeviceD3D(HWND hWnd);
void CleanupDeviceD3D();
void CreateRenderTarget();
void CleanupRenderTarget();
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void SetWindowStyle();

DisplayRaid CurrentRaid = DisplayRaid::MENU;


// Simple helper function to load an image into a DX11 texture with common settings
//bool LoadTextureFromFile(const char* filename, ID3D11ShaderResourceView** out_srv, int* out_width, int* out_height);

// Forward Declaration of Menus and Helper Functions
void ProcessWindowMovement(const HWND& hwnd);

//Static Resources used by the program


static RECT windowrect = { 500, 200, 0, 0 };
static ImGuiIO* io = nullptr;

// Main code
int main(int, char**)
{
    // Create application window
    ImGui_ImplWin32_EnableDpiAwareness();
    WNDCLASSEXW wc = { sizeof(wc), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(nullptr), nullptr, nullptr, nullptr, nullptr, L"ImGui Example", nullptr };
    ::RegisterClassExW(&wc);
    //HWND hwnd = ::CreateWindowW(wc.lpszClassName, L"Dear ImGui DirectX11 Example", WS_OVERLAPPEDWINDOW, 100, 100, 400, 800, nullptr, nullptr, wc.hInstance, nullptr);
    HWND hwnd = CreateWindowExW(WS_EX_TOPMOST, L"ImGui Example", L"ImGui Example", WS_POPUP, 800, 100, WindowWidth, WindowHeight, 0, 0, 0, 0);
    // Initialize Direct3D
    if (!CreateDeviceD3D(hwnd))
    {
        CleanupDeviceD3D();
        ::UnregisterClassW(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ::ShowWindow(hwnd, SW_SHOWDEFAULT);
    ::UpdateWindow(hwnd);

    ImGui_ImplWin32_EnableAlphaCompositing(hwnd);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); (void)io;
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX11_Init(g_pd3dDevice, g_pd3dDeviceContext);

    

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    //io->Fonts->AddFontDefault();
    //io->Fonts->AddFontFromFileTTF("./Resources/Nunito-ExtraLight.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io->Fonts->AddFontFromFileTTF("./Resources/Fonts/CreatoDisplay-Regular.otf", 14.0f);
    //IM_ASSERT(font != nullptr);

    // Our state
    ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
    bool run = true;
    bool expandedWindow = false;
    bool bOpen = false;

    SetP3DDevice(g_pd3dDevice);
    if (!InitValtanMechs()) return 1;
    if (!InitMainMenu()) return 1;
    if (!InitVykasMechs()) return 1;

    SetWindowStyle();

    while (run)
    {
        // Poll and handle messages (inputs, window resize, etc.)
        // See the WndProc() function below for our to dispatch events to the Win32 backend.
        MSG msg;
        while (::PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            if (msg.message == WM_QUIT)
                run = false;
        }
        if (!run)
            break;

        if (expandedWindow) {
            MoveWindow(hwnd, windowrect.left, windowrect.top, WindowWidth, WindowHeightExpanded, false);
        }
        else {
            MoveWindow(hwnd, windowrect.left, windowrect.top, WindowWidth, WindowHeight, false);
        }


        ProcessWindowMovement(hwnd);

        // Handle window resize (we don't resize directly in the WM_SIZE handler)

        if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
        {
            CleanupRenderTarget();
            g_pSwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
            g_ResizeWidth = g_ResizeHeight = 0;
            CreateRenderTarget();
        }

        // Start the Dear ImGui frame
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();
        //ImGui::PushFont(font);

        ImGui::SetNextWindowPos({ 0,0 });
        if (!expandedWindow) {
            ImGui::SetNextWindowSize({ static_cast<float>(WindowWidth), static_cast<float>(WindowHeight) });
        }
        else {
            ImGui::SetNextWindowSize({ static_cast<float>(WindowWidth), static_cast<float>(WindowHeightExpanded) });
        }

        ImGuiWindowFlags WindowFlags = (
            ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | 
            ImGuiWindowFlags_NoCollapse | 
            ImGuiWindowFlags_MenuBar | 
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoScrollWithMouse |
            ImGuiWindowFlags_NoTitleBar
        );

        {

            if (ImGui::Begin("Lost Ark Helper", &run, WindowFlags)) {

                if (ImGui::BeginMenuBar()) {
                    if (ImGui::BeginMenu("Menu")) {
                        if (ImGui::MenuItem("Raid Selection")) { CurrentRaid = DisplayRaid::MENU; };
                        if (ImGui::MenuItem("Exit")) { run = false; };
                        ImGui::EndMenu();
                    }

                    switch (CurrentRaid)
                    {
                    case DisplayRaid::MENU:
                        break;
                    case DisplayRaid::VALTAN:
                        if (ImGui::BeginMenu("Gates")) {
                            if (ImGui::MenuItem("Gate One")) {};
                            if (ImGui::MenuItem("Gate Two")) {};
                            ImGui::EndMenu();
                        }
                        break;
                    case DisplayRaid::VYKAS:
                        if (ImGui::BeginMenu("Vykas Gates")) {
                            if (ImGui::MenuItem("Gate One")) {};
                            if (ImGui::MenuItem("Gate Two")) {};
                            ImGui::EndMenu();
                        }
                        break;
                    case DisplayRaid::CLOWN:
                        if (ImGui::BeginMenu("Gates")) {
                            if (ImGui::MenuItem("Gate One")) {};
                            if (ImGui::MenuItem("Gate Two")) {};
                            if (ImGui::MenuItem("Gate Three")) {};
                            if (ImGui::MenuItem("Gate Four: Bingo")) {};
                            ImGui::EndMenu();
                        }
                        break;
                    case DisplayRaid::BRELSHAZA:
                        if (ImGui::BeginMenu("Gates")) {
                            if (ImGui::MenuItem("Gate One")) {};
                            if (ImGui::MenuItem("Gate Two")) {};
                            if (ImGui::MenuItem("Gate Three")) {};
                            if (ImGui::MenuItem("Gate Four")) {};
                            ImGui::EndMenu();
                        }
                        break;
                    case DisplayRaid::AKKAN:
                        break;
                    case DisplayRaid::ARGOS:
                        break;
                    case DisplayRaid::KAYANGLE:
                        break;
                    default:
                        break;
                    }

                }

                ImGui::EndMenuBar();
                GetWindowRect(hwnd, &windowrect);


                switch (CurrentRaid)
                {
                    case DisplayRaid::MENU:
                        ProcessMainMenu(expandedWindow, io->MousePos, CurrentRaid);
                        break;
                    case DisplayRaid::VALTAN:
                        ProcessValtanMechs(expandedWindow, io->MousePos);
                        break;
                    case DisplayRaid::VYKAS:
                        ProcessVykasMechs(expandedWindow, io->MousePos);
                        break;
                    case DisplayRaid::CLOWN:
                        break;
                    case DisplayRaid::BRELSHAZA:
                        break;
                    default:
                        break;
                }

                ImGui::End();

            };

        }

        // Rendering
        ImGui::Render();
        const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
        g_pd3dDeviceContext->OMSetRenderTargets(1, &g_mainRenderTargetView, nullptr);
        g_pd3dDeviceContext->ClearRenderTargetView(g_mainRenderTargetView, clear_color_with_alpha);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());


        g_pSwapChain->Present(1, 0); // Present with vsync
        //g_pSwapChain->Present(0, 0); // Present without vsync
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    CleanupDeviceD3D();
    ::DestroyWindow(hwnd);
    ::UnregisterClassW(wc.lpszClassName, wc.hInstance);

    return 0;
}

// Helper functions

bool CreateDeviceD3D(HWND hWnd)
{
    // Setup swap chain
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 2;
    sd.BufferDesc.Width = 0;
    sd.BufferDesc.Height = 0;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT createDeviceFlags = 0;
    //createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
    D3D_FEATURE_LEVEL featureLevel;
    const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
    HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
        res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &featureLevel, &g_pd3dDeviceContext);
    if (res != S_OK)
        return false;

    CreateRenderTarget();
    return true;
}

void CleanupDeviceD3D()
{
    CleanupRenderTarget();
    if (g_pSwapChain) { g_pSwapChain->Release(); g_pSwapChain = nullptr; }
    if (g_pd3dDeviceContext) { g_pd3dDeviceContext->Release(); g_pd3dDeviceContext = nullptr; }
    if (g_pd3dDevice) { g_pd3dDevice->Release(); g_pd3dDevice = nullptr; }
}

void CreateRenderTarget()
{
    ID3D11Texture2D* pBackBuffer;
    g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
    g_pd3dDevice->CreateRenderTargetView(pBackBuffer, nullptr, &g_mainRenderTargetView);
    pBackBuffer->Release();
}

void CleanupRenderTarget()
{
    if (g_mainRenderTargetView) { g_mainRenderTargetView->Release(); g_mainRenderTargetView = nullptr; }
}

// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Win32 message handler
// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;


    switch (msg)
    {
    case WM_SIZE:
        if (wParam == SIZE_MINIMIZED)
            return 0;
        g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
        g_ResizeHeight = (UINT)HIWORD(lParam);
        return 0;
    case WM_SYSCOMMAND:
        if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
            return 0;
        break;
    case WM_DESTROY:
        ::PostQuitMessage(0);
        return 0;

    case WM_LBUTTONDOWN:
        mbdown = true;
        mbdown_offset = { (long)io->MousePos.x, (long)io->MousePos.y};

        return 0;

    case WM_LBUTTONUP:
        mbdown = false;
        return 0;
    }
    return ::DefWindowProcW(hWnd, msg, wParam, lParam);
}

void SetWindowStyle()
{

    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.2f, 0.2f, 0.85f));
    ImGui::PushStyleColor(ImGuiCol_MenuBarBg, ImVec4(0.05f, 0.05f, 0.05f, 0.6f));
    ImGui::PushStyleColor(ImGuiCol_Tab, ImVec4(0.05f, 0.05f, 0.05f, 0.4f));
    ImGui::PushStyleColor(ImGuiCol_TabActive, ImVec4(0.0f, 0.15f, 0.3f, 0.8f));
    ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(0.0f, 0.15f, 0.3f, 0.3f));
    ImGui::PushStyleColor(ImGuiCol_TableHeaderBg, ImVec4(0.0f, 0.0f, 0.0f, 0.7f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);

}

void ProcessWindowMovement(const HWND& hwnd)
{

    GetWindowRect(hwnd, &windowrect);

    if (mbdown) {
        POINT pt;
        GetCursorPos(&pt);

        if (pt.y - windowrect.top > 30) return;

        SetWindowPos(hwnd, HWND_TOPMOST, pt.x - mbdown_offset.x, pt.y - mbdown_offset.y, 0, 0, SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER);
    }
}
