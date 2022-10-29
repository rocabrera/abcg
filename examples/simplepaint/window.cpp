#include "window.hpp"
#include "imgui.h"

/*
Padrao
*/
void Window::onResize(glm::ivec2 const &size) {
  m_viewportSize = size;

  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

void Window::onDestroy() {
  abcg::glDeleteProgram(m_program);
  abcg::glDeleteBuffers(1, &m_VBOPositions);
  abcg::glDeleteBuffers(1, &m_VBOColors);
  abcg::glDeleteVertexArrays(1, &m_VAO);
}

/*
Inicializa somente quando o programa é criado
- Funciona como um construtor de uma classe.
- Contém a definição de processamento de vértices (vertexShader)
- Contém a definição do processo pós rasterização (fragmentShader)
*/
void Window::onCreate() {
  auto const assetsPath{abcg::Application::getAssetsPath()};

  m_program = abcg::createOpenGLProgram({{.source = assetsPath + "pencil.vert",
                                          .stage = abcg::ShaderStage::Vertex},
                                          {.source = assetsPath + "pencil.frag",
                                          .stage = abcg::ShaderStage::Fragment}});

  abcg::glClearColor(0, 0, 0, 1);
  abcg::glClear(GL_COLOR_BUFFER_BIT);
}

/*
Atualiza a posição do mouse quando clicamos.
*/
void Window::onEvent(SDL_Event const &event) {
  
  if (event.type == SDL_MOUSEBUTTONDOWN)
    drawing = true;
  if (event.type == SDL_MOUSEBUTTONUP)
    drawing = false;
  if ((drawing==true) && (event.type == SDL_MOUSEMOTION)) {
    glm::ivec2 mousePosition;
    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    x_position = mousePosition.x;
    y_position = mousePosition.y;
  }
}

// Responsavel por converter as coordenadas do mouse para dentro do intervalo [-1,1]
float mouse_position_standardize(int x, int max_x) {
  return (2.0*x)/max_x - 1.0;
}

void Window::onPaintUI() {
  abcg::OpenGLWindow::onPaintUI();
  {
    auto const widgetSize{ImVec2(330, 200)};
    auto const window_pos_x = m_viewportSize.x - widgetSize.x - 5;
    auto const window_pos_y = m_viewportSize.y - widgetSize.y - 5;
    ImGui::SetNextWindowPos(ImVec2(window_pos_x, window_pos_y));

    ImGui::SetNextWindowSize(widgetSize);
    auto const windowFlags{ImGuiWindowFlags_NoResize   |
                           ImGuiWindowFlags_NoCollapse |
                           ImGuiWindowFlags_NoTitleBar};

    ImGui::Begin(" ", nullptr, windowFlags);

    // Edit background color
    ImGui::PushItemWidth(210);
    ImGui::ColorEdit3("Pencil Color", &m_clearColor.r);
    ImGui::SliderFloat("Pencil Size", &pencil_scale, 0.0f, 1.0f);
    ImGui::InputText("Polygon Side", input_text, IM_ARRAYSIZE(input_text));
    ImGui::PopItemWidth();


    if (ImGui::Button("Clear window", ImVec2(-1, 30))) {
      abcg::glClear(GL_COLOR_BUFFER_BIT);
    }

    ImGui::End();

  }
}

void Window::onPaint() {

  int sides = atoi(input_text);
  if (drawing==true)
    setupModel(sides);

  abcg::glViewport(0, 0, m_viewportSize.x, m_viewportSize.y);
  abcg::glUseProgram(m_program);

  glm::vec2 const translation{
             mouse_position_standardize(x_position, m_viewportSize.x), 
    (-1.0) * mouse_position_standardize(y_position, m_viewportSize.y)
  };
  auto const translationLocation{abcg::glGetUniformLocation(m_program, "translation")};
  abcg::glUniform2fv(translationLocation, 1, &translation.x);

  auto const scaleLocation{abcg::glGetUniformLocation(m_program, "scale")};
  // Improve better pencil size
  abcg::glUniform1f(scaleLocation, pencil_scale * 0.1);

  // Render
  abcg::glBindVertexArray(m_VAO);
  abcg::glDrawArrays(GL_TRIANGLE_FAN, 0, sides + 2);
  abcg::glBindVertexArray(0);

  abcg::glUseProgram(0);
}

void Window::setupModel(int sides) {
  // Release previous resources, if any
  abcg::glDeleteBuffers(1, &m_VBOPositions);
  abcg::glDeleteBuffers(1, &m_VBOColors);
  abcg::glDeleteVertexArrays(1, &m_VAO);

  // Minimum number of sides is 3
  sides = std::max(3, sides);

  std::vector<glm::vec2> positions;
  std::vector<glm::vec3> colors;

  // Polygon center
  // DUVIDA: Nao entendi esse comando
  positions.emplace_back(0, 0);
  // DUVIDA: Nao entendi esse comando
  colors.push_back(m_clearColor);

  // Border vertices
  auto const step{M_PI * 2 / sides};
  for (auto const angle : iter::range(0.0, M_PI * 2, step)) {
    positions.emplace_back(std::cos(angle), std::sin(angle));
    colors.push_back(m_clearColor);
  }

  // Duplicate second vertex
  positions.push_back(positions.at(1));
  colors.push_back(m_clearColor);

  // Generate VBO of positions
  abcg::glGenBuffers(1, &m_VBOPositions);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositions);
  abcg::glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec2),
                     positions.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Generate VBO of colors
  abcg::glGenBuffers(1, &m_VBOColors);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOColors);
  abcg::glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3),
                     colors.data(), GL_STATIC_DRAW);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Get location of attributes in the program
  auto const positionAttribute{
      abcg::glGetAttribLocation(m_program, "inPosition")};
  auto const colorAttribute{abcg::glGetAttribLocation(m_program, "inColor")};

  // Create VAO
  abcg::glGenVertexArrays(1, &m_VAO);

  // Bind vertex attributes to current VAO
  abcg::glBindVertexArray(m_VAO);

  abcg::glEnableVertexAttribArray(positionAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOPositions);
  abcg::glVertexAttribPointer(positionAttribute, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  abcg::glEnableVertexAttribArray(colorAttribute);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, m_VBOColors);
  abcg::glVertexAttribPointer(colorAttribute, 3, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
  abcg::glBindBuffer(GL_ARRAY_BUFFER, 0);

  // End of binding to current VAO
  abcg::glBindVertexArray(0);
}
