PROGRAM_NAME = maxSocket
CODE_DIRECTORY = ../../Code
LIBRARIES_DIRECTORY = ../../Libraries
CXX_SRCS = \
	$(CODE_DIRECTORY)/Common/Buffer.cpp \
	$(CODE_DIRECTORY)/Linux/Socket.cpp \
	$(CODE_DIRECTORY)/Common/IP/Address.cpp \
	$(CODE_DIRECTORY)/../Tests/UnitTests.cpp \
	$(CODE_DIRECTORY)/Linux/SocketSystem.cpp \
	$(CODE_DIRECTORY)/Linux/LinuxAddressVersion4Policy.cpp \
	$(CODE_DIRECTORY)/Linux/LinuxAddressVersion6Policy.cpp
CXX_OBJS = $(CXX_SRCS:.cpp=.o)
INCLUDE_PATHS = \
	$(CODE_DIRECTORY)/Common \
	$(CODE_DIRECTORY)/Common/Include \
	$(CODE_DIRECTORY)/Linux \
	$(CODE_DIRECTORY)/Linux/Include \
	$(LIBRARIES_DIRECTORY)
	
INCLUDE_PATHS_FLAGS = $(foreach d, $(INCLUDE_PATHS), -I$d)



CPPFLAGS += $(INCLUDE_PATHS_FLAGS) -std=c++14 -Wall -DNO_PRECOMPILED_HEADER


CLANG_COMPILER_FLAGS =
CLANG = clang++
CLANG_LINKER_FLAGS =

GCC_COMPILER_FLAGS =
GCC = g++
GCC_LINKER_FLAGS =

COMPILER = $(CLANG)


ifeq ($(COMPILER),$(GCC))
	CPPFLAGS += $(GCC_COMPILER_FLAGS)
	LINKER_FLAGS += $(GCC_LINKER_FLAGS)
endif
ifeq ($(COMPILER),$(CLANG))
	CPPFLAGS += $(CLANG_COMPILER_FLAGS)
	LINKER_FLAGS += $(CLANG_LINKER_FLAGS)
endif




all: $(PROGRAM_NAME)

$(PROGRAM_NAME): $(PCH_OBJS) $(CXX_OBJS)
	$(COMPILER) -g $(CXX_OBJS) -o $(PROGRAM_NAME) $(LINKER_FLAGS)

.cpp.o:
	$(COMPILER) -g $(CPPFLAGS) -c $< -o $@

clean:
	@- $(RM) $(PROGRAM_NAME)
	@- $(RM) $(CXX_OBJS)

distclean: clean
