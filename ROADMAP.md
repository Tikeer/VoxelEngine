# VoxelEngine - opis projektu
> Goal: A high-performance, cross-platform Voxel Engine built with C++ and OpenGL 4.1,
> designed for seamless development and deployment across Windows (Visual Studio)
> and macOS (CLion).
>
> Core Architecture:
> Modular Design: Strict separation between the Engine Core and Game/Modding logic.
> Modern Build System: CMake-driven dependency management (GLFW, GLAD, GLM, spdlog)
> using FetchContent.
> Resource Management: Efficient handling of large-scale terrain data with smart
> memory management.
>
> Performance & Systems:
> Asynchronous Pipeline: Custom thread pool for non-blocking chunk generation and meshing.
> World Management: Dynamic ChunkManager handling chunk lifecycle (loading/unloading)
> based on player position.
> Input System: Robust InputManager utilizing callback-based architecture for keyboard
> and mouse.
>
> Advanced Rendering:
> Optimization: Face Culling and Greedy Meshing to minimize draw calls and vertex count.
> Visual Fidelity: Implementation of Vertex-based Ambient Occlusion (AO) and custom
> GLSL shaders.
>
> Extensibility:
> Modding API: Planned Lua scripting integration to allow flexible gameplay extensions
> without recompiling the engine core. C# scripting (via Mono or .NET) considered
> as a long-term alternative.

# VoxelEngine — Roadmap & Plan Działania

> Plik kontekstowy dla Claude. Przy każdym pytaniu o postęp sprawdzaj ten dokument —
> weryfikuj kolejność kroków, priorytety i czy nic nie zostało pominięte.

---

## Technologia & stack

| Element | Wybór |
|---|---|
| Język | C++20 |
| Build system | CMake 3.25+ z FetchContent |
| Okno / input | GLFW 3.4 |
| OpenGL loader | GLAD 2 (GL 4.1 Core) |
| Matematyka | GLM 1.0.1 |
| Logowanie | spdlog 1.14 |
| Tekstury | stb_image |
| Szum | FastNoiseLite (do dodania w Fazie 04) |
| Testy | Catch2 (opcjonalne, Faza 06) |
| Dokumentacja | Doxygen |
| CI | GitHub Actions (Ubuntu + Windows) |

---

## Struktura projektu (zatwierdzona)

```
/VoxelEngine
├── CMakeLists.txt          ← root (FetchContent, flagi, subdirectory)
├── engine/
│   ├── CMakeLists.txt      ← statyczna biblioteka VoxelEngine
│   ├── include/            ← publiczne nagłówki (widoczne dla game/)
│   └── src/
│       ├── core/           ← Window, Application, Logger, Time
│       ├── rendering/      ← Renderer, Shader, Texture, Camera, Mesh, ChunkMesher
│       └── world/          ← Chunk, World, Block, ChunkManager, NoiseGenerator
├── game/
│   ├── CMakeLists.txt      ← wykonywalny VoxelGame, linkuje VoxelEngine
│   ├── src/                ← main.cpp, GameApp.cpp
│   └── scripts/            ← skrypty pomocnicze (Python/Lua, opcjonalne)
├── external/
│   └── .gitkeep            ← zależności przez FetchContent, nie vendorowane
├── assets/
│   └── generated/          ← w .gitignore
├── docs/                   ← Doxygen output (w .gitignore)
├── tests/                  ← Catch2, opcjonalne (Faza 06)
├── .gitignore              ← build/, external/*, cmake artefakty, IDE pliki
└── build/                  ← w .gitignore, nigdy nie commitować
```

**Ocena struktury:** ✅ Zatwierdzona. Brakuje jeszcze: `generated/`.

---

## Komendy budowania

```bash
# Debug (domyślny) z AddressSanitizer
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j$(nproc)
./build/bin/VoxelGame

# Release
cmake -B build-release -DCMAKE_BUILD_TYPE=Release
cmake --build build-release -j$(nproc)

# Testy
cmake -B build -DVOXEL_BUILD_TESTS=ON
cmake --build build
ctest --test-dir build
```

---

## Fazy — szczegółowy plan

### FAZA 01 — Fundament projektu
**Czas:** Tydzień 1–2  
**Status:** `[x] Rozpoczęto`

Zadania:
- [x] Zainicjuj repo GitHub z README.md, LICENSE (MIT), .gitignore
- [x] Wrzuć CMakeLists.txt (root + engine/ + game/) — pliki wygenerowane
- [x] Zweryfikuj że FetchContent pobiera: GLFW, GLAD, GLM, spdlog, stb
- [ ] Stwórz okno z GLFW, kontekst OpenGL 4.1 Core, wydrukuj wersję GL przez Logger
- [ ] Klasa Logger opakowująca spdlog — każdy moduł loguje przez nią
- [x] GitHub Actions CI: build Debug + Release na ubuntu-latest i windows-latest
- [ ] Pierwszy tag semantyczny: `v0.0.1`

**CV tip:** Skonfigurowany CI już przy pierwszym commicie = sygnał profesjonalizmu.

---

### FAZA 02 — Core engine
**Czas:** Tydzień 3–4  
**Status:** `[ ] Nie rozpoczęto`  
**Wymaga:** Faza 01 ukończona

Zadania:
- [ ] Klasa `Application` — game loop z fixed timestep (delta time, akumulacja)
- [ ] Klasa `Window` — opakowuje GLFW, obsługa resize, VSync toggle
- [ ] Prosty Event System (`std::function` / observer pattern)
- [ ] `InputManager` — klawiatura + mysz przez callbacki GLFW
- [ ] Klasa `Time` — pomiar FPS, delta time, fixed step accumulator

**CV tip:** Fixed timestep + event system to dowód znajomości architektury silników.

---

### FAZA 03 — Rendering pipeline
**Czas:** Tydzień 5–7  
**Status:** `[ ] Nie rozpoczęto`  
**Wymaga:** Faza 02 ukończona

Zadania:
- [ ] Klasy `Shader` i `ShaderProgram` — kompilacja GLSL, upload uniformów
- [ ] Abstrakcja VAO/VBO — klasa `Mesh`
- [ ] Klasa `Camera` — FPS-style (pitch/yaw), macierze view/projection, frustum
- [ ] `Texture2D` + `TextureAtlas` — ładowanie przez stb_image, atlas dla bloków
- [ ] `ChunkMesher` — **greedy meshing** (priorytet — duży plus na CV)
- [ ] Frustum culling — nie renderuj chunków poza frustumem

**CV tip:** Greedy meshing to klasyczny algorytm optymalizacji voxeli — koniecznie opisz w README.

---

### FAZA 04 — System świata
**Czas:** Tydzień 8–10  
**Status:** `[ ] Nie rozpoczęto`  
**Wymaga:** Faza 03 ukończona

Zadania:
- [ ] `Block` + `BlockRegistry` — id → właściwości (solid, transparent, typ)
- [ ] Klasa `Chunk` — 16×256×16 bloków, dane w flat array (`uint16_t`)
- [ ] `ChunkManager` — ładowanie / zwalnianie chunków wokół gracza, kolejkowanie
- [ ] Generacja terenu: FastNoiseLite (Perlin/Simplex), heightmap → bloki
- [ ] Biomy — prosta interpolacja noise → typ terenu (góry, równiny, ocean)
- [ ] Serializacja chunków: zapis / odczyt do pliku binarnego

**CV tip:** Generacja proceduralna + serializacja to dwa oddzielne duże punkty w opisie projektu.

---

### FAZA 05 — Gameplay & fizyka
**Czas:** Tydzień 11–13  
**Status:** `[ ] Nie rozpoczęto`  
**Wymaga:** Faza 04 ukończona

Zadania:
- [ ] AABB collision detection z siatką voxeli (własna implementacja, bez fizycznego silnika)
- [ ] Grawitacja + skakanie gracza
- [ ] Ray casting — wskazanie bloku pod kursorem (highlight)
- [ ] Stawianie i niszczenie bloków
- [ ] Prosty inventory / hotbar (opcjonalne, ale ładnie wygląda na demo)

**CV tip:** Własna detekcja kolizji z voxelami bez zewnętrznego silnika = silny punkt.

---

### FAZA 06 — Polishing & dokumentacja
**Czas:** Tydzień 14–16  
**Status:** `[ ] Nie rozpoczęto`  
**Wymaga:** Faza 05 ukończona

Zadania:
- [ ] **README.md** z: opisem projektu, GIF/screenshot gameplay, instrukcją budowania, listą technologii, benchmarkiem FPS
- [ ] Doxygen — komentarze w kodzie, generowanie `docs/`
- [ ] Benchmark: liczba chunków, FPS przy różnych odległościach renderowania
- [ ] Tag `v0.1.0` + GitHub Release z prekompilowaną binarką (Windows + Linux)
- [ ] **Opcja A:** Shadow mapping / Ambient Occlusion — efekt WOW
- [ ] **Opcja B:** Skybox (cubemap)
- [ ] **Opcja C:** Unit testy Catch2 dla ChunkMesher + NoiseGenerator

**CV tip:** GIF z gameplay w README to największy zwrot uwagi rekrutera. Nagraj go jako pierwszy po ukończeniu Fazy 05.

---

## Priorytety i kolejność (ŚCISŁA)

```
01 Fundament → 02 Core → 03 Rendering → 04 Świat → 05 Gameplay → 06 Polish
```

Nie przeskakuj faz. Każda następna faza zależy od poprzedniej.  
Wyjątek: zadania z Opcja A/B/C w Fazie 06 są równoległe i opcjonalne.

---

## Checklisty dla Claude

Kiedy użytkownik pyta o postęp:
1. Sprawdź aktualną fazę i status zadań
2. Zweryfikuj czy kolejność kroków jest zachowana
3. Zwróć uwagę jeśli coś zostało pominięte lub zrobione nie po kolei
4. Wskaż następne konkretne zadanie do wykonania

Kiedy użytkownik pokazuje kod / pliki:
- Sprawdź czy pasują do etapu w roadmapie
- Oceń jakość pod kątem projektu CV (nazewnictwo, struktura, separacja)
- Zaproponuj ulepszenia jeśli coś odbiega od planu

---

## Notatki robocze

*(Tu dopisuj postęp, decyzje architektoniczne, napotkane problemy)*

- Struktura projektu zatwierdzona w sesji inicjalnej
- CMakeLists.txt (root + engine + game) wygenerowane
- .gitignore wygenerowany
- GitHub Actions — naprawione.
- stworzenie okna w GLFW zrobione.
