# Android 3D Racing Game

Custom 3D racing car game engine built with OpenGL ES for Android.

## Assets Status

**Car Models:** 4 validated glTF models (12KB - 3.7MB each)
**Track Models:** 2 environment models
**Textures:** Multiple car and track textures
**Launcher Icons:** Adaptive icons with vector drawables

All assets verified as proper glTF binary format.

## Features

- Custom game engine written in C++17
- OpenGL ES 3.0 rendering with Phong lighting
- Physics-based vehicle dynamics (acceleration, braking, steering)
- Touch controls with split-screen input (left = steer, right = gas/brake)
- 3D car model rendering via glTF 2.0 binary parser
- Procedural oval track with barriers and collision detection
- Checkpoint and lap tracking system
- Game state machine (Menu, Racing, Paused, Finished)
- HUD overlay (speed, lap counter, race timer)
- Audio engine bridge (SoundPool-based)
- Chase camera with smooth follow
- Vector3, Quaternion, Matrix4 math library
- Texture loading pipeline (PNG/JPEG)
- Racing-themed launcher icon

## Project Structure

```
android-3d-racing-game/
├── app/
│   ├── src/main/
│   │   ├── cpp/                    # JNI bridge (Java ↔ C++)
│   │   ├── java/com/racing/engine/ # Android Activity, Renderer, Audio
│   │   ├── assets/                 # Game assets (glTF models, textures)
│   │   └── res/                    # Android resources (icons, strings)
│   └── build.gradle
├── engine/                         # C++ game engine
│   ├── core/                       # Engine, Track, game state management
│   ├── graphics/                   # Renderer, Shader, Mesh, Camera, TextureLoader
│   ├── physics/                    # Vehicle dynamics
│   ├── math/                       # Vector3, Quaternion, Matrix4
│   ├── assets/                     # AssetLoader, glTFLoader
│   └── audio/                      # AudioEngine (JNI bridge to SoundPool)
├── shaders/                        # GLSL vertex/fragment shaders
├── CMakeLists.txt                  # CMake build for native code
└── .github/workflows/              # CI/CD automation
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

Open in Android Studio, wait for Gradle sync, then click **Run**.

### Command Line Build

```bash
# Build debug APK
./gradlew assembleDebug

# Install on connected device
./gradlew installDebug

# Run tests
./gradlew test
```

### Controls

- **Left side of screen:** Steer (top = left, bottom = right)
- **Right side top:** Accelerate
- **Right side bottom:** Brake
- **Tap screen:** Start race / Restart after finish

## Development Status

All core features are implemented and functional.

- [x] Project structure and build system
- [x] Gradle build configuration (AGP 8.2)
- [x] CMake native build setup
- [x] 3D assets (validated glTF models)
- [x] Launcher icons (adaptive + vector)
- [x] OpenGL ES 3.0 setup
- [x] Physics engine foundation
- [x] JNI bridge (Java ↔ C++)
- [x] Complete renderer implementation
- [x] Model loading (glTF parser)
- [x] Vehicle controls and input
- [x] Track/level system
- [x] Game loop and state management
- [x] UI and menus (HUD overlay)
- [x] Audio system
- [ ] Multiplayer/leaderboards (future)

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
- **Shading:** Phong lighting model (ambient + diffuse + specular)
- **Shader compilation:** Embedded GLSL ES 300 shaders
- **Model format:** glTF 2.0 binary (glB) with accessor/bufferView parsing
- **Textures:** PNG/JPEG loading with fallback solid colors
- **Rendering:** VAO/VBO/EBO mesh pipeline, draw call batching

### Physics
- Velocity-based vehicle dynamics with steering rotation
- Max speed enforcement (80 units)
- Drag and ground friction simulation
- AABB collision detection against track barriers

### Game Loop
- Fixed-timestep delta clamping (max 50ms)
- State machine: MENU → RACING → PAUSED / FINISHED
- Checkpoint-based lap counting (3 laps per race)

### Camera
- Third-person chase camera with configurable distance and height
- Smooth interpolation (lerp) follow with adjustable smoothness

### Performance
- Target: 60 FPS on high-end, 30 FPS on mid-range
- Delta time clamping to prevent physics explosion
- Efficient GL state management

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

**Built with C++, OpenGL ES, and Android NDK**
