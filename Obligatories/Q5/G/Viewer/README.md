# GLarena: a plugin-based framework for teaching and assessing Computer Graphics

This repository contains the complete code to build GLarena, a program
designed to teach modern OpenGL programming. More information can be
found in "GL-Socket: A CG plugin-based framework
for teaching and assessment", *EG-2018 Education Track*

We are releasing this code under the [GNU General Public
License](https://www.gnu.org/licenses/#GPL),
version 3 or, at your option, any later version.

The code targets OpenGL~3.3 because that is the version available in
the labs we teach this course in, but can be easily retargetd to
another version.  Currently it only supports vertex, geometry and
fragment shaders for the same reason.

We use Qt for the interface, and also as support for our plugins. This
version requires Qt>=5.4.

To build the software clone this repository
```sh
git clone https://gitrepos.virvig.eu/docencia/newviewer
```
Change into the new directory
```sh
cd newviewer
```
and build:
```
qmake; make
```
Make shure that, in case you have more than one version of Qt installed,
you use the `qmake` command from a version newer than or equal to 5.4.

There are three scripts provided to start the application:
* `GLarena` starts the application with three default plugins loaded: 
  * drawvbong: a basic draw-plugin (see paper for description of
  plugin cathegories) that renders the current scene. It
  is meant for students to use as a starting point for exercises
  requiring the construction of more elaborate draw-plugins.
  * renderdefault: a basic render-plugin.
  * navigatedefault: a navigation plugin, implementing basic camera
  manipulations (interactive rotation, zoom and pan).
* `GLarenaSL` starts the application with an additional plugin loaded:
shaderloader. This plugin is meant to be a tool for teaching shader
coding, and supports the interactive definition and testing of
shaders, as well as a rudimentary self-assessment of the results by
comparison of the resulting render with that produced by the
instructor's code for the same exercise.
* `GLarenaPL` starts the application with an additional plugin loaded:
  pluginLoadr. This plugin streamlines the task of adding a new plugin
  to the source tree, generating the necessary support files and
  directory i the right place, opening in an editor the two main
  source files, and triggering an automatic recompile and reload each
  time a new edit is saved. This makes it easier to concentrate on the
  task at hand, since the venial tasks needed for the integration are
  handled by the plugin in a reasonable and automatic way. However, the plugin
  does not add the new plugin to `plugins/plugins.pro`, which can be
  optionally added when the task is complete.

These two instructional plugins (shaderLoader and pluginLoader) are
mutually incompatible at this point.

You may use Doxygen to generate documentation for the code, although
this documentation is not in-depth as of yet.


