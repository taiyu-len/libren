CXX:=g++
LINK.o=$(LINK.cc)
override CXXFLAGS += -std=c++17 -Wall -Wextra -Werror

ifeq (1, 1)
  override CXXFLAGS += -g1 -fsanitize=address,undefined
else
  override CXXFLAGS += -O3
  override CPPFLAGS += -DNDEBUG
endif

ren_test: -ldoctest -lren
