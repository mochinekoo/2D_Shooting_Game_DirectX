#include <Windows.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d2d1.h>
#include <dwrite.h>
#include "dinput.h"
#include "input.h"
#include <cstdio>
#include "MyDirectX.h"
#include "Triangle.h"
#include "Square.h"
#include "SoundManager.h"
#include "Image.h"
#include "SceneManager.h"
#include "ImGUI/imgui_impl_win32.h"
#include "ImGUI/imgui_impl_dx11.h"

using namespace MyDirectX;
#pragma comment(lib , "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d2d1.lib") 
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace {
    const int WINDOW_WIDTH = 1280;
    const int WINDOW_HEIGHT = 720;
}

int initWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd);
HRESULT initImGUI(HWND hwnd);
void updateMainLoop();
void drawMainLoop();
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    if (initWindow(hInstance, hPrevInstance, lpCmdLine, nShowCmd) == -1) {
        return -1;
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam)) {
        return true;
    }

    switch (msg) {
    case WM_DESTROY: {
        PostQuitMessage(0); //メッセージループ終了（=アプリを終了）
        break;
    }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}


int initWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    WNDCLASSEXW wndClass = {};
    wndClass.cbSize = sizeof(WNDCLASSEXW);
    wndClass.lpszClassName = L"WindowClass";
    wndClass.lpfnWndProc = WndProc;
    wndClass.style = CS_VREDRAW | CS_HREDRAW;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    RegisterClassEx(&wndClass);

    //ウインドウを作成する
    HWND hwnd = {};
    hwnd = CreateWindow(
        L"WindowClass", //クラス名
        L"テストウインドウ", //ウインドウタイトル
        WS_BORDER | WS_OVERLAPPEDWINDOW, //ウインドウスタイル
        CW_USEDEFAULT, //表示位置X（デフォルト）
        CW_USEDEFAULT, //表示位置Y（デフォルト）
        WINDOW_WIDTH, //ウインドウ幅
        WINDOW_HEIGHT, //ウインドウ高さ
        NULL, //親ウインドウ
        NULL, //メニュー
        hInstance, //インスタンス
        NULL //パラメータ
    );

    if (hwnd == NULL) {
        return -1;
    }

    MyDirectX::initDirectX(hwnd);
	HRESULT result = {};
    result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    assert(SUCCEEDED(result));
   
    ShowWindow(hwnd, nShowCmd); //ウインドウを表示
    UpdateWindow(hwnd);

    Input::initKey(hInstance, hwnd);
    SoundManager::initialize();
    SceneManager::InitManager();
    initImGUI(hwnd);

    //メッセージ
    MSG msg = {};
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            updateMainLoop();
            drawMainLoop();
        }
    }

    return 0;
}

HRESULT initImGUI(HWND hwnd) {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsLight();
    ImGui_ImplWin32_Init(hwnd);
    ID3D11Device* device = (ID3D11Device*)MyDirectX::device_;
    ID3D11DeviceContext* deviceContext = (ID3D11DeviceContext*)context_;
    ImGui_ImplDX11_Init(device, deviceContext);

    return S_OK;
}

void updateMainLoop() {
    auto currentScene = SceneManager::GetCurrentScene();
    if (currentScene != nullptr) {
        currentScene->Update();
    }

    Input::SetInputState();

    if (SoundManager::audioList.size() > 0) {
        for (SoundData soundData : SoundManager::audioList) {
            if (soundData.sourceVoice != nullptr) {
                if ((soundData.state.BuffersQueued > 0) != 0) {
                    soundData.sourceVoice->GetState(&soundData.state);
                }
            }
        }
    }
}

void drawMainLoop() {
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX11_NewFrame();
    ImGui::NewFrame();

    float color[4] = { 0, 0, 0, 1.0f };

    MyDirectX::context_->OMSetRenderTargets(1, &MyDirectX::renderTargetView, nullptr);
    MyDirectX::context_->ClearRenderTargetView(MyDirectX::renderTargetView, color);

    auto currentScene = SceneManager::GetCurrentScene();
    if (currentScene != nullptr) {
        currentScene->Draw();
    }

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    MyDirectX::swapChain->Present(1, 0);
}