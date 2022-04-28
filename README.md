# Welcome to the GIANT hackathon!

Over the next week, you'll be implementing a very simple "model" that
computes aerosol optical properties from state information. This model will be
run by a driver program that initializes it, computes the optical properties,
interpolates those properties to its own wavelength grid, and outputs results
that can be plotted.

**Sounds simple, right? So what's the big deal?**

In this hackathon, we're trying to demonstrate how an atmospheric "host model"
written in one programming language (Fortran, C, or C++) can communicate with
an "aerosol model" written in another language (Fortran, C, or C++). If we
succeed, then existing and future aerosol models can be made accessible to
atmosphere models, as long as both are written in one of the supported
languages.

In other words, this hackathon is about host-aerosol model language
interoperability. It's not very "sciency", but it's something we need to do
before we do anything more complicated.

We appreciate your willingness to work with us to address this fundamental
iѕsue before we move on to the more interest questions in aerosol science.
Thanks for participating!

## What do I need?

In principle, this interface allows an existing aerosol model to be "plugged in"
to the interface to provide the aerosol optical properties we talked about in
the introductory presentation. However, you don't have to bring in the entire
model--you only really need the logic that computes aerosol optical properties,
and the things that it requires.

Aside from that, you need [Git](https://git-scm.com) and a development
environment (with [CMake](https://www.cmake.org),
[Make](https://www.gnu.org/software/make/), and compilers for Fortran, C, and
C++) for building and running the driver with your interface.

One easy way to set things up is to use
[Docker Desktop](https://www.docker.com/products/docker-desktop/) to build and
run the driver inside a containerized Linux environment with all the right
tools. We explain how you can do this below.

In any case, if you have any difficulties installing git and Docker Desktop,
we'll have a Slack channel and a breakout room set up during the event where
we can help you either get these installed, or get you set up to develop in
another way.

## How do I provide or implement my own aerosol model?

Follow these steps to put together your model.

1. Select a programming language for your model's implementation, and copy the
   provided model template code into place within the `my_model/` folder:

   ```
   cp my_model/template/{language}/* my_model/
   ```

   where `{language}` is one of `fortran` (Fortran) , `c` (C), or `cpp` (C++).

2. Customize your model, renaming and modifying the files in the `my_model`
   directory as needed. If you are adapting an existing model to this interface,
   copy the source files you need into the `my_model` directory.

3. Edit `my_model/CMakeLists.txt` according to their naming scheme following
   the instructions in that file. Add any source files that you've imported
   from elsewhere to the list of source files in the `create_aerosol_model`
   command.

4. To build your model and run the driver tests, type
   ```
   docker build -t aerosol-test .
   ```

5. Any files you put in the container's `/output/` directory are made available
   in `aerosol-workshop-driver/output/` outside the container.

## Help!!!

This hackathon is an experiment, so everyone is bound to be confused at some
point. Make sure to join our [GIANT Slack workspace](https://join.slack.com/t/giant-lj47066/shared_invite/zt-17y9k5mxy-vcXVYzNqXmcg5MdwRLK7Wg),
where the organizers and other participants can help you with the issues you
encounter and answer questions about concepts, terminology, and the tools.

