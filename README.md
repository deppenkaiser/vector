# vector – 3D-Vektor-Mathematik

Kleine C-Bibliothek für Vektoroperationen in 3D und astronomische
Koordinaten (Kugelkoordinaten) mit `long double`-Präzision.

## Umfang

- **Kartesisch**: `vector_3d` (`long double` x/y/z) mit `vector_add`,
  `vector_sub`, `vector_cross`, `vector_dot`, `vector_norm`,
  `vector_multiply_scalar`/`vector_divide_scalar`, `vector_normalize`,
  `vector_distance`, `vector_clear`.
- **Rotationen**: `vector_rotation_x/y/z(r, phi_rad)`.
- **Nabla**: `vector_nabla` über eine Zeitzeile `vector_time_row_t`
  (3 Vektoren).
- **Astronomisch**: `vector_cartesian_to_astronomical` → `vector_astro`
  (r, phi, theta).

## Nutzung

```c
#include <vector/vector.h>

vector_3d_t a, b;
struct vector_3d s = vector_sub(a, b);
ld d = vector_distance(a, b);
```

## Abhängigkeiten

Keine weiteren Projekt-Bibliotheken.

## Wiki

Dokumentation: [vector – 3D-Vektor-Mathematik](https://czybor.i234.me/wiki/sw-module/vector/) (Quartz-Wiki)

## Build

```bash
cmake -S . -B build
cmake --build build
```

In ein Projekt einbinden: `add_subdirectory(../../libraries/vector …)`,
Einbindung des Headers über den Include-Pfad `<vector/vector.h>`.