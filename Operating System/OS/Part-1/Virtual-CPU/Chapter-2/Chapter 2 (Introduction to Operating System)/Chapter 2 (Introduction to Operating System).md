- [[What happens when a program runs?]]
- This is the basics of the [[Von Neumann Computer Architecture]]
- The body of the computer responsible for making it easy to run instruction, share memory between programs, interact with devices and many other things is called the **Operating System**.

- One of the main responsibility of OS is [[Virtualization]]. This is one of the fundamental problem that needs to be dealt with creating an operating system.

## Why is OS called a virtual machine?
- The process that the OS uses to do all the stuffs that we mentioned before is called virtualization. In this process the OS takes a physical resource such as processor, memory, disks etc and then transforms the physical resource into its own easy-to-use virtual form. Because the OS transforms a physical resource into its virtual form, we call the OS an virtual machine.

## What does it mean that the OS provides a standard library? 
- For a user to access the features of the virtual machine such as memory access, file creation, running a program etc the OS exports various system calls or API's for the user to interact with. Since the OS provides these interface to access memory and other stuff we say that the OS provides a **standard library**.

## Why is the OS called a resource manager?
- Because of virtualization we can run various process at the same time (thus sharing process), and make those processes concurrently access their own instructions and data (thus sharing memory) and also make those processes access devices (thus sharing disks), the OS is called a **resource manager**. The resources of computer includes: processor, memory, disks much more.