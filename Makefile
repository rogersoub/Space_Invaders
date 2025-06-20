# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
BIN_DIR = bin
INCLUDE_DIR = include/allegro5
LIB_DIR = C:/allegro/lib
DLL_DIR = C:/allegro/bin

# Bibliotecas Allegro
LIBS = -lallegro -lallegro_main -lallegro_primitives -lallegro_image -lallegro_font -lallegro_ttf -lallegro_audio -lallegro_acodec

# Flags
CFLAGS = -I$(INCLUDE_DIR)
LDFLAGS = -L$(LIB_DIR)

# Lista de arquivos (adicione seus arquivos aqui sem extensão)
EXECUTABLES = base_allegro jogo invaders tela frogger pong teclado passaro_andante passaro_raivoso louco bouncer circles bola

# Geração de objetos (.o) automaticamente
OBJECTS = $(addprefix $(BIN_DIR)/, $(addsuffix .o, $(EXECUTABLES)))

# Regra padrão
all: $(addprefix $(BIN_DIR)/, $(addsuffix .exe, $(EXECUTABLES)))
	@echo "Build completo!"

# Como compilar cada .exe
$(BIN_DIR)/%.exe: $(BIN_DIR)/%.o
	$(CC) $< -o $@ $(LDFLAGS) $(LIBS)
	@echo "Compilado $@"

# Como gerar os .o a partir dos .c
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compilado $<"

# Space Invaders MVC
$(BIN_DIR)/spaceinvaders.exe: $(SRC_DIR)/main.c $(SRC_DIR)/model.c $(SRC_DIR)/view.c $(SRC_DIR)/controller.c
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
	@echo "Compilado spaceinvaders!"


# Limpeza dos objetos e executáveis
clean:
	rm -f $(BIN_DIR)\*.o
	rm -f $(BIN_DIR)\*.exe
	@echo "Limpou os arquivos!"

# Cópia automática das DLLs (opcional)
copy-dll:
	copy $(DLL_DIR)\*.dll $(BIN_DIR)\
	@echo "DLLs copiadas!"