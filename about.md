# AI Co‑Creator Omni‑Engine

Turn Geometry Dash 2.2 into a procedural sandbox. Click once; watch a theme‑coherent, BPM‑synced, FX‑driven layout assemble itself — complete with palette harmony and a cinematic ending.

## Highlights
- Procedural generator aligned to BPM and grid speed.
- Live FX: Glow, Thunder (shake + chromatic), Magic Glow, Mythic Rift.
- Harmonic Palette Engine (triadic HSV) with live preview.
- 3D gradient illusion builder (layered depth).
- Ending Designer: Cinematic Slomo / Credits / Singularity.
- Reset Defaults and safe editor injection (no more fade‑to‑menu).

## Requirements
- Geode Loader: **5.80+**
- Geometry Dash: **2.2081** (Win, Android)
- Supported platforms in releases: **Win64**, **Android32**, **Android64**

## Install
1. Download the `.geode` for your platform (or the packaged ZIP and grab the `.geode` inside).
2. Drop it into your GD `mods` folder.
3. Launch GD. In the Editor, hit the gold button: **OMNI BUILD**.

## Quick Start
- Open any level in the editor.
- Click **OMNI BUILD** to open the Omni‑Panel.
- Pick a brush (Block / Pipe / Spikes / 3D).
- Tap an FX trigger to spawn an environmental effect.
- Adjust **H** (hue) to recolour the triadic palette.
- Press **GENERATE** to lay down an 80‑beat segment plus a styled end screen.
- Use **RESET DEFAULTS** if you get wild.

## Feature Map
- Procedural Layouts: places blocks/FX on musical phrases.
- FX Director: instant glow, shake + chromatic, gradients, rifts.
- Palette Designer: triadic HSV preview for coherent colours.
- 3D Illusions: layered scaling with gradient highlight.
- Endings: Timewarp + colour, Credits card, or Black‑Hole finale.
- Safety: guarded UI injection, stable spawn anchors.

## Packs
- **Debug Pack**: larger, includes symbols (easier to debug issues).
- **Slim Pack**: smaller, LTO on, ideal for publishing.

## Known Issues / Tips
- If the editor fades to menu:
  - Update Geode Loader to **>= 5.80**.
  - Disable other editor‑hooking mods and retry.
  - Reopen the editor; wait a second before opening the panel.
- If FX don’t appear: you may be off‑camera — effects spawn near `x ≈ 500`. Scroll left to see them.
- Wipe Canvas is disabled in the safe build; a public API‑based wipe will return in a later version.

## Roadmap
- Per‑platformer room generation (platformer path noise presets).
- Object‑query wipe and selective removal (public API only).
- User templates and colour LUT import.
- Percentage segment editor (e.g., 70% Wave / 20% Ship / 10% Cube).

## Credits
- Concept & Direction: bluxli (Director)
- Engineering: bluxli (Omni‑Engine, UI, CI)
- SDK: Geode Team and contributors
- Help: Idk why but why not noxav

## Links
- Source: https://github.com/bluxli :)/Procedural-AI-Architect-Engine
- Issues / Feedback: GitHub Issues

## License
Personal/portfolio use permitted. Ask before redistribution or commercial use.
