# Kernel Modules

Kernel modules are typically used to add functionality to:
- Device Drivers
- File Systems
- Networking Protocols
- Security Features

These are stored at `.ko` (kernel object) files and are written in the C programming language.

Kernel Module Management is performed through the following utilities:
- `insmod`: Insert a module into the kernel
- `rmmod`: Remove a module
- `modprobe`: Load a module and its dependencies
- `lsmod`: List currently loaded modules
- `modinfo`: Display metadata about modules
- `dmesg`: Kernel debugging messages

The dependencies between modules are tracked in:
- `/lib/modules/<kernel_version>/modules.dep` and MODPROBE is able to resolve these.

The following are the types of messages you can embed in your modules to create logs:
- KERN_EMERG: Used for emergency messages, usually those that precede a crash.
- KERN_ALERT: A situation requiring immediate action.
- KERN_CRIT: Critical conditions, often related to serious hardware or software failures.
- KERN_ERR: Used to report error conditions; device drivers often use KERN_ERR to report hardware difficulties.
- KERN_WARNING: Warnings about problematic situations that do not, in themselves, create serious problems with the system.
- KERN_NOTICE: Situations that are normal, but still worthy of note. A number of security-related conditions are reported at this level.
- KERN_INFO: Informational messages. Many drivers print information about the hardware they find at startup time at this level.
- KERN_DEBUG: Used for debugging messages.

These are listed in decreasing order of severity.

---

## Creating a Basic Kernel Module


In order to build Kernel modules on a system you have to install the required headers:
```bash
apt-get install build-essential linux-headers-$(uname -r)
```

When creating a Kernel module these will require at least the minimum two functions; "start" (initialization) called `init_module()` and "end" (cleanup) function called `cleanup_module()`.

With Kernel `2.3.13` you're now able to name these functions whatever you like, which is now preferred.

The `printk()` function will print to `/var/log/kern.log` instead of the console. 

Creating the source file in C programming language:
```c
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL")
MODULE_AUTHOR("You")
MODULE_DESCRIPTION("Hello World Kernel Module")

static int __init hello_init(void) {
	printk(KERN_INFO "Hello\n");
	return 0;
}

static void __exit hello_exit(void) {
	printk(KERN_INFO "Goodbye.");
}

module_init(hello_init)
module_exit(hello_exit)
```

Create a `Makefile` in the same directory:
```Makefile
obj-m += hello.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
```

The first statement defines a kernel object is being built with `hello.o`

The second statement dynamically interacts with the  system for the current running kernel.

Then third cleans all temporary files from the system generated during the build process.

Generate a kernel module `.ko` file:
```bash
make
```

Insert the module:
```bash
sudo insmod hello.ko
```

Check the kernel logs to verify the addition:
```bash
dmesg | tail
```

---




