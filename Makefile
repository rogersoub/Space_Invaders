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

# Flags de compilação
CFLAGS = -I$(INCLUDE_DIR) -I$(SRC_DIR)/model -I$(SRC_DIR)/view -I$(SRC_DIR)/controller
LDFLAGS = -L$(LIB_DIR)

# Arquivo principal
TARGET = spaceinvaders

# Fontes
SRCS = $(SRC_DIR)/main.c \
       $(SRC_DIR)/model/model.c \
       $(SRC_DIR)/view/view.c \
       $(SRC_DIR)/controller/controller.c

# Objetos
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# Regra padrão
all: $(BIN_DIR)/$(TARGET).exe
	@echo "Build completo!"

# Linkagem final
$(BIN_DIR)/$(TARGET).exe: $(OBJS)
	$(CC) $^ -o $@ $(CFLAGS) $(LDFLAGS) $(LIBS)
	@echo "Compilado $(TARGET)!"

# Compilar objetos
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)
	@echo "Compilado $<"

# Limpeza
clean:
	rm -f $(BIN_DIR)/*.o
	rm -f $(BIN_DIR)/*.exe
	@echo "Limpou os arquivos!"

# Cópia das DLLs
copy-dll:
	copy $(DLL_DIR)\*.dll $(BIN_DIR)\
	@echo "DLLs copiadas!"