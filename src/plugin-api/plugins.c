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

#include "plugins.h"

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>


ExEd_Plugin load_plugin(const char *path)
{
    ExEd_Plugin plugin;
    plugin.path = path;
    plugin.name = "";
    plugin.description = "";
    plugin.author = "";
    plugin.init = NULL;
    plugin.exit = NULL;

    /* Attempt dynamic loading of the plugin */
    void *handle = dlopen(path, RTLD_LAZY | RTLD_LOCAL);

    if (NULL == handle) {
        fprintf(stderr, "Error: could not open dynamic library \"%s\"\n", path);
        return plugin;
    }

    /* Load main plugin functions */
    plugin.init = dlsym(handle, "plugin_init");

    if (NULL == plugin.init) {
        fprintf(stderr, "Error: could not find \"%s\" for \"%s\"\n", "plugin_init", path);
        return plugin;
    }

    plugin.exit = dlsym(handle, "plugin_exit");

    if (NULL == plugin.exit) {
        fprintf(stderr, "Error: could not find \"%s\" for \"%s\"\n", "plugin_exit", path);
        return plugin;
    }

    /* Initialize the plugin */
    if (plugin.init(&plugin)) {
        fprintf(stderr, "Error: failed to initialized plugin \"%s\"\n", path);
        return plugin;
    }

    return plugin;
}