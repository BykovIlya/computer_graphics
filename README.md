# computer_graphics
## Лабораторные работы по компьютерной графике. Быков, Спас, 6383

## Работа с гитхаб:
  `git pull origin master`
  `git add .`
  `git commit -m "smth"`
  `git push origin master`
  

## Установка freeglut

[ссылка на архив](https://sourceforge.net/projects/freeglut/)

### Инструкция по установке:

- Make sure you have cmake installed:
  - Debian/Ubuntu: `apt-get install cmake`
- Also make sure you have packages installed that provide the relevant
  header files for x11 (including xrandr) and opengl (e.g.,
  libgl1-mesa-dev, libx11-dev and libxrandr-dev on Debian/Ubuntu).
- Install XInput: `libxi-dev / libXi-devel`
- Run `cmake .` in the freeglut directory to generate the makefile.
- Run `make` to build, and 'make install' to install freeglut.
