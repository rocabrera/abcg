# Informações Aluno

- **Nome**: Rodrigo Cabrera Castaldoni 
- **RA**: 21005515

# Descrição da Aplicação

A aplicação consiste em um organizador financeiro (separador de itens) onde podemos alocar um item por vez em uma das três possíveis categorias. Entretanto um mesmo item pode ter estar em duas categorias diferentes, mas precisam ser adicionados um por vez.

# Detalhes da Implementação

## Informações Gerais

- O código foi desenvolvido pensando em como escalar de forma simples. Por exemplo: Podem ser adicionadas novas categorias somente mexendo no arquivo ***window.hpp*** ao adiciona a categoria nas variáveis do ***categories***, ***categories_mapper***.
- É possível fazer o resize da aplicação e a posição relativa dos elementos na tela irá permanecer.
- Foi utilizado a fonte ***MontereyFLF.ttf***.

## Estruturas de dados

A estrutura de dados principal do projeto é um mapa de strings para vetores (```map<string, vector<string>>```), onde cada chave representa uma categoria e o vetor a quantidade de itens associadas aquela categoria. 

## Dados de entrada

Os dados de entrada da função ```ImGui::InputText``` são adicionados na variável ***input_text*** para posterior adição em alguma categoria.


## Funções Principais

As funções principais de desenho dos elementos do ImGui:

- ```create_categories_holders```: Responsável pelo desenho responsivo dos Headers (Os quais além de indicar a categoria do listbox também mostram a quantidade de items alocados) e ListBoxs que representam nossas categorias.

- ```create_categorie_selector```: Responsável pelo desenho responsivo do dropdown na tela, permitindo selecionar a categoria na qual o item vai ser inserido.

## Botão Enter

A lógica da aplicação se encontra no Botão **Enter**, o qual utiliza a saída da função ***create_categorie_selector*** para selecionar qual categoria do mapa o texto deve ser inserido (o qual se encontra na variável ***input_text***). Vale notar que não é possível adicionar textos vazios nas categorias. Vale notar que ao adicionar o texto na categoria a variável ***input_text*** é resetada.

## Botão Output

Reseta a variável ***input_text***.


