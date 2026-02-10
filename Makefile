CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -g

# Arch Linux Boost paths
BOOST_INC = /usr/include/boost
BOOST_LIB = /usr/lib

BOOST_LIBS = -lboost_program_options -lboost_filesystem -lboost_json -lpthread -lssl -lcrypto

BIN_DIR = bin
OBJ_DIR = obj
SRCS = src/wttrbar.cpp src/cli.cpp src/lang.cpp src/utils.cpp
OBJS = $(SRCS:src/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN_DIR)/wttrbar

$(BIN_DIR)/wttrbar: $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -L$(BOOST_LIB) $(OBJS) -o $(BIN_DIR)/wttrbar $(BOOST_LIBS)

$(OBJ_DIR)/%.o: src/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(BOOST_INC) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

.PHONY: clean release
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)


release: CXXFLAGS = -std=c++20 -Wall -Wextra -O3
release:
	$(MAKE) clean
	$(MAKE) all CXXFLAGS='-std=c++20 -Wall -Wextra -O3'
	strip $(BIN_DIR)/wttrbar

.PHONY: install
install: $(BIN_DIR)/wttrbar
	mkdir -p $(HOME)/.local/bin
	cp $(BIN_DIR)/wttrbar $(HOME)/.local/bin/