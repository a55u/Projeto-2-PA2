Markdown# 🎮 Jogo de Aventura — Otimização de Mochila Fracionária

[cite_start]Este projeto foi desenvolvido como parte dos requisitos avaliativos da disciplina de **Projeto e Análise de Algoritmos II** na **Universidade Presbiteriana Mackenzie**. [cite_start]O objetivo principal é simular um jogo de aventura em formato textual, aplicando uma **estratégia gulosa** para maximizar o lucro de um personagem ao carregar itens em sua mochila ao longo de 4 fases[cite: 4, 12, 16].

[cite_start]O programa utiliza o conceito do **Problema da Mochila Fracionária**, onde itens podem ser levados em pedaços proporcionais para preencher o espaço restante da mochila, exceto quando bloqueado pelas regras específicas de cada cenário[cite: 8, 13, 123].

---

## 📂 Estrutura de Arquivos

O projeto está modularizado de forma a separar a manipulação de arquivos da lógica pura de regras de negócio e ordenação matemática:

```text
.
├── data
│   ├── in.txt               # Arquivo de entrada com os dados das fases e itens
│   └── out.txt              # Relatório estruturado gerado pelo programa com as decisões
├── README.md                # Manual de uso e documentação do projeto
└── src
    ├── jogo_aventura.c      # Arquivo principal (Main, validação e carregador de dados/parser)
    ├── regras.c             # Implementação das regras modificadoras de valor por fase
    └── utils
        ├── mochila.c        # Algoritmo guloso de preenchimento e ordenação manual
        └── utils_mochila.h  # Definição das structs e protótipos de funções globais
⚔️ As 4 Fases e Regras de NegócioO personagem passará sequencialmente por quatro cenários, cada um com capacidades de mochila distintas e uma lógica isolada:  Floresta Encantada (MAGICOS_VALOR_DOBRADO): Todos os itens catalogados com o tipo magico têm seu valor de mercado multiplicado por 2 antes do cálculo de custo-benefício.  Ruínas Perdidas (TECNOLOGICOS_INTEIROS): Dispositivos do tipo tecnologico não aceitam divisão física. Eles só entram na mochila se couberem inteiramente; do contrário, são ignorados.  Montanhas Geladas (SOBREVIVENCIA_DESVALORIZADA): O frio extremo deteriora suprimentos essenciais. Itens do tipo sobrevivencia perdem 20% do seu valor comercial original.  Templo Subterrâneo (TRES_MELHORES_VALOR_PESO): Pelo tempo de fuga escasso, o motor de busca limita o laço a avaliar estritamente os 3 itens que tiverem os maiores coeficientes de custo-benefício ($\frac{\text{valor}}{\text{peso}}$) daquela fase.  🛠️ Como Compilar no LinuxA compilação do projeto requer o compilador GCC instalado. Como o projeto é modular, nenhum arquivo .c faz o #include de outro arquivo .c. Eles se comunicam através da interface pública do cabeçalho .h.  Abra o seu terminal na raiz do projeto e execute o seguinte comando:Bashgcc -Wall src/jogo_aventura.c src/regras.c src/utils/mochila.c -o jogo_aventura.exe
A flag -Wall habilita todas as checagens rigorosas de boas práticas e tipos do compilador, assegurando maior estabilidade na execução do código.🚀 Como ExecutarO programa foi projetado de forma dinâmica, exigindo os descritores de caminhos de entrada e saída por meio de argumentos em linha de comando na inicialização da main.  A estrutura do comando de execução é:Bash./jogo_aventura.exe <caminho_entrada> <caminho_saida>
Exemplo Prático com a nossa Árvore de Diretórios:Bash./jogo_aventura.exe data/in.txt data/out.txt
📝 Formato dos Arquivos de DadosEntrada (data/in.txt)O arquivo de entrada deve agrupar as diretivas por blocos contendo o cabeçalho descritivo da fase, seguidos da listagem exata de seus itens com separação por vírgula no padrão esperado pelo parser:  PlaintextFASE: Floresta Encantada
CAPACIDADE: 5.0
REGRA: MAGICOS_VALOR_DOBRADO
ITEM: Pocao da Cura, 80.0, 0.5, magico
ITEM: Espada Rustica, 150.0, 2.0, normal
Saída Gerada (data/out.txt)O arquivo gerado exibe de maneira cirúrgica quais itens foram selecionados, se entraram inteiros ou cortados, o peso remanescente consumido, o lucro acumulado por setor e o balanço geral ao término da jornada:  PlaintextFASE: Floresta Encantada
Capacidade da mochila: 5.00 kg
Regra aplicada: MAGICOS_VALOR_DOBRADO
Pegou (inteiro) Pocao da Cura (0.50kg, R$ 160.00)
Pegou (fracionado) Espada Rustica (2.00kg, R$ 150.00)
Lucro da fase: R$ 310.00

...

LUCRO TOTAL ACUMULADO: R$ 1880.00
