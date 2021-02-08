##
## EPITECH PROJECT, 2021
## NanoTekSpice
## File description:
## Makefile automatically generated using Epine!
##

NAME = nanotekspice

all: nanotekspice
.PHONY: all

__NAME__SRCS := $(shell find -path './src/*.cpp')
__NAME__OBJS := $(filter %.cpp,$(__NAME__SRCS))
__NAME__OBJS := $(__NAME__OBJS:.cpp=.o)
__NAME__DEPS := $(__NAME__OBJS:.o=.d)
$(NAME) $(__NAME__OBJS):
$(NAME): CPPFLAGS :=
$(NAME): CPPFLAGS += -MD -MP
$(NAME): CPPFLAGS += -I./include
$(NAME): CXXFLAGS :=
$(NAME): CXXFLAGS += -Wall
$(NAME): CXXFLAGS += -Wextra
$(NAME): CXXFLAGS += $(if DEBUG,-g3)
$(NAME): LDLIBS :=
$(NAME): LDFLAGS :=
$(NAME): LDFLAGS += -L.
$(NAME): LDFLAGS += -Wl,-rpath .
$(NAME): $(__NAME__OBJS)
	@echo [binary] $@
	@$(CXX) -o $@ $(__NAME__OBJS) $(LDFLAGS) $(LDLIBS)
-include $(__NAME__DEPS)

%.o: %.c
	@echo [C] $@
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<
%.o: %.cpp
	@echo [C++] $@
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

tests_run: ./unit_tests
	./unit_tests $(ARGS)
.PHONY: tests_run

clean:
	$(RM) $(__NAME__DEPS) $(__NAME__OBJS)
.PHONY: clean

fclean: clean
	$(RM) $(NAME)
	$(RM) ./unit_tests
.PHONY: fclean

re: fclean all
.PHONY: re

run: $(NAME)
	@./$(NAME)
.PHONY: run
