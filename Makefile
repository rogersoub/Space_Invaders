# Arquivo: Makefile

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
BIN_DIR = bin
# O INCLUDE_DIR abaixo não é usado diretamente nas flags, mas sim para referência da pasta de headers Allegro
ALLEGRO_INCLUDE_DIR = C:/allegro/include 
ALLEGRO_LIB_DIR = C:/allegro/lib
ALLEGRO_DLL_DIR = C:/allegro/bin

# Bibliotecas Allegro
# Certifique-se de que todas as bibliotecas Allegro que você usa estão listadas aqui.
# Se você tiver problemas de linkagem, verifique se está usando todas as necessárias.
LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

# Flags de compilação
# -I. adiciona o diretório atual (onde está o Makefile) aos caminhos de busca de inclusão
# -I$(SRC_DIR) adiciona o diretório src aos caminhos de busca de inclusão
# -Iinclude adiciona o diretório include aos caminhos de busca de inclusão
# -I$(ALLEGRO_INCLUDE_DIR) adiciona o diretório de inclusão do Allegro
CFLAGS = -I. -I$(SRC_DIR) -Iinclude -I$(ALLEGRO_INCLUDE_DIR)

# Flags de linkagem
# -L$(ALLEGRO_LIB_DIR) adiciona o diretório das bibliotecas do Allegro
LDFLAGS = -L$(ALLEGRO_LIB_DIR)

# Arquivo executável de saída
TARGET = spaceinvaders

# Fontes (arquivos .c do seu projeto)
# Assumimos que model.c, view.c, controller.c e main.c estão diretamente em src/
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/model.c \
       $(SRC_DIR)/view.c \
       $(SRC_DIR)/controller.c

# Objetos (arquivos .o gerados a partir dos .c)
# Substitui a extensão .c por .o e muda o diretório de src/ para bin/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))

# Regra padrão: compila e linka tudo
all: $(BIN_DIR)/$(TARGET).exe
	@echo "Build completo!"

# Regra para linkar o executável final
$(BIN_DIR)/$(TARGET).exe: $(OBJS)
	@mkdir -p $(BIN_DIR) # Garante que o diretório bin existe
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
	@echo "Compilado $(TARGET)!"

# Regra para compilar cada arquivo .c em um arquivo .o
# $< é o nome do arquivo .c que está sendo compilado
# $@ é o nome do arquivo .o de saída
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) # Garante que o diretório de saída para o .o existe
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compilado $<"

# Regra de limpeza: remove todos os arquivos .o e .exe
clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
	@echo "Limpou os arquivos!"

# Regra para copiar as DLLs do Allegro para o diretório bin/
copy-dll:
	# Use 'copy' para Windows CMD/MinGW ou 'cp' para Linux/WSL
	# Certifique-se de que o caminho das DLLs esteja correto para sua instalação do Allegro
	copy $(ALLEGRO_DLL_DIR)\*.dll $(BIN_DIR)\
	@echo "DLLs copiadas!"