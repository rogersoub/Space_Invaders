Este é um tutorial de configuração para rodar o jogo Space Invaders presente neste repositório.
* Para mais detalhes de documentação, acesse: [https://docs.google.com/document/d/18AipTrMk75dzlWV2tXrqifVCf_wZC9PVuDAR6qJaluo/edit?usp=sharing](https://docs.google.com/document/d/18AipTrMk75dzlWV2tXrqifVCf_wZC9PVuDAR6qJaluo/edit?usp=sharing)

# Organização de pastas
~~~html
Space-Invaders/
├── bin/                (onde ficam os executáveis e .dll)
├── include/            (arquivos .h)
    └── allegro5/       (tudo do allegro)
├── lib/                (bibliotecas .a, caso use local)
├── src/                (arquivos .c)
├── assets/             (imagens, sons, fontes, etc.)
    ├── audio/          (sons)
    ├── document/       (documentação e record)
    ├── font/           (fontes)
    └── images/         (imagens)
        └── document    (imagens da documentação)
└── Makefile            (arquivo de build)
~~~


# Configuração Allegro Windows 10, jun 2025

1. Instalando MingW
2. Configurando Visual Studio Code
3. Instalando Allegro 
5. Rodando o Código 

## Instalando MingW
* Link da instalação: [https://winlibs.com/](https://winlibs.com/)
* Versão: GCC 14.2.0 Win64

#### 1. Extraia o aruivo compactado do dawload em C:
#### 2. Verifique se os arquivos makefile estão em **C:\msys64\ucrt64\bin** , copie o local da pasta
#### 3. Pesquise um aplicaitvo de Variávei de Ambiente
![Variaveis](/Assets/images/document/variaveisAmb1.png)
#### 4. Variáveis de Ambiente
![Variaveis](/Assets/images/document/variaveisAmb2.png)
#### 5. Clicar duas vezes no path
![Variaveis](/Assets/images/document/variaveisAmb3.png)
#### 6. Adicione como variável de ambiente clicando em "Novo" -> colcando o caminho **C:\msys64\ucrt64\bin** 
![Variaveis](/Assets/images/document/variaveisAmb4.png)

## Configurando Visual Studio Code

1. Clone o repositório com **git clone https://github.com/rogersoubr/Space_Invaders.git**
2. Entre no diretório que colocou o arquivo.

### Extenções:

##### Debugador de C:
![Extenção Makefile:](/Assets/images/document/exC1.png)

##### Compilador de C:
![Extenção Makefile:](/Assets/images/document/exC2.png)

##### Reconhece diferentes elementos do C e coloca cor:
![Extenção Makefile:](/Assets/images/document/exC3.png)

##### Compila C com o 'Run' do VS code:
![Extenção Makefile:](/Assets/images/document/exCompilerC.png)

##### Para ver cor no makefile:
![Extenção Makefile:](/Assets/images/document/exMakefile.png)


## Instalando Allegro
* Link do allegro: [https://github.com/liballeg/allegro5/releases/tag/5.2.10.1](https://github.com/liballeg/allegro5/releases/tag/5.2.10.1)
* Versão: allegro-x86_64-w64-mingw32-gcc-14.2.0-posix-seh-dynamic-5.2.10.0.zip
1. Extrair no C:

### Se não tiver arquivos em bin, lib e include no projeto: 
2. passar tudo de lib (**C:\allegro\lib**), para a pasta **lib do seu projeto**
3. passar tudo de bin (**C:\allegro\bin**), para a pasta **bin do seu projeto** 
4. passar tudo de include (**C:\allegro\include**), para a pasta **include do seu projeto** 

# Rodando o Código 
### Sempre abrir o diretório no aplicativo MSYS2

### Usando diretamente arquivo main.c
1. compilar com: **$ gcc src/main.c src/model.c src/view.c src/controller.c -o bin/spaceinvaders.exe -I. -Isrc -Iinclude -IC:/allegro/include -LC:/allegro/lib -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec**
2. Rodar com: **bin/spaceinvaders.exe**

## Rodando com makefile (correto)
1. abrir p MSYS2 e digitar:
2. Somente na primeira vez: **rm -f**
3. **make clean**
4. **make**
5. **make copy-dll**
6. **./bin/jogo.exe**


# Extras:
### Instalando Git no MSYS2: 
 * instalei o git com o comando:  **pacman -S git** 

### Arquivos do Space invaders: 
[https://classicgaming.cc/classics/space-invaders/](https://classicgaming.cc/classics/space-invaders/)

### Minha Playlis:
[https://www.youtube.com/watch?v=qF0W5mdhKhA&list=PL1QT-z6e-iYTxq5_Y2-TTkZsBYU9iNdwO](https://www.youtube.com/watch?v=qF0W5mdhKhA&list=PL1QT-z6e-iYTxq5_Y2-TTkZsBYU9iNdwO)

### Repositórios referência
* [https://github.com/narukaioh/Space-Invaders](https://github.com/narukaioh/Space-Invaders)

* [https://github.com/ld-wg/space-invaders.c](https://github.com/ld-wg/space-invaders.c)