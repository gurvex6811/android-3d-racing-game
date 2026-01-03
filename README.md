# Android 3D Racing Game

Custom 3D racing car game engine built with OpenGL ES for Android.

## ✅ Assets Status

**Car Models:** 4 validated glTF models (12KB - 3.7MB each)  
**Track Models:** 2 environment models  
**Textures:** Multiple car and track textures  

All assets verified as proper glTF binary format (not HTML).

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
│   │   └── assets/        # Game assets (models, textures)
├── engine/                # Core game engine
│   ├── graphics/          # OpenGL ES renderer
│   ├── physics/           # Physics simulation
│   ├── math/              # Math utilities
│   └── core/              # Engine core systems
├── shaders/               # GLSL shaders
└── docs/                  # Documentation
```

## Build Requirements

- Android Studio Hedgehog or later
- NDK r25 or later
- CMake 3.18+
- Android API 21+ (Lollipop)
- JDK 17

## Building

### Using Android Studio (Recommended)

```bash
git clone https://github.com/subhobhai943/android-3d-racing-game.git
cd android-3d-racing-game
# Open in Android Studio and build
```

### Command Line

```bash
# Build project
./gradlew build

# Build APK
./gradlew assembleDebug

# Install on device
./gradlew installDebug
```

## Development Status

🚧 **In Active Development** 🚧

- [x] Project structure
- [x] Gradle build system
- [x] 3D assets (validated glTF models)
- [x] OpenGL ES setup
- [x] Physics engine foundation
- [ ] Complete renderer implementation
- [ ] Vehicle controls
- [ ] Track system
- [ ] Game loop
- [ ] UI and menus

## Automated Workflows

### Asset Management
- **Download Real 3D Assets** - Validated glTF downloads with format checking
- **Android CI** - Automated builds and APK generation

Run workflows from the [Actions tab](https://github.com/subhobhai943/android-3d-racing-game/actions).

## Documentation

- [Getting Started](docs/GETTING_STARTED.md)
- [Architecture](docs/ARCHITECTURE.md)
- [Asset Management](docs/ASSETS.md)
- [Asset Fix Guide](docs/FIX_ASSETS.md)
- [Contributing](CONTRIBUTING.md)

## License

MIT License

## Assets License

- Models: CC0 (Khronos glTF Sample Models)
- Textures: MIT (Three.js examples)
