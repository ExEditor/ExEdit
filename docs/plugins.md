# Plugin API

ExEd may be extended through the use of plugins. These plugins are dynamic libraries of native code, which can be loaded in at runtime by ExEd. The plugin API provides a framework for the development and use of these plugins. In order to write a plugin for ExEd you must provide the necessary functions for linking.

## Initializing the Plugin

When ExEd loads a plugin it initializes it by calling

```c
int plugin_init(ExEd_Plugin *plugin)
```

This function must be provided by each plugin, and can be used to set up anything that the plugin needs.

## Cleaning up

When a plugin is unloaded from ExEd the following function, which must be provided by each plugin is called

```c
int plugin_exit(ExEd_Plugin *plugin)
```

This function may be used to perform any necessary cleanup, such as freeing any memory or file descriptors allocated by the plugin.

## Registering Commands and Modes

### Modes

A mode is something that we feed information about a buffer through. Modes can be composed in various ways, but generally speaking the input of a mode has to take information of the same type that the mode before it outputs. For example, certain modes might work on abstract syntax trees, instead of regular text. In this case the mode will need to be composed with another mode which parses a buffer and spits out an AST.

A mode will often be associated with a certain type of file (usually by file extensions, but something fancier like libmagic may be used).

### Commands

Every action in ExEd should be grouped with a named command. The name of this command should be as descriptive as possible, and conceivably might be entered manually by a user (either to execute the command, or look up information about the command).

```c
plugin_register_command(ExEd_Plugin *plugin, const char *command, const char *description, int (callback*)(void *data))
```

Each registered command will be in the scope of the plugin. When a command is called globally it will search for all of the commands in the plugins that are currently loaded that match, and probably select the command from the first loaded plugin by default.

### Keybindings?

Each plugin may expose various keybindings, which are used to execute commands. We want ExEd to be as extensible as possible, so multiple default keybindings may be available for any given plugin. For instance you might have a set of keybindings which are designed to work in an environment with Emacs-style keybindings, and you might have a set of keybindings which work for a more Vim-like environment. It should also be possible to specify your own set of keybindings.
