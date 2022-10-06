#include "window.hpp"
#include "imgui.h"

void Window::onCreate() {
  // Load font with bigger size for the X's and O's
  // auto const filename{abcg::Application::getAssetsPath() +
  //                     "Inconsolata-Medium.ttf"};
  // m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 72.0f);
  // if (m_font == nullptr) {
  //   throw abcg::RuntimeError{"Cannot load font file"};
  // }
}

// void create_space(){
//     ImGui::Dummy(ImVec2(0.0f, 10.0f));
// }

void print_text_introduction(){
    ImGui::Text("Introdução");
    ImGui::Text(R"gl(
Bem vindo ao organizador de finanças pessoais
Basta escrever o nome da sua compra seguido do valor e a categoria referente a compra.
Depois Selecione Enter
)gl");
}


std::size_t create_categorie_selector(std::vector<std::string> comboItems){

    static std::size_t currentIndex{};

    if (ImGui::BeginCombo("", comboItems.at(currentIndex).c_str())) {
      for (auto index{0U}; index < comboItems.size(); ++index) {
        bool const isSelected{currentIndex == index};
        if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
          currentIndex = index;
        if (isSelected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }
  
    return currentIndex;
}

void send_to_category(std::size_t combo_index, char text){
}

void Window::onPaintUI() {


    auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
    auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar  | 
                     ImGuiWindowFlags_NoResize |
                     ImGuiComboFlags_NoPreview | // Duvida: Porque essa flag não funciona
                     ImGuiWindowFlags_NoCollapse};

    ImGui::Begin("Finance", nullptr, flags);
    print_text_introduction();
    // create_space();
    ImGui::InputText("", input_text, IM_ARRAYSIZE(input_text));
    // create_space();
    // Talvez trocar pelo Single Selection do Selection State
    std::size_t icategorie = create_categorie_selector(categories);
    fmt::print("Selected combo box item: {}\n", categories.at(icategorie));
    // create_space();
    if (ImGui::Button("Enter", ImVec2(appWindowWidth*button_width_pct, button_height))){
      // send_to_category(combo_index, input_text)
    }

    ImGui::SameLine();

    if (ImGui::Button("Erase", ImVec2(appWindowWidth*button_width_pct, button_height))){
      // Clear text camp
      // input_text = ""

      // Unselect combo box
      // ???
    }
    // create_space();

    // const char* items[] = { "Apple", "Banana", "Cherry"};
    // static int item_current = 1;

    // Ref: https://github.com/ocornut/imgui/issues/3531
    for (auto const &categorie : categories) {
      // ImGui::ListBox("", &item_current, items, IM_ARRAYSIZE(items), 4);
      // Duvida: Porque os list box não ficam side by side?
      ImGui::BeginListBox("test");
      ImGui::EndListBox();
      ImGui::SameLine();
      fmt::print("Categorie: {}\n", categorie);
    }
    ImGui::End();
}