#include <windows.h>  // Заголовочный файл для работы с функциями Windows API
#include <tlhelp32.h> // Заголовочный файл для работы с функциями для работы с процессами
#include <stdio.h>    // Заголовочный файл для работы с функциями ввода-вывода

// Функция для выхода из программы
void ExitProgram()
{
    printf("Write 'leave' to exit the program\n"); // Выводим подсказку пользователю
    char buffer[8];                                // Объявляем буфер для ввода данных
    while (scanf("%s", buffer))                    // Ждем ввода от пользователя
    {
        if (strcmp(buffer, "leave") == 0) // Если введено "leave", то...
            break;                        // Выходим из цикла
    }
}

// Главная функция программы
int main(int argc, char *argv[])
{
    DWORD currentProcessId = GetCurrentProcessId();
    HANDLE hProcessSnap; // Дескриптор снимка процессов
    PROCESSENTRY32 pe32; // Структура для хранения информации о процессе

    // Получаем снимок текущих процессов
    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hProcessSnap == INVALID_HANDLE_VALUE) // Проверяем успешность получения снимка
    {
        printf("CreateToolhelp32Snapshot error\n"); // Выводим сообщение об ошибке
        return 1;                                   // Возвращаем код ошибки
    }

    // Устанавливаем размер структуры
    pe32.dwSize = sizeof(PROCESSENTRY32);

    // Получаем информацию о первом процессе
    if (!Process32First(hProcessSnap, &pe32)) // Получаем информацию о первом процессе
    {
        printf("Process32First error\n"); // Выводим сообщение об ошибке
        CloseHandle(hProcessSnap);        // Закрываем дескриптор снимка процессов
        return 1;                         // Возвращаем код ошибки
    }

    // Перечисляем остальные процессы
    do
    {
        if (pe32.th32ProcessID == currentProcessId)
        {
            printf("Process ID: %d, Parent Process ID: %d, Name: %s <------This process\n", pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
        }
        else
        {
            printf("Process ID: %d, Parent Process ID: %d, Name: %s\n", pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);
        }
        // Выводим информацию о процессе
        // printf("Process ID: %d, Parent Process ID: %d, Name: %s\n", pe32.th32ProcessID, pe32.th32ParentProcessID, pe32.szExeFile);

        // if (strcmp(pe32.szExeFile, "ArifAbdullaev.exe") == 0)
        // {
        //     printf("<------This process\n");
        // }

    } while (Process32Next(hProcessSnap, &pe32)); // Получаем информацию о следующем процессе

    // Закрываем дескриптор снимка процессов
    CloseHandle(hProcessSnap);

    // Вызываем функцию для выхода из программы
    ExitProgram();

    return 0; // Возвращаем нулевой код завершения программы
}
