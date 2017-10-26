# LabirintoCG
Autores: Jefferson A. Coppini, Jonathan T. Rauber

ORIENTAÇÕES

# Para compilar e executar o programa:
> Basta executar o comando make

# Para alterar a taxa de atualização de quadros por segundo:
> Mudar a constante FPS em defs.h. O valor padrão é 30FPS (30 frames por segundo). Isto corresponde à 33ms (1000ms/30fps).

# Para movimentar o robô:
> As teclas direcionais UP e DOWN movimentam o robô para frente e para trás, respectivamente.
> As teclas direcionais LEFT e RIGHT mudam a direção de movimento do robô.

# Atalhos de teclado:
> Tecla M: altera o modo de ação. Modos: MANUAL e AUTOMÁTICO.
-----> No modo MANUAL, o usuário controla o robô pelo labirinto utilizando as teclas direcionais do teclado (UP, DOWN, LEFT, RIGHT).
-----> No modo AUTOMÁTICO, o usuário observa as decisões do robô para tentar sair do labirinto.

> Tecla C: altera a câmera. Existem duas câmeras disponíveis: PANORÂMICA e ATRÁS DO ROBÔ.
-----> A câmera PANORÂMICA é capaz de observar o labirinto inteiro, através de uma câmera posicionada "no céu". 
-----> A câmera ATRÁS DO ROBÔ acompanha a movimentação do robô de forma mais próxima ao solo. Ao aplicar zoom, esta câmera pode também acompanhar o robô pela frente.

> Teclas '+' e '-': aplicam ZOOM na câmera selecionada. 
-----> + aproxima a câmera
-----> - distancia a câmera
