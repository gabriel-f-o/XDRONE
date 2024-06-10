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
