##
## EPITECH PROJECT, 2021
## B-OOP-400-TLS-4-1-tekspice-nassim.gharbaoui [WSL: Ubuntu]
## File description:
## Makefile
##

NAME = nanotekspice

BUILD_DIR = $(abspath ./build)

INSTALL_DIR = $(abspath .)

CMFLAGS = -DCMAKE_INSTALL_BINDIR='$(INSTALL_DIR)'

all: $(NAME)

clean:
	cd $(BUILD_DIR) && cmake --build . --target clean

fclean: clean
	$(RM) -r $(BUILD_DIR)
	$(RM) $(NAME)

re: fclean all

$(NAME): | $(BUILD_DIR)
	cd $(BUILD_DIR) \
	&& cmake $(CMFLAGS) .. \
	&& cmake --build . --target $(NAME) -- -j8 \
	&& cmake --install .

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: all clean fclean re
