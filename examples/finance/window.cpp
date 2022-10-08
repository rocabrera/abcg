#include "window.hpp"
#include "enumerate.hpp"
#include "imgui.h"

using namespace std;


void Window::onCreate() {
  // Load font with bigger size for the X's and O's
  // auto const filename{abcg::Application::getAssetsPath() +
  //                     "Inconsolata-Medium.ttf"};
  // m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 72.0f);
  // if (m_font == nullptr) {
  //   throw abcg::RuntimeError{"Cannot load font file"};
  // }
}

void create_space(){
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
}

void print_text_introduction(){
    ImGui::Text("Introdução");
    ImGui::Text(R"gl(
Bem vindo ao organizador de finanças pessoais
Basta escrever o nome da sua compra seguido do valor e a categoria referente a compra.
Depois Selecione Enter
)gl");
}


size_t create_categorie_selector(vector<string> comboItems){

    static size_t currentIndex{};

    // ImGui::PushItemWidth(200);
    if (ImGui::BeginCombo("##categories", comboItems.at(currentIndex).c_str())) {
      for (auto index{0U}; index < comboItems.size(); ++index) {
        bool const isSelected{currentIndex == index};
        if (ImGui::Selectable(comboItems.at(index).c_str(), isSelected))
          currentIndex = index;
        if (isSelected)
          ImGui::SetItemDefaultFocus();
      }
      ImGui::EndCombo();
    }
    // ImGui::PopItemWidth();
  
    return currentIndex;
}


void create_categories_holders(vector<string> categories, map<string, vector<string>> categories_mapper){
    for (auto const &&[categorie_index, categorie] : iter::enumerate(categories)) {
      vector<string> elements = categories_mapper[categorie];

      if (ImGui::BeginListBox(fmt::format("##{}_listbox", categorie_index).c_str())){     
            for (auto const &&[element_index, element] : iter::enumerate(elements)){
                ImGui::Selectable(element.c_str());
            }

            ImGui::EndListBox();
      }
      ImGui::SameLine();
    }
}

void Window::onPaintUI() {


    auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
    auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar  | 
                     ImGuiWindowFlags_NoResize |
                     ImGuiComboFlags_NoPreview |
                     ImGuiWindowFlags_NoCollapse};

    ImGui::Begin("Finance", nullptr, flags);

    // Create Introduction Text
    print_text_introduction();
    create_space();

    // Create Input Selector
    ImGui::InputText("##inputtext", input_text, IM_ARRAYSIZE(input_text));
    create_space();

    // Create Categorie Selector
    size_t icategorie = create_categorie_selector(categories);
    create_space();

    if (ImGui::Button("Enter", ImVec2(appWindowWidth*button_width_pct, button_height))){

      // fmt::print("Selected combo box item: {}\n", categories.at(icategorie));

      categories_mapper[categories.at(icategorie)].push_back(input_text);
      
      // for (auto const &element : categories_mapper[categories.at(icategorie)]) {
      //   fmt::print("{}\n", element.c_str());
      // }
    }
    ImGui::SameLine();
    if (ImGui::Button("Erase", ImVec2(appWindowWidth*button_width_pct, button_height))){
    
    }
    create_space();

    create_categories_holders(categories, categories_mapper);
    create_space();

    ImGui::End();
}