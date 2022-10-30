# Informações Aluno

- **Nome**: Rodrigo Cabrera Castaldoni 
- **RA**: 21005515

# Descrição da Aplicação

A aplicação consiste em um ferramenta de desenho (similar ao Paint) com algumas funcionalidades, dentre elas:

- Alterar a cor do pincel.
- Alterar o tamanho do pincel.
- A quantidade de lados da geometria desenhada.
- Alterar a Primitiva de desenho do OpenGL.
- Rotacionar a geometria desenhada com velocidade constante.


# Detalhes da Implementação

## Informações Gerais

O projeto foi inicialmente baseado na atividade feita em classe chamada ```regularpolygon```. Somente um poligno é desenhado a cada quadro, o **VBO** contém a quantidade de lados do poligno especificado mais 2 vértices para o desenho ficar correto quando utilizamos a primitiva ***GL_TRIANGLE_FAN*** (conforme explicado em aula).

## Vertex Shader

No vértice shader foi adicionada a variavel uniforme ```angle``` (constante para todos os vértices) que rotaciona os pontos no sentido anti-horário antes de realizarmos o processo de translação e escalonamento, reespecivamente realizados pelas variáveis ```translation``` e ```scale```.

Vale notar que seria possível criar o seno e cosseno do ângulo como duas variáveis uniformes ao invés de calcular esse valor para todo vértice. Entretanto optei por não o fazer simplesmente por uma questão de simplicadade.

## Fragment Shader

Não foi alterado. O arquivo do fragment shader somente passa a cor do vértice conforme visto em aula. Quanto a cor nesse projeto todos os vértices sempre terão a mesma cor então não existe nenhum tipo de interpolação das cores.

## Funções Principais

As principais funções: 


- ***onCreate***: Responsável por carregar o vertex e fragment shader.

- ***onEvent***: Reponsável por atualizar a posição do mouse na variável ```mousePosition``` quando clicamos na tela. Para isso usamos uma variável boleana chamada ```drawing``` que troca seu valor conforme apertamos ou soltamos o clique.

- ***onPaintUI***: Responsável por desenhar a parte de UI da aplicação, a qual contém a maioria dos elementos que permitem iteragirmos com a aplicação, como exemplo grossura ou geometria do pincel.

- ***onPaint***: Responsável, basicamente, por popular as variáveis uniformes do vertex shader, definir a primitiva de desenho do OpenGL e chamar a função ```setupModel```. Vale notar que incrementamos a variável ```angular_shift``` em 0.5 graus a cada 1 segundo, mas desenhos o poligno a cada evento, para conseguir o efeito desejado. Além disso, utilizamos a função ```mouse_position_standardize``` responsável por fazer os valores da posição do mouse ficarem entre [-1 e 1].

- ***setupModel***: Essa função basicamente não foi alterada, ela é muito parecida com a atividade ```regularpolygon```, isto é, a posição dos vértices do **VBO** não foi alterada nessa aplicação.