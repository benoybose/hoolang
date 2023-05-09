# set(LLVM_LINK_COMPONENTS
#   Core
#   OrcJIT
#   Support
#   nativecodegen
#   )

ADD_EXECUTABLE (HowToUseLLJIT HowToUseLLJIT.cpp)
TARGET_LINK_LIBRARIES (HowToUseLLJIT LLVM)
