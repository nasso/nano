##
## EPITECH PROJECT, 2021
## NanoTekSpice
## File description:
## Makefile automatically generated using Epine!
##

NAME = nanotekspice

all: nanotekspice
.PHONY: all

__NAME__SRCS := $(shell find -path './cli/src/*.cpp')
__NAME__OBJS := $(filter %.cpp,$(__NAME__SRCS))
__NAME__OBJS := $(__NAME__OBJS:.cpp=.o)
__NAME__DEPS := $(__NAME__OBJS:.o=.d)
$(NAME) $(__NAME__OBJS): libnts.a
$(NAME): CPPFLAGS :=
$(NAME): CPPFLAGS += -MD -MP
$(NAME): CPPFLAGS += -I./cli/include
$(NAME): CPPFLAGS += -I./nts/include
$(NAME): CXXFLAGS :=
$(NAME): CXXFLAGS += -Wall
$(NAME): CXXFLAGS += -Wextra
$(NAME): CXXFLAGS += $(if DEBUG,-g3)
$(NAME): LDLIBS :=
$(NAME): LDLIBS += -l:libnts.a
$(NAME): LDFLAGS :=
$(NAME): LDFLAGS += -L.
$(NAME): LDFLAGS += -Wl,-rpath .
$(NAME): $(__NAME__OBJS)
	@echo [binary] $@
	@$(CXX) -o $@ $(__NAME__OBJS) $(LDFLAGS) $(LDLIBS)
-include $(__NAME__DEPS)

libnts_a_SRCS := $(shell find -path './nts/src/*.cpp')
libnts_a_OBJS := $(filter %.cpp,$(libnts_a_SRCS))
libnts_a_OBJS := $(libnts_a_OBJS:.cpp=.o)
libnts_a_DEPS := $(libnts_a_OBJS:.o=.d)
libnts.a $(libnts_a_OBJS):
libnts.a: CPPFLAGS :=
libnts.a: CPPFLAGS += -MD -MP
libnts.a: CPPFLAGS += -I./nts/include
libnts.a: CXXFLAGS :=
libnts.a: CXXFLAGS += -Wall
libnts.a: CXXFLAGS += -Wextra
libnts.a: CXXFLAGS += $(if DEBUG,-g3)
libnts.a: $(libnts_a_OBJS)
	@echo [static] $@
	@$(AR) rc $@ $(libnts_a_OBJS)
-include $(libnts_a_DEPS)

unit_tests_SRCS := $(shell find -path './tests/*.cpp')
unit_tests_OBJS := $(filter %.cpp,$(unit_tests_SRCS))
unit_tests_OBJS := $(unit_tests_OBJS:.cpp=.o)
unit_tests_DEPS := $(unit_tests_OBJS:.o=.d)
unit_tests $(unit_tests_OBJS): libnts.a
unit_tests: CPPFLAGS :=
unit_tests: CPPFLAGS += -MD -MP
unit_tests: CPPFLAGS += -I./include
unit_tests: CPPFLAGS += -I./nts/include
unit_tests: CXXFLAGS :=
unit_tests: CXXFLAGS += -Wall
unit_tests: CXXFLAGS += -Wextra
unit_tests: CXXFLAGS += $(if DEBUG,-g3)
unit_tests: LDLIBS :=
unit_tests: LDLIBS += -lcriterion
unit_tests: LDLIBS += -l:libnts.a
unit_tests: LDFLAGS :=
unit_tests: LDFLAGS += -L.
unit_tests: LDFLAGS += -Wl,-rpath .
unit_tests: $(unit_tests_OBJS)
	@echo [binary] $@
	@$(CXX) -o $@ $(unit_tests_OBJS) $(LDFLAGS) $(LDLIBS)
-include $(unit_tests_DEPS)

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
	$(RM) $(__NAME__DEPS) $(__NAME__OBJS) $(libnts_a_DEPS) $(libnts_a_OBJS) $(unit_tests_DEPS) $(unit_tests_OBJS)
.PHONY: clean

fclean: clean
	$(RM) $(NAME) libnts.a unit_tests
	$(RM) ./unit_tests
.PHONY: fclean

re: fclean all
.PHONY: re

run: $(NAME)
	@./$(NAME) $(ARGS)
.PHONY: run
