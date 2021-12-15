BUILD_DIR= build
SRC_DIR = src
INC_DIR = inc
C_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(C_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)


all:main

$(BUILD_DIR)/%.o:$(SRC_DIR)/%.c  
	mkdir -p $(@D)
	$(CC) -O2 -Iinc -c $^ -o $@  

main:$(OBJS)
	$(CC) -O2 -g -o $@ $^ -lbcm2835 -li2c -lm -lpthread
clean:
	rm -rf $(BUILD_DIR) main 


