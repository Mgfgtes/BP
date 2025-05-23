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
FINAL_IMAGE=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/main.c lib/i2c/i2c.c lib/DA_converter_MCP4728A1/mcp4728a1.c lib/uart/uart.c lib/adc/adc.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/main.o ${OBJECTDIR}/lib/i2c/i2c.o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o ${OBJECTDIR}/lib/uart/uart.o ${OBJECTDIR}/lib/adc/adc.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/main.o.d ${OBJECTDIR}/lib/i2c/i2c.o.d ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d ${OBJECTDIR}/lib/uart/uart.o.d ${OBJECTDIR}/lib/adc/adc.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/main.o ${OBJECTDIR}/lib/i2c/i2c.o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o ${OBJECTDIR}/lib/uart/uart.o ${OBJECTDIR}/lib/adc/adc.o

# Source Files
SOURCEFILES=src/main.c lib/i2c/i2c.c lib/DA_converter_MCP4728A1/mcp4728a1.c lib/uart/uart.c lib/adc/adc.c



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
	${MAKE}  -f nbproject/Makefile-default.mk ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=AVR64DA28
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/2c293c60bfbd42b5d51623538784742332bd3cff .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o -o ${OBJECTDIR}/src/main.o src/main.c 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/391560c3dea742adbd9f954321b4be9a932b7b95 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/e9929a230c8e27c699b22eaa95ced834c1aa759d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/c76c25eb7473348505313c29fcff5542f87875e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c 
	
${OBJECTDIR}/lib/adc/adc.o: lib/adc/adc.c  .generated_files/flags/default/978879e0c088d521ab20ef639db5fc75fcf727e4 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/adc" 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o.d 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/adc/adc.o.d" -MT "${OBJECTDIR}/lib/adc/adc.o.d" -MT ${OBJECTDIR}/lib/adc/adc.o -o ${OBJECTDIR}/lib/adc/adc.o lib/adc/adc.c 
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/2214842b8cbff849c8bd0fe5b1ecc0fd469005a5 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o -o ${OBJECTDIR}/src/main.o src/main.c 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/4a3ddda3aec8d04262b81aafc6c76bef72a6ba91 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/7cc8c1c3a0803153b4fd4384a8ab271992517d8f .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/2b04d9354142feb0af56f9eeb94ee92dc34ba25b .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c 
	
${OBJECTDIR}/lib/adc/adc.o: lib/adc/adc.c  .generated_files/flags/default/baa4888556c2e9cb271460d8241f2138df60e9a6 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/adc" 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o.d 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)  -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     -MD -MP -MF "${OBJECTDIR}/lib/adc/adc.o.d" -MT "${OBJECTDIR}/lib/adc/adc.o.d" -MT ${OBJECTDIR}/lib/adc/adc.o -o ${OBJECTDIR}/lib/adc/adc.o lib/adc/adc.c 
	
endif

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
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O0 -Og -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -gdwarf-3 -mconst-data-in-progmem -mno-const-data-in-config-mapped-progmem     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
	${MP_CC_DIR}\\avr-objcopy -O ihex "${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}" "${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.hex"
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
