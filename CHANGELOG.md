### 2.0.0
- Update to VCV Rack SDK 2.0 pre-release
- Remove DBug for now due to crashes with new SDK.

### 1.0.7
- Fix Dbug crashes on 3rd party non-CSModule modules

### 1.0.6
- Cleaned up Dbug output
- Fixed Several Dbug crash scenarios (core modules still causing issues)
- Added Test Rack to project
- Added 2x oversampling in Nip to avoid aliasing (Not original plan, but it felt & sounded right)
- Fixed several bugs that caused crashing & strange results in DBug
- Added polyphony to Nip
- Added polyphony to Pow
- Cleaned up Dip internal code
- Fix polyphony in MIO
- Switched all non-blank modules to CSModule base internally
- Added DBugMessages debugMsg to CSModule base class

### 1.0.5 (6/5/2020)
- Added DIP module parallel HP/LP filter - Huovilainen Moog Ladder based
- Added DBug module debug extender for developers
- Added 8hp blank module
- Added CSFilterBase base internally
- Added CSModule base internally
- Added clang-format
- Added vscode project files to repo
- Added MoogLadders dependency

### 1.0.4 (5/23/2020)
- Added MIO 3->1 dual polyphonic mixer
- Added IMO 1->3 dual polyphonic multiplier
- Internal oscillator refactor
- Create custom internal generic maths for min/max/clamping
- Refactor non-rack namespace to not require rack
- Move oscillator methods out of dsp namespace
- exclude Illustrator files from build

### 1.0.3 (5/21/2020)
- Added Nip hard clipper
- Added Pow voltage generator and attenuator
- Added initial internal layout methodology
- Added internal voltage clamp methods

### 1.0.2 (5/20/2020)
- Added custom knobs & inputs
- Added Blank901, Blank902, Blank904 Blank Panels

### 1.0.1 (5/18/2020)
- Fixed VBNO - Wave input CV - 10v
- Added Changelog

### 1.0.0 (5/18/2020)
- Added VBNO
