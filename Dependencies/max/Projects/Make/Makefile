PROGRAM_NAME = max
CODE_DIRECTORY = ../../Code/TranslationUnits
CXX_SRCS = \
	$(CODE_DIRECTORY)/Hardware/CPU/CPUIDPolicies/GCCAssemblyCPUIDPolicy.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/IsCPUIDAvailablePolicies/GCCAssemblyIsCPUIDAvailablePolicy.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/GCC/MakeCPUID.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/Associativity.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/CacheInfo.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/CacheLevel.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/CPUID.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/CPUIDSubleafArgumentsAndResult.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/Prefetch.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/TLB.cpp \
	$(CODE_DIRECTORY)/Hardware/CPU/TraceCache.cpp \
	$(CODE_DIRECTORY)/Logging/DoNothingLogger.cpp \
	$(CODE_DIRECTORY)/Testing/Test.cpp \
	$(CODE_DIRECTORY)/Testing/TestSuite.cpp
CXX_OBJS = $(CXX_SRCS:.cpp=.o)

INCLUDE_PATHS = \
	$(CODE_DIRECTORY)/../Include
INCLUDE_PATHS_FLAGS = $(foreach d, $(INCLUDE_PATHS), -I$d)

LIBRARY_PATHS = \
	.
LIBRARY_PATHS_FLAGS = $(foreach d, $(LIBRARY_PATHS), -L$d)

AUTOMATED_TEST_CODE_DIRECTORY = ../../Code/AutomatedTests
AUTOMATED_TEST_CXX_SRCS = \
	$(AUTOMATED_TEST_CODE_DIRECTORY)/IsBetweenTest.cpp \
	$(AUTOMATED_TEST_CODE_DIRECTORY)/RangeTest.cpp \
	$(AUTOMATED_TEST_CODE_DIRECTORY)/EntryPoint.cpp
AUTOMATED_TEST_CXX_OBJS = $(AUTOMATED_TEST_CXX_SRCS:.cpp=.o)

MANUAL_TEST_CODE_DIRECTORY = ../../Code/ManualTests
MANUAL_TEST_CXX_SRCS = \
	$(MANUAL_TEST_CODE_DIRECTORY)/AliasingOptimizationsTest.cpp \
	$(MANUAL_TEST_CODE_DIRECTORY)/EntryPoint.cpp
MANUAL_TEST_CXX_OBJS = $(MANUAL_TEST_CXX_SRCS:.cpp=.o)

CPPFLAGS += $(INCLUDE_PATHS_FLAGS) -std=c++14 -Wall
LINKER_FLAGS += $(LIBRARY_PATHS_FLAGS)

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




all: lib$(PROGRAM_NAME).a maxAutomatedTests maxManualTests

lib$(PROGRAM_NAME).a: $(PCH_OBJS) $(CXX_OBJS)
	ar rcs lib$(PROGRAM_NAME).a $(CXX_OBJS)

maxAutomatedTests: $(AUTOMATED_TEST_CXX_OBJS)
	$(COMPILER) -g $(AUTOMATED_TEST_CXX_OBJS) $(LINKER_FLAGS) -l$(PROGRAM_NAME) -o maxAutomatedTests

maxManualTests: $(MANUAL_TEST_CXX_OBJS)
	$(COMPILER) -g $(MANUAL_TEST_CXX_OBJS) $(LINKER_FLAGS) -l$(PROGRAM_NAME) -o maxManualTests
.cpp.o:
	$(COMPILER) -g $(CPPFLAGS) -c $< -o $@

clean:
	@- $(RM) lib$(PROGRAM_NAME).a
	@- $(RM) $(CXX_OBJS)
	@- $(RM) maxAutomatedTests
	@- $(RM) $(AUTOMATED_TEST_CXX_OBJS)
	@- $(RM) maxManualTests
	@- $(RM) $(MANUAL_TEST_CXX_OBJS)

distclean: clean
