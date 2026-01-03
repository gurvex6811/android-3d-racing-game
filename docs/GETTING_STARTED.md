# Getting Started

## Prerequisites

- Android Studio Hedgehog or later
- Android NDK r25 or later
- CMake 3.18+
- Git

## Setup

1. **Clone the repository**
```bash
git clone https://github.com/subhobhai943/android-3d-racing-game.git
cd android-3d-racing-game
```

2. **Open in Android Studio**
- File → Open → Select project folder
- Wait for Gradle sync
- Download NDK if prompted

3. **Build the project**
```bash
./gradlew build
```

4. **Run on device/emulator**
- Connect Android device or start emulator
- Click Run button or use: `./gradlew installDebug`

## Development Workflow

### Engine Code (C++)

Modify files in `engine/` directory:
```
engine/
├── core/       # Engine core systems
├── graphics/   # Rendering code
├── physics/    # Physics simulation
└── math/       # Math utilities
```

After changes, rebuild native code:
```bash
./gradlew :app:externalNativeBuildDebug
```

### Shaders

Edit GLSL shaders in `shaders/` directory. Changes take effect on next build.

### Android Integration

Java/Kotlin code in `app/src/main/java/`. Handles:
- OpenGL surface creation
- Touch input
- Audio playback
- UI overlays

## Testing

```bash
# Run unit tests
./gradlew test

# Run on connected device
./gradlew connectedAndroidTest
```

## Debugging

### Native Code
1. Set breakpoints in C++ files
2. Run → Debug 'app'
3. Android Studio will attach LLDB debugger

### Logs
```bash
# View engine logs
adb logcat -s RacingEngine

# View all logs
adb logcat
```

## Next Steps

1. Implement mesh loading system
2. Add texture support
3. Create simple track geometry
4. Implement touch controls
5. Add camera following vehicle