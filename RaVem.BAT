SET PATH=C:\Keil\ARM\ARMCC\bin\;C:\CodeSourcery\Sourcery_G++_Lite\bin;C:\Windows\system32;C:\Windows;C:\Windows\System32\Wbem;C:\Windows\System32\WindowsPowerShell\v1.0\;C:\Program Files (x86)\Microchip\MPLAB C32 Suite\bin;c:\Program Files (x86)\Microsoft SQL Server\100\Tools\Binn\;c:\Program Files\Microsoft SQL Server\100\Tools\Binn\;c:\Program Files\Microsoft SQL Server\100\DTS\Binn\;C:\Program Files\Java\jre6\bin;c:\cygwin\bin\;c:\altera\12.1\modelsim_ase\win32aloem
SET CPU_TYPE=LPC812M101
SET CPU_VENDOR=NXP (founded by Philips)
SET UV2_TARGET=RaVem
SET CPU_CLOCK=0x00B71B00
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_gpio.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_mrt.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_nmi.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_uart.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\main.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\device_depend.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\ravem.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\pool.__i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\system_lpc8xx.__i"
"C:\Keil\ARM\ARMCC\bin\ArmAsm" --Via ".\obj\startup_lpc8xx._ia"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\obj\ravem.lnp"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_gpio._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_mrt._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\lpc8xx_uart._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\main._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\device_depend._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\ravem._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\pool._2i"
"C:\Keil\ARM\ARMCC\bin\ArmCC" --Via ".\obj\system_lpc8xx._2i"
"C:\Keil\ARM\ARMCC\bin\ArmLink" --Via ".\obj\ravem.l2p"
C:\Keil\ARM\ARMCC\bin\fromelf.exe ".\obj\ravem.axf" --i32combined --output ".\obj\ravem.hex"
