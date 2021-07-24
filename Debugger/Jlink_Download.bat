@echo off
set dir_path=F:\\Free\\STM32\\STM32_Demo_VSCode\\STM32F10X_Demo_VSCode
set jink_cfg=F:\\Free\\STM32\\STM32_Demo_VSCode\\STM32F10X_Demo_VSCode\\Debugger\\jlink_swd.cfg
set image=F:\\Free\\STM32\\STM32_Demo_VSCode\\STM32F10X_Demo_VSCode\\Obj\\STM32F10X.hex
set stm32_cfg=F:\\Free\\STM32\\STM32_Demo_VSCode\\STM32F10X_Demo_VSCode\\Debugger\\stm32f1x.cfg

openocd -s %dir_path% -f %jink_cfg% -f %stm32_cfg% -c ^
"init;halt;reset halt;flash write_image erase %image%;reset;shutdown;"
@echo on