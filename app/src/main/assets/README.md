# Game Assets

## 3D Models

All 3D models are in glTF 2.0 format (.glb) for optimal mobile performance.

### Cars
- `sports_car.glb` - Modern sports racing car
- `formula_car.glb` - Formula-style racing car
- `vintage_car.glb` - Classic vintage racer

### Tracks
- `track_section.glb` - Modular track pieces
- `barrier.glb` - Track barriers and walls

## Textures

All textures are optimized for mobile (power-of-two dimensions).

### Car Materials
- Car paint textures (red, blue)
- Metal and chrome materials
- Tire rubber textures

### Environment
- Asphalt road texture
- Grass and terrain
- Concrete barriers

## Licenses

Models from Khronos glTF-Sample-Models: CC0 1.0 Universal
Textures from Three.js examples: MIT License

## Usage

Load models in C++ using asset manager:
```cpp
AAsset* asset = AAssetManager_open(assetManager, 
    "models/cars/sports_car.glb", AASSET_MODE_BUFFER);
```
