# ===== 基本配置 =====
CC      := gcc
TARGET  := app                    # 最终可执行文件名（生成在项目根目录）
SRC_DIR := src
INC_DIR := include
OBJ_DIR := build

CFLAGS  := -std=c11 -O2 -Wall -Wextra -I$(INC_DIR)
LDFLAGS :=                         # 需要额外库的话填这里，如 -lm

# ===== 自动搜源文件并映射到目标文件 =====
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ===== 目标：默认构建 =====
.PHONY: all
all: $(TARGET)

# 链接：把所有 .o 链成可执行文件（放在根目录）
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# 编译规则：.c -> .o ，顺便生成依赖文件 .d
# -MMD -MP 让 make 自动追踪头文件依赖，头文件改动会触发重编
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# 确保 build 目录存在
$(OBJ_DIR):
	mkdir -p $@

# 包含依赖文件（如果存在）
-include $(DEPS)

# ===== 常用辅助目标 =====
.PHONY: clean run debug
clean:
	$(RM) -r $(OBJ_DIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

# 需要带调试信息编译时： make debug
debug: CFLAGS += -g -O0
debug: clean all

