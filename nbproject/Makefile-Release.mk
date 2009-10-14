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
	${OBJECTDIR}/src/Puzle.o \
	${OBJECTDIR}/src/Juego.o \
	${OBJECTDIR}/src/Sonido.o \
	${OBJECTDIR}/main.o

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
	${MAKE}  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/puzle

dist/Release/GNU-Linux-x86/puzle: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/puzle ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/src/Puzle.o: nbproject/Makefile-${CND_CONF}.mk src/Puzle.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Puzle.o src/Puzle.cpp

${OBJECTDIR}/src/Juego.o: nbproject/Makefile-${CND_CONF}.mk src/Juego.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Juego.o src/Juego.cpp

${OBJECTDIR}/src/Sonido.o: nbproject/Makefile-${CND_CONF}.mk src/Sonido.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/src/Sonido.o src/Sonido.cpp

${OBJECTDIR}/main.o: nbproject/Makefile-${CND_CONF}.mk main.cpp 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/puzle

# Subprojects
.clean-subprojects: