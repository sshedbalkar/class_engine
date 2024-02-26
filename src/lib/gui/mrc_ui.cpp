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

static SDL_Window* __window;
static SDL_Renderer* __renderer;
static mrc_ui_t* __ui;
static ImVec4 __clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

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

static void __on_enter_frame() {
    // Poll and handle events (inputs, window resize, etc.)
    // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
    // tell if dear imgui wants to use your inputs.
    // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
    // your main application, or clear/overwrite your copy of the mouse data.
    // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
    // data to your main application, or clear/overwrite your copy of the
    // keyboard data. Generally you may always pass all inputs to dear imgui,
    // and hide them from your application based on those two flags.
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        ImGui_ImplSDL2_ProcessEvent(&event);
        if (event.type == SDL_QUIT) mrc_events_trigger_event(MRC_EVT_QUIT);
        if (event.type == SDL_WINDOWEVENT &&
            event.window.event == SDL_WINDOWEVENT_CLOSE &&
            event.window.windowID == SDL_GetWindowID(__window))
            mrc_events_trigger_event(MRC_EVT_QUIT);
    }

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
    SDL_RenderSetScale(__renderer, io.DisplayFramebufferScale.x,
                       io.DisplayFramebufferScale.y);
    SDL_SetRenderDrawColor(__renderer, (Uint8)(__clear_color.x * 255),
                           (Uint8)(__clear_color.y * 255),
                           (Uint8)(__clear_color.z * 255),
                           (Uint8)(__clear_color.w * 255));
    SDL_RenderClear(__renderer);
    ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(__renderer);
}

EXTERNC mrc_ui_t* mrc_ui_ctor2() {
    __ui = __create();
    __ui->base = &__base;
    return __ui;
}

EXTERNC mrc_ui_t* mrc_ui_ctor() {
    __ui = __create();
    __ui->base = &__base;
    //
    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif
    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags =
        (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    __window = SDL_CreateWindow("Dear ImGui SDL2+SDL_Renderer example",
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                1280, 720, window_flags);
    if (__window == nullptr) {
        mrc_print("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return NULL;
    }
    __renderer = SDL_CreateRenderer(
        __window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (__renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }
    SDL_RendererInfo info;
    SDL_GetRendererInfo(__renderer, &info);
    SDL_Log("Current SDL_Renderer: %s", info.name);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard;    // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad;    // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(__window, __renderer);
    ImGui_ImplSDLRenderer2_Init(__renderer);

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
    // ImFont* font =
    // io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f,
    // nullptr, io.Fonts->GetGlyphRangesJapanese()); IM_ASSERT(font != nullptr);

    // Our state
    __ui->show_demo_window = TRUE;
    __ui->show_another_window = FALSE;
    //
    mrc_events_reg_callback(MRC_EVT_FRAME_ENTER, &__on_enter_frame);
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

    SDL_DestroyRenderer(__renderer);
    SDL_DestroyWindow(__window);
    mrc_free(obj);
    __ui = nullptr;
    return 0;
}