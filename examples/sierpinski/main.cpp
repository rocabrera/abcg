#include "window.hpp"

int main(int argc, char **argv) {
  try {
    abcg::Application app(argc, argv);

    Window window;
    // DUVIDA: Mesmo com o double buffering true ainda funciona
    window.setOpenGLSettings({.samples = 2, .doubleBuffering = true});
    window.setWindowSettings({.width = 600,
                              .height = 600,
                              .showFullscreenButton = false,
                              .title = "Sierpinski Triangle"});

    app.run(window);
  } catch (std::exception const &exception) {
    fmt::print(stderr, "{}\n", exception.what());
    return -1;
  }
  return 0;
}