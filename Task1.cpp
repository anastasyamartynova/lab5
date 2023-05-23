// Заголовочные файлы, необходимые для класса и функций Windows
#include <windows.h>

// Класс окна
class Window {
public:
    Window(HWND hwnd) : hwnd(hwnd) {}

    // Обработчик сообщений
    LRESULT HandleMessage(UINT message, WPARAM wParam, LPARAM lParam) {
        switch (message) {
        case WM_COMMAND:
            return OnCommand(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HWND>(lParam));

        case WM_DESTROY:
            OnDestroy();
            return 0;

            // Добавить обработку других сообщений, если необходимо

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
        }
    }

private:
    // Обработчик команд
    LRESULT OnCommand(WORD /*id*/, WORD /*code*/, HWND /*hwndControl*/) {
        // Здесь можно оставить switch, чтобы обрабатывать различные команды
        switch (LOWORD(wParam)) {
            // Обработка команд
        }

        return 0;
    }

    // Обработчик разрушения окна
    void OnDestroy() {
        PostQuitMessage(0);
    }

    HWND hwnd;
};

// Функция окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    // Получение указателя на объект Window, связанного с данным окном
    Window* windowPtr = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    if (message == WM_CREATE) {
        // Получение указателя на объект Window, переданного при создании окна
        LPCREATESTRUCT createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
        windowPtr = reinterpret_cast<Window*>(createStruct->lpCreateParams);

        // Сохранение указателя на объект Window в пользовательских данных окна
        SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowPtr));
    }

    // Обработка сообщений, используя метод HandleMessage класса Window
    if (windowPtr != nullptr) {
        return windowPtr->HandleMessage(message, wParam, lParam);
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}

// Главная функция приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
    // Создание объекта окна
    Window window(hwnd);

    // Регистрация класса окна
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    // Заполнение полей структуры WNDCLASSEX
    // ...

    // Создание окна
    HWND hwnd = CreateWindowEx(
        // Параметры окна
        // ...
    );

    // Показ окна
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    // Цикл обработки сообщений
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return static_cast<int>(msg.wParam);
}

//Был создан класс Window, который инкапсулирует окно и его обработку сообщений. Вместо одной большой функции WndProc, была разделена обработка различных сообщений на методы класса Window
//Теперь в методе HandleMessage происходит выбор нужного метода обработки в зависимости от типа сообщения, и вызывается соответствующий метод класса Window
//Оператор switch был удален из функции WndProc, и его место заняли вызовы методов класса Window.