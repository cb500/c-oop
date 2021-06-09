# c-oop
This repo is just for fun while playing with some OOP constructions in C. As it is not intended to be of any OOP reference of implementation it is still useful to review some concepts like pointer to functions (callbacks), polymorphism, lazy call, etc.

## Dependencies
I use *Block Type*[1] here, so this project depends on:
- clang >= 12 (It may work with older version but was tested with clang version 12.0.0 on OpenSuse)
- libBlocksRuntime
- libdispatch
- libdispatch-devel

*NOTE*: For whatever reason that I'm not willing to investigate the above libs didn't update my "pkg-config" configuration and I had to add it on the Makefile manually. You may need to review bot *CFLAG_BLOCKS* and *LDFLAGS* to adjust accordingly to your setup :\

[1] https://clang.llvm.org/docs/BlockLanguageSpec.html