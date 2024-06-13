set(SDK_PATH "C:/Users/gabriel/SimplicityStudio/SDKs/gecko_sdk_2")
set(COPIED_SDK_PATH "gecko_sdk_4.4.3")

add_library(slc_XDRONE OBJECT
    "../${COPIED_SDK_PATH}/platform/common/src/sl_assert.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_slist.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_string.c"
    "../${COPIED_SDK_PATH}/platform/common/src/sl_syscalls.c"
    "../${COPIED_SDK_PATH}/platform/common/toolchain/src/sl_memory.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32FG28/Source/startup_efr32fg28.c"
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32FG28/Source/system_efr32fg28.c"
    "../${COPIED_SDK_PATH}/platform/emdrv/dmadrv/src/dmadrv.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_cmu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_core.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_emu.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_gpio.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_ldma.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_msc.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_system.c"
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_usart.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli_arguments.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli_command.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli_input.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli_io.c"
    "../${COPIED_SDK_PATH}/platform/service/cli/src/sl_cli_tokenize.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_dcdc_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_dpll_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_emu_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_hfxo_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_lfxo_s2.c"
    "../${COPIED_SDK_PATH}/platform/service/device_init/src/sl_device_init_nvic.c"
    "../${COPIED_SDK_PATH}/platform/service/iostream/src/sl_iostream.c"
    "../${COPIED_SDK_PATH}/platform/service/iostream/src/sl_iostream_uart.c"
    "../${COPIED_SDK_PATH}/platform/service/iostream/src/sl_iostream_usart.c"
    "../${COPIED_SDK_PATH}/platform/service/system/src/sl_system_init.c"
    "../${COPIED_SDK_PATH}/platform/service/system/src/sl_system_process_action.c"
    "../${COPIED_SDK_PATH}/util/third_party/printf/printf.c"
    "../${COPIED_SDK_PATH}/util/third_party/printf/src/iostream_printf.c"
    "../app.c"
    "../autogen/sl_cli_command_table.c"
    "../autogen/sl_cli_instances.c"
    "../autogen/sl_device_init_clocks.c"
    "../autogen/sl_event_handler.c"
    "../autogen/sl_iostream_handles.c"
    "../autogen/sl_iostream_init_usart_instances.c"
    "../autogen/sli_cli_hooks.c"
    "../main.c"
)

target_include_directories(slc_XDRONE PUBLIC
   "../config"
   "../autogen"
   "../."
    "../${COPIED_SDK_PATH}/platform/Device/SiliconLabs/EFR32FG28/Include"
    "../${COPIED_SDK_PATH}/platform/common/inc"
    "../${COPIED_SDK_PATH}/platform/service/cli/inc"
    "../${COPIED_SDK_PATH}/platform/service/cli/src"
    "../${COPIED_SDK_PATH}/platform/CMSIS/Core/Include"
    "../${COPIED_SDK_PATH}/platform/service/device_init/inc"
    "../${COPIED_SDK_PATH}/platform/emdrv/dmadrv/inc"
    "../${COPIED_SDK_PATH}/platform/emdrv/common/inc"
    "../${COPIED_SDK_PATH}/platform/emlib/inc"
    "../${COPIED_SDK_PATH}/platform/service/iostream/inc"
    "../${COPIED_SDK_PATH}/util/third_party/printf"
    "../${COPIED_SDK_PATH}/util/third_party/printf/inc"
    "../${COPIED_SDK_PATH}/platform/common/toolchain/inc"
    "../${COPIED_SDK_PATH}/platform/service/system/inc"
)

target_compile_definitions(slc_XDRONE PUBLIC
    "DEBUG_EFM=1"
    "EFR32FG28A120F1024GM48=1"
    "SL_COMPONENT_CATALOG_PRESENT=1"
)

target_link_libraries(slc_XDRONE PUBLIC
    "-Wl,--start-group"
    "gcc"
    "c"
    "m"
    "nosys"
    "-Wl,--end-group"
)
target_compile_options(slc_XDRONE PUBLIC
    $<$<COMPILE_LANGUAGE:C>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:C>:-mthumb>
    $<$<COMPILE_LANGUAGE:C>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:C>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:C>:-Wall>
    $<$<COMPILE_LANGUAGE:C>:-Wextra>
    $<$<COMPILE_LANGUAGE:C>:-Os>
    $<$<COMPILE_LANGUAGE:C>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:C>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:C>:-fomit-frame-pointer>
    "$<$<COMPILE_LANGUAGE:C>:SHELL:-imacros sl_gcc_preinclude.h>"
    $<$<COMPILE_LANGUAGE:C>:-mcmse>
    $<$<COMPILE_LANGUAGE:C>:-fno-builtin-printf>
    $<$<COMPILE_LANGUAGE:C>:-fno-builtin-sprintf>
    $<$<COMPILE_LANGUAGE:C>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:C>:-g>
    $<$<COMPILE_LANGUAGE:CXX>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:CXX>:-mthumb>
    $<$<COMPILE_LANGUAGE:CXX>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:CXX>:-mfloat-abi=hard>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-rtti>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-exceptions>
    $<$<COMPILE_LANGUAGE:CXX>:-Wall>
    $<$<COMPILE_LANGUAGE:CXX>:-Wextra>
    $<$<COMPILE_LANGUAGE:CXX>:-Os>
    $<$<COMPILE_LANGUAGE:CXX>:-fdata-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-ffunction-sections>
    $<$<COMPILE_LANGUAGE:CXX>:-fomit-frame-pointer>
    "$<$<COMPILE_LANGUAGE:CXX>:SHELL:-imacros sl_gcc_preinclude.h>"
    $<$<COMPILE_LANGUAGE:CXX>:-mcmse>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-builtin-printf>
    $<$<COMPILE_LANGUAGE:CXX>:-fno-builtin-sprintf>
    $<$<COMPILE_LANGUAGE:CXX>:--specs=nano.specs>
    $<$<COMPILE_LANGUAGE:CXX>:-g>
    $<$<COMPILE_LANGUAGE:ASM>:-mcpu=cortex-m33>
    $<$<COMPILE_LANGUAGE:ASM>:-mthumb>
    $<$<COMPILE_LANGUAGE:ASM>:-mfpu=fpv5-sp-d16>
    $<$<COMPILE_LANGUAGE:ASM>:-mfloat-abi=hard>
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-imacros sl_gcc_preinclude.h>"
    "$<$<COMPILE_LANGUAGE:ASM>:SHELL:-x assembler-with-cpp>"
)

set(post_build_command )
set_property(TARGET slc_XDRONE PROPERTY C_STANDARD 99)
set_property(TARGET slc_XDRONE PROPERTY CXX_STANDARD 11)
set_property(TARGET slc_XDRONE PROPERTY CXX_EXTENSIONS OFF)

target_link_options(slc_XDRONE INTERFACE
    -mcpu=cortex-m33
    -mthumb
    -mfpu=fpv5-sp-d16
    -mfloat-abi=hard
    -T${CMAKE_CURRENT_LIST_DIR}/../autogen/linkerfile.ld
    --specs=nano.specs
    "SHELL:-Xlinker -Map=$<TARGET_FILE_DIR:XDRONE>/XDRONE.map"
    -Wl,--gc-sections
    -Wl,--no-warn-rwx-segments
)

# BEGIN_SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA
