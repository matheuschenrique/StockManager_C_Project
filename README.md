# StockManager_C_Project

Programa simples, que implementa um gerenciamento de estoque de produtos. Ele oferece algumas funcionalidades para cadastrar, buscar, atualizar as quantidades em estoque e exibir os produtos.

## Estrutura do Projeto
O projeto está organizado da seguinte maneira
- **src**: Pasta que contém os arquivos de código do projeto.
  - **main.cpp**: Arquivo principal, que contém a função main(), responsável por executar o loop principal.
  - **product.cpp**: Implementa as funções utilizadas no estoque.
  - **current_time.cpp**: Implementa uma função que obtém a hora atual, utilizado para fins de registros.
  - **menu.cpp**: Implementa as funções do menu que será mostrado no terminal.
- **include**: Pasta que contém os arquivos de cabeçalho do projeto.
  - **product.h**: Cabeçalho que define a struct Product e todas outras que a utilizam como base.
  - **menu.h**: Cabeçalho que declara as funções do menu.
- **CMakeLists.txt**: Arquivo de configuração do CMake, especificando suas dependências e compilando o código

## Tipos de Produtos
Até o momento foram implementados alguns tipos de produtos, que permitem cadastrar, buscar, atualizar e exibir o produto. Os tipos específicos implementados são:
1. Livros
2. Eletrônicos
3. Roupas
4. Alimentos

## Utilização
Em um primeiro momento, será mostrado um menu no terminal, que permitirá a escolha de uma das opções a seguir:
1. Registrar Produto: Cadastrar um novo produto, informando o tipo e demais detalhes.
2. Pesquisar Produto: Permite pesquisar um produto a partir de seu nome ou código.
3. Atualizar Estoque: Permite atualizar a quantidade em estoque de um produto existente.
4. Exibir Produtos: Exibe todos os produtos cadastrados.
5. Sair: Encerra o programa

## Repositório em C++
Uma outra versão deste projeto foi implementada utilizando a linguagem C++, que pode ser conferido no repositório [StockManager_Cpp_Project](https://github.com/matheuschenrique/StockManager_Cpp_Project), oferecendo as mesmas funcionalidades, mas com implementação em outra linguagem.
