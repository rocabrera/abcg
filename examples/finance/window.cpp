#include "window.hpp"
#include "core.h"
#include "enumerate.hpp"
#include "imgui.h"

using namespace std;


void Window::onCreate() {
  // Load font with bigger size for the X's and O's
  auto const filename{abcg::Application::getAssetsPath() +
                      "MontereyFLF.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 72.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError{"Cannot load font file"};
  }
}

void create_space(){
    ImGui::Dummy(ImVec2(0.0f, 10.0f));
}

void print_text_introduction(float appWindowWidth, ImFont* m_font){
    ImGui::PushFont(m_font);
    string text = "Finance Organizer";
    ImGui::SetCursorPosX((appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
    ImGui::Text("%s", text.c_str());
    ImGui::PopFont();
    create_space();
    text = "Welcome to the finance organizer program. Just write something to add in one of the available categories!";
    ImGui::SetCursorPosX((appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
    ImGui::Text("%s", text.c_str());
}

size_t create_categorie_selector(vector<string> comboItems, float width_space){
    static size_t currentIndex{};
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width_space) * 0.5;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    
    ImGui::PushItemWidth(width_space);
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
    ImGui::PopItemWidth();
  
    return currentIndex;
}

void create_categories_holders(vector<string> categories, map<string, vector<string>> categories_mapper, float width_categorie_holders){

    // Create List box Headers
    ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 255, 255));
    for (auto const &&[categorie_index, categorie] : iter::enumerate(categories)){
        vector<string> elements = categories_mapper[categorie];
        ImGui::SetCursorPosX((width_categorie_holders*(categorie_index+1) 
                              + width_categorie_holders*categorie_index 
                              - ImGui::CalcTextSize(categorie.c_str()).x) / 2);
        ImGui::Text("%s: %zu", categorie.c_str(), elements.size());
        ImGui::SameLine();
    }
    ImGui::PopStyleColor();

    ImGui::Dummy(ImVec2(0.0f, 2.0f));
    ImGui::NewLine();

    // Create List box Holders
    for (auto const &&[categorie_index, categorie] : iter::enumerate(categories)){
      vector<string> elements = categories_mapper[categorie];
      ImGui::PushItemWidth(width_categorie_holders);
      if (ImGui::BeginListBox(fmt::format("##{}_listbox", categorie_index).c_str())){     
            for (auto const &&[element_index, element] : iter::enumerate(elements)){
                ImGui::Selectable(element.c_str());
            }
            ImGui::EndListBox();
      }
      ImGui::SameLine();
      ImGui::PopItemWidth();
    }
}

void Window::onPaintUI() {

    auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
    auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    float width_categorie_holders = (appWindowWidth)/categories.size();
    float width_selector = appWindowWidth*0.52;

    auto const flags{ImGuiWindowFlags_NoTitleBar | 
                     ImGuiWindowFlags_NoResize  |
                     ImGuiWindowFlags_NoCollapse};


    ImGui::Begin("Finance", nullptr, flags);
    // Create Introduction Text
    print_text_introduction(appWindowWidth,m_font);
    create_space();

    // Create Input Selector: Duvida - Gostaria de colocar isso em uma função!
    float avail = ImGui::GetContentRegionAvail().x;
    float off = (avail - width_selector) * 0.5;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
    ImGui::PushItemWidth(width_selector);
    ImGui::InputText("##inputtext", input_text, IM_ARRAYSIZE(input_text));
    ImGui::PopItemWidth();
    create_space();

    // Create Categorie Selector
    size_t icategorie = create_categorie_selector(categories, width_selector);
    create_space();

    // Create Buttons: DUVIDA - Gostaria de colocar isso em uma função!
    available_X = ImGui::GetContentRegionAvail().x;
    button_offset = (available_X - appWindowWidth*button_width_pct) * 0.325;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + button_offset);
    
    if (ImGui::Button("Enter", ImVec2(appWindowWidth*button_width_pct, button_height))){
      if (strlen(input_text) != 0){
        categories_mapper[categories.at(icategorie)].push_back(input_text);
        input_text[0] = '\0';
      }
    }
    ImGui::SameLine();
    if (ImGui::Button("Erase", ImVec2(appWindowWidth*button_width_pct, button_height))){
      input_text[0] = '\0';
    }

    create_space();
    create_space();
    create_space();

    // Create List box Category Holders
    create_categories_holders(categories, categories_mapper, width_categorie_holders);
    create_space();

    ImGui::End();
}