# Contributing

Thanks for your interest in contributing to the 3D Racing Game project!

## Getting Started

1. Fork the repository
2. Clone your fork
3. Create a feature branch: `git checkout -b feature/amazing-feature`
4. Make your changes
5. Commit: `git commit -m 'Add amazing feature'`
6. Push: `git push origin feature/amazing-feature`
7. Open a Pull Request

## Code Standards

### C++ Code
- Follow Google C++ Style Guide
- Use meaningful variable names
- Add comments for complex logic
- Keep functions small and focused

### Naming Conventions
- Classes: PascalCase (e.g., `Vehicle`, `Engine`)
- Functions: camelCase (e.g., `updatePhysics`)
- Variables: camelCase (e.g., `deltaTime`)
- Constants: UPPER_SNAKE_CASE (e.g., `MAX_SPEED`)

### Performance
- Profile before optimizing
- Minimize memory allocations in game loop
- Use object pools for frequently created objects
- Keep draw calls under 100 per frame

## Pull Request Process

1. Ensure code builds without warnings
2. Test on both ARM and x86 devices
3. Update documentation if needed
4. Add tests for new features
5. Follow the PR template

## Reporting Issues

Include:
- Device model and Android version
- Steps to reproduce
- Expected vs actual behavior
- Relevant logs
- Screenshots/videos if applicable

## Questions?

Open a GitHub issue with the `question` label.