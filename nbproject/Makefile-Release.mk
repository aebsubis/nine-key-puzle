#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/Juego.o \
	${OBJECTDIR}/src/Sonido.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/src/Pieza.o \
	${OBJECTDIR}/src/Puzzle.o \
	${OBJECTDIR}/src/Juego_EstadoHistorial.o \
	${OBJECTDIR}/src/Juego_EstadoMenu.o \
	${OBJECTDIR}/src/Directorio.o \
	${OBJECTDIR}/src/Juego_EstadoJugando.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/nine-key-puzle

dist/Release/GNU-Linux-x86/nine-key-puzle: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/nine-key-puzle ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Juego.o: nbproject/Makefile-${CND_CONF}.mk src/Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Juego.o src/Juego.cpp

${OBJECTDIR}/src/Sonido.o: nbproject/Makefile-${CND_CONF}.mk src/Sonido.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Sonido.o src/Sonido.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cpp

${OBJECTDIR}/src/Pieza.o: nbproject/Makefile-${CND_CONF}.mk src/Pieza.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Pieza.o src/Pieza.cpp

${OBJECTDIR}/src/Puzzle.o: nbproject/Makefile-${CND_CONF}.mk src/Puzzle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Puzzle.o src/Puzzle.cpp

${OBJECTDIR}/src/Juego_EstadoHistorial.o: nbproject/Makefile-${CND_CONF}.mk src/Juego_EstadoHistorial.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Juego_EstadoHistorial.o src/Juego_EstadoHistorial.cpp

${OBJECTDIR}/src/Juego_EstadoMenu.o: nbproject/Makefile-${CND_CONF}.mk src/Juego_EstadoMenu.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Juego_EstadoMenu.o src/Juego_EstadoMenu.cpp

${OBJECTDIR}/src/Directorio.o: nbproject/Makefile-${CND_CONF}.mk src/Directorio.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Directorio.o src/Directorio.cpp

${OBJECTDIR}/src/Juego_EstadoJugando.o: nbproject/Makefile-${CND_CONF}.mk src/Juego_EstadoJugando.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Juego_EstadoJugando.o src/Juego_EstadoJugando.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/nine-key-puzle

# Subprojects
.clean-subprojects:
