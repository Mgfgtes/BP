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
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/c7b4d2da56efc9895fed1d8e5fbe1ec356390507 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o -o ${OBJECTDIR}/src/main.o src/main.c 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/6bf4d6b405e392ca4fb7aea0ecfaf3d4b2c288da .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/746049ac62429986e0bbdf11a010f11f213b3670 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/6a4e437d5ff7b7d3acade192bee2b2095a3fe9ba .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c 
	
${OBJECTDIR}/lib/adc/adc.o: lib/adc/adc.c  .generated_files/flags/default/5c35bf33df21ebbbcb5e8b1f3cdc0df93a0958f8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/adc" 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o.d 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -D__DEBUG=1 -g -DDEBUG  -gdwarf-2  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/adc/adc.o.d" -MT "${OBJECTDIR}/lib/adc/adc.o.d" -MT ${OBJECTDIR}/lib/adc/adc.o -o ${OBJECTDIR}/lib/adc/adc.o lib/adc/adc.c 
	
else
${OBJECTDIR}/src/main.o: src/main.c  .generated_files/flags/default/92bd839d497a23959075a07bbf895d960524d34d .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.o.d 
	@${RM} ${OBJECTDIR}/src/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/src/main.o.d" -MT "${OBJECTDIR}/src/main.o.d" -MT ${OBJECTDIR}/src/main.o -o ${OBJECTDIR}/src/main.o src/main.c 
	
${OBJECTDIR}/lib/i2c/i2c.o: lib/i2c/i2c.c  .generated_files/flags/default/d157781dbe9deb9735111729f18cf4fdf1058ca8 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/i2c" 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o.d 
	@${RM} ${OBJECTDIR}/lib/i2c/i2c.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT "${OBJECTDIR}/lib/i2c/i2c.o.d" -MT ${OBJECTDIR}/lib/i2c/i2c.o -o ${OBJECTDIR}/lib/i2c/i2c.o lib/i2c/i2c.c 
	
${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o: lib/DA_converter_MCP4728A1/mcp4728a1.c  .generated_files/flags/default/5a47ef8e139a6ea497a7b0a530867682e02039c0 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/DA_converter_MCP4728A1" 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d 
	@${RM} ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT "${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o.d" -MT ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o -o ${OBJECTDIR}/lib/DA_converter_MCP4728A1/mcp4728a1.o lib/DA_converter_MCP4728A1/mcp4728a1.c 
	
${OBJECTDIR}/lib/uart/uart.o: lib/uart/uart.c  .generated_files/flags/default/eed2108df81c67f23562cc3b6784e630bd8f8ff9 .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/uart" 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o.d 
	@${RM} ${OBJECTDIR}/lib/uart/uart.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/uart/uart.o.d" -MT "${OBJECTDIR}/lib/uart/uart.o.d" -MT ${OBJECTDIR}/lib/uart/uart.o -o ${OBJECTDIR}/lib/uart/uart.o lib/uart/uart.c 
	
${OBJECTDIR}/lib/adc/adc.o: lib/adc/adc.c  .generated_files/flags/default/63d929f06670eb7e59460f8883c4b307d1c2e7fb .generated_files/flags/default/da39a3ee5e6b4b0d3255bfef95601890afd80709
	@${MKDIR} "${OBJECTDIR}/lib/adc" 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o.d 
	@${RM} ${OBJECTDIR}/lib/adc/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -c  -x c -D__$(MP_PROCESSOR_OPTION)__   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall -DXPRJ_default=$(CND_CONF)  $(COMPARISON_BUILD)      -MD -MP -MF "${OBJECTDIR}/lib/adc/adc.o.d" -MT "${OBJECTDIR}/lib/adc/adc.o.d" -MT ${OBJECTDIR}/lib/adc/adc.o -o ${OBJECTDIR}/lib/adc/adc.o lib/adc/adc.c 
	
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
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.map  -D__DEBUG=1  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"   -gdwarf-2 -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group  -Wl,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1
	@${RM} ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.hex 
	
else
${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} ${DISTDIR} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -mcpu=$(MP_PROCESSOR_OPTION) -Wl,-Map=${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.map  -DXPRJ_default=$(CND_CONF)  -Wl,--defsym=__MPLAB_BUILD=1   -mdfp="${DFP_DIR}/xc8"  -Wl,--gc-sections -O1 -ffunction-sections -fdata-sections -fshort-enums -fno-common -funsigned-char -funsigned-bitfields -Wall     $(COMPARISON_BUILD) -Wl,--memorysummary,${DISTDIR}/memoryfile.xml -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  -o ${DISTDIR}/BJT_tester_2v0.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -Wl,--start-group  -Wl,-lm -Wl,--end-group 
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
