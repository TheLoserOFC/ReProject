#include "Main.h"
#include <string.h>
#include <stdio.h>
#include "imgui-docking/imgui_internal.h"
#include "Utils/Utils.hpp"
#include "API/API.hpp"
#include "d3dx9tex.h"

char user_name[255] = "";
char pass_word[255] = "";
static bool logued = false;


void Render_Profile(ImTextureID user_texture_id, float tamanho, ImU32 col, int Segmentos)
{
	auto window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	window->DrawList->PathClear();
	ImVec2 pos = window->DC.CursorPos;
	if ((col & IM_COL32_A_MASK) == 0 || Segmentos <= 2)
		return;


	const bool push_texture_id = window->DrawList->_TextureIdStack.empty() || user_texture_id != window->DrawList->_TextureIdStack.back();
	if (push_texture_id)
		window->DrawList->PushTextureID(user_texture_id);

	int vert_start_idx = window->DrawList->VtxBuffer.Size;
	const float a_max = IM_PI * 2.0f * ((float)Segmentos - 1.0f) / (float)Segmentos;
	window->DrawList->PathArcTo(pos, tamanho, 0.0f, a_max, Segmentos - 1);
	window->DrawList->PathFillConvex(col);
	int vert_end_idx = window->DrawList->VtxBuffer.Size;

	ImGui::ShadeVertsLinearUV(window->DrawList, vert_start_idx, vert_end_idx, ImVec2(pos.x - tamanho, pos.y - tamanho), ImVec2(pos.x + tamanho, pos.y + tamanho), ImVec2(0, 0), ImVec2(1, 1), true);

	if (push_texture_id)
		window->DrawList->PopTextureID();
}


int APIENTRY WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, LOADER_BRAND, NULL };

	RegisterClassEx(&wc);
	main_hwnd =  CreateWindow(wc.lpszClassName, LOADER_BRAND, WS_VISIBLE | WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 3, 3, NULL, NULL, wc.hInstance, NULL);
	
	if (!CreateDeviceD3D(main_hwnd)) {
		CleanupDeviceD3D();
		UnregisterClass(wc.lpszClassName, wc.hInstance);
		return 1;
	}

	ShowWindow(main_hwnd, SW_HIDE);
	UpdateWindow(main_hwnd);
	SetLayeredWindowAttributes(main_hwnd, 0, 0, 0);
	ImGui::CreateContext();

	ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr;

	ImGui::StyleColorsDark();



	
	ImGui_ImplWin32_Init(main_hwnd);
	ImGui_ImplDX9_Init(g_pd3dDevice);


	//Inicialização das Imagens
	D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &logo, sizeof(logo), 250, 90, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &logo_img);

	D3DXCreateTextureFromFileInMemoryEx(g_pd3dDevice, &NoUser_b, sizeof(NoUser_b), 64, 64, D3DX_DEFAULT, D3DUSAGE_DYNAMIC, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &NoUser);

	
	//Inicialização da fontes
	io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\Arial.ttf", 14.0f, NULL, io.Fonts->GetGlyphRangesJapanese());



	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);
	auto x = float(screen_rect.right - WINDOW_WIDTH) / 2.f;
	auto y = float(screen_rect.bottom - WINDOW_HEIGHT) / 2.f;

	
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));


	logued = API::AutoLogin();


	while (msg.message != WM_QUIT)
	{


		if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		ImGui_ImplDX9_NewFrame();
		ImGui_ImplWin32_NewFrame();
		
		ImGui::NewFrame();
	
			ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiCond_Once);
			ImGui::SetNextWindowSize(ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT));
			ImGui::SetNextWindowBgAlpha(0.0f);

			
			if (!logued) {

				
				ImGui::Begin("                                    Revolution Cheats | Login", &loader_active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
				{
					for (int i = 0; i < 2; i++) {
						ImGui::NewLine();
					}
					ImGui::SameLine(0, 35);
					ImGui::Spacing();
					ImGui::SameLine(0, 35);
					ImGui::Image((void*)logo_img, ImVec2(250, 90));
					ImGui::SetCursorPosX(90);
					ImGui::Text("Username");				
					ImGui::NewLine();
					ImGui::SameLine(0, 65);
					ImGui::Spacing();
					ImGui::SameLine(0, 15);
					ImGui::SetNextItemWidth(225);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));
					ImGui::InputText("", user_name , IM_ARRAYSIZE(user_name));
					ImGui::PopStyleColor(1);
					ImGui::SetCursorPosX(90);
					ImGui::Text("Password");
					ImGui::NewLine();
					ImGui::SameLine(0, 65);
					ImGui::Spacing();
					ImGui::SameLine(0, 15);
					ImGui::SetNextItemWidth(225);
					ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.f, 0.f, 0.f, 1.f));
					ImGui::InputText(" ", pass_word, IM_ARRAYSIZE(pass_word), ImGuiInputTextFlags_Password);
					ImGui::PopStyleColor(1);
					ImGui::NewLine();
					for (int i = 0; i < 1; i++) {
						ImGui::NewLine();
						ImGui::SameLine(0, 68);
					}
					ImGui::Spacing();
					ImGui::SameLine(0, 68);
					if (ImGui::Button("Login", ImVec2(120, 40))) {
						if (std::strlen(user_name) == 0) {
							MessageBoxA(NULL, "Please enter the username!", titles.c_str(), MB_SETFOREGROUND);
						}
						else if (std::strlen(pass_word) == 0) {
							MessageBoxA(NULL, "Please enter the password!", titles.c_str(), MB_SETFOREGROUND);
						}
						else {
							
								API::SaveInfo(user_name, pass_word);
								MessageBoxA(NULL, ("Welcome " + user).c_str(), titles.c_str(), NULL);
								logued = true;
					
						}	
					}
					ImGui::End();
				}
			}
			else {
			
				ImGui::SetNextWindowSize(ImVec2(500, 400));
				ImGui::Begin("                                                Revolution Cheats | Logued", &loader_active, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
				{
					ImGui::SetCursorPos(ImVec2(35, 360));
					ImGui::BeginChild("id_boxRight", ImVec2());
					ImGui::Text("teste");
					ImGui::EndChild();
					
						ImGui::SetCursorPos(ImVec2(35, 360));
						Render_Profile((void*)NoUser, 20, ImColor(196, 196, 196), 40);
						ImGui::SetCursorPos(ImVec2(70, 345));
						ImGui::Text((user).c_str());
						ImGui::SetCursorPos(ImVec2(71, 365));
						ImGui::Text(("Till: " + expiration).c_str());

						ImGui::SetCursorPos(ImVec2(240, 340));
						if (ImGui::Button("Start", ImVec2(145, 45))) {
							
						}
				}
				ImGui::End();
			}
			
		ImGui::EndFrame();
		

	

		g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		if (g_pd3dDevice->BeginScene() >= 0)
		{
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
			g_pd3dDevice->EndScene();
		}

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}

		HRESULT result = g_pd3dDevice->Present(NULL, NULL, NULL, NULL);

		if (result == D3DERR_DEVICELOST && g_pd3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET) {
			ResetDevice();
		}
		if (!loader_active) {
			msg.message = WM_QUIT;
		}
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	//CleanupDeviceD3D();
	//DestroyWindow(main_hwnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);

	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	switch (msg)
	{
	case WM_SIZE:
		if (g_pd3dDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			g_d3dpp.BackBufferWidth = LOWORD(lParam);
			g_d3dpp.BackBufferHeight = HIWORD(lParam);
			//ResetDevice();
		}
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}