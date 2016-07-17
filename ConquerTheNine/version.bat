@echo #ifndef VERSION_H_ > version.h
@echo #define VERSION_H_ >> version.h

@echo( >> version.h

@git describe --dirty --always --tags > version.info
@set /p V=<version.info

@echo #define VERSION_STR "%V%" >> version.h

@echo( >> version.h
@echo #endif // VERSION_H_ >> version.h
