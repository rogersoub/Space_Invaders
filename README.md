# MingW
* Link da instalação: https://winlibs.com/
* Versão: GCC 14.2.0 Win64

# Allegro
* Link do allegro: https://github.com/liballeg/allegro5/releases/tag/5.2.10.1
* Versão: allegro-x86_64-w64-mingw32-gcc-14.2.0-posix-seh-dynamic-5.2.10.0.zip
1. Extrair no C:
2. passar tudo de lib, bin e include para a pasta do seu projeto
3. coloca como variável de ambiente

# Rodando o Código usando arquivo main.c
### Exemplo 
1. compilar com: **gcc main.c -o bin\jogo.exe -IC:\allegro\include -LC:\allegro\lib -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec**
2. **.\bin\jogo.exe**

# Rodando com makefile
2. abrir p MSYS2 e digitar:
    2.1. Somente na primeira vez: **rm -f**
    2.2. **make**
    2.3. **./bin/jogo.exe**

# Extenções:
![Extenção Makefile:](Assets\images\document\exMakefile.png)

# Organização de pastas
Space-Invaders/
├── bin/              (onde ficam os executáveis e .dll)
├── include/          (arquivos .h)
├── lib/              (bibliotecas .a, caso use local)
├── src/              (arquivos .c)
├── assets/           (imagens, sons, fontes, etc.)
    └── document      (imagens da documentação)
└── Makefile          (arquivo de build)

# Usar Git no MSYS2
 * instalei o git com o comando:  **pacman -S git** 