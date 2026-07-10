# Changelog

All notable changes to this project will be documented here.

## [v1.2.1] - 2026-07-10
### Added
- Debug + Slim build packs for Windows (Win64), Android32, Android64.
- In‑game diagnostics log line when opening the panel (confirms SDK/Loader).

### Changed
- Pinned builds to Geode SDK 5.80; mod.json now requires Loader >= 5.80.
- Safe editor injection: guarded menu lookups to prevent editor fade/crash.

### Fixed
- Crash when opening the editor caused by touching UI before it initialised.
- Slim jobs accidentally using old SDK — workflow now forces 5.80.

## [v1.2.0] - 2026-07-09
### Added
- AI Architect Omni‑Panel: “OMNI BUILD” button in the editor.
- Procedural generator: BPM‑aligned block placement and effect drops.
- Live FX triggers: Glow, Thunder (shake + chromatic), Magic Glow, Mythic Rift.
- Harmonic Palette Engine: triadic HSV palette with live preview.
- 3D Gradient Illusions: layered isometric shapes with gradient highlight.
- Ending Designer: Cinematic Slomo, Credits Card, or Singularity finisher.
- Reset Defaults: one tap restores panel to sane presets.

### Notes
- First public build; expect rapid iteration.i mean expect ultra uh idk :) 
