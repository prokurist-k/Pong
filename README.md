# Pong

A Pong implementation written in C++20 using SDL2.

The project started as an experiment with Data-Oriented Design, focusing on memory layout and CPU cache behavior rather than traditional object-oriented programming.

### Architecture

- Entity-component system
- Separate component pools
- Systems for input, movement, collision detection and rendering
- Entity management through Ids and component signatures

### Dependencies

- SDL2
- Dear ImGui
- miniaudio

### Build

Built using CMake and C++20.
