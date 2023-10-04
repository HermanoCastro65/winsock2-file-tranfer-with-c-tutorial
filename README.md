## Compilando o Código do Cliente e do Servidor em C com Winsock2
Neste tutorial, explicarei como compilar o código do cliente e do servidor em C usando o GCC e a biblioteca Winsock2 no Windows.

### Pré-requisitos
Antes de começar, certifique-se de ter os seguintes pré-requisitos instalados no seu sistema:
1. GCC: O GCC (GNU Compiler Collection) é necessário para compilar o código em C. Você pode instalá-lo usando o MinGW no Windows.
2. Biblioteca Winsock2: A biblioteca Winsock2 é usada para trabalhar com sockets no Windows. Ela geralmente já está incluída nas distribuições MinGW.

### Compilando o Código do Servidor
1. Abra o terminal do Windows (Prompt de Comando ou PowerShell).
2. Navegue até o diretório onde está localizado o arquivo de código fonte do servidor (por exemplo, servidor.c).
3.Use o seguinte comando para compilar o código do servidor:

```bash
gcc -o servidor servidor.c -lws2_32
```
Certifique-se de que o arquivo "servidor.c" esteja no diretório. O GCC criará um arquivo executável chamado "servidor".

4. Execute o servidor com o seguinte comando:

```bash
./servidor
```
O servidor estará pronto para aceitar conexões de clientes.

### Compilando o Código do Cliente
1. Abra um novo terminal (mantenha o servidor em execução no terminal anterior).

2. Navegue até o diretório onde está localizado o arquivo de código fonte do cliente (por exemplo, cliente.c).

3. Use o seguinte comando para compilar o código do cliente:

```bash
gcc -o cliente cliente.c -lws2_32
```

Certifique-se de que o arquivo "cliente.c" esteja no diretório. O GCC criará um arquivo executável chamado "cliente".

4. Execute o cliente com o seguinte comando:

```bash
./cliente <IP_do_Servidor> <Nome_do_Arquivo>
```

Substitua `<IP_do_Servidor>` pelo endereço IP do servidor e `<Nome_do_Arquivo>` pelo nome do arquivo que deseja transferir. Certifique-se de que o servidor esteja em execução antes de executar o cliente.

### Conclusão
Agora você aprendeu como compilar o código do cliente e do servidor em C usando o GCC e a biblioteca Winsock2 no Windows. Certifique-se de configurar corretamente a infraestrutura de rede para que o cliente e o servidor possam se comunicar.

Lembre-se de que este é um exemplo simplificado e pode ser necessário realizar ajustes adicionais para atender aos requisitos específicos do seu projeto.

