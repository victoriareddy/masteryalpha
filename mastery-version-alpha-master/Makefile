# Compiler and flags
CC = gcc
CFLAGS = -Wall
DEBUG_FLAGS = -g -DDEBUG

#dirs
OUTPUT_DIR = outputs
BIN_DIR = bin

# Source and object files
SRC = trie.c
READABLE_OBJ = $(BIN_DIR)/trie.o
OBJ = $(BIN_DIR)/main.o $(BIN_DIR)/parser.o $(BIN_DIR)/util.o
EXEC = $(BIN_DIR)/second_trie
REFERENCE_EXEC = trie_ref

#default target doesnt do anything
default: 
	echo "oops read the makefile!"

# stitch - generates the executable and the bin dir. PLEASE PLEASE PLEASE DO NOT DELETE BIN
stitch: $(BIN_DIR) $(READABLE_OBJ)
	$(CC) $(OBJ) $(READABLE_OBJ) -o $(EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Pattern rule for compiling .c files into .o files
$(BIN_DIR)/%.o: %.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Debug target (compiles with debug flags)
lilo: CFLAGS += $(DEBUG_FLAGS)
lilo: stitch

# Checks all outputs for all test cases
pleakley: stitch
	@for testfile in testcases/*; do \
		echo "Running $$testfile..."; \
		./$(EXEC) -w $$testfile; \
	done

# compare target compares output with trie_ref
nani: stitch
	@mkdir -p $(OUTPUT_DIR)
	@for testfile in testcases/*; do \
		base_name=$$(basename $$testfile); \
		./$(EXEC) -w $$testfile > $(OUTPUT_DIR)/$$base_name.out; \
		./$(REFERENCE_EXEC) -w $$testfile > $(OUTPUT_DIR)/$$base_name.ref; \
		out_tmp=$$(mktemp); \
		ref_tmp=$$(mktemp); \
		tr -d '\n' < $(OUTPUT_DIR)/$$base_name.out > $$out_tmp; \
		tr -d '\n' < $(OUTPUT_DIR)/$$base_name.ref > $$ref_tmp; \
		if diff $$out_tmp $$ref_tmp > /dev/null; then \
			echo "✅ PASSED $$testfile"; \
		else \
			echo "❌ FAILED $$testfile"; \
			echo "Diff (ignoring newlines):"; \
			diff $$out_tmp $$ref_tmp; \
		fi; \
		rm -f $$out_tmp $$ref_tmp; \
	done


# Clean target to remove compiled files DO NOT REMOVE THE SUPPLIED .o FILES
cobra:
	rm -f $(EXEC) $(READABLE_OBJ)
