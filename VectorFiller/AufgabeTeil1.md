# Aufgabenstellung – Teil 1: Analyse und Architekturentwurf

## Kontext

Du erhältst ein bestehendes Programm, das einen großen Vektor mit Zufallszahlen befüllt.
Deine Aufgabe in diesem Teil ist **kein Coding** – du sollst die Architektur analysieren und einen Entwurf erarbeiten.

---

## Ausgangsmaterial

**Gegeben sind:**

Der folgende Client-Code, der einen fertigen Vektor verarbeitet:

```cpp
#pragma once
#include <vector>
#include <memory>
#include <numeric>
#include <iostream>
#include "VectorFactory.h"

namespace atlas::container {

    class Client {
        using FACTORY_POINTER = std::unique_ptr<VectorFactory<int>>;

        FACTORY_POINTER factory_;
        size_t size_;

    public:
        explicit Client(FACTORY_POINTER factory, const size_t size)
            : factory_(std::move(factory)), size_(size) {}

        void processVector() const {
            const auto data = factory_->createAndFillVector(size_);
            //const auto sum = std::accumulate(data->begin(), data->end(), 0LL);
            //std::cout << "Sum: " << sum << std::endl;
        }
    };
}
```

Sowie die Signatur einer Fabrikmethode, die den Vektor erzeugt und befüllt:

```cpp

        [[nodiscard]] virtual auto createAndFillVector(const size_t size) noexcept -> VECTOR_POINTER = 0;

```

---

## Anforderungen

- Der Vektor soll mit befüllt werden
- Das Befüllen soll durch **Nebenläufigkeit beschleunigt** werden
- Der Client `processVector` soll **nicht verändert** werden
- (Die Anzahl der genutzten Threads soll sich an `std::thread::hardware_concurrency()` orientieren)

---

## Deine Aufgabe

Beantworte folgende Fragen **schriftlich und ohne Code** – Stichpunkte oder kurze Absätze genügen.

### Frage 1 – Verantwortlichkeiten identifizieren

Welche **eigenständigen Verantwortlichkeiten** erkennst du in diesem System?  
Beschreibe jede Verantwortlichkeit in einem Satz. Überlege dabei: Was muss das System *können*, und welche dieser Fähigkeiten gehören logisch *nicht* zusammen?

> **Hinweis:** Denke nicht in Klassen, sondern zunächst in Aufgaben. Was muss *erledigt* werden, bevor `processVector` aufgerufen werden kann?

---

### Frage 2 – Abhängigkeiten

Skizziere auf Papier, **welche Verantwortlichkeit welche andere kennen muss**.  
Wer ist Auftraggeber, wer ist Dienstleister?  
Gibt es Verantwortlichkeiten, die bewusst **nichts** voneinander wissen sollten?

---

### Frage 3 – Der Messwunsch

Das Team möchte wissen, wie lange das Befüllen des Vektors dauert.  
Die Zeitmessung ist **keine Kundenanforderung**, sondern ein separates technisches Interesse.

Wo würdest du die Zeitmessung einbauen, und warum?  


---

### Frage 4 – Generizität des Generators

`VectorFactory` 
Welche Einschränkungen – oder bewussten Freiheiten – sollte diese Komponente haben?

---

## Abgabe

Halte deine Ergebnisse fest. In Teil 2 wirst du auf Basis dieser Analyse **Interfaces in C++ definieren** –
dein Entwurf von heute ist die Grundlage dafür.