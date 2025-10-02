# 📡 Minitalk

Minitalk é um projeto que visa criar um programa de comunicação de dados simples usando sinais UNIX (`SIGUSR1` e `SIGUSR2`). O projeto consiste em um servidor, que exibe seu PID e recebe a mensagem, e um cliente, que envia a mensagem caractere por caractere para o PID do servidor.

## 🚀 Funcionalidades

| Executável | Descrição | Status |
| :--- | :--- | :--- |
| **`server`** | Recebe mensagens via sinais e as exibe. | Mandatório |
| **`client`** | Envia uma string para o servidor PID, um bit por sinal. | Mandatório |
| **`server_bonus`** | Funcionalidade idêntica ao `server`. | Bônus |
| **`client_bonus`** | Envia a string e **recebe confirmação (ACK)** do servidor a cada caractere enviado, indicando que a transmissão foi bem-sucedida. | Bônus |

-----

## 🛠️ Como Usar

### 1\. Compilação

Para compilar o projeto mandatório e bônus, use o `Makefile`:

```bash
# Compila o mandatório (cria: server, client)
make all

# Compila o bônus (cria: server_bonus, client_bonus)
make bonus
```

### 2\. Execução (Mandatório)

**Passo 1: Inicie o Servidor**

Execute o servidor. Ele imprimirá seu PID, que é o número que o cliente precisa:

```bash
./server
# Saída: Server PID: 12345
```

**Passo 2: Inicie o Cliente**

Use o executável `client` e passe o PID do servidor e a mensagem como argumentos:

```bash
./client 12345 "Esta é a mensagem a ser enviada."
```

### 3\. Execução (Bônus - Com Confirmação de Envio)

Use a versão `_bonus` do cliente, que informa o sucesso do envio no final.

**Passo 1: Inicie o Servidor**

```bash
./server_bonus
# Saída: Server PID: 12345
```

**Passo 2: Inicie o Cliente Bônus**

O cliente bônus exibirá uma confirmação ao final do envio.

```bash
./client_bonus 12345 "Mensagem com ACK!"
# Se for bem-sucedido, o cliente imprimirá: Mensagem enviada com sucesso.
```

-----

## 📝 Regras de Sintaxe e Erro

O programa `client` (e `client_bonus`) possui validação de argumentos e retornará um erro se a sintaxe for inválida.

**Formato Correto:**

```bash
./client <PID_do_Servidor> "<Mensagem a Enviar>"
```

**Erros de Parsing (O cliente sairá com `Error`):**

  * Número incorreto de argumentos (`./client 12345`)
  * PID inválido (Ex: `0`, um número muito grande, ou não-numérico)

-----

## ⚙️ Estrutura do `Makefile`

O `Makefile` é configurado para gerenciar as versões mandatórias e bônus de forma independente.

| Alvo | Ação |
| :--- | :--- |
| **`all`** | Compila `server` e `client` (versão mandatória). |
| **`bonus`** | Compila `server_bonus` e `client_bonus` (versão bônus). |
| **`clean`** | Remove arquivos objeto (`.o`) dentro do diretório `obj`. |
| **`fclean`** | Executa `clean` e remove os executáveis (`server`, `client`, `server_bonus`, `client_bonus`). |
| **`re`** | Executa `fclean` e, em seguida, `all`. |