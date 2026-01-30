# Базовый проект C++ и Allegro5

Это скелет проекта для работы в `VScode`. Если вы хотите работать в `Codeblocks` или вы сами хотите установить `Allegro5` не используя готовый код - смотрите файл `INSTALL.md`.

## Как работает проект

Он идет сразу с установленой библиотекой `Allegro5` 
и двумя вспомогательными файлами: `AllegroUtil.cpp` и `AllegroUtil.hpp`.
Далее весь код можно писать самостоятельно.

### Компиляция на Windows

Изменяем файл `build.bat` там где указаны комментарии.
```bat
g++ ^
@REM Ниже указываем все файлы нужные в проекте
example_2.cpp AllegroUtil.cpp ^ 
@REM Ниже указываем куда компилируется программа и какое у неё название
-o bin/program ^ 
-Iallegro/include -Lallegro/lib ^
-lallegro -lallegro_main -lallegro_primitives
```

Запускаем в `cmd` и готово.

### Компиляция на Linux

Изменяем файл `build.sh` там где указаны комментарии.
```sh
g++ \
# Ниже указываем все файлы нужные в проекте
main.cpp AllegroUtil.cpp \ 
# Ниже указываем куда компилируется программа и какое у неё название
-o linux/app \
$(pkg-config --cflags --libs allegro-5 allegro_primitives-5)
```

Запускаем в `bash` и готово.