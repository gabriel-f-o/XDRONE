set(SDK_PATH "C:/Users/Gabriel/SimplicityStudio/SDKs/gecko_sdk")
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
    "../${COPIED_SDK_PATH}/platform/emlib/src/em_timer.c"
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

# BEGIN_SIMPLICITY_STUDIO_METADATA=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=END_SIMPLICITY_STUDIO_METADATA
