The kernel is loaded into memory and begins to execute

Boot time is a period of special vulnerability
Errors in configuration, missing or unreliable equipment, and damaged filesystems can all prevent a computer from coming up

administrators first task is to configure the boot process on a new system when adding new hardware

when a computer is first turned on, it executes the boot code stored in ROM
that code attempts to figure out how to load and start the kernel
the kernel [[probes]] the hardware and spawns an init process



### recovery boot to shell
- administrators need recovery tools to manage disk crashes or server misconfiguration
- so instead of starting the entire system at the fullest, UNIX systems can boot just enough to run a shell on the system console
- this is known as [[single-user mode]]


### Steps in the boot process
- load the bootloader from the MBR (master boot record)
- loading and initialization of the kernel
- device detection and configuration
- creation of the kernel process
- administration intervention (single-user mode)
- execution of startup scripts
during these steps the administrator have limited control on what they can do, what they can actually do:
- change the bootstrap configuration file (change the startup script)
- change arguments the boot loader passes to the kernel