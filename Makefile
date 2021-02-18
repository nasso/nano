##
## EPITECH PROJECT, 2021
## B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
## File description:
## Makefile
##

NAME = nanotekspice

TESTS_BIN = unit_tests

BUILD_DIR = build

INSTALL_DIR = $(abspath .)

CMFLAGS = -DCMAKE_INSTALL_BINDIR='$(INSTALL_DIR)'

MAKEFLAGS += --no-print-directory

all: | $(BUILD_DIR)
	cd $(BUILD_DIR) \
	&& cmake $(CMFLAGS) .. \
	&& cmake --build . --target $(NAME) \
	&& cmake --install .

clean:
	if [ -d "$(BUILD_DIR)" ]; then \
		cd "$(BUILD_DIR)" && cmake --build . --target clean; \
	fi

fclean: clean
	$(RM) -r $(BUILD_DIR)
	$(RM) $(NAME)
	$(RM) $(TESTS_BIN)

tests_run: | $(BUILD_DIR)
	cd $(BUILD_DIR) \
	&& cmake $(CMFLAGS) .. \
	&& cmake --build . --target $(TESTS_BIN) \
	&& cmake --install . --component tests
	./$(TESTS_BIN)

re: fclean all

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean fclean tests_run re
