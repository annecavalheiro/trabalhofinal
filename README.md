# Navegamazon

Ferramenta digital para consulta e análise de pontos turísticos do centro de Manaus.


## 📋 Sobre o Projeto

Software desenvolvido para conectar turistas à cidade de Manaus, apresentando os principais pontos turísticos e eventos da capital. A plataforma permite ao visitante descobrir atrações de acordo com seus interesses, proporcionando uma experiência personalizada e completa da cultura manauara.

## ✨ Funcionalidades

- Manter os principais pontos turisticos
- Carregamento local (.txt)
- Filtros personalizados:
    - Pesquisa por categorias de cada local

## 🛠️ Tecnologias Utilizadas

- **Linguagem:** C
- **Compilador:** GCC
- **Sistema Operacional:** Windows
- **Ferramentas:** Git, Bloco de notas

## 📦 Instalação e Compilação

### Pré-requisitos

- GCC (versão 7.0 ou superior) ou Clang
- Sistema operacional compatível (Windows com MinGW)

### Compilação no Windows

```bash
gcc -o main.exe main.c -Wall -Wextra -std=c99
main.exe
```

## 💻 Como Usar

### Execução Básica

```bash
./main.exe
```
### Menu Principal

Ao executar o programa, você verá o menu principal com as seguintes opções:
```
NAVEGAMAZON - GUIA TURISTICO (CENTRO DE MANAUS)
1 - Inserir novo lugar
2 - Listar lugares
3 - Filtrar por categorias
4 - Salvar em TXT (locais.txt)
5 - Deletar por nome do local
0 - Sair
```

### Funcionalidades Detalhadas

#### 1️⃣ Inserir Novo Lugar

Cadastre um novo ponto turístico informando:
- Nome do local
- Descrição detalhada
- Endereço (rua e CEP)
- Contatos (até 3 telefones, e-mail e site)
- Categorias múltiplas (escolha entre 14 opções)
- Valor da entrada (R$ 0,00 para gratuito)

**Exemplo de uso:**
```
Escolha uma opcao: 1
Nome do lugar: Teatro Amazonas
Descricao: Patrimônio histórico e cultural da cidade
Rua: Av. Eduardo Ribeiro
CEP: 69010-000
Quantos telefones? (max 3): 1
Telefone 1: (92) 3622-1880
...
```

#### 2️⃣ Listar Lugares

Visualize todos os locais cadastrados com informações completas:
- Nome e descrição
- Endereço e contatos
- Categorias atribuídas
- Ranking (nota de 0 a 5)
- Valor da entrada
- Comentários de visitantes (se houver)

#### 3️⃣ Filtrar por Categorias

Busque locais por categoria específica:
- Selecione uma das 14 categorias disponíveis
- O sistema exibirá apenas os locais que correspondem à categoria escolhida
- Ideal para encontrar restaurantes, museus, igrejas, etc.

**Exemplo:**
```
Escolha uma categoria: 11 (Museu)
Resultado: Lista todos os museus cadastrados
```

#### 4️⃣ Salvar em TXT

- Os dados são automaticamente salvos no arquivo `locais.txt`
- Use esta opção para garantir que todas as alterações foram salvas
- O arquivo é carregado automaticamente ao iniciar o programa

#### 5️⃣ Deletar Local

Remove um local do cadastro:
- Digite o nome exato do local
- O sistema confirmará se encontrou o local
- Os dados são automaticamente atualizados no arquivo

**⚠️ Atenção:** A exclusão é permanente!

### Dicas de Uso

💡 **Categorias Múltiplas**: Um local pode ter várias categorias. Por exemplo, uma igreja histórica pode ser marcada como "Igreja", "Patrimônio Histórico" e "Cultural".

💡 **Dados Persistentes**: Todos os dados são salvos automaticamente em `locais.txt` e carregados ao iniciar o programa.

💡 **Entrada Gratuita**: Para locais gratuitos, digite `0` no valor da entrada.

💡 **Busca Precisa**: Ao deletar um local, digite o nome exatamente como foi cadastrado (case-sensitive).


## 📁 Estrutura do Projeto

```
projeto/
├── src/
│   ├── main.c
│   ├── modulo1.c
│   ├── modulo1.h
│   ├── modulo2.c
│   └── modulo2.h
├── include/
│   └── headers adicionais
├── bin/
│   └── executáveis compilados
├── tests/
│   └── arquivos de teste
├── docs/
│   └── documentação adicional
├── Makefile
├── README.md
└── LICENSE
```

## 👥 Equipe

- **Anne Cavalheiro** - [GitHub](https://github.com/annecavalheiro) - Responsabilidade principal
- **Anne Oliveira** - [GitHub](https://github.com/annehdob) - Estruturas de dados
- **Anderson ** - [GitHub](https://github.com/andersonsas) - Interface e I/O
- **Samily Moldes** - [GitHub]() - Testes e documentação




Desenvolvido com ❤️ pela equipe [Monstros SA] | Projeto acadêmico - [IFAM - TADS]

