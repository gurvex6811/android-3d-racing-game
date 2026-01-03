# Android 3D Racing Game

Custom 3D racing car game engine built with OpenGL ES for Android.

## Features

- Custom game engine written in C++
- OpenGL ES 3.0 rendering
- Physics-based vehicle dynamics
- Touch controls
- 3D car models and track rendering

## Project Structure

```
android-3d-racing-game/
├── app/                    # Android application
│   ├── src/main/
│   │   ├── cpp/           # Native C++ engine code
│   │   ├── java/          # Java/Kotlin Android code
│   │   └── assets/        # Game assets
├── engine/                # Core game engine
│   ├── graphics/          # OpenGL ES renderer
│   ├── physics/           # Physics simulation
│   ├── math/              # Math utilities
│   └── core/              # Engine core systems
├── shaders/               # GLSL shaders
└── docs/                  # Documentation
```

## Build Requirements

- Android Studio Arctic Fox or later
- NDK r21 or later
- CMake 3.18+
- Android API 21+ (Lollipop)

## Building

```bash
git clone https://github.com/subhobhai943/android-3d-racing-game.git
cd android-3d-racing-game
# Open in Android Studio and build
```

## Development Status

🚧 **In Active Development** 🚧

- [x] Project structure
- [ ] OpenGL ES renderer
- [ ] Physics engine
- [ ] Vehicle controls
- [ ] Track system
- [ ] Game loop

## License

MIT License