//
// Created by faliszewskii on 18.04.24.
//

#include "Gui.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include <glm/gtc/type_ptr.hpp>

Gui::Gui(AppContext &appContext, GLFWwindow *window) : appContext(appContext) {
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCanvasResizeCallback("#canvas");
#endif
    const char* glsl_version = "#version 400";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Load Fonts
    // - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
    // - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
    // - If the file cannot be loaded, the function will return a nullptr. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
    // - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
    // - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
    // - Read 'docs/FONTS.md' for more instructions and details.
    // - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
    // - Our Emscripten build process allows embedding fonts to be accessible at runtime from the "fonts/" folder. See Makefile.emscripten for details.
    //io.Fonts->AddFontDefault();
    //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
    //io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
    //ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());
    //IM_ASSERT(font != nullptr);

//    ImGui_ImplOpenGL3_Init();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void Gui::newFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::render() {
    showSceneWindow();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

Gui::~Gui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::showSceneWindow() {

    showScene();

    ImGui::Begin("Scene Window");

    // Robot

    bool fieldModified = false;
    // User input for free angles.
    ImGui::SeparatorText("Arm angles");
    for(int i = 0; i < appContext.robot->kinematics.armRotationAngles.size(); i++) {
        auto &angle = appContext.robot->kinematics.armRotationAngles[i];
        fieldModified |= ImGui::SliderAngle(std::string(std::to_string(i) + ". arm").c_str(), &angle, 0.01f);
    }
    if(fieldModified) appContext.robot->kinematics.movementState = RobotKinematics::FreeAngles; // Change focus to free angles.
    fieldModified = false;

    // User input for needle position for inverse kinematics.
    fieldModified |= ImGui::DragFloat3("Needle position", glm::value_ptr(appContext.robot->kinematics.needlePosition), 0.002f);
    fieldModified |= ImGui::DragFloat3("Needle orientation", glm::value_ptr(appContext.robot->kinematics.needleOrientation), 0.002f);
    if(fieldModified) {
        appContext.robot->kinematics.needleOrientation = glm::normalize(appContext.robot->kinematics.needleOrientation);
        appContext.robot->kinematics.movementState = RobotKinematics::FreeInverseKinematics;
    }
    fieldModified = false;

    bool animated = appContext.robot->kinematics.movementState == RobotKinematics::AnimatedInverseKinematics;
    fieldModified |= ImGui::Checkbox("Animation", &animated);
    if(fieldModified) appContext.robot->kinematics.movementState = animated? RobotKinematics::AnimatedInverseKinematics: RobotKinematics::FreeAngles;

    ImGui::SameLine();
    const char* items[] = { "Infinity", "Chaotic", "Circle"};
    int &i = reinterpret_cast<int &>(appContext.robot->kinematics.animation);
    ImGui::Combo("##combo", &i, items, IM_ARRAYSIZE(items));

    // Point Light

    ImGui::DragFloat3("Light position", glm::value_ptr(appContext.pointLight.position), 0.02f);

    ImGui::End();
}

void Gui::showScene () const
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    static bool use_work_area = true;
    ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
    ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

    static ImGuiWindowFlags flags =
            ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings
            | ImGuiWindowFlags_NoBringToFrontOnFocus;

    if (!ImGui::Begin("Scene", nullptr, flags))
    {
        // Error
        ImGui::End();
        return;
    }

    ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

    // add rendered texture to ImGUI scene window
    uint64_t textureID = appContext.frameBufferManager->get_texture();
    ImVec2 canvas_sz = ImVec2{ viewportPanelSize.x, viewportPanelSize.y };
    ImGui::Image(reinterpret_cast<void*>(textureID), canvas_sz, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

    ImGui::End();
}
