# Android 3D Racing Game

Custom 3D racing car game engine built with OpenGL ES for Android.

## ✅ Assets Status

**Car Models:** 4 validated glTF models (12KB - 3.7MB each)  
**Track Models:** 2 environment models  
**Textures:** Multiple car and track textures  
**Launcher Icons:** Adaptive icons with vector drawables

All assets verified as proper glTF binary format.

## Features

- 🏎️ Custom game engine written in C++
- 🎨 OpenGL ES 3.0 rendering
- ⚡ Physics-based vehicle dynamics
- 🕹️ Touch controls
- 🚗 3D car models and track rendering
- 🎨 Racing-themed launcher icon

## Project Structure

```
android-3d-racing-game/
├── app/
│   ├── src/main/
│   │   ├── cpp/              # Native C++ engine (JNI bridge)
│   │   ├── java/             # Java Android code
│   │   ├── assets/           # Game assets (models, textures)
│   │   └── res/              # Android resources (icons, strings)
│   └── build.gradle
├── engine/               # C++ game engine
│   ├── core/             # Engine core (initialization, loop)
│   ├── graphics/         # OpenGL ES renderer, shaders
│   ├── physics/          # Vehicle physics simulation
│   └── math/             # Matrix, vector math
├── shaders/              # GLSL vertex/fragment shaders
├── CMakeLists.txt        # CMake build for native code
└── .github/workflows/    # CI/CD automation
```

## Build Requirements

- **Android Studio:** Hedgehog (2023.1.1) or later
- **NDK:** r26.1.10909125 or later
- **CMake:** 3.22.1+
- **JDK:** 17
- **Android API:** 21+ (Lollipop) minimum, 34 target
- **Gradle:** 8.2

## Quick Start

### Using Android Studio (Recommended)

```bash
git clone https://github.com/subhobhai943/android-3d-racing-game.git
cd android-3d-racing-game
```

Open in Android Studio, wait for Gradle sync, then click **Run** (▶️).

### Command Line Build

```bash
# Build debug APK
./gradlew assembleDebug

# Install on connected device
./gradlew installDebug

# Run tests
./gradlew test
```

## Development Status

🚧 **In Active Development** 🚧

- [x] Project structure and build system
- [x] Gradle build configuration (AGP 8.2)
- [x] CMake native build setup
- [x] 3D assets (validated glTF models)
- [x] Launcher icons (adaptive + vector)
- [x] OpenGL ES 3.0 setup
- [x] Physics engine foundation
- [x] JNI bridge (Java ↔ C++)
- [ ] Complete renderer implementation
- [ ] Model loading (glTF parser)
- [ ] Vehicle controls and input
- [ ] Track/level system
- [ ] Game loop and state management
- [ ] UI and menus
- [ ] Audio system
- [ ] Multiplayer/leaderboards

## Automated Workflows

Run from [Actions tab](https://github.com/subhobhai943/android-3d-racing-game/actions):

1. **Android CI** - Builds APK with NDK, runs tests, uploads artifacts
2. **Download Real 3D Assets** - Validated glTF model downloads
3. **Generate Launcher Icons** - Creates PNG icons for all densities

## Documentation

- [Getting Started](docs/GETTING_STARTED.md) - Setup and first build
- [Architecture](docs/ARCHITECTURE.md) - Engine design overview
- [Asset Management](docs/ASSETS.md) - Working with 3D models
- [Asset Fix Guide](docs/FIX_ASSETS.md) - Troubleshooting assets
- [Contributing](CONTRIBUTING.md) - How to contribute

## Technical Details

### Graphics
- **API:** OpenGL ES 3.0
- **Shading:** Phong lighting model
- **Formats:** glTF 2.0 for models, PNG/JPEG for textures

### Physics
- Custom rigid body dynamics
- Vehicle suspension simulation
- Collision detection (AABB + mesh)

### Performance
- Target: 60 FPS on high-end, 30 FPS on mid-range
- LOD system for distant objects
- Texture compression (ETC2)
- Draw call batching

## License

MIT License - See [LICENSE](LICENSE) for details

## Assets License

- **3D Models:** CC0 (Khronos glTF Sample Models)
- **Textures:** MIT (Three.js examples)
- **Launcher Icon:** Original design, MIT

## Contributing

Contributions welcome! See [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines.

## Support

Found a bug? [Open an issue](https://github.com/subhobhai943/android-3d-racing-game/issues)

---

**Built with ❤️ using C++, OpenGL ES, and Android NDK**