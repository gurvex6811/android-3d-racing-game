# Asset Management

## Automated Asset Downloads

This project uses GitHub Actions workflows to automatically download and manage game assets.

### Available Workflows

#### 1. Download Game Assets
**File:** `.github/workflows/download-assets.yml`

**Triggers:**
- Manual dispatch (Actions tab)
- Weekly schedule (Sundays)

**Downloads:**
- 3D car models in glTF format
- Track environment models
- PBR textures (car paints, materials)
- Track textures (asphalt, grass, concrete)

#### 2. Download Premium Racing Models
**File:** `.github/workflows/download-premium-models.yml`

**Triggers:**
- Manual dispatch with options

**Features:**
- Custom model URL support
- Automatic glTF optimization
- Metadata generation
- Python-based downloader

#### 3. Update Asset Library
**File:** `.github/workflows/update-asset-library.yml`

**Triggers:**
- Manual dispatch
- Weekly schedule (Mondays 2 AM)

**Downloads:**
- Multiple car types (sports, formula, classic, muscle)
- Track barriers, checkpoints, scenery
- Complete texture sets
- Generates asset configuration JSON

### Running Workflows Manually

1. Go to **Actions** tab in GitHub
2. Select workflow from left sidebar
3. Click **Run workflow** button
4. Select branch (usually `main`)
5. Click **Run workflow**

### Asset Sources

All assets are downloaded from free, open-source repositories:

- **3D Models:** Khronos glTF Sample Models (CC0 1.0 Universal)
- **Textures:** Three.js Examples (MIT License)

### Asset Structure

```
app/src/main/assets/
├── models/
│   ├── cars/
│   │   ├── sports_car_low.glb
│   │   ├── formula_car.glb
│   │   ├── classic_car.glb
│   │   └── muscle_car.glb
│   └── tracks/
│       ├── barrier.glb
│       ├── checkpoint.glb
│       └── tree.glb
├── textures/
│   ├── cars/
│   │   ├── paint_metallic.jpg
│   │   └── carbon_fiber.png
│   └── tracks/
│       ├── asphalt.jpg
│       ├── grass.jpg
│       └── dirt.jpg
├── asset_config.json
└── asset_manifest.json
```

### Loading Assets in Code

#### C++ (Native)

```cpp
#include "AssetLoader.h"

// Initialize
AssetLoader::initialize(assetManager);

// Load car model
ModelData carModel = AssetLoader::loadModel("models/cars/sports_car_low.glb");

// Load texture
auto textureData = AssetLoader::loadTexture("textures/cars/paint_metallic.jpg");

// Load config
std::string config = AssetLoader::loadConfig();
```

#### Java (Android)

```java
AssetManager assets = getAssets();
InputStream is = assets.open("models/cars/sports_car_low.glb");
```

### Adding Custom Models

#### Option 1: Via Workflow

1. Run "Download Premium Racing Models" workflow
2. Select "custom" source
3. Provide direct URL to .glb file
4. Workflow will download and commit

#### Option 2: Manual Addition

1. Place .glb file in `app/src/main/assets/models/cars/`
2. Update `asset_config.json`
3. Commit and push

### Asset Optimization

Workflows automatically optimize assets:

- **Models:** Compressed glTF with Draco
- **Textures:** Converted to power-of-two sizes
- **Total Size:** Kept under 50MB for fast loading

### Licenses

All downloaded assets are:
- ✅ Free for commercial use
- ✅ No attribution required (CC0)
- ✅ Open source (MIT, CC0)

### Custom Asset Guidelines

When adding your own assets:

1. **Models:**
   - Format: glTF 2.0 (.glb)
   - Triangles: < 20,000 per car
   - Use Draco compression

2. **Textures:**
   - Format: PNG or JPEG
   - Size: Power-of-two (512, 1024, 2048)
   - Use mipmaps

3. **Performance:**
   - Total assets < 100MB
   - Individual models < 5MB
   - Textures < 2MB each