#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <cstddef>
#include <random>

#include "abcgOpenGL.hpp"
using namespace std;

class Window : public abcg::OpenGLWindow {
protected:
  void onEvent(SDL_Event const &event) override;
  void onCreate() override;
  void onPaint() override;
  void onPaintUI() override;
  void onResize(glm::ivec2 const &size) override;
  void onDestroy() override;

private:
  
  // Variable used to set when to draw in the window.
  bool drawing{false};

  // Spinning
  bool is_spinning{};

  // Variables used to get mouse position.
  float x_position{};
  float y_position{};

  // Variable used to set pencil size
  float pencil_scale{0.2};

  // Variable used to set angular shift in a vertice
  float angular_shift{0.0};

  // Variable used to set how many sides the polygon has
  char polygon_sides[128] = "3";



  //
  size_t idrawtype{1};

  // DRA
  vector<string> DRAW_TYPES{"GL_TRIANGLES", 
                            "GL_TRIANGLE_FAN", 
                            "GL_TRIANGLE_STRIP"};
  
  glm::ivec2 m_viewportSize{};
  glm::vec3 m_clearColor{0.906f, 0.910f, 0.918f};
  GLuint m_VAO{};
  GLuint m_VBOPositions{};
  GLuint m_VBOColors{};
  GLuint m_program{};

  abcg::Timer m_timer;
  int m_delay{1000};

  void setupModel(int sides);
};

#endif
