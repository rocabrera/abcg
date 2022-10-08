#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"
#include <string>

using namespace std;

// DUVIDA:
// Em comparação com o projeto firstapp, desta vez não substituímos o método onPaint. 
// Podemos fazer isso pois todo o conteúdo da janela será 
// composto por controles de UI desenhados em onPaintUI.

class Window : public abcg::OpenGLWindow {
protected:
  void onCreate() override;
  // void onPaint() override;
  void onPaintUI() override;

  float button_width_pct{0.25};
  float button_height{50};
  char input_text[128] = "";
  ImFont *m_font{};

  vector<string> categories{"Investiments", "Income", "Outcome"};

  //Duvida: inicializar as chaves do mapa através de categories
  map<string, vector<string>> categories_mapper {
    {"Investiments", {}},
    {"Income", {}},
    {"Outcome", {}}
  };

  float available_X;
  float button_offset;
};

#endif