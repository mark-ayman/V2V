@echo off
set /p Layer_Name=Please Enter Layer Name :
set /p Driver_Name=Please Enter Driver Name :
md %Driver_Name%
cd %Driver_Name%
type nul > %Driver_Name%_Interface.h
type nul > %Driver_Name%_Private.h
type nul > %Driver_Name%_Config.h
type nul > %Driver_Name%_Prog.c
(
echo #ifndef %Layer_Name%_%Driver_Name%_%Driver_Name%_INTERFACE_H_
echo #define %Layer_Name%_%Driver_Name%_%Driver_Name%_INTERFACE_H_
echo
echo
echo #endif

)> %Driver_Name%_Interface.h

(
echo #ifndef %Layer_Name%_%Driver_Name%_%Driver_Name%_PRIVATE_H_
echo #define %Layer_Name%_%Driver_Name%_%Driver_Name%_PRIVATE_H_
echo
echo
echo #endif

) > %Driver_Name%_Private.h

(
echo #ifndef %Layer_Name%_%Driver_Name%_%Driver_Name%_CONFIG_H_
echo #define %Layer_Name%_%Driver_Name%_%Driver_Name%_CONFIG_H_
echo
echo
echo #endif

) > %Driver_Name%_Config.h
