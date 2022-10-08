#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include "abcgOpenGL.hpp"

// DUVIDA:
// Em comparação com o projeto firstapp, desta vez não substituímos o método onPaint. 
// Podemos fazer isso pois todo o conteúdo da janela será 
// composto por controles de UI desenhados em onPaintUI.

class Window : public abcg::OpenGLWindow {
protected:

  void onCreate() override;
  void onPaintUI() override;

private:
  static int const m_N{3}; // Board size is m_N x m_N

  enum class GameState { Play, Draw, WinX, WinO };
  GameState m_gameState;

  bool m_XsTurn{true};
  std::array<char, m_N * m_N> m_board{}; // '\0', 'X' or 'O'

  ImFont *m_font{};

  void checkEndCondition();
  void restartGame();
};

#endif