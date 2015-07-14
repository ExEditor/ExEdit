# Plugin API

The following functions must be provided by any plugin loaded by ExEd.

## Initializing the Plugin
    int plugin_init(ExEd_Plugin *plugin)

## Cleaning up
	int plugin_exit(ExEd_Plugin *plugin)

## Registering Commands and Modes

### Modes

A mode is something that we feed information about a buffer through. Modes can be composed in various ways, but generally speaking the input of a mode has to take information of the same type as the mode before it outputs. For example, certain modes might work on abstract syntax trees, instead of regular text. In this case the mode will need to be composed with another mode which parses a buffer and spits out an AST.

A mode will often be associated with a certain type of file (usually by file extensions, but something fancier like libmagic may be used).

### Commands

Every action in ExEd should be grouped with a named command. The name of this command should be as descriptive as possible, and conceivably might be entered manually by a user (either to execute the command, or look up information about the command).

    plugin_register_command(ExEd_Plugin *plugin)

Each registered command will be in the scope of the plugin. When a command is called globally it will search for all of the commands in the plugins that are currently loaded that match, and probably select the command from the first loaded plugin by default.

### Keybindings?

Each plugin may expose various keybindings, which are used to execute commands. We want ExEd to be as extensible as possible, so multiple default keybindings may be available for any given plugin. For instance you might have a set of keybindings which are designed to work in an environment with Emacs-style keybindings, and you might have a set of keybindings which work for a more Vim-like environment. It should also be possible to specify your own set of keybindings.
