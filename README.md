# CG_opengl_game
Somente testado no Linux.

[Gameplay in Youtube](https://www.youtube.com/watch?v=s_5Ied786_4)

## Compilação

Para compilar o jogo basta digitar o seguinte comando na linha de comando:
>make LucasTrabCG

É necessário as bibliotecas **glut** e **libjpeg** para linkar e rodar o jogo.
>sudo apt-get install freeglut3 freeglut3-dev libjpeg-dev

Em alguns computadores o uso do DOUBLE BUFFER do glut causa lentidão no jogo, e portanto, deixei desabilitado. Porém, se você desejar usá-lo, descomente a terceira linha do Makefile e compile o jogo novamente. A terceira linha do Makefile é esta:
>(...)
>#CFLAGS+=-D USE_GLUT_DOUBLE_BUFFERS
>(...)

