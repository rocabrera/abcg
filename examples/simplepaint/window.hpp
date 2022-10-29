#ifndef WINDOW_HPP_
#define WINDOW_HPP_

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

  float x_position{};
  float y_position{};
  float pencil_scale{0.2};
  bool drawing{false};
  glm::ivec2 m_viewportSize{};
  glm::vec3 m_clearColor{0.906f, 0.910f, 0.918f};

  GLuint m_VAO{};
  GLuint m_VBOPositions{};
  GLuint m_VBOColors{};
  GLuint m_program{};

  default_random_engine m_randomEngine;

  void setupModel(int sides);
};

#endif
