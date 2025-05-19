# SaltLakeCity &nbsp;![](https://img.shields.io/badge/build-passing-brightgreen) ![](https://img.shields.io/badge/tests-passing-brightgreen)

*A modular Unreal Engine project that showcases a full gameplay framework, an MVC-style GUI stack, and a stand-alone automation-test plugin.*

---

## ✨  What is SaltLakeCity?

SaltLakeCity is a mid-scope **Unreal Engine 4.27** (forward-compatible with **UE 5.3**) prototype built to demonstrate clean C++ architecture and a lean artist pipeline.  
It contains roughly **30 kLOC** of gameplay code plus an additional **3 kLOC** of automation tests.  UE4 in-editor assets (including meshes, shaders, textures) live in a separate depot, so that this coding repo stays lightweight.

---

## 🚀  Highlights

| Domain | Feature |
|--------|---------|
| **Gameplay** | • Component-based **Ability System** (`Abilities/`) <br>• Data-driven **Job/AI framework** (`Jobs/`) |
| **UI / UX** | • **MVC GUI stack**:<br>&nbsp;&nbsp;`Models/` ↔ `Views/Widgets/` ↔ `Controllers/` <br>• Automatic widget pooling to avoid Slate GC hitches |
| **Architecture** | • Consistent header / cpp split, `IBB*` interfaces for dependency inversion <br>• Sub-system modules (`GameStates/`, `Services/`) keep coupling low <br>• Built with TDD methodology in mind |
| **Testing** | • Stand-alone **SaltLakeCityTests** plugin with unit, functional & PIE tests <br>• Run in editor (`Session Frontend → Automation`) or CI (`RunUAT BuildPlugin ...`) |
| **Performance** | • Object pools for GUI & AI tasks <br>• `STAT` groups plus UE Insights markers |

---

## 🛠️  Prerequisites

| Requirement | Version |
|-------------|---------|
| Unreal Engine | 4.27 .2 (**tested**), 5.3+ (*works after automatic upgrade; Nanite/Lumen optional*) |
| Visual Studio | 2017 or later with UE4 support enabled |
| Windows | 10 or 11 64-bit (other platforms untested) |
| Git LFS | Only needed if you pull the private content depot |

---

## 📂  Repository layout
SaltLakeCity/
│
├─ Source/                     # All gameplay and engine-side C++
│   ├─ Abilities/              # Modular ability components & data
│   ├─ Actors/                 # Custom pawns, AI, interaction props
│   ├─ GUI/                    # MVC-style UI (Models / Views / Presenters)
│   ├─ Jobs/                   # Worker-task system and job definitions
│   ├─ GameStates/             # State machines, save / load services
│   └─ …                       # Other feature folders (AI, Services, etc.)
│
├─ SourcePlugins/              # Optional plugins kept separate from the core
│   └─ SaltLakeCityTests/      # Automation & functional test suite
│
├─ Content/                    # Minimal placeholder assets (maps, configs)
│                              # Heavy art assets live in a private depot
│
├─ Config/                     # DefaultEngine.ini, input, render settings
│
├─ .github/workflows/          # CI pipeline: build + run tests
│
└─ README.md                   # You are here

> **Where are the assets?**  
> As this is a repository meant to highlight coding skills, no asset is not made available.
