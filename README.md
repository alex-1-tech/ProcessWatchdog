# ProcScope (Process Watchdog)

**ProcScope** — это легковесный и расширяемый монитор процессов на Qt.  
Позволяет в реальном времени отслеживать процессы в системе, управлять ими (Kill / Stop / Continue), фильтровать и автоматически обновлять список.

---

## Возможности

- Автоматическое обновление списка процессов
- Фильтрация по имени и PID
- Управление процессами (SIGSTOP, SIGCONT, SIGKILL)
- Асинхронное получение данных (через `QtConcurrent`)
- Умное кэширование — обновляются только изменённые строки
- Гибкая архитектура с разделением на слои:
  - UI (MainWindow)
  - ViewModel (ProcessViewModel)
  - Core: ProcessMonitor, ProcessManager
  - Threads: DataCollection (периодический сбор)

---

## 🛠 Сборка

### Зависимости

- CMake ≥ 3.10
- C++20
- Qt5 (Core, Widgets, Gui, Concurrent)

### 🔧 Команды

```bash
git clone https://github.com/yourname/ProcScope.git
cd ProcScope
mkdir build && cd build
cmake ..
make
./ProcScope
