@echo off
setlocal
@chcp 65001 >nul

rem rem Путь к MinGW и SFML
rem set SFML_INCLUDE=C:\MinGW\SFML-2.4.2\include
rem set SFML_LIB=C:\MinGW\SFML-2.4.2\lib


rem Проверка существования файла конфигурации
if not exist compil.config (
    echo Ошибка: файл compil.config не найден.
    exit /b 1
)

rem Чтение конфигурационного файла
for /f "tokens=1,2 delims==" %%i in (compil.config) do (
    set %%i=%%j
)

rem Проверка аргументов
if "%1"=="-o" (
	echo Компиляция и сборка, и Запуск...
	g++ -c code\main.cpp -I%SFML_INCLUDE% -DFOR_WINDOWS -o temp\main.o
	if errorlevel 1 (
		echo Ошибка при компиляции.
		exit /b 1
	)
	
	g++ temp\main.o -o Engrave -L%SFML_LIB% -lsfml-graphics -lsfml-window -lsfml-system
	if errorlevel 1 (
		echo Ошибка при сборке.
		exit /b 1
	)
	
	echo Запуск программы...
	Engrave
	exit /b 0
) else if "%1"=="-c" (
	echo Компиляция...
	g++ -c code\main.cpp -I%SFML_INCLUDE% -DFOR_WINDOWS -o temp\main.o
	if errorlevel 1 (
		echo Ошибка при компиляции.
		exit /b 1
	)
	
	g++ temp\main.o -o Engrave -L%SFML_LIB% -lsfml-graphics -lsfml-window -lsfml-system
	if errorlevel 1 (
		echo Ошибка при сборке.
		exit /b 1
	)

	echo Успешно скомпилировано и собрано!!!
	exit /b 0
) else if "%1"=="" (
	echo Запуск последней версии программы...
	Engrave
	exit /b 0
) else if "%1"=="-w" (
	echo Запуск последней версии программы...
	Engrave
	exit /b 0
) else (
	echo Неправильный аргумент. Используйте -o, -c, -w или без аргументов.
	exit /b 1
)

endlocal
