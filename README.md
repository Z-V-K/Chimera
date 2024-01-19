
# Chimera

A league of legends scripting platform started in 2021.

## Contents

### Core
The main part of the application. It contains:
- Rebuilt game structures in Framework dir
- Addresses and offsets in Addresses dir
- Hooks, callbacks, bypasses, UI and other helper functions for SDK in Impl dir
- Interface with external plugins made in C++ and LUA in SDK dir

### Core Plugin
The scripting core of the application. It contains all the features needed to help the player achieve better performance than legit players.

### Core LUA
The LUA documentation for the [EmmyLua](https://github.com/EmmyLua) plugin for the LUA SDK.

## Build
### Core
Build using vs2022 tools with C++20 standard.

### Core Plugin
Build using LLVM with C++20 standard.