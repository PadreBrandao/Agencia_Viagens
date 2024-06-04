
CC = gcc
CFLAGS = -Wall -g -I.
TARGET = programa
SRCS = src/main.c include/functions/getPassword.c include/functions/reserva.c include/functions/Voos.c include/functions/Hoteis.c include/functions/limparListas.c include/functions/ReservasUtils.c include/functions/utilizadores.c include/ficheiros/ficheiros.c include/ficheiros/adicionar.c include/ficheiros/utilizadores2.c 

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
