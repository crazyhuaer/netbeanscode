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
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/base.o \
	${OBJECTDIR}/cii/array.o \
	${OBJECTDIR}/cii/atom.o \
	${OBJECTDIR}/cii/except.o \
	${OBJECTDIR}/cii/list.o \
	${OBJECTDIR}/cii/mem.o \
	${OBJECTDIR}/cii/ring.o \
	${OBJECTDIR}/cii/stack.o \
	${OBJECTDIR}/cii/table.o \
	${OBJECTDIR}/lib_network.o \
	${OBJECTDIR}/lib_system.o \
	${OBJECTDIR}/log.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/threadpool.o


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
LDLIBSOPTIONS=-Llib.x86

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/smarthome

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/smarthome: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/smarthome ${OBJECTFILES} ${LDLIBSOPTIONS} -pthread -levent -lmemcached

${OBJECTDIR}/base.o: base.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/base.o base.c

${OBJECTDIR}/cii/array.o: cii/array.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/array.o cii/array.c

${OBJECTDIR}/cii/atom.o: cii/atom.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/atom.o cii/atom.c

${OBJECTDIR}/cii/except.o: cii/except.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/except.o cii/except.c

${OBJECTDIR}/cii/list.o: cii/list.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/list.o cii/list.c

${OBJECTDIR}/cii/mem.o: cii/mem.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/mem.o cii/mem.c

${OBJECTDIR}/cii/ring.o: cii/ring.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/ring.o cii/ring.c

${OBJECTDIR}/cii/stack.o: cii/stack.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/stack.o cii/stack.c

${OBJECTDIR}/cii/table.o: cii/table.c 
	${MKDIR} -p ${OBJECTDIR}/cii
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/cii/table.o cii/table.c

${OBJECTDIR}/lib_network.o: lib_network.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib_network.o lib_network.c

${OBJECTDIR}/lib_system.o: lib_system.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib_system.o lib_system.c

${OBJECTDIR}/log.o: log.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/log.o log.c

${OBJECTDIR}/main.o: main.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/main.o main.c

${OBJECTDIR}/threadpool.o: threadpool.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -O2 -Iinclude.x86 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/threadpool.o threadpool.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/smarthome

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
