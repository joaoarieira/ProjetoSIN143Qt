IMPORTANTE:
No arquivo loginwindow.cpp na linha 14, altere o caminho do arquivo
do banco de dados para o caminho correto na sua máquina, por exemplo,
"C:/Correcoes/ProjetoSIN143Qt/db_sorveteria.db". Não utilizar barras
invertidas: "C:\...\...\".

Baixamos a IDE através do link https://www.qt.io/download versão Open Source.

O pacote para compilação e execução utilizado foi o
Desktop Qt 5.12.3 MinGW 64-bit, sendo executado no modo debug.

Para abrir o projeto, basta abrir o arquivo ProjetoSIN143Qt.pro.

Para rodá-lo, lembre-se de escolher o pacote citado. Basta clicar
em run.

------------
UTILIZAÇÃO:
O login e a senha foram previamente preenchidos para teste, sendo
possível acessar o sistema através dos logins:

username: userjoao
password: 123123

username: atendente
password: 123123

O segundo usuário não possui acesso aos CRUDs do sistema.

Após o login ser feito, a tela principal do caixa será aberta.
Para gerenciar um pedido, coloque o código do produto e a quantidade.
Para que o produto+quantidade sejam adicionados ao pedido, tecle ENTER.
Os códigos disponíveis para teste são de 1 até 10.
Para começar um novo pedido, o valor total recebido deve ser maior
ou igual ao subtotal do pedido.
As opções de crud estão em uma barra de menus.
O restante é bem simples.

------------

COMENTÁRIOS:
Caso queira verificar se o programa realmente está se comunicando
com um banco de dados, instale o SQLiteStudio através do link

https://sqlitestudio.pl/index.rvt?act=download

Tentamos criar uma aplicação pra rodar sem precisar da IDE,
até conseguimos, porém a aplicação não consegue se comunicar
com o banco de dados corretamente. Acreditamos ser um bug da
própria versão da IDE.

Estamos utilizando o Qt Creator 4.9.1 que é baseado no Qt 5.12.3
com última atualização no dia 26 de maio de 2019.






