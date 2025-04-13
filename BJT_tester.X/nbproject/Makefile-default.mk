#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c lib/uart/uart.c lib/i2c/i2c.c lib/DA_converter_MCP4728A1/mcp4728a1.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/lib/uart/uart.o ${OBJECTDIR}/lib/i2c/i2c.o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/lib/uart/uart.o.d ${OBJECTDIR}/lib/i2c/i2c.o.d ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/lib/uart/uart.o ${OBJECTDIR}/lib/i2c/i2c.o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o

# Source Files
SOURCEFILES=src/main.c lib/uart/uart.c lib/i2c/i2c.c lib/DA_converter_MCP4728A1/mcp4728a1.c

# Pack Options 
PACK_COMPILER_OPTIONS=-I "${DFP_DIR}/include"
PACK_COMMON_OPTIONS=-B "${DFP_DIR}/gcc/dev/avr64da28"



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=AVR64DA28
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/f77d62c34137129bedc7dfd00c01a84ba90f94be .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o  -o ${OBJECTDIR}/src/main.o src/main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/d22ab3012733fa29a0f53209015958e4f5ff91b9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o  -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/776ca3dc28245984e44f39d44671893c5bdcd265 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o  -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/cf36e86c9e310db5440f224b9356724df07d0471 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS} -g -DDEBUG  -gdwarf-2  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o  -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/90cc48b4e68604a583d9d065f4159ce155cbfa .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o  -o ${OBJECTDIR}/src/main.o src/main.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/653a811b478699e0d0baf064d05a2c68e5f6b23f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o  -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/53fba6f6c36a1550762c2d06caf35ba153e89504 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o  -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/1c1665ffc46c56f2c39c053db068571541d98da1 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	 ${MP_CC}  $(MP_EXTRA_CC_PRE) -mmcu=avr64da28 ${PACK_COMPILER_OPTIONS} ${PACK_COMMON_OPTIONS}  -x c -c -D__$(MP_PROCESSOR_OPTION)__  -funsigned-char -funsigned-bitfields -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -Wall -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o  -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c  -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=avr64da28 ${PACK_COMMON_OPTIONS}   -gdwarf-2 -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\BJT_tester.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1 -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	
	
	
	
	
	
else
${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mmcu=avr64da28 ${PACK_COMMON_OPTIONS}  -D__$(MP_PROCESSOR_OPTION)__  -Wl,-Map="${DISTDIR}\BJT_tester.X.${IMAGE_TYPE}.map"    -o ${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}      -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION) -Wl,--gc-sections -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/BJT_tester.X.${IMAGE_TYPE}.hex"
	
	
	
	
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${OBJECTDIR}
	${RM} -r ${DISTDIR}

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(wildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
