/*
  The MIT License (MIT)

  Copyright (c) 2015 Calvin Beck

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.

 */

#ifndef PLUGINS_H
#define PLUGINS_H

#include <stdlib.h>


/* Structure for commands in a plugin */
typedef struct ExEd_Command {
    const char *command;  /* Name of the command */
    const char *description;  /* Description of the command */
    int (*callback)(void *data);
} ExEd_Command;


/* Structure for plugins */
typedef struct ExEd_Plugin {
    const char *path; /* Path for the dynamic library which has been loaded */
    char *name; /* Name of the plugin */
    char *description; /* Description of the plugin */
    char *author; /* Author of the plugin */
    char *author_email; /* Contact information for author */

    /* Entry points */
    int (*init)(struct ExEd_Plugin*);
    int (*exit)(struct ExEd_Plugin*);

    /* Plugin commands */
    ExEd_Command *commands;
    size_t num_commands;
} ExEd_Plugin;


/* Load plugins dynamically.

   init and exit will be NULL on failures.
 */
ExEd_Plugin load_plugin(const char *path);


/* Register a command in a plugin.

   Returns 0 on success, and -1 on failure.
 */
int plugin_register_command(ExEd_Plugin *plugin, const char *command, const char *description, int (*callback)(void *data));

#endif
