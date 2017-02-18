# Fundamentals of C and Embedded using Mob Programming

This repository provides the starting point for an interactive workshop
[introduced at PillarCon 2017](https://schmonz.com/talk/2017-pillarcon/).
Abstract:

> Interested in high-profile embedded projects? Pair Programming not
> Extreme enough for you? Come test-drive a Raspberry Pi from a Mac, using
> [Mob Programming](https://agilein3minut.es/32)
> to help us learn fast.
> 
> Don't know what to try next? Take the keyboard. Got an idea? Step away
> and talk someone else through it. After only two hours, we'll have
> written tests and code in C, mocked hardware-specific calls,
> cross-compiled from our development host, and deployed working software
> to the target.

You're welcome to use these materials to run your own workshop.


## Learning Outcomes

- What "host" and "target" mean
- How to use a cross compiler to build for our target
- How to not use it very often
- How to test-drive on our fast, comfortable host system
- How to know when it's worth testing on our target system


## What Is Cool

- This Raspberry Pi has an onboard LED. It can turn on and off.


## What We'll Do

- We're going to test-drive that together. In C. On this Mac.


## Why We'll Do It

- We _could_ SSH into the Raspberry Pi and develop directly on it. It's
  a regular computer.
- By pretending it's expensive and time-consuming to deploy and test,
  we're going to learn the basics of development for embedded systems.


## How We'll Do It

- Take turns sitting at the keyboard.
- We'll talk you through what to do.
- If you have an idea, step away from the keyboard and tell it to us.
- We'll rotate every 5 minutes or less.


## What I've Already Done

- Raspberry Pi with a working LED, running NetBSD 7
- Mac-hosted RPi cross compiler and toolchain (gcc, built from NetBSD 7 source checkout)
- Host compiler and toolchain (clang from Xcode)
- Makefile to build for Mac or Raspberry Pi
- A place to put tests
- Vim with a key mapped to run tests
- A place to put fake system calls
- Googling for how to toggle the LED


## What the Docs Say

- Hardware: onboard LED is controlled by GPIO pin 16
- Enable access to the GPIO device: `gpio=YES` in `/etc/rc.conf` (and reboot)
- Enable writing to pin 16: `gpio0 16 set out act_led` in
  `/etc/gpio.conf` (and run `gpioctl` with same args)


## What I Think We'll Need To Do

- open the system GPIO device read-write
- call the toggle `ioctl()` on that pin
- close the GPIO device


## Test-Driving It

Here's one possible path through solving the problem.

1. Inspect our starting point for understanding
2. `git co -b pillarcon2017`
3. Run `make` and do just enough to get to green
4. Add an acceptance test for our desired public interface, get to green
5. For manual testing: have `do_toggle` call the interface and tell us it did
6. Add a unit test that it calls `open()`
7. Test that it opens for write (2nd arg is `O_WRONLY`)
    - And now really call `open()` (get it with `#include "syscalls.h"`)
8. Test that it opens the right device (1st arg is `/dev/gpio0`)
9. Run `make TARGET_SYSTEM=rpi` and create just enough `rpi_syscalls.h`
   (`#include <fcntl.h>`) to get to green
10. Deployed! Does it run on the Pi? probably call the real `open()`? Light anything up yet?
11. Test that if `open()` fails, we don't call `ioctl()` or `close()`
    - So we need those fakes now too
12. Test that we call `ioctl()` with 2nd arg `GPIOTOGGLE`
13. Test that we call `ioctl()` with 3rd arg (`struct gpio_req`) specifying pin 16
14. Test that if `ioctl()` fails, we do still call `close()`
    1. So now really call both
15. Let's pretend deploying is expensive, and test our tests a little first
16. Test that if the first `led_toggle()` has a failure and the second
    `led_toggle()` succeeds, we call all three system calls the right
    number of times
17. Does it seem like it's probably going to work?
18. Let's deploy and find out!


## What You Can Do Next

- Raspberry Pis are cheap
- NetBSD is a free, open source OS that wants to give you a cross compiler
- Keep playing and having fun!
