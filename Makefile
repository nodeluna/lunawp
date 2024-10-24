CC = g++
STD = -std=c++23
INCLUDE_DIR = include
CFLAGS = -O1 -I$(INCLUDE_DIR) -Wall -Wextra -pedantic $(STD)
TARGET = lunawp
BUILD_DIR = build
SRC_DIR = src
PREFIX = /usr
INSTALL_DIR = $(PREFIX)/bin
MANPAGE_DIR = $(PREFIX)/share/man/man1
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
HEADERS := $(shell find $(INCLUDE_DIR) -name "*.h")
OBJS := $(patsubst src/%.cpp, build/%.o, $(SRCS))


ifneq ($(findstring clang++, $(CC)),)
        CFLAGS += $(CFLAGS) -D__cpp_concepts=202002L -Wno-builtin-macro-redefined -Wno-macro-redefined
endif


all: mkdir_build $(TARGET)

build/%.o : src/%.cpp
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(TARGET) : $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

mkdir_build:
	@for i in $(BUILD_DIR); do\
		if [ ! -f "$$i" ]; then\
			mkdir -p $$i;\
		fi;\
	done

clean:
	@for i in $(BUILD_DIR) $(TARGET); do\
		if [ -f "$$i" ] || [ -d "$$i" ]; then\
			rm -r "$$i";\
		fi;\
	done


install:
	$(info :: Installing $(TARGET))
	install -Dm755 $(TARGET) $(INSTALL_DIR)/$(TARGET)
	mkdir -p $(MANPAGE_DIR)/
	install -Dm644 man/$(TARGET).1 $(MANPAGE_DIR)/

uninstall:
	$(info :: Uninstalling $(TARGET))
	rm $(INSTALL_DIR)/$(TARGET)
	rm $(MANPAGE_DIR)/$(TARGET).1


cppcheck:
	$(info :: running static code analysis)
	$(info  )
	cppcheck --cppcheck-build-dir=build --std=c++23 --check-level=exhaustive\
		--suppress=unreadVariable --suppress=missingIncludeSystem --enable=all -I $(INCLUDE_DIR) $(SRC_DIR)


format:
	clang-format -i $(SRCS) $(HEADERS)

-include $(OBJS:.o=.d)
