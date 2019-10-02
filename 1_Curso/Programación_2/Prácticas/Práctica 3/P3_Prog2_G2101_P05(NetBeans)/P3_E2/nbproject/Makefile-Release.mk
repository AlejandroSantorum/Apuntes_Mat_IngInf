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
CND_PLATFORM=Cygwin-Windows
CND_DLIB_EXT=dll
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/45fde427/functions.o \
	${OBJECTDIR}/_ext/45fde427/graph.o \
	${OBJECTDIR}/_ext/45fde427/node.o \
	${OBJECTDIR}/_ext/45fde427/p3_e2.o \
	${OBJECTDIR}/_ext/45fde427/queue.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/p3_e2.exe

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/p3_e2.exe: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/p3_e2 ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/_ext/45fde427/functions.o: ../../../Desktop/P3_E2/functions.c
	${MKDIR} -p ${OBJECTDIR}/_ext/45fde427
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/45fde427/functions.o ../../../Desktop/P3_E2/functions.c

${OBJECTDIR}/_ext/45fde427/graph.o: ../../../Desktop/P3_E2/graph.c
	${MKDIR} -p ${OBJECTDIR}/_ext/45fde427
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/45fde427/graph.o ../../../Desktop/P3_E2/graph.c

${OBJECTDIR}/_ext/45fde427/node.o: ../../../Desktop/P3_E2/node.c
	${MKDIR} -p ${OBJECTDIR}/_ext/45fde427
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/45fde427/node.o ../../../Desktop/P3_E2/node.c

${OBJECTDIR}/_ext/45fde427/p3_e2.o: ../../../Desktop/P3_E2/p3_e2.c
	${MKDIR} -p ${OBJECTDIR}/_ext/45fde427
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/45fde427/p3_e2.o ../../../Desktop/P3_E2/p3_e2.c

${OBJECTDIR}/_ext/45fde427/queue.o: ../../../Desktop/P3_E2/queue.c
	${MKDIR} -p ${OBJECTDIR}/_ext/45fde427
	${RM} "$@.d"
	$(COMPILE.c) -O2 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/45fde427/queue.o ../../../Desktop/P3_E2/queue.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
