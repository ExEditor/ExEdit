# User Interface

The user interface is not a part of the editor.

Vim bindings, Emacs bindings... I don't care. None of these things have anything to do with the actual functionality of the editor. The core should support anything, be it Vim, Emacs, or something special (perhaps a stenographic editor would be delightful).

This is achieved using a client / server architecture.

# Client / Server Architecture

At its core the editor is supposed to be extensible, and is pretty much just a library for handling text editor like functions, which can be modified using the plugin and scripting APIs.

The actual editor is meant to be run as a server. This server loads configuration files, plugins, scripts, and whatever you want. The server allows you to quickly connect to a session which has already been started, and will allow you to share resources between clients. This should make for a better workflow.

Clients exist to basically be displays for the server. They display the data on the server. Buffers, text, whatever. The clients can have any interface. They can have completely different philosophies for key bindings, be graphical or textual... Whatever. They just have to talk to the server over the specified protocol.

## Default Client

To start with we are going to write a simple curses based client.

## Protocol

To be determined.

- Send commands to the server
- Read / display buffers from the server

### Markup

There needs to be some markup language which tells the client where to draw things.

# Plugin / Scripting Design

Plugins should use the dynamic loader. It should be easy enough to modify just about any aspect of the editor with a native code plugin.

The plugin API will be used to implement the scripting APIs. Essentially the scripting APIs merely expose the native plugin API to the scripting language.

## Package Management

Must be easy to install and manage plugins / scripts!

## Desired Languages for scripting / plugins

Some languages we might like to start with.

- Haskell
- Python
- Lua
- Emacs Lisp

## Emacs Lisp

It should actually be possible to implement a shim between our plugin / scripting API and emacs lisp... Which would mean we could have a large number of decent plugins and scripts instantly.

# Modes / extensions

Lazy loading to speed up start times. We do not want to initialize a plugin / script until it's needed.

## How Modes Work

Each position in a buffer can have a different mode if desired.

Metamode which assigns modes to positions in the buffer.

# Ropes

The editor will use ropes to handle the current section of text that will be edited. Ideally the entire file will be loaded into memory at any given time... This should be fine because a modern OS should just swap.

# Undo Trees

Undo and redo should probably allow for some kind of tree traversal, so that we can always easily revert to a given change.
