CC = gcc
CFLAGS = -Wall -I./src
BIN_DIR = bin

all: $(BIN_DIR)/demo $(BIN_DIR)/test_csek

$(BIN_DIR)/demo: examples/demo.c src/csek.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ examples/demo.c src/csek.c

$(BIN_DIR)/test_csek: tests/test_csek.c src/csek.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ tests/test_csek.c src/csek.c

$(BIN_DIR)/chat: examples/chat.c src/csek.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ examples/chat.c src/csek.c

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(BIN_DIR)