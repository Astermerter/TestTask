# Руководство пользователя


## Как установить

1. Никаких сторонних библиотек устанавливать не надо, все работает со стандартными библиотеками предустановленными компилятором C++ 
2. Если компилятор не установлен то для Unix: "sudo apt update" "sudo apt install g++" / windows: выберете удобный компилятор и скачайте в интернете (можете выбрать [visual studio](https://visualstudio.microsoft.com/ru/downloads/))


## Как запустить 

1. Запустите "Makefile" прописав в директории "make" или скомпилируйте проект и запустите Unix: "g++ main.cpp sub.cpp -o prog" "./prog" / windows: для visual studio нажмите "F5"
2. Введите все данные которые запрашивает консоль


# Руководство Разработчика

### Пункты установки и запуска такие же как и у пользователя
Вся информация по всем реализованным функциям и классу реализующему решение подписана в виде комментариев в файле "head.h", более конкретные комментарии по неинтуетивным частям функций есть в файле "sub.cpp" возле сложного элемента

Так же общие шаблоны для создания main.v и test.v (файла логики и файла тестирования) есть в директории проекта в папке "examples" (при создании файлов они будут не похожи на шаблоны, шаблоны лишь отражают общее решение)