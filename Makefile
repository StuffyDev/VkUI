# Компилятор
CXX = g++

# Флаги компилятора
# -std=c++17: используем стандарт C++17
# -g: добавляем отладочную информацию
# -Wall: включаем все предупреждения
CXXFLAGS = -std=c++17 -g -Wall

# Директории
SRCDIR = src
INCDIR = include
BUILDDIR = build
BINDIR = bin

# Имя исполняемого файла
TARGET = $(BINDIR)/vkui_app

# Исходники и объектные файлы
SOURCES = $(wildcard $(SRCDIR)/*.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%.cpp, $(BUILDDIR)/%.o, $(SOURCES))

# Флаги для подключения библиотек
# Используем pkg-config для автоматического поиска путей к Vulkan и GLFW
INCLUDES = -I$(INCDIR)
LDFLAGS = $(shell pkg-config --libs glfw3 vulkan)

# Цель по умолчанию (первая в файле)
all: $(TARGET)

# Правило для сборки исполняемого файла
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)
	@echo "Сборка завершена. Запусти приложение командой: ./$(TARGET)"

# Правило для компиляции .cpp файлов в .o файлы
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Очистка
clean:
	@echo "Очистка проекта..."
	@rm -rf $(BUILDDIR)/* $(BINDIR)/*

# Псевдо-цели
.PHONY: all clean
