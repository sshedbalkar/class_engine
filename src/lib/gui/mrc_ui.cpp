/**
 * Copyright (c) Santosh Shedbalkar
 * Year: 2024 - 2024
 * All rights reserved
 *
 * File: mrc_ui.cpp
 */

#include "mrc_ui.h"

extern "C" {
#include <SDL2/SDL.h>
#include "mrc_console.h"
#include "mrc_memory.h"
#include "mrc_events.h"
#include "mrc_list_core_events.h"
#include "mrc_data_container.h"
#include "mrc_graphics.h"
}

#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"

#define IMGUI_USER_CONFIG "mrc_imconfig.h"

#if !SDL_VERSION_ATLEAST(2, 0, 17)
#error This backend requires SDL 2.0.17+ because of SDL_RenderGeometry() function
#endif

static mrc_obj_static_t __base = {MRC_GRAPHICS_UI, (mrc_fn_vp_v_t)&mrc_ui_ctor,
                                  (mrc_fn_i_vp_t)&mrc_ui_dtor};

static mrc_ui_t* __ui;
static ImVec4 __clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
static SDL_Event* __sdl_evt;
static mrc_graphics_t* __graphics;

EXTERNC void mrc_ui_init(mrc_ui_t* obj) { (void)obj; }
EXTERNC void mrc_ui_test1(mrc_ui_t* obj) {
    (void)obj;
    mrc_print("mrc_ui_test1");
}

EXTERNC mrc_obj_static_t* mrc_ui_static_init() {
    ImGui::SetAllocatorFunctions(&mrc_alloc_c, &mrc_free_c, NULL);
    return &__base;
}

EXTERNC int mrc_ui_static_term() { return 0; }

static mrc_ui_t* __create() {
    mrc_ui_t* app = (mrc_ui_t*)mrc_alloc(sizeof(mrc_ui_t));
    return app;
}

static void __on_sdl_event() {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application, or clear/overwrite your copy of the
    // keyboard data. Generally you may always pass all inputs to dear imgui,
    // and hide them from your application based on those two flags.
    __sdl_evt = (SDL_Event*)mrc_data_container_get(MRC_H_SDL_EVT_OBJ);
    ImGui_ImplSDL2_ProcessEvent(__sdl_evt);
    if (__sdl_evt->type == SDL_WINDOWEVENT &&
        __sdl_evt->window.event == SDL_WINDOWEVENT_CLOSE &&
        __sdl_evt->window.windowID == SDL_GetWindowID(__graphics->window)) {
        mrc_print("Quitttt2\n");
        mrc_events_trigger_event(MRC_EVT_QUIT);
    }
}

static void __on_enter_frame() {
    ImGuiIO& io = ImGui::GetIO();
    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer2_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in
    // ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear
    // ImGui!).
    bool show_demo_window = (bool)__ui->show_demo_window;
    bool show_another_window = (bool)__ui->show_another_window;
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair
    // to create a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");    // Create a window called "Hello,
                                          // world!" and append into it.

        ImGui::Text(
            "This is some useful text.");    // Display some text (you can use a
                                             // format strings too)
        ImGui::Checkbox("Demo Window",
                        &show_demo_window);    // Edit bools storing our
                                               // window open/close state

        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat(
            "float", &f, 0.0f,
            1.0f);    // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3(
            "clear color",
            (float*)&__clear_color);    // Edit 3 floats representing a color

        if (ImGui::Button(
                "Button"))    // Buttons return true when clicked (most widgets
                              // return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                    1000.0f / io.Framerate, io.Framerate);
        ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
        ImGui::Begin("Another Window",
                     &show_another_window);    // Pass a pointer to our bool
                                               // variable (the window will have
                                               // a closing button that will
                                               // clear the bool when clicked)
        ImGui::Text("Hello from another window!");
        if (ImGui::Button("Close Me")) show_another_window = false;
        ImGui::End();
    }
    if (show_demo_window)
        __ui->show_demo_window = TRUE;
    else
        __ui->show_demo_window = FALSE;
    if (show_another_window)
        __ui->show_another_window = TRUE;
    else
        __ui->show_another_window = FALSE;

    // Rendering
    ImGui::Render();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_RenderSetScale(__graphics->renderer, io.DisplayFramebufferScale.x,
                       io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(__graphics->renderer, (Uint8)(__clear_color.x * 255),
                           (Uint8)(__clear_color.y * 255),
                           (Uint8)(__clear_color.z * 255),
                           (Uint8)(__clear_color.w * 255));
    SDL_RenderClear(__graphics->renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(__graphics->renderer);
}

EXTERNC mrc_ui_t* mrc_ui_ctor2() {
    __ui = __create();
    __ui->base = &__base;
    return __ui;
}

EXTERNC mrc_ui_t* mrc_ui_ctor() {
    __ui = __create();
    __ui->base = &__base;

    // Setup Dear ImGui context
    __graphics = (mrc_graphics_t*)mrc_data_container_get(MRC_H_GRAPHICS_OBJ);
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;    // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(__graphics->window, __graphics->renderer);
    ImGui_ImplSDLRenderer2_Init(__graphics->renderer);

    // Fonts
    io.Fonts->AddFontDefault();
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/DroidSans.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/Roboto-Medium.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/Cousine-Regular.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/Karla-Regular.ttf", 14.0f);
    io.Fonts->AddFontFromFileTTF("imgui/misc/fonts/ProggyTiny.ttf", 14.0f);
    ImFont* font = io.Fonts->AddFontFromFileTTF(
        "imgui/misc/fonts/FiraCode-Regular.ttf", 14.0f);
    io.FontDefault = font;
    io.ConfigDockingTransparentPayload = true;
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
    // nullptr, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != nullptr);

    // Our state
    __ui->show_demo_window = TRUE;
    __ui->show_another_window = FALSE;
    //
    mrc_events_reg_callback(MRC_EVT_FRAME_ENTER, &__on_enter_frame);
    mrc_events_reg_callback(MRC_EVT_SDL_EVENT, &__on_sdl_event);
    return __ui;
}

EXTERNC int mrc_ui_dtor2(mrc_ui_t* obj) {
    mrc_free(obj);
    __ui = nullptr;
    return 0;
}

EXTERNC int mrc_ui_dtor(mrc_ui_t* obj) {
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    mrc_free(obj);
    __ui = nullptr;
    return 0;
}