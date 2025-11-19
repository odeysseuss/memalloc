cc := clang
cflags := -std=c11 -Wall -Wextra -pedantic -MMD -MP
incdir := -Iinclude
objdir := build/obj

srcs := $(wildcard src/*.c)
objs := $(srcs:src/%.c=$(objdir)/%.o)
deps := $(srcs:src/%.c=$(objdir)/%.d)
exec := build/memalloc

-include $(deps)

all: $(exec)

run: $(exec)
	./$(exec)

$(exec): $(objs)
	$(cc) $^ -o $@

$(objdir)/%.o: src/%.c | $(objdir)
	$(cc) $(cflags) $(incdir) -c $< -o $@

$(objdir):
	mkdir -p $@

clean:
	rm -rf $(exec) $(objdir)
