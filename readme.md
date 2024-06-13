# Simulador de Pêndulos Duplos Caóticos

Apesar da aparente simplicidade do pêndulo duplo[^1], sua trajetória é extremamente sensível às condições iniciais, o que o torna capaz de demonstar comportamento caótico[^2], sendo então um excelente exemplo de um sistema dinâmico não-linear[^3].

O movimento dos pêndulos, que foram modelados de forma orientada à objetos, é calculado a partir de uma fórmula que considera uma constante gravitacional, o ângulo do pêndulo em relação ao eixo Y, a aceleração e velocidade angular e também uma constante arbitrária que simula a resistência do ar e/ou outros fatores que afetam a perda de energia do sistema.

Essa fórmula é derivada da equação de movimento de um pêndulo duplo. Tal equação e o processo de derivação são melhor explicadas em artigos disponíveis na internet.[^4][^5][^6]

[^1]: Um pêndulo duplo consiste em dois pêndulos conectados de ponta a ponta.
[^2]: Pequenas diferenças nas condições iniciais produzem resultados amplamente divergentes para tais sistemas dinâmicos, tornando a previsão a longo prazo geralmente impossível.
[^3]: Um sistema dinâmico não-linear é caracterizado por equações que não seguem a superposição linear, resultando em comportamentos complexos como o caos.
[^4]: https://web.mit.edu/jorloff/www/chaosTalk/double-pendulum/double-pendulum-en.html#kinematics
[^5]: https://www.phys.lsu.edu/faculty/gonzalez/Teaching/Phys7221/DoublePendulum.pdf
[^6]: https://www.phys.lsu.edu/faculty/gonzalez/Teaching/Phys7221/DoublePendulum.pdf
