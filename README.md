# VkUI Engine

## 🇬🇧 English

VkUI is an experimental project to build a lightweight, high-performance UI rendering library from scratch using C++ and the Vulkan API. The primary goal is to parse and render layouts described in HTML and styled with CSS, without relying on a web browser engine.

### Current Status
- ✅ Basic project structure with Make build system.
- ✅ GLFW window creation and management.
- ✅ Full Vulkan initialization (Instance, Physical/Logical Device, Swapchain).
- ✅ A complete, albeit simple, graphics pipeline.
- ✅ **The first triangle is successfully rendered to the screen!**

### How to Build
1.  **Install Dependencies:**
    - A C++17 compliant compiler (`g++`, `clang++`) and `make`: `sudo apt install build-essential`
    - The official [Vulkan SDK](https://vulkan.lunarg.com/sdk/home).
    - GLFW: `sudo apt install libglfw3-dev`
    - `pkg-config`: `sudo apt install pkg-config`

2.  **Compile Shaders:**
    The project uses GLSL shaders that must be compiled to SPIR-V.
    ```bash
    glslc shaders/shader.vert -o shaders/vert.spv
    glslc shaders/shader.frag -o shaders/frag.spv
    ```

3.  **Build the Project:**
    Run `make` from the root directory.
    ```bash
    make
    ```

### How to Run
After a successful build, the executable will be in the `bin/` directory.
```bash
./bin/vkui_app
```

---

## 🇷🇺 Русский

VkUI — это экспериментальный проект по созданию легковесной, высокопроизводительной библиотеки для рендеринга UI с нуля на C++ и Vulkan API. Основная цель — научиться парсить и отрисовывать разметку, описанную в HTML и стилизованную с помощью CSS, не используя движок веб-браузера.

### Текущий Статус
- ✅ Базовая структура проекта и система сборки на Make.
- ✅ Создание и управление окном с помощью GLFW.
- ✅ Полная инициализация Vulkan (Instance, Physical/Logical Device, Swapchain).
- ✅ Завершенный, хотя и простой, графический конвейер.
- ✅ **Первый треугольник успешно отрисован на экране!**

### Как Собрать
1.  **Установите Зависимости:**
    - Компилятор C++17 (`g++`, `clang++`) и `make`: `sudo apt install build-essential`
    - Официальный [Vulkan SDK](https://vulkan.lunarg.com/sdk/home).
    - GLFW: `sudo apt install libglfw3-dev`
    - `pkg-config`: `sudo apt install pkg-config`

2.  **Скомпилируйте Шейдеры:**
    Проект использует GLSL шейдеры, которые нужно скомпилировать в SPIR-V.
    ```bash
    glslc shaders/shader.vert -o shaders/vert.spv
    glslc shaders/shader.frag -o shaders/frag.spv
    ```

3.  **Соберите Проект:**
    Запустите `make` в корневой директории проекта.
    ```bash
    make
    ```

### Как Запустить
После успешной сборки исполняемый файл будет находиться в папке `bin/`.
```bash
./bin/vkui_app
```