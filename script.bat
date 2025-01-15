@echo off
setlocal
@chcp 65001 >nul

rem Путь к MinGW и SFML
set SFML_INCLUDE=C:\MinGW\SFML-2.4.2\include
set SFML_LIB=C:\MinGW\SFML-2.4.2\lib

rem Проверка аргументов
if "%1"=="-o" (
	echo Компиляция и сборка, и Запуск...
	g++ -c code\main.cpp -I%SFML_INCLUDE% -DFOR_WINDOWS -o temp\main.o
	if errorlevel 1 (
		echo Ошибка при компиляции.
		exit /b 1
	)
	
	g++ temp\main.o -o Engrave.exe -L%SFML_LIB% -lsfml-graphics -lsfml-window -lsfml-system
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
	
	g++ temp\main.o -o Engrave.exe -L%SFML_LIB% -lsfml-graphics -lsfml-window -lsfml-system
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
