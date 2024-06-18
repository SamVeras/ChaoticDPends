# Simulador de Comportamento Caótico de Pêndulos Duplos

### Índice

- [Descrição](#descrição)
- [Funcionalidade](#funcionalidade)
- [Instruções de Uso](#instruções-de-uso)
- [Compilação](#compilação)
- [Estrutura de arquivos](#estrutura-de-arquivos)
- [Diagrama de classes](#diagrama-de-classes)
- [Configurando os parâmetros da simulação](#configurando-os-parâmetros-da-simulação)
- [Continhas](#continhas)
- [Créditos e Atribuições](#créditos-e-atribuições)

## Descrição

Apesar da aparente simplicidade do pêndulo duplo[^1][^2], sua trajetória é
extremamente sensível às condições iniciais, o que o torna capaz de demonstar
comportamento caótico[^3], sendo então um excelente exemplo de um sistema
dinâmico não-linear[^4].

O movimento dos pêndulos, que foram modelados de forma orientada à objetos, é
calculado a partir de uma fórmula que considera uma constante gravitacional, o
ângulo do pêndulo em relação ao eixo Y, a aceleração e velocidade angular e
também uma constante arbitrária que simula a resistência do ar e/ou outros
fatores que afetam a perda de energia do sistema.

## Funcionalidade

- Simular milhares de pêndulos duplos com condições iniciais personalizáveis.
- Visualização gráfica do movimento dos pêndulos.
- Analisar e comparar trajetórias ao correr do tempo

## Instruções de Uso

### Drag & Drop

- É possível carregar diferentes configurações do programa **arrastando e soltando**
  um arquivo `.toml` com configurações relevantes para a janela do programa.

### Teclas de Atalho

- `ESC`ou `Q`: Fechar o programa
- `1` ou `-`, `3` ou `=`: Controlar a velocidade de simulação
- `2`: Resetar a velocidade de simulação
- `P` ou `ESPAÇO`: Pausar a simulação
- `R`: Reiniciar a simulação atual e câmera
- `F1` ou `F`: Mostrar a taxa de quadros por segundo
- `F2` ou `D`: Mostrar informação de depuração
- `F3` ou `T`: Mostrar o contador de tempo da simulação
- `F4` ou `C`: Mostrar informações de câmera

## Compilação

### Requisitos

- C++17 ou superior
- Biblioteca [raylib](https://www.raylib.com) para visualização
- make para compilar

### Instruções

- `make`: compilar.
- `make run`: executar o binário principal (`/bin/pendulos`).
- `make clean`: remover arquivos-objeto e executáveis.

## Estrutura de arquivos

```
.
├──/aux                  # Arquivos auxiliares (temporários, logs, etc.)
├──/bin                  # Binários compilados
├──/build                # Arquivos de build
├──/include              # Arquivos de cabeçalho (declarações)
│   ├──/toml++           # Biblioteca toml++
│   │   └── toml.hpp
│   ├── classes.hpp      # Classes usadas no projeto
│   ├── config.hpp       # Classe de configuração
│   ├── functions.hpp    # Funções auxiliares
│   ├── game.hpp         # Classe principal do jogo
│   └── global.hpp       # Variáveis e constantes globais
├──/res                  # Recursos (fontes, imagens, etc.)
├──/src                  # Arquivos-fonte (implementações)
│   ├── config.cpp
│   ├── functions.cpp
│   ├── game.cpp
│   ├── main.cpp
│   └── pendulums.cpp    # Implementação das classes de pêndulos
├──/test                 # Testes
├── config.toml          # Arquivo de configuração inicial
├── makefile
└── readme.md

```

## Diagrama de classes

```mermaid
%%{init: {'theme': 'neutral' } }%%
classDiagram
  class Drawable {
      <<Abstract>>
      +void update(float dt)
      +void draw() const
  }

  class Pendulum {
      <<Abstract>>
      -Vector2 origin
      -float damping
      +Pendulum(Vector2 o, float d)
      +~Pendulum()
  }

  class SimplePendulum {
      -PendulumArm arm
      +SimplePendulum(Vector2 o, int l, float m, double t, Color c, float d)
      +~SimplePendulum()
      +void update(float dt) override
      +void draw() const override
  }

  class DoublePendulum {
      -PendulumArm arm1
      -PendulumArm arm2
      +DoublePendulum(Vector2 o, int l1, float m1, double t1, Color c1, int l2, float m2, double t2, Color c2, float d)
      +~DoublePendulum()
      +void update(float dt) override
      +void draw() const override
  }

  class PendulumArm {
      int length
      float mass
      double theta
      double theta_v
      double theta_a
      Color color
  }

  class Game {
      -Config settings
      -std::vector<std::unique_ptr<Drawable>> drawables
      -double timer
      -const float delta_t
      -float accumulator
      -float sim_speed
      -void display_fps()
      -void display_debug()
      -void display_timer()
      -void reset()
      -void full_reset()
      +void add_drawable(std::unique_ptr<Drawable> ptr)
      +void input()
      +void run()
      +Game()
      +~Game()
  }

  class Config {
      +std::string title
      +int win_width
      +int win_height
      +int framerate
      +Color background_color
      +Vector2 origin
      +size_t count
      +float damping
      +int length_1
      +int length_2
      +float mass_1
      +float mass_2
      +double initial_theta_1
      +double initial_theta_2
      +double final_theta_1
      +double final_theta_2
      +Color initial_color_1
      +Color final_color_1
      +Color initial_color_2
      +Color final_color_2
      +bool show_fps
      +bool debug_mode
      +bool show_timer
      +bool camera_debug
      +std::string font_path
      +float font_size
      +Font font
      +void init_font()
      +Config(const std::string& file_path)
      +~Config()
  }

  class Funções {
      +unsigned char rand_char()
      +double rand_angle()
      +Color load_color(const toml::v3::node_view<toml::v3::node>& node)
      +Color invert_color(const Color& color)
      +double degrees_to_radians(double angle)
      +double radians_to_degrees(double radians)
      +double angle_interpolation(double from, double to, double p)
      +Color color_interpolation(const Color& from, const Color& to, double p)
      +double angle_difference(double from, double to)
      +std::string format_float(float n, float dec)
      +void toggle_maximized()
  }

  class `config.toml` {
      <<Arquivo>>
    ++ Configurações
  }

  class `toml++` {
      <<Biblioteca>>
  }

  class raylib {
      <<Biblioteca>>
  }

  Drawable        <|-- Pendulum
  Pendulum        <|-- SimplePendulum
  Pendulum        <|-- DoublePendulum
  SimplePendulum  *-- "1" PendulumArm
  DoublePendulum  *-- "2" PendulumArm
  Game            *-- "múltiplos" Drawable
  Game            *-- "1" Config
  Config          *-- `config.toml` : Carrega
  Config          ..> `toml++` : Utiliza
  Funções         ..> `toml++` : Utiliza
  Funções         ..> raylib : Utiliza
  SimplePendulum  ..> raylib : Utiliza
  DoublePendulum  ..> raylib : Utiliza
```

## Configurando os parâmetros da simulação

No arquivo `config.toml`:

```toml
[window]
title = "Simulação de Pêndulos"
width = 640
height = 480
framerate = 60
background = [0, 0, 0, 255]
font = "res/LiberationMono-Bold.ttf"
font_size = 18
```

- `title`: Título da janela
- `width`: Largura em pixels
- `height`: Altura em pixels
- `framerate`: Taxa de atualização
- `background`: Cor do fundo da tela
- `font`: Caminho da fonte à ser carregada
- `font_size`: Tamanho da fonte

```toml
[debug]
show_timer = true
show_fps = true
debug_mode = false
```

- `show_timer`: Ligar ou desligar o timer de simulação
- `show_fps`: Ligar ou desligar o contador de frames
- `debug_mode`: Ligar ou desligar as informações de depuração
- `camera_debug`: Ligar ou delisgar as informações de câmera

```toml
[pendulums]
origin = [400, 400]
count = 10000
damping = 0.001
```

- `origin`: Coordenadas do ponto de origem dos pêndulos
- `count`: Número de pêndulos a serem instânciados
- `damping`: Variável que controla a diminuição da energia do sistema

```toml
[first_arm] # a configuração do [second_arm] é idêntica
length = 200
initial_theta = 180
final_theta = 180.5
initial_color = [255, 255, 255, 255]
final_color = [255, 0, 0, 255]
mass = 1
```

- `length`: Comprimento do braço do pêndulo
- `initial_theta`: Ângulo inicial dos braços
- `final_theta`: Ângulo final dos braços
- `initial_color`: Cor inicial dos braços
- `final_color`: Cor final dos braços
- `mass`: Massa do pêndulo, com o ponto gravitacional na ponta do braço.

_Nota: Os pêndulos instanciados terão seus ângulos interpolados entre o_ $\theta$_
inicial e o_ $\theta$ _final. \
As cores também serão interpoladas para cada braço, em proporção ao número total
de pêndulos._

## Continhas

Sejam $\theta_1$ e $\theta_2$ os ângulos dos pêndulos relativos ao eixo $y$,
$L_1$ e $L_2$ os comprimentos dos braços dos pêndulos e $m_1$ e $m_2$ as massas
dos pêndulos (localizadas na ponta de cada um).

$\theta_1'$ e $\theta_2'$ então são as velocidades angulares e $\theta_1'' \cdot
\Delta t$ e $\theta_2'' \cdot \Delta t$ são as acelerações dos ângulos
considerando a diferença de tempo entre cada frame.

$$
\theta_1'' = \frac {-g (2 \cdot m_1 + m_2) \sin{\theta_1} - m_2 \cdot g \cdot
\sin{(\theta_1 - 2 \cdot \theta_2)} - 2 \sin{(\theta_1 - \theta_2) \cdot m_2
\cdot (\theta_2'^2 \cdot L_2 + \theta_1'^2 \cdot L_1 \cos{(\theta_1 -
\theta_2)})}} {L1 \cdot (2 \cdot m_1 + m_2 - m_2 \cdot \cos{(2 \cdot \theta_1 -
2 \cdot \theta_2)})}
$$

$$
\theta_2'' = \frac {2 \cdot \sin{\theta_1 - \theta_2}(\theta_1'^2 \cdot L_1
(m_1 + m_2) + g \cdot (m_1 + m_2) \cdot \cos{\theta_1} + \theta_2'^2 \cdot L_2
\cdot m_2 \cdot \cos{(\theta_1 - \theta_2)})} {L2 \cdot (2 \cdot m_1 + m_2 - m_2
\cdot \cos{(2 \cdot \theta_1 - 2 \cdot \theta_2)})}
$$

Essa fórmula é derivada da equação de movimento de um pêndulo duplo. Tal equação
e o processo de derivação são melhor explicadas em artigos disponíveis na
internet.[^5][^6]

## Créditos e Atribuições

- ROMULUS FONT projetada por Hewett Tsoi.
- Liberation :tm: Fonts projetadas por Red Hat.
- Contribuidores da biblioteca Raylib.
- Contribuidores da biblioteca toml++.
- Eu kk

[^1]: Um pêndulo duplo consiste em dois pêndulos conectados de ponta a ponta.
[^2]: http://www.physics.usyd.edu.au/~wheat/dpend_html/
[^3]:
    Pequenas diferenças nas condições iniciais produzem resultados amplamente
    divergentes para tais sistemas dinâmicos, tornando a previsão a longo prazo
    geralmente impossível.

[^4]:
    Um sistema dinâmico não-linear é caracterizado por equações que não seguem
    a superposição linear, resultando em comportamentos complexos como o caos.

[^5]: https://web.mit.edu/jorloff/www/chaosTalk/double-pendulum/double-pendulum-en.html#kinematics
[^6]: https://www.phys.lsu.edu/faculty/gonzalez/Teaching/Phys7221/DoublePendulum.pdf
