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

  float button_width_pct{0.35};
  float button_height{50};
  char input_text[128] = "";

  vector<string> categories{"Investiments", "Income", "Outcome"};

  map<string, vector<string>> categories_mapper {
    {"Investiments", {"test1", "batata1"}},
    {"Income", {"test2"}},
    {"Outcome", {"test3", "limao3", "pato3"}}
  };

};

#endif