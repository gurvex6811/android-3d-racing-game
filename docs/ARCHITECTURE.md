# Architecture

## Engine Components

### Core Engine
- **Engine.cpp/h**: Main engine class managing initialization, game loop
- **GameLoop**: Fixed timestep for physics, variable for rendering

### Graphics System
- **Shader.cpp/h**: GLSL shader loading and management
- **Renderer**: OpenGL ES 3.0 rendering pipeline
- **Camera**: Third-person follow camera system
- **Mesh**: 3D model loading and rendering

### Physics Engine
- **Vehicle.cpp/h**: Vehicle dynamics and controls
- **Collision**: Bounding box and mesh collision detection
- **RigidBody**: Mass, velocity, acceleration simulation

### Math Library
- **Matrix4.h**: 4x4 matrix operations
- **Vector3/4**: Vector math utilities
- **Quaternion**: Rotation calculations

## Rendering Pipeline

1. Clear buffers (color + depth)
2. Update camera matrices (view, projection)
3. Render track geometry
4. Render vehicles with lighting
5. Render UI overlay
6. Swap buffers

## Game Loop

```
while (running) {
    handleInput();
    updatePhysics(deltaTime);
    updateGameLogic(deltaTime);
    render();
}
```

## Asset Management

- Models: GLTF/OBJ format
- Textures: PNG compressed to ETC2
- Shaders: GLSL ES 3.0
- Audio: OGG Vorbis

## Performance Targets

- 60 FPS on high-end devices
- 30 FPS on mid-range devices
- Max 50MB RAM usage
- < 100MB APK size