#include "gui.h"
#include "overlay.h"
#include "settings.h"
#include "../reading/reader.h"
#include "../globals/entity.h"
#include "menu.h"
#include "fonts.h"
#include "image.h"
#include "../features/triggerbot.h"
#include "config.h"
#include "../features/radar.h"

#include <Windows.h>
#include <winuser.h>
#include <thread>
#include <iostream>
#include <string>
#include "../security/skCrypter.h"

#include "../../external/imgui/imgui.h"
#include "../../external/imgui/imgui_impl_dx11.h"
#include "../../external/imgui/imgui_impl_win32.h"
#include "../../external/imgui/imgui_internal.h"

#include "../../external/imgui/D3DX11.h"
#include "../../external/imgui/d3dx11tex.h"
#include <d3d11.h>
#include "input.h"

#pragma comment(lib, "d3d11.lib")

void ToggleTransparency(bool enable) {
    LONG_PTR style = GetWindowLongPtr(overlay::hwnd, GWL_EXSTYLE);
    if (enable) {
        style |= WS_EX_TRANSPARENT;
    }
    else {
        style &= ~WS_EX_TRANSPARENT;
    }
    SetWindowLongPtr(overlay::hwnd, GWL_EXSTYLE, style);

    // To make the changes take effect immediately
    SetWindowPos(overlay::hwnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
}


void gui::MainLoop(Overlay& overlay)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    DWORD picker_flags = ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar | ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaPreview;

    ImFontConfig cfg;
    //cfg.FontBuilderFlags = ImGuiFreeTypeBuilderFlags_ForceAutoHint | ImGuiFreeTypeBuilderFlags_LightHinting | ImGuiFreeTypeBuilderFlags_LoadColor;
    static const ImWchar weapon_ranges[] = { 0xE000, 0xE02A, 0 }; // Adjust range based on your icon set

    font::inter_default = io.Fonts->AddFontFromMemoryTTF(inter_medium, sizeof(inter_medium), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::inter_bold = io.Fonts->AddFontFromMemoryTTF(inter_bold, sizeof(inter_bold), 17.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::outlined_font = io.Fonts->AddFontFromMemoryTTF(outlined_letters, sizeof(outlined_letters), 25.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::icon = io.Fonts->AddFontFromMemoryTTF(icon_font, sizeof(icon_font), 15.f, &cfg, io.Fonts->GetGlyphRangesCyrillic());
    font::weapons = io.Fonts->AddFontFromMemoryTTF(weapon_font, sizeof(weapon_font), 13.5f, &cfg, weapon_ranges);

    if (!font::inter_default || !font::inter_bold || !font::icon || !font::weapons || !font::outlined_font) {
        std::cerr << skCrypt("Failed to load one or more fonts!") << std::endl;
        return;
    }

    ImGui::StyleColorsDark();

    ImGui_ImplDX11_Init(overlay::d3d11Device, overlay::d3d11DevCon);
    ImGui_ImplWin32_Init(overlay::hwnd);

    D3DX11_IMAGE_LOAD_INFO info; ID3DX11ThreadPump* pump{ nullptr };
    if (pic::widget == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, widget_icon, sizeof(widget_icon), &info, pump, &pic::widget, 0);

    if (pic::aimbot == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, aimbot, sizeof(aimbot), &info, pump, &pic::aimbot, 0);
    if (pic::visuals == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, visuals, sizeof(visuals), &info, pump, &pic::visuals, 0);
    if (pic::skins == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, skins, sizeof(skins), &info, pump, &pic::skins, 0);
    if (pic::settings == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, settingspic, sizeof(settingspic), &info, pump, &pic::settings, 0);

    if (pic::weapon_ak47 == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, weapon_ak47, sizeof(weapon_ak47), &info, pump, &pic::weapon_ak47, 0);
    if (pic::weapon_m4a1 == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, weapon_m4a1, sizeof(weapon_m4a1), &info, pump, &pic::weapon_m4a1, 0);
    if (pic::weapon_galil == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, weapon_galil, sizeof(weapon_galil), &info, pump, &pic::weapon_galil, 0);

   // if (pic::user_circle == nullptr) D3DX11CreateShaderResourceViewFromMemory(overlay::d3d11Device, user_circle, sizeof(user_circle), &info, pump, &pic::user_circle, 0);

    config::refresh();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    MSG msg;
    ImVec4 clear_clr = { 0, 0, 0, 0 };
   
    overlay.ToggleTransparency(false);

    while (gui::open)
    {

        int currentFPS = static_cast<int>(ImGui::GetIO().Framerate);

        static std::string fps = std::to_string(currentFPS);
        static const char* fps_cstr = fps.c_str();

        static int F = 0;
        if (F > 200)
        {
            fps = std::to_string(currentFPS);
            fps_cstr = fps.c_str();
            F = 0;
        }
        else
        {
            F++;
        }

        if (currentFPS > settings::MaxRenderFPS)
        {
            int FrameWait = static_cast<int>(1000000.0f / settings::MaxRenderFPS);
            std::this_thread::sleep_for(std::chrono::microseconds(FrameWait));
        }

        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // translate keystroke messages into the right format
            TranslateMessage(&msg);

            // send the message to the WindowProc function
            DispatchMessage(&msg);

            // check to see if it's time to quit
            if (msg.message == WM_QUIT)
            {
                gui::open = false;
            }
        }

        if (GetAsyncKeyState(VK_END) && 1)
            gui::open = false;

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();

        ImGui::NewFrame();
        //--------------------------------------------------------------------------------------------------------------//

        gui::drawList = ImGui::GetBackgroundDrawList();
        gui::drawListForeground = ImGui::GetForegroundDrawList();

        ImGuiStyle* style = &ImGui::GetStyle();

        style->WindowPadding = ImVec2(0, 0), style->WindowBorderSize = 0;
        style->ItemSpacing = ImVec2(12, 12); //Item Padding
        style->ScrollbarSize = 7.f;

        if (GetAsyncKeyState(VK_INSERT) & 1)
        {
            gui::bMenu = !gui::bMenu;
            if (gui::bMenu)
            {
                overlay.ToggleTransparency(false);
            }
            else
            {
                overlay.ToggleTransparency(true);
            }
        }

        if (gui::open)
        {
            if (gui::bMenu) {
                static float color[4] = { 0.f, 1.f, 1.f, 1.f };
                c::accent = { color[0], color[1], color[2], 1.f };

                ImGui::SetNextWindowSize(ImVec2(775, 570)); //Window Size

                //Main Menu
                ImGui::Begin(skCrypt("Goat"), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoBringToFrontOnFocus);
                {
                    const ImVec2& pos = ImGui::GetWindowPos();
                    const ImVec2& spacing = style->ItemSpacing;
                    const ImVec2& region = ImGui::GetContentRegionMax();

                    gui::drawList->AddRectFilled(pos, { pos + region }, ImGui::GetColorU32(c::bg::background), c::bg::rounding);

                    gui::drawList->AddRectFilled(pos + spacing, pos + ImVec2(155, 90), ImGui::GetColorU32(c::child::background), c::child::rounding);
                    gui::drawList->AddRect(pos + spacing, pos + ImVec2(155, 90), ImGui::GetColorU32(c::child::outline), c::child::rounding);

                    gui::drawList->AddRectFilled(pos + ImVec2(0, 90) + spacing, pos + ImVec2(155, region.y - spacing.y), ImGui::GetColorU32(c::child::background), c::child::rounding);
                    gui::drawList->AddRect(pos + ImVec2(0, 90) + spacing, pos + ImVec2(155, region.y - spacing.y), ImGui::GetColorU32(c::child::outline), c::child::rounding);

                    gui::drawList->AddRectFilled(pos + ImVec2(155, 0) + spacing, pos + ImVec2(region.x - 90 - spacing.x, 90), ImGui::GetColorU32(c::child::background), c::child::rounding);
                    gui::drawList->AddRect(pos + ImVec2(155, 0) + spacing, pos + ImVec2(region.x - 90 - spacing.x, 90), ImGui::GetColorU32(c::child::outline), c::child::rounding);

                    gui::drawList->AddRectFilled(pos + ImVec2(region.x - 90 - spacing.x, 0) + spacing, pos + ImVec2(region.x - spacing.x, 90), ImGui::GetColorU32(c::child::background), c::child::rounding);
                    gui::drawList->AddRect(pos + ImVec2(region.x - 90 - spacing.x, 0) + spacing, pos + ImVec2(region.x - spacing.x, 90), ImGui::GetColorU32(c::child::outline), c::child::rounding);

                    // gui::drawList->AddImageRounded(pic::user_circle, pos + ImVec2(region.x - 90 - spacing.x, 0) + spacing + ImVec2(13, 13), pos + ImVec2(region.x - spacing.x, 90) - ImVec2(13, 13), ImVec2(0, 0), ImVec2(1, 1), ImGui::GetColorU32(c::text::text_active), 30.f);

                     //gui::drawList->AddCircle(pos + ImVec2(region.x - (90 + spacing.x) / 2, (90 + spacing.x) / 2), 28.f, ImGui::GetColorU32(c::accent), 100.f, 2.f);

                    gui::drawList->AddText(font::inter_bold, 17, pos + (ImVec2(155, 90) + spacing - ImGui::CalcTextSize("PWS")) / 2, ImGui::GetColorU32(c::text::text_active), skCrypt("PWS"));

                    static int tabs = 0, sub_tabs = 0;

                    ImGui::SetCursorPos(ImVec2(spacing.x * 2, 90 + spacing.y * 2));
                    ImGui::BeginGroup();
                    {
                        if (ImGui::Tabs(0 == tabs, pic::visuals, skCrypt("Visuals"), ImVec2(155 - spacing.x * 3, 35), NULL)) tabs = 0;

                        if (ImGui::Tabs(1 == tabs, pic::aimbot, skCrypt("Aimbot"), ImVec2(155 - spacing.x * 3, 35), NULL)) tabs = 1;

                        if (ImGui::Tabs(2 == tabs, pic::skins, skCrypt("Skins"), ImVec2(155 - spacing.x * 3, 35), NULL)) tabs = 2;

                        if (ImGui::Tabs(3 == tabs, pic::settings, skCrypt("Misc"), ImVec2(155 - spacing.x * 3, 35), NULL)) tabs = 3;

                        if (ImGui::Tabs(4 == tabs, pic::settings, skCrypt("Settings"), ImVec2(155 - spacing.x * 3, 35), NULL)) tabs = 4;
                    }
                    ImGui::EndGroup();

                    ImGui::SetCursorPos(ImVec2(155 + (spacing.x * 2) + (48 / 2), ((48 + spacing.y) / 2) - 1));
                    ImGui::BeginGroup();
                    {
                        if (ImGui::SubTab(0 == sub_tabs, pic::weapon_ak47, ImVec2(48, 48))) sub_tabs = 0;
                        ImGui::SameLine(0, 24);
                        if (ImGui::SubTab(1 == sub_tabs, pic::weapon_m4a1, ImVec2(48, 48))) sub_tabs = 1;
                        ImGui::SameLine(0, 24);
                        if (ImGui::SubTab(2 == sub_tabs, pic::weapon_galil, ImVec2(48, 48))) sub_tabs = 2;
                    }
                    ImGui::EndGroup();

                    static float tab_alpha = 0.f; /* */ static float tab_add; /* */ static int active_tab = 0;

                    tab_alpha = ImClamp(tab_alpha + (4.f * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);
                    tab_add = ImClamp(tab_add + ((350.f) * ImGui::GetIO().DeltaTime * (tabs == active_tab ? 1.f : -1.f)), 0.f, 1.f);

                    if (tab_alpha == 0.f && tab_add == 0.f) active_tab = tabs;

                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, tab_alpha * style->Alpha);

                    ImGui::SetCursorPos(ImVec2(155, 90) + spacing);

                    //tab 0 = visuals
                    if (active_tab == 0) {

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("Player"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {

                                ImGui::Checkbox(skCrypt("ESP Switch"), &settings::esp::bEspSwitch);

                                ImGui::Checkbox(skCrypt("Box"), &settings::esp::bBox);

                                ImGui::Checkbox(skCrypt("Corner Box"), &settings::esp::bCornerBox);

                                ImGui::Checkbox(skCrypt("Fill Box"), &settings::esp::bFillBox);

                                ImGui::Checkbox(skCrypt("Skeleton"), &settings::esp::bSkeleton);

                                ImGui::Checkbox(skCrypt("Snap Lines"), &settings::esp::bSnapLines);

                                ImGui::Checkbox(skCrypt("Names"), &settings::esp::bNames);

                                ImGui::Checkbox(skCrypt("Weapons"), &settings::esp::bWeapon);

                                //ImGui::Checkbox("Health", &settings::esp::bHealth);

                                ImGui::Checkbox(skCrypt("Ammo"), &settings::esp::bAmmo);



                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);

                            }
                            ImGui::EndChild();

                            //ImGui::BeginChild("Glow", ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            //{

                             //   static int select = 0;
                             //   const char* items[10]{ "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten" };
                             //   ImGui::Combo("Combo", &select, items, IM_ARRAYSIZE(items), 10);
                            //
                              //  static bool multi_num[5] = { false, true, true, true, false };
                               // const char* multi_items[5] = { "One", "Two", "Three", "Four", "Five" };
                              //  ImGui::MultiCombo("MultiCombo", multi_num, multi_items, 5);

                            //}
                           // ImGui::EndChild();
                        }
                        ImGui::EndGroup();

                        //ImGui::SameLine();

                        /*ImGui::BeginGroup();
                        {
                            ImGui::BeginChild("World", ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {

                                static char input[64] = { "" };
                                ImGui::InputTextEx("TextField", "Enter your text here", input, 64, ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40), NULL);

                                static int number = 0;
                                if (ImGui::Button("Button", ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {

                                    if (number >= 4) number = 1; else number++;


                                }
                            }
                            ImGui::EndChild();

                            ImGui::BeginChild("Wallhack", ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {

                                static int key, m;
                                ImGui::Keybind("Keybind", &key, &m);

                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup(); */
                    }

                    //aimbot
                    if (active_tab == 1) {
                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("Aimbot"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                ImGui::Checkbox(skCrypt("Aimbot Switch"), &settings::aimbot::bAimbotSwitch);
                                ImGui::Checkbox(skCrypt("Aimbot"), &settings::aimbot::bAimbot);
                                static int m; //1 == hold, 2 == toggle, 3 == always
                                static int k;
                                ImGui::Keybind(skCrypt("Hotkey:"), &k, &m);

                                auto p = asciiToVK.find(k);
                                if (p != asciiToVK.end())
                                    settings::aimbot::aim_key = (int)p->second; // Return the corresponding VK

                                ImGui::Checkbox(skCrypt("Fov"), &settings::aimbot::bFov);
                                ImGui::SliderInt(skCrypt("Fov Size"), &settings::aimbot::fovSize, 10, 300);
                                ImGui::ColorEdit4(skCrypt("FOV Color"), settings::aimbot::fov_color, picker_flags);
                                ImGui::SliderInt(skCrypt("Smoothing"), &settings::aimbot::smoothing, 0, 10);

                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);
                            }
                            ImGui::EndChild();

                            ImGui::BeginChild(skCrypt("Triggerbot"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                static int m; //1 == hold, 2 == toggle, 3 == always
                                static int k;
                                ImGui::Checkbox(skCrypt("Triggerbot"), &settings::triggerbot::bTrigger);
                                ImGui::Keybind(skCrypt("Hotkey:"), &k, &m);
                                ImGui::SliderInt(skCrypt("Shot Delay"), &triggerbot::TriggerDelay, 0, 500);
                                ImGui::SliderInt(skCrypt("Shot Duration (rifles)"), &triggerbot::ShotDuration, 10, 500);

                                auto p = asciiToVK.find(k);
                                if (p != asciiToVK.end())
                                    settings::triggerbot::trigger_key = (int)p->second; // Return the corresponding VK

                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup();

                        ImGui::SameLine();

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("Recoil Control"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                ImGui::Checkbox(skCrypt("RCS"), &settings::rcs::bRcs);
                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup();

                    }

                    //misc
                    if (active_tab == 3) {

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("Hit Sfx"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                const char* items[3]{ ("None", "Neverlose", "Gamesense") };
                                ImGui::Combo(("Hitsound"), &settings::misc::hitsound, items, 3);

                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);

                            }
                            ImGui::EndChild();

                            ImGui::BeginChild(skCrypt("Radar"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                ImGui::Checkbox(skCrypt("Custom Radar"), &settings::misc::bRadar);
                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup();

                    }

                    //settings
                    if (active_tab == 4) {

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("General"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                ImGui::SliderFloat(skCrypt("FPS"), &settings::MaxRenderFPS, 90.f, 1000.f, skCrypt("%.1fF"));

                                ImGui::Checkbox(skCrypt("Watermark"), &gui::bWatermark);

                                ImGui::ColorEdit4(skCrypt("Menu Theme"), color, picker_flags);

                                if (ImGui::Button(skCrypt("Refresh Cache"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40)))
                                    cache::cacheUpdateNeeded = true;

                                ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 200);

                            }
                            ImGui::EndChild();

                            ImGui::BeginChild(skCrypt("Colors"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                ImGui::ColorEdit4(skCrypt("Box"), settings::esp::box_color, picker_flags);
                                ImGui::ColorEdit4(skCrypt("Corner Box Color"), settings::esp::cornerbox_color, picker_flags);
                                ImGui::ColorEdit4(skCrypt("Snap Lines Color"), settings::esp::snaplines_color, picker_flags);
                                ImGui::ColorEdit4(skCrypt("Skeleton Color"), settings::esp::skeleton_color, picker_flags);
                                ImGui::ColorEdit4(skCrypt("Fill Box Color"), settings::esp::fillbox_color, picker_flags);
                                //ImGui::ColorEdit4("Weapon Color", settings::esp::weapon_color, picker_flags);
                                ImGui::ColorEdit4(skCrypt("Names Color"), settings::esp::name_color, picker_flags);
                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup();

                        ImGui::SameLine();

                        ImGui::BeginGroup();
                        {
                            ImGui::BeginChild(skCrypt("Config"), ImVec2((region.x - (spacing.x * 3 + 155)) / 2, (region.y - (spacing.y * 3 + 90)) / 2.0f));
                            {
                                auto size = config::list.size();
                                for (int i = 0; i < size; i++) {
                                    auto config_name = config::list[i];
                                    bool selected = (i == config::selected_cfg);

                                    if (ImGui::Selectable(config_name.c_str(), &selected))
                                        config::selected_cfg = i;

                                    if (selected)
                                        ImGui::SetItemDefaultFocus();
                                }

                                static char buffer[64]{};

                                ImGui::InputTextEx(skCrypt("Config Name:"), skCrypt("enter name here..."), buffer, sizeof(buffer), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40), NULL);

                                if (ImGui::Button(skCrypt("Load Config"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
                                    if (strlen(buffer) > 1)
                                        config::load(buffer);
                                    else
                                        config::load(config::list[config::selected_cfg]);
                                }

                                if (ImGui::Button(skCrypt("Save Config"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
                                    if (strlen(buffer) > 1)
                                        config::save(buffer);
                                    else
                                        config::save(config::list[config::selected_cfg]);
                                }

                                if (ImGui::Button(skCrypt("Remove Config"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
                                    if (strlen(buffer) > 1)
                                        config::remove(buffer);
                                    else
                                        config::remove(config::list[config::selected_cfg]);
                                }

                                if (ImGui::Button(skCrypt("Refresh Configs"), ImVec2(ImGui::GetContentRegionMax().x - style->WindowPadding.x, 40))) {
                                    config::refresh();
                                }
                            }
                            ImGui::EndChild();
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::PopStyleVar();
                }
                ImGui::End();
            }

            if (gui::bWatermark) {
                static float ibar_size = ImGui::CalcTextSize(skCrypt("PWS")).x + ImGui::CalcTextSize("|").x + ImGui::CalcTextSize(("Merlijn, Jip, David")).x + ImGui::CalcTextSize("|").x + ImGui::CalcTextSize(fps_cstr).x + ImGui::CalcTextSize("|").x + ImGui::CalcTextSize("filler").x + (style->ItemSpacing.x * 8);
                static float position = GetSystemMetrics(SM_CXSCREEN);
                position = ImLerp(position, true ? GetSystemMetrics(SM_CXSCREEN) - (ibar_size + 7) : GetSystemMetrics(SM_CXSCREEN), ImGui::GetIO().DeltaTime * 8.f);

                if (position <= (GetSystemMetrics(SM_CXSCREEN) - 2)) {

                    ImGui::SetNextWindowPos(ImVec2(position, 5));
                    ImGui::SetNextWindowSize(ImVec2(ibar_size, 45));

                    ImGui::Begin(skCrypt("info-bar"), nullptr, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
                    {
                        const ImVec2& pos = ImGui::GetWindowPos(), spacing = style->ItemSpacing, region = ImGui::GetContentRegionMax();

                        ImGui::GetBackgroundDrawList()->AddRectFilled(pos, pos + ImVec2(ibar_size, 45), ImGui::GetColorU32(c::bg::background), c::child::rounding);
                        ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(0, 10), pos + ImVec2(4, 35), ImGui::GetColorU32(c::accent), c::bg::rounding, ImDrawCornerFlags_Right);
                        ImGui::GetBackgroundDrawList()->AddRectFilled(pos + ImVec2(region.x - 4, 10), pos + ImVec2(region.x, 35), ImGui::GetColorU32(c::accent), c::bg::rounding, ImDrawCornerFlags_Left);
                        ImGui::GetBackgroundDrawList()->AddRect(pos, pos + ImVec2(ibar_size, 45), ImGui::GetColorU32(c::child::outline), c::child::rounding);

                        const char* info_set[4] = { skCrypt("PWS"), ("Merlijn, Jip, David"), fps_cstr, "." };
                        static int info_bar_size = 0;

                        ImGui::SetCursorPos(ImVec2(spacing.x, (45 - ImGui::CalcTextSize(("Merlijn, Jip, David™")).y) / 2));
                        ImGui::BeginGroup();
                        {

                            for (int i = 0; i < sizeof(info_set) / sizeof(info_set[0]); i++) {
                                ImGui::TextColored(i < 1 ? ImColor(ImGui::GetColorU32(c::accent)) : ImColor(ImGui::GetColorU32(c::text::text)), info_set[i]);
                                ImGui::SameLine();

                                if (i < 3) {
                                    ImGui::TextColored(ImColor(ImGui::GetColorU32(c::text::text)), "|");
                                    ImGui::SameLine();
                                }
                            }
                        }
                        ImGui::EndGroup();
                    }
                    ImGui::End();
                }
            }

            read.Read(); //Reading and main function loop
        }

        //--------------------------------------------------------------------------------------------------------------//
        ImGui::Render();
        overlay::d3d11DevCon->OMSetRenderTargets(1, &overlay::render_target_view, NULL);
        overlay::d3d11DevCon->ClearRenderTargetView(overlay::render_target_view, (float*)&clear_clr);

        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

        overlay::swap_chain->Present(0, 0);
    }
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
}

